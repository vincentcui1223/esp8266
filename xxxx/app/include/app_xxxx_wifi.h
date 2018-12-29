#ifndef __APP_XXXX_WIFI_H__
#define __APP_XXXX_WIFI_H__

#include <xxxx_comm.h>
#include <sal_xxxx_timer.h>
#include <sal_xxxx_wifi.h>

#define APP_XXXX_WIFI_STATION_CONNECT_CHECK_TIME 10000

extern sal_xxxx_wifi_station_config_t 	wifi_station_cfg;
extern sal_xxxx_wifi_softAp_config_t 	wifi_softAp_cfg;

extern sal_xxxx_timer_t wifi_station_connect_timer;

extern int32
app_xxxx_wifi_init(sal_xxxx_wifi_mode_t wifiMode);


#endif

