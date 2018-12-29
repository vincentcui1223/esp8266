#ifndef __SAL_XXXX_TO_SDK_H__
#define __SAL_XXXX_TO_SDK_H__

#define SAL_XXXX_WIFI_MODE_XLATE_TO_CHIP(salMode, chipMode, ret) \
		do{	\
			ret = XXXX_ERR_OK;	\
			switch(salMode)	\
			{	\
				case SAL_XXXX_WIFI_MODE_STATION:			\
					chipMode	=	STATION_MODE; 			break;	\
				case SAL_XXXX_WIFI_MODE_SOFT_AP:			\
					chipMode	=	SOFTAP_MODE; 			break;	\
				case SAL_XXXX_WIFI_MODE_STATION_AND_AP:	\
					chipMode	=	STATIONAP_MODE; 		break;	\
				default:	\
					ret = XXXX_ERR_FAILED;	\
			}	\
		}while(0)
#define SAL_XXXX_WIFI_MODE_XLATE_FROM_CHIP(salMode, chipMode, ret) \
		do{	\
			ret = XXXX_ERR_OK;	\
			switch(chipMode)	\
			{	\
				case STATION_MODE:	\
					salMode	=	SAL_XXXX_WIFI_MODE_STATION; 			break;	\
				case SOFTAP_MODE:			\
					salMode	=	SAL_XXXX_WIFI_MODE_SOFT_AP; 			break;	\
				case STATIONAP_MODE:	\
					salMode	=	SAL_XXXX_WIFI_MODE_STATION_AND_AP; 	break;	\
				default:	\
					ret = XXXX_ERR_FAILED;	\
			}	\
		}while(0)		

#define SAL_XXXX_WIFI_AUTH_XLATE_TO_CHIP(salAuth, chipAuth, ret) \
		do{ \
			ret = XXXX_ERR_OK;	\
			switch(salAuth) \
			{	\
				case SAL_XXXX_WIFI_AUTH_OPEN:			\
					chipAuth	=	AUTH_OPEN;			break;	\
				case SAL_XXXX_WIFI_AUTH_WEP:			\
					chipAuth	=	AUTH_WEP;			break;	\
				case SAL_XXXX_WIFI_AUTH_WPA_PSK:	\
					chipAuth	=	AUTH_WPA_PSK;		break;	\
				case SAL_XXXX_WIFI_AUTH_WPA2_PSK:			\
					chipAuth	=	AUTH_WPA2_PSK;			break;	\
				case SAL_XXXX_WIFI_AUTH_WPA_WPA2_PSK:	\
					chipAuth	=	AUTH_WPA_WPA2_PSK;		break;	\
				default:	\
					ret = XXXX_ERR_FAILED;	\
			}	\
		}while(0)
#define SAL_XXXX_WIFI_AUTH_XLATE_FROM_CHIP(salAuth, chipAuth, ret) \
		do{ \
			ret = XXXX_ERR_OK;	\
			switch(chipAuth) \
			{	\
				case AUTH_OPEN: 		\
					salAuth =	SAL_XXXX_WIFI_AUTH_OPEN;		break;	\
				case AUTH_WEP:			\
					salAuth =	SAL_XXXX_WIFI_AUTH_WEP; 		break;	\
				case AUTH_WPA_PSK:	\
					salAuth =	SAL_XXXX_WIFI_AUTH_WPA_PSK; 	break;	\
				case AUTH_WPA2_PSK: 		\
					salAuth =	SAL_XXXX_WIFI_AUTH_WPA2_PSK;	break;	\
				case AUTH_WPA_WPA2_PSK: \
					salAuth =	SAL_XXXX_WIFI_AUTH_WPA_WPA2_PSK;break;	\
				default:	\
					ret = XXXX_ERR_FAILED;	\
			}	\
		}while(0)

