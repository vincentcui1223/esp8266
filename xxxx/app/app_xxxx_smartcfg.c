
#include <hal_xxxx_key.h>
#include <sal_xxxx_wifi.h>
#include <sal_xxxx_smartCfg.h>
#include <app_xxxx_smartCfg.h>


LOCAL void ICACHE_FLASH_ATTR
_app_xxxx_smartCfg_start_cb(void)
{
	sal_xxxx_smartCfg_stop();
	sal_xxxx_smartCfg_type_set(SAL_XXXX_SMARTCFG_TYPE_ESP8266_SMART_TOUCH);
	sal_xxxx_wifi_mode_set(SAL_XXXX_WIFI_MODE_STATION, COMM_XXXX_CONFIG_TYPE_CURRENT);
	sal_xxxx_smartCfg_start();
	return;
}

LOCAL void ICACHE_FLASH_ATTR
_app_xxxx_smartCfg_done_cb(sal_xxxx_smartCfg_status_t status, sal_xxxx_smartCfg_done_info_t *pInfo)
{
/*	Sample Code:
	
    switch(status) {
        case SC_STATUS_WAIT:
            os_printf("SC_STATUS_WAIT\n");
            break;
        case SC_STATUS_FIND_CHANNEL:
            os_printf("SC_STATUS_FIND_CHANNEL\n");
            break;
        case SC_STATUS_GETTING_SSID_PSWD:
            os_printf("SC_STATUS_GETTING_SSID_PSWD\n");
			sc_type *type = pdata;
            if (*type == SC_TYPE_ESPTOUCH) {
                os_printf("SC_TYPE:SC_TYPE_ESPTOUCH\n");
            } else {
                os_printf("SC_TYPE:SC_TYPE_AIRKISS\n");
            }
            break;
        case SC_STATUS_LINK:
            os_printf("SC_STATUS_LINK\n");
            struct station_config *sta_conf = pdata;
	
	        wifi_station_set_config(sta_conf);
	        wifi_station_disconnect();
	        wifi_station_connect();
            break;
        case SC_STATUS_LINK_OVER:
            os_printf("SC_STATUS_LINK_OVER\n");
            if (pdata != NULL) {
				//SC_TYPE_ESPTOUCH
                uint8 phone_ip[4] = {0};

                os_memcpy(phone_ip, (uint8*)pdata, 4);
                os_printf("Phone ip: %d.%d.%d.%d\n",phone_ip[0],phone_ip[1],phone_ip[2],phone_ip[3]);
            } else {
            	//SC_TYPE_AIRKISS - support airkiss v2.0
				airkiss_start_discover();
            }
            smartconfig_stop();
            break;
    }
*/
	int32 ret;

	switch(status)	
	{	
		case SAL_XXXX_SMARTCFG_STATUS_WAITE:	
			DBG_PRINT(("status is WAITE\n"), DEB_PRINTF_LEVEL_COMM);
			break;
		case SAL_XXXX_SMARTCFG_STATUS_FIND_CHANNEL:
			DBG_PRINT(("status is FIND_CHANNEL\n"), DEB_PRINTF_LEVEL_COMM);
			break;
		case SAL_XXXX_SMARTCFG_STATUS_GETTING_SSID_PSWD:	
			DBG_PRINT(("status is GETTING_SSID_PSWD\n"), DEB_PRINTF_LEVEL_COMM);
			DBG_PRINT(("smartCfg_type=%d\n", pInfo->smartCfg_type), DEB_PRINTF_LEVEL_COMM);
			break;
		case SAL_XXXX_SMARTCFG_STATUS_LINK: 		
			DBG_PRINT(("status is LINK\n"), DEB_PRINTF_LEVEL_COMM);
			DBG_PRINT(("smartCfg_ssid=%s\n", pInfo->stationCfg.ssid), DEB_PRINTF_LEVEL_COMM);
			DBG_PRINT(("smartCfg_pwd=%s\n", pInfo->stationCfg.password), DEB_PRINTF_LEVEL_COMM);	
		    XXXX_ERR_CHK_VOID_RETURN(sal_xxxx_wifi_stationConfig_set(&pInfo->stationCfg), ret);
	        XXXX_ERR_CHK_VOID_RETURN(sal_xxxx_wifi_station_disconnect(), ret);
	        XXXX_ERR_CHK_VOID_RETURN(sal_xxxx_wifi_station_connect(), ret);
			break;
		case SAL_XXXX_SMARTCFG_STATUS_LINK_OVER: 
			DBG_PRINT(("status is LINK_OVER\n"), DEB_PRINTF_LEVEL_COMM);
			DBG_PRINT(("smartCfg_ipAddr=%d.%d.%d.%d\n", pInfo->ipv4_addr.octet[0], pInfo->ipv4_addr.octet[1], pInfo->ipv4_addr.octet[2], pInfo->ipv4_addr.octet[3]), DEB_PRINTF_LEVEL_COMM);	
/*
	Sample Code:
			if (pdata != NULL) {
				//SC_TYPE_ESPTOUCH
				uint8 phone_ip[4] = {0};

				os_memcpy(phone_ip, (uint8*)pdata, 4);
				os_printf("Phone ip: %d.%d.%d.%d\n",phone_ip[0],phone_ip[1],phone_ip[2],phone_ip[3]);
			} else {
				//SC_TYPE_AIRKISS - support airkiss v2.0
				airkiss_start_discover();
			}
			smartconfig_stop();
*/	
			/*TBD*/
			XXXX_ERR_CHK_VOID_RETURN(sal_xxxx_smartCfg_stop(), ret);
			break;
		default:	
			VOID_RETURN();	
	}	

	return;
}



int32 ICACHE_FLASH_ATTR
app_xxxx_smartCfg_init(void)
{
	int32 ret;
	XXXX_ERR_CHK(sal_xxxx_smartCfg_done_cb_register(_app_xxxx_smartCfg_done_cb), ret);
	XXXX_ERR_CHK(hal_xxxx_key_press_cb_register(HAL_XXXX_KEY_RESET_IDX, HAL_XXXX_KEY_PRESS_TYPE_LONG, _app_xxxx_smartCfg_start_cb), ret);

	return XXXX_ERR_OK;
}


