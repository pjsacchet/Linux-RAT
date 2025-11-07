#include <stdio.h>
#include <stdint.h>
#include <unistd.h>


int handleDisconnectExit(int* client_fd);

int handleDisconnectSleep(int* client_fd, uint64_t sleep, uint64_t port);