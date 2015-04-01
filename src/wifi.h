#ifndef __WIFI_H__
#define __WIFI_H__

#include <iwlib.h>

//Prototypes
struct wireless_scan *Wifi_GetNetworks(const char *Interface);

#endif //__WIFI_H__

