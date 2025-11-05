// Patrick Sacchet
// This file handles startup functionality and command handling 

#include <stdio.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>


// Callout and establish connection to C2
int callout(uint16_t port, int* client_fd)
{
    int status = 1, new;
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    *client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0)
    {
        printf("callout: Failed to create socket\n");
        status = 0;
        goto cleanup;
    }

    status = inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
    if (status <= 0)
    {
        printf("callout: Failed inet_pton\n");
        goto cleanup;
    }

    status = connect(*client_fd, (struct sockaddr*)&address, sizeof(address));
    if (status < 0)
    {
        printf("callout: Failed connect\n");
        goto cleanup;
    }

    // If our return was a 0, make sure we set it to 'success' prior to returning 
    if (status == 0)
    {
        status = 1;
    }


cleanup:
    return status;
}


// Main entry point for this program; reach out to C2 and establish connection
    // Will also parse reponses from C2 and call into appropiate funcitonality + send collected data 
int main() 
{
    uint16_t port = 1337;
    int client_fd = 0;

    printf("Establishing connection to C2...\n");

    if (!callout(port, &client_fd))
    {
        printf("Failed our callout to C2\n");
        return 0;
    }

    printf("Successfully connected to C2\n");

    close(client_fd);


    return 0;
}