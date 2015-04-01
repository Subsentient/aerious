
#include <iwlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "exec.h"
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
	
	iw_sockets_close(Socket);
	
	//Gives us a linked list traversed with ->next
	return Head.result;
}

struct wireless_config Wifi_GetStatus(const char *const Interface)
{
	struct wireless_config RetVal;
	memset(&RetVal, 0, sizeof RetVal);
	
	int Socket = iw_sockets_open();
	//Whether or not it fails we just return the structure.
	iw_get_basic_config(Socket, Interface, &RetVal);
	
	return RetVal;
}

bool Wifi_SetESSID(const char *const Interface, const char *const ESSID)
{
	char Buf[2048];
	
	snprintf(Buf, sizeof Buf, "iwconfig %s essid \"%s\"", Interface, ESSID);
	
	pid_t PID = Exec_SpawnProcess(Buf);
	
	int ExitStatus;
	if (!Exec_WaitForExit(PID, 100 /*10 secs*/, &ExitStatus)) return false;
	
	return !ExitStatus;
}
