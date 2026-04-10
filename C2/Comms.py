# Patrick Sacchet
# This file will implement functionality for imnplementing our comms blending
    # Will be done via HTTP blending

import socket

import Common

def handleHTTPPostPacket(sock : socket.socket, command : Common.Command) -> bool:
    packet = ""

    # Need to create proper header for POST message

    # Convert our command into bytes and maybe encrypt it

    # Send it

    return True


def handleHTTPGetPacket(sock : socket.socket, command : Common.Command) -> bool:
    packet = ""

    # Create proper header for GET message

    # Convert our command into bytes and maybe encrypt it

    # Send it


    return True


