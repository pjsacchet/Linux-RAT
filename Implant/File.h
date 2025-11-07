#include <stdio.h>
#include <stdint.h>

#include "Common.h"


int handleGetFile(char* filepath, uint64_t* file_size, char* file_bytes);

int sendFileContents(int* client_fd, uint64_t file_size, char* file_bytes);
