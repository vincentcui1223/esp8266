#include <sal_xxxx_wifi.h>
#include <sal_xxxx_udp.h>
#include <sal_xxxx_timer.h>

#define NAKE_API_TEST 1

#if TEST_UDP_ROUT_XIAOMI
	#define ESP8266_IP 				192,168,31,72
	#define XIAOMI_PHONE_IP 		192,168,31,37
	#define PC_IP 					192,168,31,165
#else
	#define ESP8266_IP 				192,168,1,153
	#define XIAOMI_PHONE_IP 		192,168,1,152
	#define PC_IP					192,168,1,151
#endif

#define UDP_CLIENT_DPORT	9999
#define UDP_CLIENT_SPORT	8888
#define UDP_SERVER_DPORT	7777
#define UDP_SERVER_SPORT	6666


sal_xxxx_udp_info_t	udp_client;
sal_xxxx_udp_info_t	udp_server;

sal_xxxx_timer_t	app_xxxx_udp_client_timer;


LOCAL void _app_xxxx_udp_dump(sal_xxxx_udp_info_t *pUdp)
{
	os_printf("sal_udp_addr=0x%x\n", (uint32)pUdp);
	os_printf("UserCfg DIP=%d.%d.%d.%d, Dport=%d\n", pUdp->dip.octet[0], pUdp->dip.octet[1], pUdp->dip.octet[2], pUdp->dip.octet[3], pUdp->dport);
	os_printf("UserCfg SIP=%d.%d.%d.%d, Sport=%d\n", pUdp->sip.octet[0], pUdp->sip.octet[1], pUdp->sip.octet[2], pUdp->sip.octet[3], pUdp->sport);
	os_printf("Espconn DIP=%d.%d.%d.%d, Dport=%d\n", pUdp->udp.remote_ip[0], pUdp->udp.remote_ip[1], pUdp->udp.remote_ip[2], pUdp->udp.remote_ip[3], pUdp->udp.remote_port);
	os_printf("Espconn SIP=%d.%d.%d.%d, Sport=%d\n", pUdp->udp.local_ip[0], pUdp->udp.local_ip[1], pUdp->udp.local_ip[2], pUdp->udp.local_ip[3], pUdp->udp.local_port);

	return;
}
	

LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_udp_client_rxDone_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_udp_info_t* pUdp = (sal_xxxx_udp_info_t*)arg;

	os_printf("-------------UDP Client RX Done CB--------------\n");
	_app_xxxx_udp_dump(pUdp);
	os_printf("rx_datalen = %d, data=%s\n", pUdp->rx_data_len, pUdp->rx_data);
	os_printf("\n\n\n\n");
	
	XXXX_ERR_CHK(sal_xxxx_udp_tx_string(pUdp, "UDP client has received......"), ret);	
	
	return XXXX_ERR_OK;
}
LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_udp_client_txDone_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_udp_info_t* pUdp = (sal_xxxx_udp_info_t*)arg;

	os_printf("-------------UDP Client TX Done CB--------------\n");
	_app_xxxx_udp_dump(pUdp);
	os_printf("tx_datalen = %d, data=%s\n", pUdp->tx_data_len, pUdp->tx_data);
	os_printf("\n\n\n\n");

	return XXXX_ERR_OK;
}

LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_udp_server_rxDone_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_udp_info_t* pUdp = (sal_xxxx_udp_info_t*)arg;

	os_printf("-------------UDP Server RX Done CB--------------\n");
	_app_xxxx_udp_dump(pUdp);
	os_printf("rx_datalen = %d, data=%s\n", pUdp->rx_data_len, pUdp->rx_data);
	os_printf("\n\n\n\n");

	XXXX_ERR_CHK(sal_xxxx_udp_tx_string(pUdp, "UDP server has received......"), ret);

	return XXXX_ERR_OK;
}
LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_udp_server_txDone_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_udp_info_t* pUdp = (sal_xxxx_udp_info_t*)arg;

	os_printf("-------------UDP Server TX Done CB--------------\n");
	_app_xxxx_udp_dump(pUdp);
	os_printf("tx_datalen = %d, data=%s\n", pUdp->tx_data_len, pUdp->tx_data);
	os_printf("\n\n\n\n");

	return XXXX_ERR_OK;
}

LOCAL int32 ICACHE_FLASH_ATTR
_app_xxxx_udp_client_init(sal_xxxx_udp_info_t		*pUdp_client)
{
	int32 ret;
	/*******************************init UDP client***********************************************/
	XXXX_ERR_CHK(sal_xxxx_udp_init(pUdp_client), ret);
#if TEST_UDP_BC_IF
	UINT32_TO_IPV4_ADDR(pUdp_client->dip, IPV4_UINT32(255,255,255,255));
#else
	UINT32_TO_IPV4_ADDR(pUdp_client->dip, IPV4_UINT32(XIAOMI_PHONE_IP));
#endif
	UINT32_TO_IPV4_ADDR(pUdp_client->sip, IPV4_UINT32(ESP8266_IP));
	pUdp_client->dport	=	UDP_CLIENT_DPORT;
	pUdp_client->sport	=	UDP_CLIENT_SPORT;
	XXXX_ERR_CHK(sal_xxxx_udp_sync(pUdp_client), ret);
	XXXX_ERR_CHK(sal_xxxx_udp_cbFunc_register(SAL_XXXX_UDP_CB_FUNC_TX_DONE, app_xxxx_udp_client_txDone_cb, pUdp_client), ret);
	XXXX_ERR_CHK(sal_xxxx_udp_cbFunc_register(SAL_XXXX_UDP_CB_FUNC_RX_DONE, app_xxxx_udp_client_rxDone_cb, pUdp_client), ret);
	XXXX_ERR_CHK(sal_xxxx_udp_create(pUdp_client), ret);

	return XXXX_ERR_OK;
}

