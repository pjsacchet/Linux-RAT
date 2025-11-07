#include <stdio.h>
#include <stdint.h>


int handleGetFile(char* filepath, uint64_t* file_size, char* file_bytes);

int sendFileContents(int* client_fd, uint64_t file_size, char* file_bytes);
