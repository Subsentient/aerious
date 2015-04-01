#ifndef __WIFI_H__
#define __WIFI_H__

#include <iwlib.h>

//Prototypes
struct wireless_scan *Wifi_GetNetworks(const char *Interface);
struct wireless_config Wifi_GetStatus(const char *const Interface);

#endif //__WIFI_H__