LOCAL void ICACHE_FLASH_ATTR
_app_xxxx_udp_client_timer_cb(void *arg)
{
	int32 ret;
	XXXX_ERR_CHK_VOID_RETURN(sal_xxxx_udp_tx_string((sal_xxxx_udp_info_t*)arg, "UDP send......"), ret);	
}



LOCAL int32 ICACHE_FLASH_ATTR
_app_xxxx_udp_server_init(sal_xxxx_udp_info_t		*pUdp_server)
{
	int32 ret;
	/*******************************init UDP server***********************************************/
	XXXX_ERR_CHK(sal_xxxx_udp_init(pUdp_server), ret);
#if TEST_UDP_BC_IF
	UINT32_TO_IPV4_ADDR(pUdp_server->dip, IPV4_UINT32(255,255,255,255));
#else
	UINT32_TO_IPV4_ADDR(pUdp_server->dip, IPV4_UINT32(PC_IP));
#endif
	UINT32_TO_IPV4_ADDR(pUdp_server->sip, IPV4_UINT32(ESP8266_IP));
	pUdp_server->dport	=	UDP_SERVER_DPORT;
	pUdp_server->sport	=	UDP_SERVER_SPORT;
	XXXX_ERR_CHK(sal_xxxx_udp_sync(pUdp_server), ret);
	XXXX_ERR_CHK(sal_xxxx_udp_cbFunc_register(SAL_XXXX_UDP_CB_FUNC_TX_DONE, app_xxxx_udp_server_txDone_cb, pUdp_server), ret);
	XXXX_ERR_CHK(sal_xxxx_udp_cbFunc_register(SAL_XXXX_UDP_CB_FUNC_RX_DONE, app_xxxx_udp_server_rxDone_cb, pUdp_server), ret);
	XXXX_ERR_CHK(sal_xxxx_udp_create(pUdp_server), ret);

	return XXXX_ERR_OK;
}

#if NAKE_API_TEST
sal_xxxx_udp_info_t	udp_test;
sal_xxxx_timer_t	app_xxxx_udpTest_timer;


LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_udp_rxDone_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_udp_info_t* pUdp = (sal_xxxx_udp_info_t*)arg;

	os_printf("-------------UDP RX Done CB--------------\n");
	_app_xxxx_udp_dump(pUdp);
	os_printf("rx_datalen = %d, data=%s\n", pUdp->rx_data_len, pUdp->rx_data);
	os_printf("\n\n\n\n");

	return XXXX_ERR_OK;
}
LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_udp_txDone_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_udp_info_t* pUdp = (sal_xxxx_udp_info_t*)arg;

	os_printf("-------------UDP TX Done CB--------------\n");
	_app_xxxx_udp_dump(pUdp);
	os_printf("tx_datalen = %d, data=%s\n", pUdp->tx_data_len, pUdp->tx_data);
	os_printf("\n\n\n\n");

	return XXXX_ERR_OK;
}


LOCAL void ICACHE_FLASH_ATTR
_app_xxxx_udp_timer_cb(void *arg)
{
	int32 ret;

	static i=0;
	
	i++;
	os_printf("UDP1-2 Tx %d\n", i);
	//XXXX_ERR_CHK_VOID_RETURN(sal_xxxx_udp_tx_string(&udp1, "UDP1 send data......"), ret);	
	//XXXX_ERR_CHK_VOID_RETURN(sal_xxxx_udp_tx_string(&udp2, "UDP1 tx data......"), ret);	

	espconn_sent(&udp_test.udp_conn, "Hello World!", os_strlen("Hello World!"));

	//XXXX_ERR_CHK_VOID_RETURN(sal_xxxx_udp_tx_string(&udp3, "UDP3 bc data......"), ret);	
	
	return;
}

