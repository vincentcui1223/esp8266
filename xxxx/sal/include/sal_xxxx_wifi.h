#ifndef __SAL_XXXX_WIFI_H__
#define __SAL_XXXX_WIFI_H__

#include <xxxx_comm.h>

typedef enum sal_xxxx_wifi_interface_e
{
	SAL_XXXX_WIFI_INTERFACE_STATION = (0x1<<0),
	SAL_XXXX_WIFI_INTERFACE_SOFT_AP = (0x1<<1),
	SAL_XXXX_WIFI_INTERFACE_STATION_AND_SOFT_AP = SAL_XXXX_WIFI_INTERFACE_STATION|SAL_XXXX_WIFI_INTERFACE_SOFT_AP,
	SAL_XXXX_WIFI_INTERFACE_END
}sal_xxxx_wifi_interface_t;

typedef enum sal_xxxx_wifi_mode_e
{
	SAL_XXXX_WIFI_MODE_STATION,
	SAL_XXXX_WIFI_MODE_SOFT_AP,
	SAL_XXXX_WIFI_MODE_STATION_AND_AP,
	SAL_XXXX_WIFI_MODE_END
}sal_xxxx_wifi_mode_t;

typedef enum sal_xxxx_wifi_auth_e
{
	SAL_XXXX_WIFI_AUTH_OPEN			= 0,
	SAL_XXXX_WIFI_AUTH_WEP,
	SAL_XXXX_WIFI_AUTH_WPA_PSK,
	SAL_XXXX_WIFI_AUTH_WPA2_PSK,
	SAL_XXXX_WIFI_AUTH_WPA_WPA2_PSK,
	SAL_XXXX_WIFI_AUTH_END
}sal_xxxx_wifi_auth_t;

typedef struct sal_xxxx_wifi_fast_scan_threshold_s
{
	uint32 rssi;
	sal_xxxx_wifi_auth_t auth;
}sal_xxxx_wifi_fast_scan_threshold_t;


#define SAL_XXXX_WIFI_SSID_LEN 	32
#define SAL_XXXX_WIFI_PWD_LEN 	64
#define SAL_XXXX_WIFI_BSSID_LEN 6
typedef struct sal_xxxx_wifi_station_config_s
{
    char 	ssid[SAL_XXXX_WIFI_SSID_LEN];
    char 	password[SAL_XXXX_WIFI_PWD_LEN];
    uint32 	bssid_set;
    char 	bssid[SAL_XXXX_WIFI_BSSID_LEN];	
	sal_xxxx_wifi_fast_scan_threshold_t threshold;
}sal_xxxx_wifi_station_config_t;

typedef enum sal_xxxx_wifi_station_connect_status_e
{
	SAL_XXXX_WIFI_STATION_CONNECT_STATUS_IDLE,
	SAL_XXXX_WIFI_STATION_CONNECT_STATUS_CONNECTING,
	SAL_XXXX_WIFI_STATION_CONNECT_STATUS_WRONG_PASSWORD,
	SAL_XXXX_WIFI_STATION_CONNECT_STATUS_NO_AP_FOUND,
	SAL_XXXX_WIFI_STATION_CONNECT_STATUS_CONNECT_FAIL,
	SAL_XXXX_WIFI_STATION_CONNECT_STATUS_GOT_IP,
	SAL_XXXX_WIFI_STATION_CONNECT_STATUS_END
}sal_xxxx_wifi_station_connect_status_t;

typedef enum sal_xxxx_wifi_event_e
{
	SAL_XXXX_WIFI_EVENT_STAMODE_CONNECTED = 0,
	SAL_XXXX_WIFI_EVENT_STAMODE_DISCONNECTED,
	SAL_XXXX_WIFI_EVENT_STAMODE_AUTHMODE_CHANGE,
	SAL_XXXX_WIFI_EVENT_STAMODE_GOT_IP,
	SAL_XXXX_WIFI_EVENT_STAMODE_DHCP_TIMEOUT,
	SAL_XXXX_WIFI_EVENT_SOFTAPMODE_STACONNECTED,
	SAL_XXXX_WIFI_EVENT_SOFTAPMODE_STADISCONNECTED,
	SAL_XXXX_WIFI_EVENT_SOFTAPMODE_PROBEREQRECVED,
	SAL_XXXX_WIFI_EVENT_OPMODE_CHANGED,
	SAL_XXXX_WIFI_EVENT_SOFTAPMODE_DISTRIBUTE_STA_IP,
	SAL_XXXX_WIFI_EVENT_END
}sal_xxxx_wifi_event_t;

typedef struct sal_xxxx_wifi_eventInfo_StaMode_connected_s
{
    uint8 	ssid[SAL_XXXX_WIFI_SSID_LEN];
    uint32 	ssid_len;
    uint8 	bssid[SAL_XXXX_WIFI_BSSID_LEN];
    uint32 	channel;	
}sal_xxxx_wifi_eventInfo_StaMode_connected_t;

