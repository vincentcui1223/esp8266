#ifndef __SAL_XXXX_SMARTCFG_H__
#define __SAL_XXXX_SMARTCFG_H__

#include <xxxx_comm.h>

#include <sal_xxxx_wifi.h>

typedef enum sal_xxxx_smartCfg_type_e
{
	SAL_XXXX_SMARTCFG_TYPE_ESP8266_SMART_TOUCH,
	SAL_XXXX_SMARTCFG_TYPE_AIR_KISS,	
	SAL_XXXX_SMARTCFG_TYPE_ESP8266_SMART_TOUCH_AND_AIR_KISS,
	SAL_XXXX_SMARTCFG_TYPE_END
}sal_xxxx_smartCfg_type_t;

#define SAL_XXXX_SMARTCFG_TYPE_XLATE_TO_CHIP(salType, chipType, ret) \
	do{	\
		ret = XXXX_ERR_OK;	\
		switch(salType)	\
		{	\
			case SAL_XXXX_SMARTCFG_TYPE_ESP8266_SMART_TOUCH:	\
				chipType	=	SC_TYPE_ESPTOUCH; 			break;	\
			case SAL_XXXX_SMARTCFG_TYPE_AIR_KISS:			\
				chipType	=	SC_TYPE_AIRKISS; 			break;	\
			case SAL_XXXX_SMARTCFG_TYPE_ESP8266_SMART_TOUCH_AND_AIR_KISS:	\
				chipType	=	SC_TYPE_ESPTOUCH_AIRKISS; 	break;	\
			default:	\
				ret = XXXX_ERR_FAILED;	\
		}	\
	}while(0)

#define SAL_XXXX_SMARTCFG_TYPE_XLATE_FROM_CHIP(salType, chipType, ret) \
	do{	\
		ret = XXXX_ERR_OK;	\
		switch(chipType)	\
		{	\
			case SC_TYPE_ESPTOUCH:	\
				salType	=	SAL_XXXX_SMARTCFG_TYPE_ESP8266_SMART_TOUCH; 				break;	\
			case SC_TYPE_AIRKISS:			\
				salType	=	SAL_XXXX_SMARTCFG_TYPE_AIR_KISS; 						break;	\
			case SC_TYPE_ESPTOUCH_AIRKISS:	\
				salType	=	SAL_XXXX_SMARTCFG_TYPE_ESP8266_SMART_TOUCH_AND_AIR_KISS; break;	\
			default:	\
				ret = XXXX_ERR_FAILED;	\
		}	\
	}while(0)		

typedef enum sal_xxxx_smartCfg_status_e
{
	SAL_XXXX_SMARTCFG_STATUS_WAITE,
	SAL_XXXX_SMARTCFG_STATUS_FIND_CHANNEL,
	SAL_XXXX_SMARTCFG_STATUS_GETTING_SSID_PSWD,
	SAL_XXXX_SMARTCFG_STATUS_LINK,
	SAL_XXXX_SMARTCFG_STATUS_LINK_OVER,
	SAL_XXXX_SMARTCFG_STATUS_END
}sal_xxxx_smartCfg_status_t;

#define SAL_XXXX_SMARTCFG_STATUS_XLATE_TO_CHIP(salStatus, chipStatus, ret) \
	do{	\
		ret = XXXX_ERR_OK;	\
		switch(salStatus)	\
		{	\
			case SAL_XXXX_SMARTCFG_STATUS_WAITE:	\
				chipStatus	=	SC_STATUS_WAIT; 					break;	\
			case SAL_XXXX_SMARTCFG_STATUS_FIND_CHANNEL:			\
				chipStatus	=	SC_STATUS_FIND_CHANNEL; 			break;	\
			case SAL_XXXX_SMARTCFG_STATUS_GETTING_SSID_PSWD:	\
				chipStatus	=	SC_STATUS_GETTING_SSID_PSWD; 		break;	\
			case SAL_XXXX_SMARTCFG_STATUS_LINK:			\
				chipStatus	=	SC_STATUS_LINK;						break;	\
			case SAL_XXXX_SMARTCFG_STATUS_LINK_OVER: \
				chipStatus	=	SC_STATUS_LINK_OVER;				break;	\
			default:	\
				ret = XXXX_ERR_FAILED;	\
		}	\
	}while(0)

#define SAL_XXXX_SMARTCFG_STATUS_XLATE_FROM_CHIP(salStatus, chipStatus, ret) \
	do{	\
		ret = XXXX_ERR_OK;	\
		switch(chipStatus)	\
		{	\
			case SC_STATUS_WAIT:	\
				salStatus	=	SAL_XXXX_SMARTCFG_STATUS_WAITE; 			break;	\
			case SC_STATUS_FIND_CHANNEL:			\
				salStatus	=	SAL_XXXX_SMARTCFG_STATUS_FIND_CHANNEL; 		break;	\
			case SC_STATUS_GETTING_SSID_PSWD:	\
				salStatus	=	SAL_XXXX_SMARTCFG_STATUS_GETTING_SSID_PSWD; break;	\
			case SC_STATUS_LINK:			\
				salStatus	=	SAL_XXXX_SMARTCFG_STATUS_LINK; 				break;	\
			case SC_STATUS_LINK_OVER:	\
				salStatus	=	SAL_XXXX_SMARTCFG_STATUS_LINK_OVER; 		break;	\
			default:	\
				ret = XXXX_ERR_FAILED;	\
		}	\
	}while(0)

typedef struct sal_xxxx_smartCfg_done_info_s
{
	sal_xxxx_smartCfg_type_t 		smartCfg_type;
	sal_xxxx_wifi_station_config_t	stationCfg;
	xxxx_ipv4_addr_t				ipv4_addr;
}sal_xxxx_smartCfg_done_info_t;

typedef void (* smartCfg_done_cb_func)(sal_xxxx_smartCfg_status_t status, sal_xxxx_smartCfg_done_info_t *pInfo);
#define XXXX_FUNC_SAL_SMARTCFG_DONE_CB smartCfg_done_cb_func
			
extern int32 sal_xxxx_smartCfg_type_set(sal_xxxx_smartCfg_type_t type);
extern int32 sal_xxxx_smartCfg_type_get(sal_xxxx_smartCfg_type_t *pType);

extern int32 sal_xxxx_smartCfg_start(void);
extern int32 sal_xxxx_smartCfg_stop(void);

extern int32 sal_xxxx_smartCfg_done_cb_register(XXXX_FUNC_SAL_SMARTCFG_DONE_CB cb_func);
extern int32 sal_xxxx_smartCfg_done_cb_unregister(void);


#endif

