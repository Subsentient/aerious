#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "substrings/substrings.h"

#include "config.h"

char *NetCmds[] = { "ifconfig %s up", "ifconfig %s down", "dhclient %s", "iwconfig %s" };

bool Config_ReadConfig(void)
{
	FILE *Descriptor = fopen(AERIOUS_CONFIG, "rb");
	struct stat FileStat;
	
	if (!Descriptor || stat(AERIOUS_CONFIG, &FileStat) != 0)
	{
		if (Descriptor) fclose(Descriptor);
		return false;
	}
	
	
	///Interesting config reading stuff goes here.
	return true;
	
}