typedef enum sal_xxxx_wifi_staMode_disconnect_reason_e
{
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_UNSPECIFIED,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_AUTH_EXPIRE,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_AUTH_LEAVE,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_ASSOC_EXPIRE,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_ASSOC_TOOMANY,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_NOT_AUTHED,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_NOT_ASSOCED,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_ASSOC_LEAVE,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_ASSOC_NOT_AUTHED,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_DISASSOC_PWRCAP_BAD,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_DISASSOC_SUPCHAN_BAD,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_IE_INVALID,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_MIC_FAILURE,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_4WAY_HANDSHAKE_TIMEOUT,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_GROUP_KEY_UPDATE_TIMEOUT,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_IE_IN_4WAY_DIFFERS,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_GROUP_CIPHER_INVALID,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_PAIRWISE_CIPHER_INVALID,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_AKMP_INVALID,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_UNSUPP_RSN_IE_VERSION,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_INVALID_RSN_IE_CAP,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_802_1X_AUTH_FAILED,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_CIPHER_SUITE_REJECTED,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_BEACON_TIMEOUT,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_NO_AP_FOUND,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_AUTH_FAIL,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_ASSOC_FAIL,
    SAL_XXXX_WIFI_STA_MODE_DISCONNECT_REASON_HANDSHAKE_TIMEOUT,
	SAL_XXXX_WIFI_STA_MODE_DISCONNECT_END
}sal_xxxx_wifi_staMode_disconnect_reason_t;

typedef struct sal_xxxx_wifi_eventInfo_StaMode_disConnected_s
{
    uint8 										ssid[SAL_XXXX_WIFI_SSID_LEN];
    uint32 										ssid_len;
    uint8 										bssid[SAL_XXXX_WIFI_BSSID_LEN];
    sal_xxxx_wifi_staMode_disconnect_reason_t 	reason;	
}sal_xxxx_wifi_eventInfo_StaMode_disConnected_t;

typedef struct sal_xxxx_wifi_eventInfo_StaMode_authChange_s
{
    sal_xxxx_wifi_auth_t old_mode;
    sal_xxxx_wifi_auth_t new_mode;
} sal_xxxx_wifi_eventInfo_StaMode_authChange_t;

typedef struct sal_xxxx_wifi_eventInfo_StaMode_gotIp_s
{
    xxxx_ipv4_addr_t	stationIp;
	xxxx_ipv4_addr_t	stationIpMask;
	xxxx_ipv4_addr_t	gateWayIp;
} sal_xxxx_wifi_eventInfo_StaMode_gotIp_t;

typedef struct sal_xxxx_wifi_eventInfo_SoftAPMode_StaConnected_s
{
    xxxx_mac_addr_t		station_mac;
	uint32 				aid;	/*TBD, do not know the means*/
} sal_xxxx_wifi_eventInfo_SoftAPMode_StaConnected_t;

typedef struct sal_xxxx_wifi_eventInfo_SoftAPMode_Distribute_Sta_IP_s
{
    xxxx_mac_addr_t		station_mac;
	xxxx_ipv4_addr_t	stationIp;
	uint32 				aid;	/*TBD, do not know the means*/
} sal_xxxx_wifi_eventInfo_SoftAPMode_Distribute_Sta_IP_t;

typedef struct sal_xxxx_wifi_eventInfo_SoftAPMode_StaDisConnected_s
{
    xxxx_mac_addr_t		station_mac;
	uint32 				aid;	/*TBD, do not know the means*/
} sal_xxxx_wifi_eventInfo_SoftAPMode_StaDisConnected_t;

typedef struct sal_xxxx_wifi_eventInfo_SoftAPMode_ProbeReqRecved_s
{
	uint32 				rssi;
    xxxx_mac_addr_t		station_mac;
} sal_xxxx_wifi_eventInfo_SoftAPMode_ProbeReqRecved_t;

typedef struct sal_xxxx_wifi_eventInfo_opModeChange_s
{
    sal_xxxx_wifi_mode_t old_opmode;
    sal_xxxx_wifi_mode_t new_opmode;
} sal_xxxx_wifi_eventInfo_opModeChange_t;

typedef struct sal_xxxx_wifi_eventInfo_s
{
	union{
	    sal_xxxx_wifi_eventInfo_StaMode_connected_t				connected;
	    sal_xxxx_wifi_eventInfo_StaMode_disConnected_t   		disconnected;
	    sal_xxxx_wifi_eventInfo_StaMode_authChange_t        	auth_change;
	    sal_xxxx_wifi_eventInfo_StaMode_gotIp_t             	got_ip;
	    sal_xxxx_wifi_eventInfo_SoftAPMode_StaConnected_t   	sta_connected;
	    sal_xxxx_wifi_eventInfo_SoftAPMode_Distribute_Sta_IP_t	distribute_sta_ip;
	    sal_xxxx_wifi_eventInfo_SoftAPMode_StaDisConnected_t    sta_disconnected;
	    sal_xxxx_wifi_eventInfo_SoftAPMode_ProbeReqRecved_t   	ap_probeReqRecved;
	    sal_xxxx_wifi_eventInfo_opModeChange_t               	opmode_changed;
	};
}sal_xxxx_wifi_eventInfo_t;