#define SAL_XXXX_WIFI_CONNECT_STATUS_XLATE_FROM_CHIP(salStatus, chipStatus, ret) \
		do{ \
			ret = XXXX_ERR_OK;	\
			switch(chipStatus) \
			{	\
				case STATION_IDLE:		\
					salStatus = SAL_XXXX_WIFI_STATION_CONNECT_STATUS_IDLE;		break;	\
				case STATION_CONNECTING:			\
					salStatus = SAL_XXXX_WIFI_STATION_CONNECT_STATUS_CONNECTING;		break;	\
				case STATION_WRONG_PASSWORD:	\
					salStatus = SAL_XXXX_WIFI_STATION_CONNECT_STATUS_WRONG_PASSWORD;	break;	\
				case STATION_NO_AP_FOUND:		\
					salStatus = SAL_XXXX_WIFI_STATION_CONNECT_STATUS_NO_AP_FOUND;	break;	\
				case STATION_CONNECT_FAIL: \
					salStatus = SAL_XXXX_WIFI_STATION_CONNECT_STATUS_CONNECT_FAIL;break;	\
				case STATION_GOT_IP: \
					salStatus = SAL_XXXX_WIFI_STATION_CONNECT_STATUS_GOT_IP;break;	\
				default:	\
					ret = XXXX_ERR_FAILED;	\
			}	\
		}while(0)
#define SAL_XXXX_WIFI_EVENT_XLATE_FROM_CHIP(salEvent, chipEvent, ret) \
		do{ \
			ret = XXXX_ERR_OK;	\
			switch(chipEvent) \
			{	\
				case EVENT_STAMODE_CONNECTED:		\
					salEvent =	SAL_XXXX_WIFI_EVENT_STAMODE_CONNECTED;		break;	\
				case EVENT_STAMODE_DISCONNECTED:			\
					salEvent =	SAL_XXXX_WIFI_EVENT_STAMODE_DISCONNECTED;		break;	\
				case EVENT_STAMODE_AUTHMODE_CHANGE: \
					salEvent =	SAL_XXXX_WIFI_EVENT_STAMODE_AUTHMODE_CHANGE;	break;	\
				case EVENT_STAMODE_GOT_IP:		\
					salEvent =	SAL_XXXX_WIFI_EVENT_STAMODE_GOT_IP; break;	\
				case EVENT_STAMODE_DHCP_TIMEOUT: \
					salEvent =	SAL_XXXX_WIFI_EVENT_STAMODE_DHCP_TIMEOUT;	break;	\
				case EVENT_SOFTAPMODE_STACONNECTED: \
					salEvent = SAL_XXXX_WIFI_EVENT_SOFTAPMODE_STACONNECTED; break;	\
				case EVENT_SOFTAPMODE_STADISCONNECTED:	\
					salEvent =	SAL_XXXX_WIFI_EVENT_SOFTAPMODE_STADISCONNECTED; break;	\
				case EVENT_SOFTAPMODE_PROBEREQRECVED:		\
					salEvent =	SAL_XXXX_WIFI_EVENT_SOFTAPMODE_PROBEREQRECVED; break;	\
				case EVENT_OPMODE_CHANGED: \
					salEvent =	SAL_XXXX_WIFI_EVENT_OPMODE_CHANGED; break;	\
				case EVENT_SOFTAPMODE_DISTRIBUTE_STA_IP: \
					salEvent = SAL_XXXX_WIFI_EVENT_SOFTAPMODE_DISTRIBUTE_STA_IP; break; \
				default:	\
					ret = XXXX_ERR_FAILED;	\
			}	\
		}while(0)
