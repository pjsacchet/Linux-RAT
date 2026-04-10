// Patrick Sacchet
// Will handle shutdown command
#include "Shutdown.h"

void handleShutdown()
{
	sync(); // be nice and write anything pending to disk

	// Use a syscall so we dont need to altert the user
	if (reboot(RB_POWER_OFF) == -1)
	{
		printf("Failed to power off target!\n");
		return;
	}
	return;
}