#ifndef __WIFI_H__
#define __WIFI_H__

#include <iwlib.h>
#include <stdbool.h>
//Prototypes
struct wireless_scan *Wifi_GetNetworks(const char *Interface);
struct wireless_config Wifi_GetStatus(const char *const Interface);
bool Wifi_SetESSID(const char *const Interface, const char *const ESSID);
bool Wifi_Auth_WEP(const char *Interface, const char *Key);
bool Wifi_Auth_WPA(const char *Interface, const char *ESSID, const char *Passphrase);


#endif //__WIFI_H__

