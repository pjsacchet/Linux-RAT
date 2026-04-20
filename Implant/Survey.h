#ifndef SURVEY_HEADER_H
#define SURVEY_HEADER_H

#include <sys/utsname.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>    
#include <sys/socket.h>
#include <net/if.h>

#include "Common.h"

int handleSurvey(int* client_fd);

#endif