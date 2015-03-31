#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <netdb.h>

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

bool NetIface_IsUp(const char *const Interface)
{ //Uses sysfs to check if the interface is up
	char Filename[256];
	
	snprintf(Filename, sizeof Filename, "/sys/class/net/%s/operstate", Interface);
	
	FILE *Descriptor = fopen(Filename, "rb");
	
	if (!Descriptor) return false;
	
	char InBuf[2048];
	int Inc = 0;
	
	for (int Char; (Char = getc(Descriptor)) != EOF && Inc < sizeof InBuf - 1; ++Inc)
	{
		InBuf[Inc] = Char;
	}
	InBuf[Inc] = '\0';
	
	fclose(Descriptor);
	
	if (!strcmp(InBuf, "up\n")) return true;
	
	return false;
}

bool NetIface_GetIP(const char *const Interface, char *const OutStream, unsigned OutStreamSize, bool IPv6)
{ //Gets you the IP for the specified network interface, if one is present.
	struct ifaddrs *IFAddr = NULL;
	const int Family = IPv6 ? AF_INET6 : AF_INET;
	
	if (getifaddrs(&IFAddr) == -1)
	{
		return false;
	}
	
	for (struct ifaddrs *IFList = IFAddr; IFList != NULL; IFList = IFList->ifa_next)
	{
		if (!IFList->ifa_addr) continue;
		
		if (IFList->ifa_addr->sa_family == Family && !strcmp(IFList->ifa_name, Interface))
		{ //If the family matches and the interface name matches
			char IP[512];
			const int StructSize = IPv6 ? sizeof(struct sockaddr_in6) : sizeof(struct sockaddr_in);
			
			if (getnameinfo(IFList->ifa_addr, StructSize, IP, NI_MAXHOST,
							NULL, 0, NI_NUMERICHOST) != 0)				
			{
				return false;
			}
			
			if (OutStream)
			{ //Only if we want the IP
				//Give them the IP they wanted.
				SubStrings.Copy(OutStream, IP, OutStreamSize);
			}
			return true;
		}
	}
	freeifaddrs(IFAddr);
	
	return false;
}