#define SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_XLATE_FROM_CHIP(salEvent, chipEvent, ret) \
		do{ \
			ret = XXXX_ERR_OK;	\
			switch(chipEvent) \
			{	\
				case REASON_UNSPECIFIED:		\
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_UNSPECIFIED;		break;	\
				case REASON_AUTH_EXPIRE:			\
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_AUTH_EXPIRE;		break;	\
				case REASON_AUTH_LEAVE: \
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_AUTH_LEAVE;	break;	\
				case REASON_ASSOC_EXPIRE:		\
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_ASSOC_EXPIRE; break;	\
				case REASON_ASSOC_TOOMANY: \
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_ASSOC_TOOMANY;	break;	\
				case REASON_NOT_AUTHED: \
					salEvent = 	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_NOT_AUTHED; break;	\
				case REASON_NOT_ASSOCED:	\
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_NOT_ASSOCED; break;	\
				case REASON_ASSOC_LEAVE:		\
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_ASSOC_LEAVE; break;	\
				case REASON_ASSOC_NOT_AUTHED: \
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_ASSOC_NOT_AUTHED; break;	\
				case REASON_DISASSOC_PWRCAP_BAD: \
					salEvent = 	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_DISASSOC_PWRCAP_BAD; break; \
				case REASON_DISASSOC_SUPCHAN_BAD:		\
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_DISASSOC_SUPCHAN_BAD;		break;	\
				case REASON_IE_INVALID:			\
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_IE_INVALID;		break;	\
				case REASON_MIC_FAILURE: \
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_MIC_FAILURE;	break;	\
				case REASON_4WAY_HANDSHAKE_TIMEOUT:		\
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_4WAY_HANDSHAKE_TIMEOUT; break;	\
				case REASON_GROUP_KEY_UPDATE_TIMEOUT: \
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_GROUP_KEY_UPDATE_TIMEOUT;	break;	\
				case REASON_IE_IN_4WAY_DIFFERS: \
					salEvent = 	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_IE_IN_4WAY_DIFFERS; break;	\
				case REASON_GROUP_CIPHER_INVALID:	\
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_GROUP_CIPHER_INVALID; break;	\
				case REASON_PAIRWISE_CIPHER_INVALID:		\
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_PAIRWISE_CIPHER_INVALID; break;	\
				case REASON_AKMP_INVALID: \
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_AKMP_INVALID; break;	\
				case REASON_UNSUPP_RSN_IE_VERSION: \
					salEvent = 	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_UNSUPP_RSN_IE_VERSION; break; \
				case REASON_INVALID_RSN_IE_CAP: \
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_INVALID_RSN_IE_CAP;	break;	\
				case REASON_802_1X_AUTH_FAILED: \
					salEvent =  SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_802_1X_AUTH_FAILED; break;	\
				case REASON_CIPHER_SUITE_REJECTED:	\
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_CIPHER_SUITE_REJECTED; break;	\
				case REASON_BEACON_TIMEOUT:		\
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_BEACON_TIMEOUT; break;	\
				case REASON_NO_AP_FOUND: \
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_NO_AP_FOUND; break;	\
				case REASON_AUTH_FAIL: \
					salEvent = SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_AUTH_FAIL; break; \
				case REASON_ASSOC_FAIL:		\
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_ASSOC_FAIL; break; \
				case REASON_HANDSHAKE_TIMEOUT: \
					salEvent =	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_HANDSHAKE_TIMEOUT; break;	\
				default:	\
					ret = XXXX_ERR_FAILED;	\
			}	\
		}while(0)
					
#define SAL_XXXX_TCP_CONNECT_ERR_XLATE_FROM_CHIP(salErr, chipErr, ret) \
		do{ \
			ret = XXXX_ERR_OK;	\
			switch(chipErr)	\
			{	\
				case ESPCONN_TIMEOUT:	\
					salErr =	SAL_XXXX_TCP_DIS_CONNECT_ERR_TIMEOUT; 		break;	\
				case ESPCONN_ABRT:			\
					salErr =	SAL_XXXX_TCP_DIS_CONNECT_ERR_ABRT; 			break;	\
				case ESPCONN_RST:	\
					salErr =	SAL_XXXX_TCP_DIS_CONNECT_ERR_RST;			break;	\
				case ESPCONN_CLSD:	\
					salErr =	SAL_XXXX_TCP_DIS_CONNECT_ERR_CLSD; 			break;	\
				case ESPCONN_CONN:			\
					salErr =	SAL_XXXX_TCP_DIS_CONNECT_ERR_CONN; 			break;	\
				case ESPCONN_HANDSHAKE:	\
					salErr =	SAL_XXXX_TCP_DIS_CONNECT_ERR_HANDSHAKE;		break;	\
				case ESPCONN_PROTO_MSG:	\
					salErr =	SAL_XXXX_TCP_DIS_CONNECT_ERR_PROTO_MSG;		break;	\
				default:	\
					ret = XXXX_ERR_FAILED;	\
			}	\
		}while(0)	

#endif

