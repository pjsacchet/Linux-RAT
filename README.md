# Linux-RAT
Rudimentary Linux Remote Access Tool &amp; C2 Server

## Building
cd Implant
make

(output in /Out/linuxRAT)

## Use
Currently, the user will need to start the C2 via python on their host machine. It will immedaitely ask for which port the user has configured the implant to reach out on. Following connection, the user will be prompted with options:

```
# python3 RAT.py
Please enter the port number on which you would like to listen for the RAT on > 1337
Waiting for implant callout...
Connection established to 172.17.0.2 on port 33380
Please choose from the following options:
         0) disconnect
         1) getfile
         2) putfile
         3) dirlist
```

### disconnect
With disconnect, the user can configure the C2 to temporarily disconnect from the implant, but at the same time, can tell the implant to connect back after some set amount of time on a different port so as to reduce suspician by network admins. From the C2 output will look as follows:

```
> 0
Number of seconds for implant to sleep before callback (0 to kill implant) > 5
Port number you would like the implant to call back in on > 1300
Sent 1032 bytes to implant
Closing connection to implant...
Reopening port 1300 for implant to call back in on...
Waiting for implant callout...
Connection established to 172.17.0.2 on port 60392
Please choose from the following options:
         0) disconnect
         1) getfile
         2) putfile
         3) dirlist
```

From the implant, output will look as follows:

```
# ./linuxRAT
Establishing connection to C2...
Successfully connected to C2; starting implant loop...
Waiting for C2 command...

Read 1032 bytes from socket
Received disconnect command!
Putting implant to sleep for 5 seconds; callback port is on 1300
Sleeping for 5 seconds...
Attempting to reconnect to C2...
Re-established connection to C2!
Waiting for C2 command...
```

The user can also instruct the implant to exit by setting the sleep to 0:

```
> 0
Number of seconds for implant to sleep before callback (0 to kill implant) > 0
Sent 1032 bytes to implant
Closing connection to implant...
```

From the stager output will look like:

```
Read 1032 bytes from socket
Received disconnect command!
Exiting implant...
Disconnected from C2
```

### getfile
With getfile, the user can specify the target location of the desired file and the desired location to write it to:

```
> 1
File location on target > /tmp/test.txt
File location to write locally > test.txt
Sent 1032 bytes to implant
Received file 12 bytes large
```

And the output from out implant:

```
# ./linuxRAT
Establishing connection to C2...
Successfully connected to C2; starting implant loop...
Waiting for C2 command...

Read 1032 bytes from socket
Received getfile command!
Opening /tmp/test.txt for reading...
Sending 12 bytes back to C2...
```

