#include <sal_xxxx_tcp.h>

sal_xxxx_tcp_info_t	tcp_client;
sal_xxxx_tcp_info_t	tcp_server;

LOCAL void _app_xxxx_tcp_dump(sal_xxxx_tcp_info_t *pTcp)
{
	os_printf("UserCfg DIP=%d.%d.%d.%d, Dport=%d\n", pTcp->dip.octet[0], pTcp->dip.octet[1], pTcp->dip.octet[2], pTcp->dip.octet[3], pTcp->dport);
	os_printf("UserCfg SIP=%d.%d.%d.%d, Sport=%d\n", pTcp->sip.octet[0], pTcp->sip.octet[1], pTcp->sip.octet[2], pTcp->sip.octet[3], pTcp->sport);
	os_printf("Espconn DIP=%d.%d.%d.%d, Dport=%d\n", pTcp->tcp.remote_ip[0], pTcp->tcp.remote_ip[1], pTcp->tcp.remote_ip[2], pTcp->tcp.remote_ip[3], pTcp->tcp.remote_port);
	os_printf("Espconn SIP=%d.%d.%d.%d, Sport=%d\n", pTcp->tcp.local_ip[0], pTcp->tcp.local_ip[1], pTcp->tcp.local_ip[2], pTcp->tcp.local_ip[3], pTcp->tcp.local_port);
	return;
}
	

LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_tcp_client_rxDone_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_tcp_info_t* pTcp = (sal_xxxx_tcp_info_t*)arg;

	os_printf("-------------TCP Client RX Done CB--------------\n");
	_app_xxxx_tcp_dump(pTcp);
	os_printf("rx_datalen = %d, data=%s\n", pTcp->rx_data_len, pTcp->rx_data);
	os_printf("\n\n\n\n");
	
	return XXXX_ERR_OK;
}
LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_tcp_client_txDone_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_tcp_info_t* pTcp = (sal_xxxx_tcp_info_t*)arg;

	os_printf("-------------TCP Client TX Done CB--------------\n");
	_app_xxxx_tcp_dump(pTcp);
	os_printf("tx_datalen = %d, data=%s\n", pTcp->tx_data_len, pTcp->tx_data);
	os_printf("\n\n\n\n");

	return XXXX_ERR_OK;
}

LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_tcp_client_connect_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_tcp_info_t* pTcp = (sal_xxxx_tcp_info_t*)arg;

	os_printf("-------------TCP Client Connect CB--------------\n");
	_app_xxxx_tcp_dump(pTcp);
	os_printf("\n\n\n\n");

	return XXXX_ERR_OK;
}

LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_tcp_client_connectException_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_tcp_info_t* pTcp = (sal_xxxx_tcp_info_t*)arg;

	os_printf("-------------TCP Client Connect Exception CB, err=%d--------------\n", pTcp->connect_excepion_err);
	_app_xxxx_tcp_dump(pTcp);
	os_printf("\n\n\n\n");

	return XXXX_ERR_OK;
}

LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_tcp_client_disconnect_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_tcp_info_t* pTcp = (sal_xxxx_tcp_info_t*)arg;

	os_printf("-------------TCP Client DisConnect CB--------------\n");
	_app_xxxx_tcp_dump(pTcp);
	os_printf("\n\n\n\n");

	return XXXX_ERR_OK;
}

LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_tcp_client_writeBufferFinish_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_tcp_info_t* pTcp = (sal_xxxx_tcp_info_t*)arg;

	os_printf("-------------TCP Client Write Buffer Finished CB--------------\n");
	_app_xxxx_tcp_dump(pTcp);
	os_printf("\n\n\n\n");

	return XXXX_ERR_OK;
}



LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_tcp_server_rxDone_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_tcp_info_t* pTcp = (sal_xxxx_tcp_info_t*)arg;

	os_printf("-------------TCP Server RX Done CB--------------\n");
	_app_xxxx_tcp_dump(pTcp);
	os_printf("rx_datalen = %d, data=%s\n", pTcp->rx_data_len, pTcp->rx_data);
	os_printf("\n\n\n\n");

	XXXX_ERR_CHK(sal_xxxx_tcp_tx_string(pTcp, "TCP server has received......"), ret);

	return XXXX_ERR_OK;
}
LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_tcp_server_txDone_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_tcp_info_t* pTcp = (sal_xxxx_tcp_info_t*)arg;

	os_printf("-------------TCP Server TX Done CB--------------\n");
	_app_xxxx_tcp_dump(pTcp);
	os_printf("tx_datalen = %d, data=%s\n", pTcp->tx_data_len, pTcp->tx_data);
	os_printf("\n\n\n\n");

	return XXXX_ERR_OK;
}

LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_tcp_server_connect_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_tcp_info_t* pTcp = (sal_xxxx_tcp_info_t*)arg;

	os_printf("-------------TCP Server Connect CB--------------\n");
	_app_xxxx_tcp_dump(pTcp);
	os_printf("\n\n\n\n");

	return XXXX_ERR_OK;
}

LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_tcp_server_connectException_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_tcp_info_t* pTcp = (sal_xxxx_tcp_info_t*)arg;

	os_printf("-------------TCP Server Connect Exception CB, err=%d--------------\n", pTcp->connect_excepion_err);
	_app_xxxx_tcp_dump(pTcp);
	os_printf("\n\n\n\n");

	return XXXX_ERR_OK;
}

LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_tcp_server_disconnect_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_tcp_info_t* pTcp = (sal_xxxx_tcp_info_t*)arg;

	os_printf("-------------TCP Server DisConnect CB--------------\n");
	_app_xxxx_tcp_dump(pTcp);
	os_printf("\n\n\n\n");

	return XXXX_ERR_OK;
}

LOCAL int32 ICACHE_FLASH_ATTR
app_xxxx_tcp_server_writeBufferFinish_cb(void *arg)
{
	int32 ret;
	XXXX_PARA_CHK(arg==NULL, XXXX_ERR_FAILED);
	sal_xxxx_tcp_info_t* pTcp = (sal_xxxx_tcp_info_t*)arg;

	os_printf("-------------TCP Server Write Buffer Finished CB--------------\n");
	_app_xxxx_tcp_dump(pTcp);
	os_printf("\n\n\n\n");

	return XXXX_ERR_OK;
}


LOCAL int32 ICACHE_FLASH_ATTR
_app_xxxx_tcp_client_init(sal_xxxx_tcp_info_t		*pTcp_client)
{
	int32 ret;
	/*******************************init TCP client***********************************************/
	XXXX_ERR_CHK(sal_xxxx_tcp_init(pTcp_client), ret);
	UINT32_TO_IPV4_ADDR(pTcp_client->dip, IPV4_UINT32(192,168,1,152));
	UINT32_TO_IPV4_ADDR(pTcp_client->sip, IPV4_UINT32(192,168,1,151));
	pTcp_client->dport	=	9988;
	pTcp_client->sport	=	8877;
	XXXX_ERR_CHK(sal_xxxx_tcp_sync(pTcp_client), ret);
	
	XXXX_ERR_CHK(sal_xxxx_tcp_cbFunc_register(SAL_XXXX_TCP_CB_FUNC_TX_DONE, 			app_xxxx_tcp_client_txDone_cb, 				pTcp_client),	ret);
	XXXX_ERR_CHK(sal_xxxx_tcp_cbFunc_register(SAL_XXXX_TCP_CB_FUNC_RX_DONE, 			app_xxxx_tcp_client_rxDone_cb, 				pTcp_client), 	ret);
	XXXX_ERR_CHK(sal_xxxx_tcp_cbFunc_register(SAL_XXXX_TCP_CB_FUNC_CONNECT, 			app_xxxx_tcp_client_connect_cb, 			pTcp_client), 	ret);
	XXXX_ERR_CHK(sal_xxxx_tcp_cbFunc_register(SAL_XXXX_TCP_CB_FUNC_CONNECT_EXCEPTION, 	app_xxxx_tcp_client_connectException_cb,	pTcp_client), 	ret);
	XXXX_ERR_CHK(sal_xxxx_tcp_cbFunc_register(SAL_XXXX_TCP_CB_FUNC_DISCONNECT, 			app_xxxx_tcp_client_disconnect_cb, 			pTcp_client), 	ret);
	XXXX_ERR_CHK(sal_xxxx_tcp_cbFunc_register(SAL_XXXX_TCP_CB_FUNC_WRITE_FINISH_FN, 	app_xxxx_tcp_client_writeBufferFinish_cb, 	pTcp_client), 	ret);

	XXXX_ERR_CHK(sal_xxxx_tcp_client_connect(pTcp_client), ret);

	//XXXX_ERR_CHK(sal_xxxx_tcp_tx_string(pTcp_client, "TCP connect to server......"), ret);	

	return XXXX_ERR_OK;
}


