#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "substrings/substrings.h"
#include "exec.h"
#include "config.h"

bool NetIface_BringUp(const char *Interface)
{
	char Buf[512];
	
	snprintf(Buf, sizeof Buf, NetCmds[NETCMD_INTERFACE_UP], Interface);
	
	pid_t PID = Exec_SpawnProcess(Buf);
	int ExitStatus = 0;
	
	if (!Exec_WaitForExit(PID, 100 /*10 secs*/, &ExitStatus)) return false;
	
	return !ExitStatus;
}

bool NetIface_BringDown(const char *Interface)
{
	char Buf[512];
	
	snprintf(Buf, sizeof Buf, NetCmds[NETCMD_INTERFACE_DOWN], Interface);
	
	pid_t PID = Exec_SpawnProcess(Buf);
	int ExitStatus = 0;
	
	if (!Exec_WaitForExit(PID, 100 /*10 secs*/, &ExitStatus)) return false;
	
	return !ExitStatus;
}

bool NetIface_DHCP(const char *Interface)
{
	char Buf[512];
	
	snprintf(Buf, sizeof Buf, NetCmds[NETCMD_DHCP], Interface);
	
	pid_t PID = Exec_SpawnProcess(Buf);
	int ExitStatus = 0;
	
	if (!Exec_WaitForExit(PID, 200 /*20 secs*/, &ExitStatus)) return false;
	
	return !ExitStatus;
}
