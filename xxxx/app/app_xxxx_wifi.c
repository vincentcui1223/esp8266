#include <app_xxxx_wifi.h>
#include <app_xxxx_sntp.h>
#include <app_xxxx_udp.h>
#include <app_xxxx_tcp.h>


sal_xxxx_wifi_station_config_t 	wifi_station_cfg;
sal_xxxx_wifi_softAp_config_t 	wifi_softAp_cfg;

sal_xxxx_timer_t wifi_station_connect_timer;
//sal_xxxx_timer_t wifi_softAp_connect_timer;


LOCAL int32 ICACHE_FLASH_ATTR
_sal_xxxx_wifi_event_station_connect_callback(sal_xxxx_wifi_event_t event, sal_xxxx_wifi_eventInfo_t *pEventInfo)
{
	os_printf("station connected to AP: \n");
	os_printf("AP ssid: %s\n", pEventInfo->connected.ssid);
	os_printf("AP ssid_len: %d\n", pEventInfo->connected.ssid_len);
	os_printf("AP bssid: %s\n", pEventInfo->connected.bssid);
	os_printf("AP channel: %d\n", pEventInfo->connected.channel);

	return XXXX_ERR_OK;	
}

LOCAL int32 ICACHE_FLASH_ATTR
_sal_xxxx_wifi_event_station_gotIp_callback(sal_xxxx_wifi_event_t event, sal_xxxx_wifi_eventInfo_t *pEventInfo)
{

    uint8 	ssid[SAL_XXXX_WIFI_SSID_LEN];
    uint32 	ssid_len;
    uint8 	bssid[SAL_XXXX_WIFI_BSSID_LEN];
    uint32 	channel;	

	os_printf("station got IP from AP: \n");
	os_printf("station IP: %d.%d.%d.%d\n", pEventInfo->got_ip.stationIp.octet[0], pEventInfo->got_ip.stationIp.octet[1], pEventInfo->got_ip.stationIp.octet[2], pEventInfo->got_ip.stationIp.octet[3]);
	os_printf("station Mask: %d.%d.%d.%d\n", pEventInfo->got_ip.stationIpMask.octet[0], pEventInfo->got_ip.stationIpMask.octet[1], pEventInfo->got_ip.stationIpMask.octet[2], pEventInfo->got_ip.stationIpMask.octet[3]);
	os_printf("station gateWay IP: %d.%d.%d.%d\n", pEventInfo->got_ip.gateWayIp.octet[0], pEventInfo->got_ip.gateWayIp.octet[1], pEventInfo->got_ip.gateWayIp.octet[2], pEventInfo->got_ip.gateWayIp.octet[3]);

	return XXXX_ERR_OK;	
}

LOCAL int32 ICACHE_FLASH_ATTR
_sal_xxxx_wifi_event_station_disconnect_callback(sal_xxxx_wifi_event_t event, sal_xxxx_wifi_eventInfo_t *pEventInfo)
{
	os_printf("station disconnected to AP: \n");
	os_printf("AP ssid: %s\n", pEventInfo->disconnected.ssid);
	os_printf("AP ssid_len: %d\n", pEventInfo->disconnected.ssid_len);
	os_printf("AP bssid: %s\n", pEventInfo->disconnected.bssid);
	os_printf("reason: %d\n", pEventInfo->disconnected.reason);

	return XXXX_ERR_OK;	
}

LOCAL void ICACHE_FLASH_ATTR
_app_xxxx_wifi_station_connect_timer_cb(void *arg)
{
	int32 ret;
	sal_xxxx_wifi_station_connect_status_t status;
	sal_xxxx_wifi_ipInfo_t ipInfo;
	
	XXXX_ERR_CHK_VOID_RETURN(sal_xxxx_wifi_station_connectStatus_get(&status),	ret);
	
	os_printf("station connected to AP status = %d: \n", status);
	if(status==SAL_XXXX_WIFI_STATION_CONNECT_STATUS_GOT_IP)
	{
		XXXX_ERR_CHK_VOID_RETURN(sal_xxxx_wifi_ipInfo_get(SAL_XXXX_WIFI_INTERFACE_STATION, &ipInfo), ret);
		os_printf("station IP: %d.%d.%d.%d\n", ipInfo.ip.octet[0], ipInfo.ip.octet[1], ipInfo.ip.octet[2], ipInfo.ip.octet[3]);
		os_printf("station Mask: %d.%d.%d.%d\n", ipInfo.ipMask.octet[0], ipInfo.ipMask.octet[1], ipInfo.ipMask.octet[2], ipInfo.ipMask.octet[3]);
		os_printf("station gateWay IP: %d.%d.%d.%d\n", ipInfo.gateWayIp.octet[0], ipInfo.gateWayIp.octet[1], ipInfo.gateWayIp.octet[2], ipInfo.gateWayIp.octet[3]);

		XXXX_ERR_CHK_VOID_RETURN(sal_xxxx_timer_disable(&wifi_station_connect_timer), ret);

		XXXX_ERR_CHK_VOID_RETURN(app_xxxx_sntp_init(), ret);
		XXXX_ERR_CHK_VOID_RETURN(app_xxxx_udp_init(), ret);
		//XXXX_ERR_CHK_VOID_RETURN(app_xxxx_tcp_init(), ret);
	}
	else
	{
		
	}

	return;
}


