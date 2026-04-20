# Patrick Sacchet
# File will handle sending a shutdown command to target 

import socket
import Common

def handleShutdown(sock : socket.socket) -> bool:

    # Print the user to ensure they REALLY want to shutdown the target
    choice = (int(input('Are you SURE you want to shutdown the target?\n' \
                        '\t 1) Yes\n' \
                        '\t 2) No\n')))
    
    match (choice):
        case 1:
            print("Sending shutdown command...")
            shutdown_command = Common.Command(command=Common.Commands.shutdown) # don't need any details here
            bytes_sent = sock.send(bytes(shutdown_command))

            print(f"Sent {bytes_sent} bytes to implant")

        case 2:
            print("Canceling shutdown....")
            return False

        case _:
            print("Not a valid choice; canceling shutdown...")
            return False

    return True