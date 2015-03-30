#include <stdbool.h>

#ifndef __CONFIG_H__
#define __CONFIG_H__

//constants
#define AERIOUS_CONFIG "/etc/aerious.conf"

//Structures
enum NetCmdEnum { NETCMD_INVALID, NETCMD_INTERFACE_UP, NETCMD_INTERFACE_DOWN, NETCMD_DHCP, NETCMD_IWCONFIG, NETCMD_MAX };


//globals
extern char *NetCmds[];			

//Prototypes
bool Config_ReadConfig(void);

#endif //__CONFIG_H__