LOCAL int32 ICACHE_FLASH_ATTR
_sal_xxxx_wifi_event_softAp_stationConnect_callback(sal_xxxx_wifi_event_t event, sal_xxxx_wifi_eventInfo_t *pEventInfo)
{
	os_printf("soft AP, station connected: \n");
	os_printf("station MAC: %x:%x:%x:%x:%x:%x, aid=%d\n", 
		pEventInfo->sta_connected.station_mac.octet[0], pEventInfo->sta_connected.station_mac.octet[1], pEventInfo->sta_connected.station_mac.octet[2], 
		pEventInfo->sta_connected.station_mac.octet[3], pEventInfo->sta_connected.station_mac.octet[4], pEventInfo->sta_connected.station_mac.octet[5], 
		pEventInfo->sta_connected.aid);

	return XXXX_ERR_OK;	
}

LOCAL int32 ICACHE_FLASH_ATTR
_sal_xxxx_wifi_event_softAp_stationDisConnect_callback(sal_xxxx_wifi_event_t event, sal_xxxx_wifi_eventInfo_t *pEventInfo)
{
	os_printf("soft AP, station disconnected: \n");
	os_printf("station MAC: %x:%x:%x:%x:%x:%x, aid=%d\n", 
		pEventInfo->sta_disconnected.station_mac.octet[0], pEventInfo->sta_disconnected.station_mac.octet[1], pEventInfo->sta_disconnected.station_mac.octet[2], 
		pEventInfo->sta_disconnected.station_mac.octet[3], pEventInfo->sta_disconnected.station_mac.octet[4], pEventInfo->sta_disconnected.station_mac.octet[5], 
		pEventInfo->sta_disconnected.aid);

	return XXXX_ERR_OK;	
}

LOCAL int32 ICACHE_FLASH_ATTR
_sal_xxxx_wifi_event_softAp_stationDistrbuteIp_callback(sal_xxxx_wifi_event_t event, sal_xxxx_wifi_eventInfo_t *pEventInfo)
{
	os_printf("soft AP, station distribute IP: \n");
	os_printf("station MAC: %x:%x:%x:%x:%x:%x, Ip=%d.%d.%d.%d, aid=%d\n", 
		pEventInfo->distribute_sta_ip.station_mac.octet[0], pEventInfo->distribute_sta_ip.station_mac.octet[1], pEventInfo->distribute_sta_ip.station_mac.octet[2], 
		pEventInfo->distribute_sta_ip.station_mac.octet[3], pEventInfo->distribute_sta_ip.station_mac.octet[4], pEventInfo->distribute_sta_ip.station_mac.octet[5], 
		pEventInfo->distribute_sta_ip.stationIp.octet[0], pEventInfo->distribute_sta_ip.stationIp.octet[1], pEventInfo->distribute_sta_ip.stationIp.octet[2], pEventInfo->distribute_sta_ip.stationIp.octet[3], 
		pEventInfo->distribute_sta_ip.aid);

	return XXXX_ERR_OK;	
}

LOCAL int32 ICACHE_FLASH_ATTR
_app_xxxx_wifi_init_stationMode_ip_set(void)
{
	int32	ret;
	sal_xxxx_wifi_ipInfo_t ipInfo;

	UINT32_TO_IPV4_ADDR(ipInfo.ip, IPV4_UINT32(192,168,1,30));
	UINT32_TO_IPV4_ADDR(ipInfo.ipMask, IPV4_UINT32(255,255,255,0));
	UINT32_TO_IPV4_ADDR(ipInfo.gateWayIp, IPV4_UINT32(192,168,1,1));
	XXXX_ERR_CHK(sal_xxxx_wifi_ipInfo_set(SAL_XXXX_WIFI_MODE_STATION,	&ipInfo), ret);

	xxxx_ipv4_addr_t dnsServerIp;
	UINT32_TO_IPV4_ADDR(dnsServerIp, IPV4_UINT32(218,4,4,4));
	XXXX_ERR_CHK(sal_xxxx_dns_serverIp_set(0, &dnsServerIp), ret);
	UINT32_TO_IPV4_ADDR(dnsServerIp, IPV4_UINT32(218,2,2,2));
	XXXX_ERR_CHK(sal_xxxx_dns_serverIp_set(1, &dnsServerIp), ret);

	return XXXX_ERR_OK;
}


