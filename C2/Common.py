# Patrick Sacchet
# This file defines common data types shared between the implant and C2

import ctypes
from enum import IntEnum


# Define our options for the user to choose from 
class Commands(IntEnum):
    disconnect = 0
    getfile = 1
    putfile = 2
    dirlist = 3