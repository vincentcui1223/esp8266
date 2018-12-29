
#include <sal_xxxx_smartCfg.h>

LOCAL sal_xxxx_smartCfg_type_t 	smartCfg_type = SAL_XXXX_SMARTCFG_TYPE_END;
sal_xxxx_smartCfg_done_info_t 	smartCfg_done_info;

XXXX_FUNC_SAL_SMARTCFG_DONE_CB smartCfg_done_cb;

LOCAL void ICACHE_FLASH_ATTR
_sal_xxxx_smartCfg_done_cb(sc_status status, void *pdata)
{
	int32 ret;
	sal_xxxx_smartCfg_status_t salStatus;

	sc_type *pChipType;
	struct station_config *pSta_conf;
	uint8 	ipv4_addr[IPV4_ADDR_LEN];
	
	switch(status)
	{
        case SC_STATUS_WAIT:
            break;
        case SC_STATUS_FIND_CHANNEL:
            break;
		case SC_STATUS_GETTING_SSID_PSWD:
			pChipType = (sc_type*)pdata;
			SAL_XXXX_SMARTCFG_TYPE_XLATE_TO_CHIP(smartCfg_done_info.smartCfg_type, *pChipType, ret);
			if(ret!=XXXX_ERR_OK)
				VOID_RETURN();	
			break;
		case SC_STATUS_LINK:
			pSta_conf = (struct station_config*)pdata;
			if(pSta_conf==NULL)
				VOID_RETURN();
			os_memcpy(smartCfg_done_info.stationCfg.ssid, 		pSta_conf->ssid, SAL_XXXX_WIFI_SSID_LEN);
			os_memcpy(smartCfg_done_info.stationCfg.password, 	pSta_conf->password, SAL_XXXX_WIFI_SSID_LEN);
			smartCfg_done_info.stationCfg.bssid_set			=	pSta_conf->bssid_set;
			os_memcpy(smartCfg_done_info.stationCfg.bssid, 	pSta_conf->bssid, SAL_XXXX_WIFI_BSSID_LEN);
			smartCfg_done_info.stationCfg.threshold.rssi	=	pSta_conf->threshold.rssi;
			SAL_XXXX_WIFI_AUTH_XLATE_FROM_CHIP(smartCfg_done_info.stationCfg.threshold.auth,pSta_conf->threshold.authmode, ret);
			if(ret!=XXXX_ERR_OK)
				VOID_RETURN();	
			break;	
		case SC_STATUS_LINK_OVER:
			if(pdata!=NULL)
			{
				os_memcpy(ipv4_addr, (uint8*)pdata, IPV4_ADDR_LEN);
				os_memcpy(smartCfg_done_info.ipv4_addr.octet, ipv4_addr, IPV4_ADDR_LEN);
			}
			else
				os_memset(smartCfg_done_info.ipv4_addr.octet, 0, IPV4_ADDR_LEN);
			break;
		default:
			VOID_RETURN();
	}
	
	SAL_XXXX_SMARTCFG_STATUS_XLATE_FROM_CHIP(salStatus, status, ret);
	if(ret!=XXXX_ERR_OK)
		VOID_RETURN();	
	
	if(smartCfg_done_cb!=NULL)
		smartCfg_done_cb(salStatus, &smartCfg_done_info);

	return;
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_smartCfg_type_set(sal_xxxx_smartCfg_type_t type)
{
	int32 ret;
	XXXX_PARA_CHK((type>=SAL_XXXX_SMARTCFG_TYPE_END), XXXX_ERR_FAILED);

	sc_type chipType;
	SAL_XXXX_SMARTCFG_TYPE_XLATE_TO_CHIP(type, chipType, ret);
	if(ret!=XXXX_ERR_OK)
		RETURN(ret);
	ret=smartconfig_set_type(chipType);
	if(ret==FALSE)
		RETURN(XXXX_ERR_FAILED);	
	smartCfg_type = type;
	
	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_smartCfg_type_get(sal_xxxx_smartCfg_type_t *pType)
{
	*pType = smartCfg_type;
	
	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_smartCfg_start(void)
{
	int32 ret;

	os_memset(&smartCfg_done_info, 0, sizeof(sal_xxxx_smartCfg_done_info_t));
	ret	=smartconfig_start(_sal_xxxx_smartCfg_done_cb);	
	if(ret==FALSE)
		RETURN(XXXX_ERR_FAILED);

	return XXXX_ERR_OK;
}


int32 ICACHE_FLASH_ATTR
sal_xxxx_smartCfg_stop(void)
{
	int32 ret;
	
	ret	=smartconfig_stop();	
	if(ret==FALSE)
		RETURN(XXXX_ERR_FAILED);

	return XXXX_ERR_OK;
}


int32 ICACHE_FLASH_ATTR
sal_xxxx_smartCfg_done_cb_register(XXXX_FUNC_SAL_SMARTCFG_DONE_CB cb_func)
{
	smartCfg_done_cb = cb_func;
	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_smartCfg_done_cb_unregister(void)
{
	smartCfg_done_cb = NULL;
	return XXXX_ERR_OK;
}



