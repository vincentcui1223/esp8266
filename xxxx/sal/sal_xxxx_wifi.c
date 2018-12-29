
#include <sal_xxxx_wifi.h>
#include <sal_xxxx_to_sdk.h>

SAL_XXXX_WIFI_EVENT_CB_FUNC sal_xxxx_wifi_event_cb[SAL_XXXX_WIFI_EVENT_END] = {NULL};


LOCAL void ICACHE_FLASH_ATTR
_sal_xxxx_wifi_event_handler_cb_func(System_Event_t *event)
{
	int32 ret;
	sal_xxxx_wifi_event_t 		sal_event;
	sal_xxxx_wifi_eventInfo_t 	sal_eventInfo;

	SAL_XXXX_WIFI_EVENT_XLATE_FROM_CHIP(sal_event, event->event,	ret);
	if(ret!=XXXX_ERR_OK)
		VOID_RETURN();

	if(sal_xxxx_wifi_event_cb[sal_event]==NULL)
		return;

	switch(sal_event)
	{
		case SAL_XXXX_WIFI_EVENT_STAMODE_CONNECTED:
			os_memcpy(sal_eventInfo.connected.ssid, 	event->event_info.connected.ssid, SAL_XXXX_WIFI_SSID_LEN);
			sal_eventInfo.connected.ssid_len		=	event->event_info.connected.ssid_len;
			os_memcpy(sal_eventInfo.connected.bssid, 	event->event_info.connected.bssid, SAL_XXXX_WIFI_BSSID_LEN);
			sal_eventInfo.connected.channel			=	event->event_info.connected.channel;
			break;
		case SAL_XXXX_WIFI_EVENT_STAMODE_DISCONNECTED:
			os_memcpy(sal_eventInfo.disconnected.ssid, 		event->event_info.disconnected.ssid, SAL_XXXX_WIFI_SSID_LEN);
			sal_eventInfo.disconnected.ssid_len		=		event->event_info.disconnected.ssid_len;
			os_memcpy(sal_eventInfo.disconnected.bssid, 	event->event_info.disconnected.bssid, SAL_XXXX_WIFI_BSSID_LEN);
			SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_XLATE_FROM_CHIP(sal_eventInfo.disconnected.reason, event->event_info.disconnected.reason, ret);
			if(ret!=XXXX_ERR_OK)
				VOID_RETURN();
			break;			
		case SAL_XXXX_WIFI_EVENT_STAMODE_AUTHMODE_CHANGE:
			SAL_XXXX_WIFI_AUTH_XLATE_FROM_CHIP(sal_eventInfo.auth_change.old_mode, event->event_info.auth_change.old_mode, ret);
			if(ret!=XXXX_ERR_OK)
				VOID_RETURN();
			SAL_XXXX_WIFI_AUTH_XLATE_FROM_CHIP(sal_eventInfo.auth_change.new_mode, event->event_info.auth_change.new_mode, ret);
			if(ret!=XXXX_ERR_OK)
				VOID_RETURN();
			break;	
		case SAL_XXXX_WIFI_EVENT_STAMODE_GOT_IP:
			UINT32_TO_IPV4_ADDR(sal_eventInfo.got_ip.stationIp, 	event->event_info.got_ip.ip.addr);
			UINT32_TO_IPV4_ADDR(sal_eventInfo.got_ip.stationIpMask,	event->event_info.got_ip.mask.addr);
			UINT32_TO_IPV4_ADDR(sal_eventInfo.got_ip.gateWayIp, 	event->event_info.got_ip.gw.addr);
			break;
		case SAL_XXXX_WIFI_EVENT_STAMODE_DHCP_TIMEOUT:
			break;
		case SAL_XXXX_WIFI_EVENT_SOFTAPMODE_STACONNECTED:
			os_memcpy(sal_eventInfo.sta_connected.station_mac.octet, event->event_info.sta_connected.mac, MAC_ADDR_LEN);
			sal_eventInfo.sta_connected.aid			=	event->event_info.sta_connected.aid;
			break;
		case SAL_XXXX_WIFI_EVENT_SOFTAPMODE_STADISCONNECTED:
			os_memcpy(sal_eventInfo.sta_disconnected.station_mac.octet, event->event_info.sta_disconnected.mac, MAC_ADDR_LEN);
			sal_eventInfo.sta_disconnected.aid		=	event->event_info.sta_disconnected.aid;
			break;
		case SAL_XXXX_WIFI_EVENT_SOFTAPMODE_PROBEREQRECVED:
			sal_eventInfo.ap_probeReqRecved.rssi	=	event->event_info.ap_probereqrecved.rssi;
			os_memcpy(sal_eventInfo.ap_probeReqRecved.station_mac.octet, event->event_info.ap_probereqrecved.mac, MAC_ADDR_LEN);
			break;
		case SAL_XXXX_WIFI_EVENT_OPMODE_CHANGED:
			SAL_XXXX_WIFI_MODE_XLATE_FROM_CHIP(sal_eventInfo.opmode_changed.old_opmode, event->event_info.opmode_changed.old_opmode, ret);
			if(ret!=XXXX_ERR_OK)
				VOID_RETURN();
			SAL_XXXX_WIFI_MODE_XLATE_FROM_CHIP(sal_eventInfo.opmode_changed.new_opmode, event->event_info.opmode_changed.new_opmode, ret);
			if(ret!=XXXX_ERR_OK)
				VOID_RETURN();
			break;	
		case SAL_XXXX_WIFI_EVENT_SOFTAPMODE_DISTRIBUTE_STA_IP:
			os_memcpy(sal_eventInfo.distribute_sta_ip.station_mac.octet, event->event_info.distribute_sta_ip.mac, MAC_ADDR_LEN);
			UINT32_TO_IPV4_ADDR(sal_eventInfo.distribute_sta_ip.stationIp, 	event->event_info.distribute_sta_ip.ip.addr);
			sal_eventInfo.distribute_sta_ip.aid		=	event->event_info.distribute_sta_ip.aid;
			break;
		default:
			VOID_RETURN();
	}

	if(sal_xxxx_wifi_event_cb[sal_event]!=NULL)
		XXXX_ERR_CHK_VOID_RETURN(sal_xxxx_wifi_event_cb[sal_event](sal_event, &sal_eventInfo),	ret);
	
	return;	
}


