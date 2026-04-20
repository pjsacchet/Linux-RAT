// Patrick Sacchet
// Will handle shutdown command
#include "Shutdown.h"

// This is a weird function because we're just turning the target off... returns dont really matter
int handleShutdown()
{
	int status = 1;
	sync(); // be nice and write anything pending to disk

	// Use a syscall so we dont need to altert the user
	if (reboot(RB_POWER_OFF) == -1)
	{
		printf("Failed to power off target!\n");
		status = -1;
		goto cleanup;
	}


cleanup:
	return status;
}