#include <sal_xxxx_tcp.h>

LOCAL void ICACHE_FLASH_ATTR
_sal_xxxx_tcp_espconn_recv_callback(void *arg, char *pdata, unsigned short len)
{
	int32 ret;
	sal_xxxx_tcp_info_t *pTcp = (sal_xxxx_tcp_info_t*)arg;

	XXXX_PARA_CHK_VOID_RETURN((len>SAL_XXXX_TCP_DATA_MAX));
	
	os_memcpy(pTcp->rx_data, pdata, len);
	pTcp->rx_data_len	=	len;
	pTcp->rx_data[pTcp->rx_data_len]	=	'\0';
	if(pTcp->rxDone_cb_func!=NULL)
		XXXX_ERR_CHK_VOID_RETURN(pTcp->rxDone_cb_func((void*)pTcp),	ret);
	
	return;
}

LOCAL void ICACHE_FLASH_ATTR
_sal_xxxx_tcp_espconn_sent_callback(void *arg)
{
	int32 ret;
	sal_xxxx_tcp_info_t *pTcp = (sal_xxxx_tcp_info_t*)arg;

	if(pTcp->txDone_cb_func!=NULL)
		XXXX_ERR_CHK_VOID_RETURN(pTcp->txDone_cb_func((void*)pTcp),	ret);
	
	return;	
}

LOCAL void ICACHE_FLASH_ATTR
_sal_xxxx_tcp_espconn_connect_callback(void *arg)
{
	int32 ret;
	sal_xxxx_tcp_info_t *pTcp = (sal_xxxx_tcp_info_t*)arg;

	if(pTcp->connect_callback!=NULL)
		XXXX_ERR_CHK_VOID_RETURN(pTcp->connect_callback((void*)pTcp), ret);
	
	return; 
}


LOCAL void ICACHE_FLASH_ATTR
_sal_xxxx_tcp_espconn_connectException_callback(void *arg, sint8 err)
{
	int32 ret;
	sal_xxxx_tcp_info_t *pTcp = (sal_xxxx_tcp_info_t*)arg;

	if(pTcp->connectException_callback!=NULL)
	{
		SAL_XXXX_TCP_CONNECT_ERR_XLATE_FROM_CHIP(pTcp->connect_excepion_err, err,	ret);
		if(ret!=XXXX_ERR_OK)
			VOID_RETURN();
		XXXX_ERR_CHK_VOID_RETURN(pTcp->connectException_callback((void*)pTcp), ret);
	}
	
	return; 
}

LOCAL void ICACHE_FLASH_ATTR
_sal_xxxx_tcp_espconn_disconnect_callback(void *arg)
{
	int32 ret;
	sal_xxxx_tcp_info_t *pTcp = (sal_xxxx_tcp_info_t*)arg;

	if(pTcp->disconnect_callback!=NULL)
		XXXX_ERR_CHK_VOID_RETURN(pTcp->disconnect_callback((void*)pTcp), ret);
	
	return; 
}


LOCAL void ICACHE_FLASH_ATTR
_sal_xxxx_tcp_espconn_write_finish_fn_callback(void *arg)
{
	int32 ret;
	sal_xxxx_tcp_info_t *pTcp = (sal_xxxx_tcp_info_t*)arg;

	if(pTcp->write_finish_fn!=NULL)
		XXXX_ERR_CHK_VOID_RETURN(pTcp->write_finish_fn((void*)pTcp), ret);
	
	return; 
}

ICACHE_FLASH_ATTR int32 
sal_xxxx_tcp_init(sal_xxxx_tcp_info_t *pTcp)
{
	int32 ret;
	XXXX_PARA_CHK(pTcp==NULL,	XXXX_ERR_FAILED);

	os_memset(&pTcp->tcp_conn, 0, sizeof(struct espconn));
	pTcp->tcp_conn.type 		= 	ESPCONN_TCP;
	pTcp->tcp_conn.proto.tcp 	=	&pTcp->tcp;

	pTcp->tcp_conn.recv_callback	=	_sal_xxxx_tcp_espconn_recv_callback;
	pTcp->tcp_conn.sent_callback	=	_sal_xxxx_tcp_espconn_sent_callback;
	pTcp->tcp.connect_callback		=	_sal_xxxx_tcp_espconn_connect_callback;
	pTcp->tcp.reconnect_callback	=	_sal_xxxx_tcp_espconn_connectException_callback;
	pTcp->tcp.disconnect_callback	=	_sal_xxxx_tcp_espconn_disconnect_callback;
	pTcp->tcp.write_finish_fn		=	_sal_xxxx_tcp_espconn_write_finish_fn_callback;

	return XXXX_ERR_OK;
}