int32 sal_xxxx_wifi_event_cbFunc_register(sal_xxxx_wifi_event_t event, SAL_XXXX_WIFI_EVENT_CB_FUNC func)
{
	int32 ret;

	XXXX_PARA_CHK(event>SAL_XXXX_WIFI_EVENT_END, ret);

	if(event==SAL_XXXX_WIFI_EVENT_END)	
		wifi_set_event_handler_cb(_sal_xxxx_wifi_event_handler_cb_func);
	else
		sal_xxxx_wifi_event_cb[event]	=	func;

	return XXXX_ERR_OK;
}

int32 sal_xxxx_wifi_event_cbFunc_unregister(sal_xxxx_wifi_event_t event)
{
	int32 ret;

	XXXX_PARA_CHK(event>=SAL_XXXX_WIFI_EVENT_END, ret);
	sal_xxxx_wifi_event_cb[event]	=	NULL;

	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_wifi_mode_set(sal_xxxx_wifi_mode_t mode, comm_xxxx_config_type_t configType)
{
	int32 ret;
	XXXX_PARA_CHK((mode>=SAL_XXXX_WIFI_MODE_END), XXXX_ERR_FAILED);
	XXXX_PARA_CHK((configType>=COMM_XXXX_CONFIG_TYPE_END), XXXX_ERR_FAILED);

	uint8 chipMode;
	SAL_XXXX_WIFI_MODE_XLATE_TO_CHIP(mode, chipMode, ret);
	if(ret!=XXXX_ERR_OK)
		RETURN(ret);
	if(configType==COMM_XXXX_CONFIG_TYPE_CURRENT)
		ret=wifi_set_opmode_current(chipMode);
	if(configType==COMM_XXXX_CONFIG_TYPE_FLASH)
		ret=wifi_set_opmode(chipMode);
	if(ret==FALSE)
		RETURN(XXXX_ERR_FAILED);

	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_wifi_mode_get(sal_xxxx_wifi_mode_t *pMode, comm_xxxx_config_type_t configType)
{
	int32 ret;
	XXXX_PARA_CHK((pMode==NULL), XXXX_ERR_FAILED);
	XXXX_PARA_CHK((configType>=COMM_XXXX_CONFIG_TYPE_END), XXXX_ERR_FAILED);

	uint8 chipMode;
	if(configType==COMM_XXXX_CONFIG_TYPE_CURRENT)
		chipMode = wifi_get_opmode();
	if(configType==COMM_XXXX_CONFIG_TYPE_FLASH)
		chipMode = wifi_get_opmode_default();
	SAL_XXXX_WIFI_MODE_XLATE_FROM_CHIP(*pMode, chipMode, ret);
	if(ret!=XXXX_ERR_OK)
		RETURN(ret);
	
	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_wifi_udpBC_interface_set(sal_xxxx_wifi_interface_t interface)
{
	int32 ret;
	switch(interface)
	{
		case SAL_XXXX_WIFI_INTERFACE_STATION:
			XXXX_ERR_CHK_ERRCODE(wifi_set_broadcast_if(1),	ret,	TRUE); break;
		case SAL_XXXX_WIFI_INTERFACE_SOFT_AP:
			XXXX_ERR_CHK_ERRCODE(wifi_set_broadcast_if(2),	ret,	TRUE); break;
		case SAL_XXXX_WIFI_INTERFACE_STATION_AND_SOFT_AP:
			XXXX_ERR_CHK_ERRCODE(wifi_set_broadcast_if(3),	ret,	TRUE); break;
		default:
			RETURN(XXXX_ERR_FAILED);
	}
	return XXXX_ERR_OK; 
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_wifi_udpBC_interface_get(sal_xxxx_wifi_interface_t *pInterface)
{
	uint8 val = wifi_get_broadcast_if();
	
	switch(val)
	{
		case 1:
			*pInterface =SAL_XXXX_WIFI_INTERFACE_STATION;	break;
		case 2:
			*pInterface =SAL_XXXX_WIFI_INTERFACE_SOFT_AP;	break;
		case 3:
			*pInterface =SAL_XXXX_WIFI_INTERFACE_STATION_AND_SOFT_AP;	break;
		default:
			RETURN(XXXX_ERR_FAILED);
	}
	return XXXX_ERR_OK; 
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_wifi_ipInfo_get(sal_xxxx_wifi_interface_t interface, sal_xxxx_wifi_ipInfo_t *pIpInfo)
{	
	int32 ret;
	XXXX_PARA_CHK((pIpInfo==NULL), XXXX_ERR_FAILED);	
	struct ip_info ipInfo;

	switch(interface)
	{
		case SAL_XXXX_WIFI_INTERFACE_STATION:
			XXXX_ERR_CHK_ERRCODE(wifi_get_ip_info(STATION_IF, &ipInfo),	ret,	TRUE);
			break;
		case SAL_XXXX_WIFI_INTERFACE_SOFT_AP:
			XXXX_ERR_CHK_ERRCODE(wifi_get_ip_info(SOFTAP_IF, &ipInfo), 	ret,	TRUE);
			break;
		default:
			RETURN(XXXX_ERR_FAILED);
	}

	//DBG_PRINT(("ip=0x%x, ip[0]=0x%x, ip[1]=0x%x, ip[2]=0x%x, ip[3]=0x%x\n", ipInfo.ip.addr, (ipInfo.ip.addr>>24)&0xff, (ipInfo.ip.addr>>16)&0xff, (ipInfo.ip.addr>>8)&0xff, (ipInfo.ip.addr>>0)&0xff), DEB_PRINTF_LEVEL_ALL);

	UINT32_TO_IPV4_ADDR(pIpInfo->ip, 		ipInfo.ip.addr);
	UINT32_TO_IPV4_ADDR(pIpInfo->ipMask, 	ipInfo.netmask.addr);
	UINT32_TO_IPV4_ADDR(pIpInfo->gateWayIp, ipInfo.gw.addr);

	//uint32 ip = IPV4_UINT32(192, 168, 31, 100);
	//DBG_PRINT(("ip=0x%x\n", ip), DEB_PRINTF_LEVEL_ALL);

	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_wifi_ipInfo_set(sal_xxxx_wifi_interface_t interface, sal_xxxx_wifi_ipInfo_t *pIpInfo)
{	
	int32 ret;
	XXXX_PARA_CHK((pIpInfo==NULL), XXXX_ERR_FAILED);
	comm_xxxx_enable_t dhcp_server_enable;
	
	struct ip_info ipInfo;

	IPV4_ADDR_TO_UINT32(pIpInfo->ip, 		ipInfo.ip.addr);
	IPV4_ADDR_TO_UINT32(pIpInfo->ipMask, 	ipInfo.netmask.addr);
	IPV4_ADDR_TO_UINT32(pIpInfo->gateWayIp, ipInfo.gw.addr);

	switch(interface)
	{
		case SAL_XXXX_WIFI_INTERFACE_STATION:
			XXXX_ERR_CHK(sal_xxxx_wifi_station_dhcp_set(SAL_XXXX_WIFI_INTERFACE_STATION, DISABLED), ret);
			XXXX_ERR_CHK_ERRCODE(wifi_set_ip_info(STATION_IF, &ipInfo),	ret,	TRUE);
			break;
		case SAL_XXXX_WIFI_INTERFACE_SOFT_AP:
			XXXX_ERR_CHK(sal_xxxx_wifi_station_dhcp_get(SAL_XXXX_WIFI_INTERFACE_SOFT_AP, &dhcp_server_enable), ret);
			if(dhcp_server_enable==ENABLED)
				XXXX_ERR_CHK(sal_xxxx_wifi_station_dhcp_set(SAL_XXXX_WIFI_INTERFACE_SOFT_AP, DISABLED), ret);
			XXXX_ERR_CHK_ERRCODE(wifi_set_ip_info(SOFTAP_IF, &ipInfo), 	ret,	TRUE);
			if(dhcp_server_enable==ENABLED)
				XXXX_ERR_CHK(sal_xxxx_wifi_station_dhcp_set(SAL_XXXX_WIFI_INTERFACE_SOFT_AP, ENABLED), ret);
			break;
		default:
			RETURN(XXXX_ERR_FAILED);
	}

	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_wifi_station_dhcp_get(sal_xxxx_wifi_interface_t interface, comm_xxxx_enable_t *pEnable)
{
	enum dhcp_status status;
	XXXX_PARA_CHK((pEnable==NULL), XXXX_ERR_FAILED);	
	switch(interface)
	{
		case SAL_XXXX_WIFI_INTERFACE_STATION:
			status	=	wifi_station_dhcpc_status();
			break;
		case SAL_XXXX_WIFI_INTERFACE_SOFT_AP:
			status	=	wifi_softap_dhcps_status();
			break;
		default:
			RETURN(XXXX_ERR_FAILED);
	}
	*pEnable	=	(status==DHCP_STOPPED) ? DISABLED : ENABLED;
	return XXXX_ERR_OK;
}


int32 ICACHE_FLASH_ATTR
sal_xxxx_wifi_station_dhcp_set(sal_xxxx_wifi_interface_t interface, comm_xxxx_enable_t enable)
{
	int32 ret;
	XXXX_PARA_CHK((enable>ENABLED), XXXX_ERR_FAILED);	
	switch(interface)
	{
		case SAL_XXXX_WIFI_INTERFACE_STATION:
			if(enable==ENABLED)
				XXXX_ERR_CHK_ERRCODE(wifi_station_dhcpc_start(),	ret,	TRUE);
			else
				XXXX_ERR_CHK_ERRCODE(wifi_station_dhcpc_stop(),		ret,	TRUE);
			break;
		case SAL_XXXX_WIFI_INTERFACE_SOFT_AP:
			if(enable==ENABLED)
				XXXX_ERR_CHK_ERRCODE(wifi_softap_dhcps_start(),	ret,	TRUE);
			else
				XXXX_ERR_CHK_ERRCODE(wifi_softap_dhcps_stop(),		ret,	TRUE);
			break;
		default:
			RETURN(XXXX_ERR_FAILED);
	}
	return XXXX_ERR_OK;
}




int32 ICACHE_FLASH_ATTR
sal_xxxx_wifi_station_config_set(sal_xxxx_wifi_station_config_t *pWifiInfo, comm_xxxx_config_type_t configType)
{
	int32 ret;
	
	XXXX_PARA_CHK((pWifiInfo==NULL), XXXX_ERR_FAILED);

	struct station_config stationCfg;
	
	os_memcpy(stationCfg.ssid,		pWifiInfo->ssid,		 SAL_XXXX_WIFI_SSID_LEN);
	os_memcpy(stationCfg.password,	pWifiInfo->password,	 SAL_XXXX_WIFI_SSID_LEN);
	stationCfg.bssid_set  		=	pWifiInfo->bssid_set;
	os_memcpy(stationCfg.bssid,		pWifiInfo->bssid,	 SAL_XXXX_WIFI_BSSID_LEN);
	stationCfg.threshold.rssi	=	pWifiInfo->threshold.rssi;
	SAL_XXXX_WIFI_AUTH_XLATE_TO_CHIP(pWifiInfo->threshold.auth, stationCfg.threshold.authmode, ret);
	if(ret!=XXXX_ERR_OK)
		RETURN(ret);

	if(configType==COMM_XXXX_CONFIG_TYPE_CURRENT)
		XXXX_ERR_CHK_ERRCODE(wifi_station_set_config_current(&stationCfg),	ret,	TRUE);
	else if(configType==COMM_XXXX_CONFIG_TYPE_FLASH)
		XXXX_ERR_CHK_ERRCODE(wifi_station_set_config(&stationCfg),	ret,	TRUE);
	else
		RETURN(XXXX_ERR_FAILED);

	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_wifi_station_config_get(sal_xxxx_wifi_station_config_t *pWifiInfo, comm_xxxx_config_type_t configType)
{
	int32 ret;
	
	XXXX_PARA_CHK((pWifiInfo==NULL), XXXX_ERR_FAILED);

	struct station_config stationCfg;
	if(configType==COMM_XXXX_CONFIG_TYPE_CURRENT)
		XXXX_ERR_CHK_ERRCODE(wifi_station_get_config(&stationCfg),	ret,	TRUE);
	else if(configType==COMM_XXXX_CONFIG_TYPE_FLASH)
		XXXX_ERR_CHK_ERRCODE(wifi_station_get_config_default(&stationCfg),	ret,	TRUE);
	else
		RETURN(XXXX_ERR_FAILED);
	
	os_memcpy(pWifiInfo->ssid,			stationCfg.ssid,		SAL_XXXX_WIFI_SSID_LEN);
	os_memcpy(pWifiInfo->password,		stationCfg.password,	SAL_XXXX_WIFI_SSID_LEN);
	pWifiInfo->bssid_set			=	stationCfg.bssid_set;
	os_memcpy(pWifiInfo->bssid,	 		stationCfg.bssid,		SAL_XXXX_WIFI_BSSID_LEN);
	pWifiInfo->threshold.rssi		=	stationCfg.threshold.rssi;
	SAL_XXXX_WIFI_AUTH_XLATE_FROM_CHIP(pWifiInfo->threshold.auth,stationCfg.threshold.authmode, ret);
	if(ret!=XXXX_ERR_OK)
		RETURN(ret);

	return XXXX_ERR_OK;
}


int32 ICACHE_FLASH_ATTR
sal_xxxx_wifi_station_connect(void)
{
	int32 ret;
	ret=wifi_station_connect();
	if(ret==FALSE)
		RETURN(XXXX_ERR_FAILED);

	return XXXX_ERR_OK;	
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_wifi_station_disconnect(void)
{
	int32 ret;
	ret=wifi_station_disconnect();
	if(ret==FALSE)
		RETURN(XXXX_ERR_FAILED);

	return XXXX_ERR_OK; 
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_wifi_station_connectStatus_get(sal_xxxx_wifi_station_connect_status_t *pStatus)
{
	int32 ret;

	uint32 chipStatus;
	chipStatus=wifi_station_get_connect_status();
	SAL_XXXX_WIFI_CONNECT_STATUS_XLATE_FROM_CHIP(*pStatus, chipStatus, ret);
	if(ret!=XXXX_ERR_OK)
		RETURN(ret);

	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_wifi_softap_config_get(sal_xxxx_wifi_softAp_config_t *pSoftApInfo, comm_xxxx_config_type_t configType)
{
	int32 ret;	
	XXXX_PARA_CHK((pSoftApInfo==NULL), XXXX_ERR_FAILED);
	
	struct softap_config config;
	if(configType==COMM_XXXX_CONFIG_TYPE_CURRENT)
		XXXX_ERR_CHK_ERRCODE(wifi_softap_get_config(&config),	ret,	TRUE);
	else if(configType==COMM_XXXX_CONFIG_TYPE_FLASH)
		XXXX_ERR_CHK_ERRCODE(wifi_softap_get_config_default(&config),	ret,	TRUE);
	else
		RETURN(XXXX_ERR_FAILED);
	
	os_memcpy(pSoftApInfo->ssid,			config.ssid,		SAL_XXXX_WIFI_SSID_LEN);
	pSoftApInfo->ssid_len				=	config.ssid_len;
	os_memcpy(pSoftApInfo->password,		config.password,	SAL_XXXX_WIFI_SSID_LEN);
	pSoftApInfo->channel				=	config.channel;
	SAL_XXXX_WIFI_AUTH_XLATE_FROM_CHIP(pSoftApInfo->authMode,	config.authmode,	ret);
	if(ret!=XXXX_ERR_OK)
		RETURN(ret);
	pSoftApInfo->ssid_hide				=	config.ssid_hidden==0 ? DISABLED : ENABLED;
	pSoftApInfo->max_connection_device	=	config.max_connection;
	pSoftApInfo->beacon_interval		=	config.beacon_interval;

	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_wifi_softap_config_set(sal_xxxx_wifi_softAp_config_t *pSoftApInfo, comm_xxxx_config_type_t configType)
{
	int32 ret;	
	XXXX_PARA_CHK((pSoftApInfo==NULL), XXXX_ERR_FAILED);
	XXXX_PARA_CHK((pSoftApInfo->ssid_len>SAL_XXXX_WIFI_SSID_LEN), XXXX_ERR_FAILED);
	XXXX_PARA_CHK((pSoftApInfo->channel<SAL_XXXX_WIFI_SOFT_AP_CHANNEL_MIN || pSoftApInfo->channel>SAL_XXXX_WIFI_SOFT_AP_CHANNEL_MAX), XXXX_ERR_FAILED);
	XXXX_PARA_CHK((pSoftApInfo->ssid_hide>ENABLED), XXXX_ERR_FAILED);
	XXXX_PARA_CHK((pSoftApInfo->max_connection_device>SAL_XXXX_WIFI_SOFT_AP_MAX_CONNECT_NUM), XXXX_ERR_FAILED);
	XXXX_PARA_CHK((pSoftApInfo->beacon_interval<SAL_XXXX_WIFI_SOFT_AP_BEACOM_INTERVAL_MIN || pSoftApInfo->beacon_interval>SAL_XXXX_WIFI_SOFT_AP_BEACOM_INTERVAL_MAX), XXXX_ERR_FAILED);
		

	struct softap_config config;
	os_memcpy(config.ssid,			pSoftApInfo->ssid,			SAL_XXXX_WIFI_SSID_LEN);
	config.ssid_len				=	pSoftApInfo->ssid_len;
	os_memcpy(config.password,		pSoftApInfo->password,		SAL_XXXX_WIFI_SSID_LEN);
	config.channel				=	pSoftApInfo->channel;
	SAL_XXXX_WIFI_AUTH_XLATE_TO_CHIP(pSoftApInfo->authMode,	config.authmode,	ret);
	if(ret!=XXXX_ERR_OK)
		RETURN(ret);
	config.ssid_hidden			=	pSoftApInfo->ssid_hide==ENABLED ? 1 : 0;
	config.max_connection		=	pSoftApInfo->max_connection_device;
	config.beacon_interval		=	pSoftApInfo->beacon_interval;	

	if(configType==COMM_XXXX_CONFIG_TYPE_CURRENT)
		XXXX_ERR_CHK_ERRCODE(wifi_softap_set_config_current(&config),	ret,	TRUE);
	else if(configType==COMM_XXXX_CONFIG_TYPE_FLASH)
		XXXX_ERR_CHK_ERRCODE(wifi_softap_set_config(&config),			ret,	TRUE);
	else
		RETURN(XXXX_ERR_FAILED);

	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR 
sal_xxxx_wifi_softap_stationNum_get(uint32 *pStationNum)
{
	XXXX_PARA_CHK((pStationNum==NULL), XXXX_ERR_FAILED);
	*pStationNum	=	wifi_softap_get_station_num();

	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR 
sal_xxxx_wifi_softap_stationInfo_get(sal_xxxx_wifi_softAp_stationInfo_t *pStationList)
{
	uint32 i=0;
	XXXX_PARA_CHK((pStationList==NULL), XXXX_ERR_FAILED);

	struct station_info * pStaList = wifi_softap_get_station_info();

	while(pStaList!=NULL)
	{
		os_memcpy(pStationList[i].bssid,			pStaList->bssid, 	SAL_XXXX_WIFI_BSSID_LEN);
		UINT32_TO_IPV4_ADDR(pStationList[i].ipAddr, pStaList->ip.addr);
		pStaList	=	pStaList->next.stqe_next;
		i++;
	}

	wifi_softap_free_station_info();
	
	return XXXX_ERR_OK;
}




