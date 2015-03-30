#include <stdbool.h>

//constants
#define AERIOUS_CONFIG "/etc/aerious.conf"

//Structures
enum NetCmdEnum { NETCMD_INVALID, NETCMD_INTERFACE_UP, NETCMD_INTERFACE_DOWN, NETCMD_DHCP, NETCMD_IWCONFIG, NETCMD_MAX } Cmd;


//globals
extern char *NetCmds[];			

//Prototypes
bool Config_ReadConfig(void);
