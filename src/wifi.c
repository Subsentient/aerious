
#include <iwlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wifi.h"

struct wireless_scan *Wifi_GetNetworks(const char *Interface)
{
	
	iwrange Range;
	int Socket = iw_sockets_open();
	
	if (iw_get_range_info(Socket, Interface, &Range) == -1)
	{
		return NULL;
	}

	wireless_scan_head Head;
	if (iw_scan(Socket, (char*)Interface, Range.we_version_compiled, &Head) == -1)
	{
		return NULL;
	}
	
	return Head.result;
}
