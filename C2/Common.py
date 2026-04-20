# Patrick Sacchet
# This file defines common data types shared between the implant and C2

import ctypes
from enum import IntEnum


##################################
#           Commands             #
##################################

# Define our options for the user to choose from 
class Commands(IntEnum):
    disconnect = 0
    shutdown = 1
    getfile = 2
    putfile = 3
    dirlist = 4
    survey = 5

class DisconnectCommand(ctypes.Structure):
    _fields_ = [
        ("sleep", ctypes.c_uint32),
        ("callbackport", ctypes.c_int32)
    ]

# Do we need a class for shutdown if there's no details to send the implant...

class GetFileCommand(ctypes.Structure):
    _fields_ = [
        ("filepath", ctypes.c_char * 1024) # use an actual array...
    ]

class PutFileCommand(ctypes.Structure):
    _fields_ = [
        ("filepath", ctypes.c_char_p),
        ("filebytes", ctypes.c_char_p)
    ]

class DirListCommand(ctypes.Structure):
    _fields_ = [
        ("dirpath", ctypes.c_char_p)
    ]

# Do we need a class for survey if there's no details to send the implant...

class CommandDetails(ctypes.Union):
    _fields_ = [
        ("disconnectcommand", DisconnectCommand),
        ("getfilecommand", GetFileCommand),
        ("putfilecommand", PutFileCommand),
        ("dirlistcommand", DirListCommand)
    ]

# Mimics our Command struct in C2/Common.h
class Command(ctypes.Structure):
    _fields_ = [
        ("command", ctypes.c_uint8),
        ("commanddetails", CommandDetails)
    ]

##################################
#           Responses            #
##################################

# No reponse for disconnect needed

# No response for shutdown needed

class GetFileResponse(ctypes.Structure):
    _fields_ = [
        ("filesize", ctypes.c_uint64),
        ("filebytes", ctypes.c_char * 1024)
    ]

class PutFileResponse(ctypes.Structure):
    _fields_ = [
        ("byteswritten", ctypes.c_uint64)
    ]

class DirListResponse(ctypes.Structure):
    _fields_ = [
        ("dirs", ctypes.c_char_p)
    ]

class SurveyResponse(ctypes.Structure):
    _fields_ = [
        ("osname", ctypes.c_char * 50), 
        ("osrelease", ctypes.c_char * 50), 
        ("osversion", ctypes.c_char * 50),
        ("arch", ctypes.c_char * 50),
        ("mac", ctypes.c_char * 50)
    ]

class ResponseDetails(ctypes.Union):
    _fields_ = [
        ("getfileresponse", GetFileResponse),
        ("putfileresponse", PutFileResponse),
        ("dirlistresponse", DirListResponse),
        ("surveyresponse", SurveyResponse)
    ]

# Mimics our Response struct in C2/Common.h
class Response(ctypes.Structure):
    _fields_ = [
        ("response", ctypes.c_uint8),
        ("responsedetails", ResponseDetails)
    ]