LOCAL int32 ICACHE_FLASH_ATTR
_app_xxxx_wifi_init_stationMode(void)
{
	int32 ret;

	os_memset(&wifi_station_cfg, 0, sizeof(sal_xxxx_wifi_station_config_t));
#if TEST_UDP_ROUT_XIAOMI
	os_strcpy(wifi_station_cfg.ssid,		"Xiaomi_cuitao_2.4G");
#else
	os_strcpy(wifi_station_cfg.ssid,		"TP-LINK_CUI_TAO");
#endif
	os_strcpy(wifi_station_cfg.password,	"lmct19841223");
	XXXX_ERR_CHK(sal_xxxx_wifi_station_config_set(&wifi_station_cfg, COMM_XXXX_CONFIG_TYPE_CURRENT), ret);
	
	XXXX_ERR_CHK(sal_xxxx_wifi_event_cbFunc_register(SAL_XXXX_WIFI_EVENT_STAMODE_CONNECTED, 	_sal_xxxx_wifi_event_station_connect_callback), 	ret);
	XXXX_ERR_CHK(sal_xxxx_wifi_event_cbFunc_register(SAL_XXXX_WIFI_EVENT_STAMODE_GOT_IP,		_sal_xxxx_wifi_event_station_gotIp_callback),		ret);
	XXXX_ERR_CHK(sal_xxxx_wifi_event_cbFunc_register(SAL_XXXX_WIFI_EVENT_STAMODE_DISCONNECTED,	_sal_xxxx_wifi_event_station_disconnect_callback),	ret);

	//XXXX_ERR_CHK(_app_xxxx_wifi_init_stationMode_ip_set(), ret);
		
	XXXX_ERR_CHK(sal_xxxx_timer_disable(&wifi_station_connect_timer), ret);
	XXXX_ERR_CHK(sal_xxxx_timer_init(&wifi_station_connect_timer,	_app_xxxx_wifi_station_connect_timer_cb , NULL), ret);
	XXXX_ERR_CHK(sal_xxxx_timer_enable(&wifi_station_connect_timer, APP_XXXX_WIFI_STATION_CONNECT_CHECK_TIME,	1), ret);

	return XXXX_ERR_OK;
}

LOCAL int32 ICACHE_FLASH_ATTR
_app_xxxx_wifi_init_softApMode(void)
{
	int32 ret;

	os_memset(&wifi_softAp_cfg, 0, sizeof(sal_xxxx_wifi_softAp_config_t));
	os_strcpy(wifi_softAp_cfg.ssid, 			"ESP8266");
	wifi_softAp_cfg.ssid_len				=	os_strlen(wifi_softAp_cfg.ssid);
	os_strcpy(wifi_softAp_cfg.password, 		"esp8266esp8266");
	wifi_softAp_cfg.channel 				=	1;
	wifi_softAp_cfg.authMode				=	SAL_XXXX_WIFI_AUTH_WPA_WPA2_PSK;
	wifi_softAp_cfg.ssid_hide				=	DISABLED;
	wifi_softAp_cfg.max_connection_device	=	SAL_XXXX_WIFI_SOFT_AP_MAX_CONNECT_NUM;
	wifi_softAp_cfg.beacon_interval 		=	SAL_XXXX_WIFI_SOFT_AP_BEACOM_INTERVAL_DEFAULT;
	XXXX_ERR_CHK(sal_xxxx_wifi_softap_config_set(&wifi_softAp_cfg, COMM_XXXX_CONFIG_TYPE_CURRENT), ret);

	XXXX_ERR_CHK(sal_xxxx_wifi_event_cbFunc_register(SAL_XXXX_WIFI_EVENT_SOFTAPMODE_STACONNECTED, 		_sal_xxxx_wifi_event_softAp_stationConnect_callback), 		ret);
	XXXX_ERR_CHK(sal_xxxx_wifi_event_cbFunc_register(SAL_XXXX_WIFI_EVENT_SOFTAPMODE_STADISCONNECTED,	_sal_xxxx_wifi_event_softAp_stationDisConnect_callback),	ret);
	XXXX_ERR_CHK(sal_xxxx_wifi_event_cbFunc_register(SAL_XXXX_WIFI_EVENT_SOFTAPMODE_DISTRIBUTE_STA_IP,	_sal_xxxx_wifi_event_softAp_stationDistrbuteIp_callback),	ret);	

	return XXXX_ERR_OK;
}


int32 ICACHE_FLASH_ATTR
app_xxxx_wifi_init(sal_xxxx_wifi_mode_t wifiMode)
{
	int32 ret;

	XXXX_PARA_CHK(wifiMode>SAL_XXXX_WIFI_MODE_STATION_AND_AP,	ret);
	XXXX_ERR_CHK(sal_xxxx_wifi_event_cbFunc_register(SAL_XXXX_WIFI_EVENT_END, NULL), ret);
	
	XXXX_ERR_CHK(sal_xxxx_wifi_mode_set(wifiMode, COMM_XXXX_CONFIG_TYPE_CURRENT),	ret);
	if(wifiMode==SAL_XXXX_WIFI_MODE_STATION || wifiMode==SAL_XXXX_WIFI_MODE_STATION_AND_AP)
		XXXX_ERR_CHK(_app_xxxx_wifi_init_stationMode(),	ret);
	if(wifiMode==SAL_XXXX_WIFI_MODE_SOFT_AP || wifiMode==SAL_XXXX_WIFI_MODE_STATION_AND_AP)
		XXXX_ERR_CHK(_app_xxxx_wifi_init_softApMode(),	ret);
	
	return XXXX_ERR_OK;
}