LOCAL int32 ICACHE_FLASH_ATTR
_app_xxxx_udp123_init(void)
{
	int32 ret;
#if 0
	/*******************************init UDP client***********************************************/
	XXXX_ERR_CHK(sal_xxxx_udp_init(pUdp1), ret);
	UINT32_TO_IPV4_ADDR(pUdp1->dip, IPV4_UINT32(192,168,1,151));
	UINT32_TO_IPV4_ADDR(pUdp1->sip, IPV4_UINT32(192,168,1,153));
	pUdp1->dport	=	7776;
	pUdp1->sport	=	6665;
	XXXX_ERR_CHK(sal_xxxx_udp_sync(pUdp1), ret);
	XXXX_ERR_CHK(sal_xxxx_udp_cbFunc_register(SAL_XXXX_UDP_CB_FUNC_TX_DONE, app_xxxx_udp_txDone_cb, pUdp1), ret);
	XXXX_ERR_CHK(sal_xxxx_udp_cbFunc_register(SAL_XXXX_UDP_CB_FUNC_RX_DONE, app_xxxx_udp_rxDone_cb, pUdp1), ret);
	XXXX_ERR_CHK(sal_xxxx_udp_create(pUdp1), ret);

	XXXX_ERR_CHK(sal_xxxx_udp_init(pUdp2), ret);
	UINT32_TO_IPV4_ADDR(pUdp2->dip, IPV4_UINT32(192,168,1,152));
	UINT32_TO_IPV4_ADDR(pUdp2->sip, IPV4_UINT32(192,168,1,153));
	pUdp2->dport	=	7776;
	pUdp2->sport	=	6655;
	XXXX_ERR_CHK(sal_xxxx_udp_sync(pUdp2), ret);
	XXXX_ERR_CHK(sal_xxxx_udp_cbFunc_register(SAL_XXXX_UDP_CB_FUNC_TX_DONE, app_xxxx_udp_txDone_cb, pUdp2), ret);
	XXXX_ERR_CHK(sal_xxxx_udp_cbFunc_register(SAL_XXXX_UDP_CB_FUNC_RX_DONE, app_xxxx_udp_rxDone_cb, pUdp2), ret);
	XXXX_ERR_CHK(sal_xxxx_udp_create(pUdp2), ret);


#endif

	udp_test.udp_conn.type 			= 	ESPCONN_UDP;
	udp_test.udp_conn.proto.udp 	=	&udp_test.udp;
	const char udp_remote_ip[4] = { 255, 255, 255, 255 };
	const char udp_local_ip[4] = {ESP8266_IP};
	os_memcpy(udp_test.udp.remote_ip, udp_remote_ip, 4);
	os_memcpy(udp_test.udp.local_ip, udp_local_ip, 4);
	udp_test.udp.remote_port		=	7666;
	udp_test.udp.local_port			=	6555;
	XXXX_ERR_CHK(sal_xxxx_udp_cbFunc_register(SAL_XXXX_UDP_CB_FUNC_TX_DONE, app_xxxx_udp_txDone_cb, &udp_test), ret);
	XXXX_ERR_CHK(sal_xxxx_udp_cbFunc_register(SAL_XXXX_UDP_CB_FUNC_RX_DONE, app_xxxx_udp_rxDone_cb, &udp_test), ret);
	espconn_create(&udp_test.udp_conn);

#if 0
	XXXX_ERR_CHK(sal_xxxx_udp_init(udp_test), ret);
	UINT32_TO_IPV4_ADDR(udp_test.dip, IPV4_UINT32(255,255,255,255));
	UINT32_TO_IPV4_ADDR(udp_test.sip, IPV4_UINT32(ESP8266_IP));
	udp_test.dport	=	7666;
	udp_test.sport	=	6555;
	XXXX_ERR_CHK(sal_xxxx_udp_sync(&udp_test), ret);
	XXXX_ERR_CHK(sal_xxxx_udp_cbFunc_register(SAL_XXXX_UDP_CB_FUNC_TX_DONE, app_xxxx_udp_txDone_cb, &udp_test), ret);
	XXXX_ERR_CHK(sal_xxxx_udp_cbFunc_register(SAL_XXXX_UDP_CB_FUNC_RX_DONE, app_xxxx_udp_rxDone_cb, &udp_test), ret);
	XXXX_ERR_CHK(sal_xxxx_udp_create(&udp_test), ret);
#endif

	sal_xxxx_timer_disable(&app_xxxx_udpTest_timer);
	sal_xxxx_timer_init(&app_xxxx_udpTest_timer, _app_xxxx_udp_timer_cb , NULL);
	sal_xxxx_timer_enable(&app_xxxx_udpTest_timer,	5000,	1);

	return XXXX_ERR_OK;
}
#endif


int32 ICACHE_FLASH_ATTR
app_xxxx_udp_init(void)
{
	int32 ret;

	XXXX_ERR_CHK(sal_xxxx_wifi_udpBC_interface_set(SAL_XXXX_WIFI_INTERFACE_STATION), ret);
#if NAKE_API_TEST
	XXXX_ERR_CHK(_app_xxxx_udp123_init(), 	ret);
#else
	XXXX_ERR_CHK(_app_xxxx_udp_client_init(&udp_client), 	ret);
	XXXX_ERR_CHK(_app_xxxx_udp_server_init(&udp_server), 	ret);

	sal_xxxx_timer_disable(&app_xxxx_udp_client_timer);
	sal_xxxx_timer_init(&app_xxxx_udp_client_timer, _app_xxxx_udp_client_timer_cb , (void*)(&udp_client));
	sal_xxxx_timer_enable(&app_xxxx_udp_client_timer,	5000,	1);
#endif
	
	return XXXX_ERR_OK;
}