ICACHE_FLASH_ATTR int32 
sal_xxxx_tcp_sync(sal_xxxx_tcp_info_t *pTcp)
{
	XXXX_PARA_CHK(pTcp==NULL,	XXXX_ERR_FAILED);

	os_memcpy(pTcp->tcp.remote_ip, 	pTcp->dip.octet, IPV4_ADDR_LEN);
	os_memcpy(pTcp->tcp.local_ip, 	pTcp->sip.octet, IPV4_ADDR_LEN);
	pTcp->tcp.remote_port		=	pTcp->dport;
	pTcp->tcp.local_port		=	pTcp->sport;

	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR 
sal_xxxx_tcp_cbFunc_register(sal_xxxx_tcp_cbFunc_type_t type, SAL_XXXX_TCP_FUNC_CB cbFunc, sal_xxxx_tcp_info_t *pTcp)
{
	switch(type)
	{
		case SAL_XXXX_TCP_CB_FUNC_TX_DONE:
			pTcp->txDone_cb_func		=		cbFunc;
			break;
		case SAL_XXXX_TCP_CB_FUNC_RX_DONE:
			pTcp->rxDone_cb_func		=		cbFunc;
			break;
		case SAL_XXXX_TCP_CB_FUNC_CONNECT:
			pTcp->connect_callback		=		cbFunc;
			break;
		case SAL_XXXX_TCP_CB_FUNC_CONNECT_EXCEPTION:
			pTcp->connectException_callback	=		cbFunc;
			break;
		case SAL_XXXX_TCP_CB_FUNC_DISCONNECT:
			pTcp->disconnect_callback	=		cbFunc;
			break;
		case SAL_XXXX_TCP_CB_FUNC_WRITE_FINISH_FN:
			pTcp->write_finish_fn		=		cbFunc;
			break;
		default:	
			RETURN(XXXX_ERR_FAILED);
	}
	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR 
sal_xxxx_tcp_cbFunc_unregister(sal_xxxx_tcp_cbFunc_type_t type, sal_xxxx_tcp_info_t *pTcp)
{
	switch(type)
	{
		case SAL_XXXX_TCP_CB_FUNC_TX_DONE:
			pTcp->txDone_cb_func		=		NULL;
			break;
		case SAL_XXXX_TCP_CB_FUNC_RX_DONE:
			pTcp->txDone_cb_func		=		NULL;
			break;
		case SAL_XXXX_TCP_CB_FUNC_CONNECT:
			pTcp->connect_callback		=		NULL;
			break;
		case SAL_XXXX_TCP_CB_FUNC_CONNECT_EXCEPTION:
			pTcp->connectException_callback	=		NULL;
			break;
		case SAL_XXXX_TCP_CB_FUNC_DISCONNECT:
			pTcp->disconnect_callback	=		NULL;
			break;
		case SAL_XXXX_TCP_CB_FUNC_WRITE_FINISH_FN:
			pTcp->write_finish_fn		=		NULL;
			break;
		default:	
			RETURN(XXXX_ERR_FAILED);
	}
	return XXXX_ERR_OK;
}

ICACHE_FLASH_ATTR int32 
sal_xxxx_tcp_server_create(sal_xxxx_tcp_info_t *pTcp, uint32 timeOut_sec)
{
	int32 ret;
	XXXX_PARA_CHK(pTcp==NULL,	XXXX_ERR_FAILED);
	XXXX_PARA_CHK(timeOut_sec>SAL_XXXX_TCP_CONNECTION_TIME_OUT_MAX,	XXXX_ERR_FAILED);
	
	XXXX_ERR_CHK_ERRCODE(espconn_accept(&pTcp->tcp_conn), ret, ESPCONN_OK);
	XXXX_ERR_CHK_ERRCODE(espconn_regist_time(&pTcp->tcp_conn, timeOut_sec, 1), ret, ESPCONN_OK);

	return XXXX_ERR_OK;
}

ICACHE_FLASH_ATTR int32 
sal_xxxx_tcp_client_connect(sal_xxxx_tcp_info_t *pTcp)
{
	int32 ret;
	XXXX_PARA_CHK(pTcp==NULL,	XXXX_ERR_FAILED);

	XXXX_ERR_CHK_ERRCODE(espconn_connect(&pTcp->tcp_conn), ret, ESPCONN_OK);

	return XXXX_ERR_OK;
}


ICACHE_FLASH_ATTR int32 
sal_xxxx_tcp_disconnect(sal_xxxx_tcp_info_t *pTcp)
{
	int32 ret;
	XXXX_PARA_CHK(pTcp==NULL,	XXXX_ERR_FAILED);

	XXXX_ERR_CHK_ERRCODE(espconn_disconnect(&pTcp->tcp_conn), ret, ESPCONN_OK);

	return XXXX_ERR_OK;
}


ICACHE_FLASH_ATTR int32 
sal_xxxx_tcp_delete(sal_xxxx_tcp_info_t *pTcp)
{
	int32 ret;
	XXXX_PARA_CHK(pTcp==NULL,	XXXX_ERR_FAILED);

	XXXX_ERR_CHK_ERRCODE(espconn_delete(&pTcp->tcp_conn), ret, ESPCONN_OK);

	return XXXX_ERR_OK;
}


ICACHE_FLASH_ATTR int32 
sal_xxxx_tcp_tx(sal_xxxx_tcp_info_t *pTcp)
{
	int32 ret;

	XXXX_PARA_CHK(pTcp==NULL,	XXXX_ERR_FAILED);
	
	XXXX_ERR_CHK_ERRCODE(espconn_sent(&pTcp->tcp_conn, pTcp->tx_data, pTcp->tx_data_len), ret, ESPCONN_OK);
	
	return XXXX_ERR_OK;
}

ICACHE_FLASH_ATTR int32  
sal_xxxx_tcp_tx_string(sal_xxxx_tcp_info_t *pTcp, char* string)
{
	XXXX_PARA_CHK(pTcp==NULL,	XXXX_ERR_FAILED);
	
	pTcp->tx_data_len	=	string==NULL ? 0 : (os_strlen(string)+1);
	XXXX_PARA_CHK(pTcp->tx_data_len>SAL_XXXX_TCP_DATA_MAX,	XXXX_ERR_FAILED);
	
	
	os_memcpy(pTcp->tx_data, string, pTcp->tx_data_len);
	pTcp->tx_data[pTcp->tx_data_len]	=	'\0';
	
	return sal_xxxx_tcp_tx(pTcp);	
}