LOCAL int32 ICACHE_FLASH_ATTR
_app_xxxx_tcp_server_init(sal_xxxx_tcp_info_t		*pTcp_server)
{
	int32 ret;
	/*******************************init TCP server***********************************************/
	XXXX_ERR_CHK(sal_xxxx_tcp_init(pTcp_server), ret);
	UINT32_TO_IPV4_ADDR(pTcp_server->dip, IPV4_UINT32(192,168,1,152));
	UINT32_TO_IPV4_ADDR(pTcp_server->sip, IPV4_UINT32(192,168,1,151));
	pTcp_server->dport	=	7766;
	pTcp_server->sport	=	6655;
	XXXX_ERR_CHK(sal_xxxx_tcp_sync(pTcp_server), ret);
	
	XXXX_ERR_CHK(sal_xxxx_tcp_cbFunc_register(SAL_XXXX_TCP_CB_FUNC_TX_DONE, 			app_xxxx_tcp_client_txDone_cb, 				pTcp_server),	ret);
	XXXX_ERR_CHK(sal_xxxx_tcp_cbFunc_register(SAL_XXXX_TCP_CB_FUNC_RX_DONE, 			app_xxxx_tcp_client_rxDone_cb, 				pTcp_server), 	ret);
	XXXX_ERR_CHK(sal_xxxx_tcp_cbFunc_register(SAL_XXXX_TCP_CB_FUNC_CONNECT, 			app_xxxx_tcp_client_connect_cb, 			pTcp_server), 	ret);
	XXXX_ERR_CHK(sal_xxxx_tcp_cbFunc_register(SAL_XXXX_TCP_CB_FUNC_CONNECT_EXCEPTION, 	app_xxxx_tcp_client_connectException_cb,	pTcp_server), 	ret);
	XXXX_ERR_CHK(sal_xxxx_tcp_cbFunc_register(SAL_XXXX_TCP_CB_FUNC_DISCONNECT, 			app_xxxx_tcp_client_disconnect_cb, 			pTcp_server), 	ret);
	XXXX_ERR_CHK(sal_xxxx_tcp_cbFunc_register(SAL_XXXX_TCP_CB_FUNC_WRITE_FINISH_FN, 	app_xxxx_tcp_client_writeBufferFinish_cb, 	pTcp_server), 	ret);

	XXXX_ERR_CHK(sal_xxxx_tcp_server_create(pTcp_server, SAL_XXXX_TCP_CONNECTION_TIME_OUT_MAX), ret);

	return XXXX_ERR_OK;
}


int32 ICACHE_FLASH_ATTR
app_xxxx_tcp_init(void)
{
	int32 ret;

	XXXX_ERR_CHK(_app_xxxx_tcp_client_init(&tcp_client), 	ret);
	XXXX_ERR_CHK(_app_xxxx_tcp_server_init(&tcp_server), 	ret);
	
	return XXXX_ERR_OK;
}