typedef struct sal_xxxx_wifi_ipInfo_s
{
    xxxx_ipv4_addr_t	ip;
	xxxx_ipv4_addr_t	ipMask;
	xxxx_ipv4_addr_t	gateWayIp;
} sal_xxxx_wifi_ipInfo_t;

#define SAL_XXXX_WIFI_SOFT_AP_MAX_CONNECT_NUM 			4
#define SAL_XXXX_WIFI_SOFT_AP_BEACOM_INTERVAL_MIN		100
#define SAL_XXXX_WIFI_SOFT_AP_BEACOM_INTERVAL_DEFAULT	100
#define SAL_XXXX_WIFI_SOFT_AP_BEACOM_INTERVAL_MAX		60000


#define SAL_XXXX_WIFI_SOFT_AP_CHANNEL_MIN				1
#define SAL_XXXX_WIFI_SOFT_AP_CHANNEL_MAX				13


typedef struct sal_xxxx_wifi_softAp_config_s
{
    char 	ssid[SAL_XXXX_WIFI_SSID_LEN];
	uint32	ssid_len;
    char 	password[SAL_XXXX_WIFI_PWD_LEN];

	uint32 	channel;
	sal_xxxx_wifi_auth_t	authMode;
	comm_xxxx_enable_t		ssid_hide;

	uint32	max_connection_device;
	uint32 	beacon_interval;		/*Note: support 100 ~ 60000 ms, default 100*/
}sal_xxxx_wifi_softAp_config_t;

typedef struct sal_xxxx_wifi_softAp_stationInfo_s
{
	char 				bssid[SAL_XXXX_WIFI_BSSID_LEN];
	xxxx_ipv4_addr_t	ipAddr;
}sal_xxxx_wifi_softAp_stationInfo_t;


typedef int32 (*sal_xxxx_wifi_event_callback)(sal_xxxx_wifi_event_t event, sal_xxxx_wifi_eventInfo_t *pEventInfo);
#define SAL_XXXX_WIFI_EVENT_CB_FUNC	sal_xxxx_wifi_event_callback

extern int32 sal_xxxx_wifi_mode_set(sal_xxxx_wifi_mode_t mode, comm_xxxx_config_type_t configType);
extern int32 sal_xxxx_wifi_mode_get(sal_xxxx_wifi_mode_t *pMode, comm_xxxx_config_type_t configType);

extern int32 sal_xxxx_wifi_udpBC_interface_set(sal_xxxx_wifi_interface_t interface);
extern int32 sal_xxxx_wifi_udpBC_interface_get(sal_xxxx_wifi_interface_t *pInterface);

extern int32 sal_xxxx_wifi_ipInfo_get(sal_xxxx_wifi_interface_t interface, sal_xxxx_wifi_ipInfo_t *pIpInfo);
extern int32 sal_xxxx_wifi_ipInfo_set(sal_xxxx_wifi_interface_t interface, sal_xxxx_wifi_ipInfo_t *pIpInfo);

extern int32 sal_xxxx_wifi_station_dhcp_get(sal_xxxx_wifi_interface_t interface, comm_xxxx_enable_t *pEnable);
extern int32 sal_xxxx_wifi_station_dhcp_set(sal_xxxx_wifi_interface_t interface, comm_xxxx_enable_t enable);

extern int32 sal_xxxx_wifi_event_cbFunc_register(sal_xxxx_wifi_event_t event, SAL_XXXX_WIFI_EVENT_CB_FUNC func);
extern int32 sal_xxxx_wifi_event_cbFunc_unregister(sal_xxxx_wifi_event_t event);

extern int32 sal_xxxx_wifi_station_config_set(sal_xxxx_wifi_station_config_t *pWifiInfo, comm_xxxx_config_type_t configType);
extern int32 sal_xxxx_wifi_station_config_get(sal_xxxx_wifi_station_config_t *pWifiInfo, comm_xxxx_config_type_t configType);

extern int32 sal_xxxx_wifi_station_connect(void);
extern int32 sal_xxxx_wifi_station_disconnect(void);
extern int32 sal_xxxx_wifi_station_connectStatus_get(sal_xxxx_wifi_station_connect_status_t *pStatus);

extern int32 sal_xxxx_wifi_softap_config_get(sal_xxxx_wifi_softAp_config_t *pSoftApInfo, comm_xxxx_config_type_t configType);
extern int32 sal_xxxx_wifi_softap_config_set(sal_xxxx_wifi_softAp_config_t *pSoftApInfo, comm_xxxx_config_type_t configType);

extern int32 sal_xxxx_wifi_softap_stationNum_get(uint32 *pStationNum);
extern int32 sal_xxxx_wifi_softap_stationInfo_get(sal_xxxx_wifi_softAp_stationInfo_t *pStationList);


	


#endif

