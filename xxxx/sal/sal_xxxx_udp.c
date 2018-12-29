
#include <sal_xxxx_udp.h>

LOCAL void _sal_xxxx_udp_dump(struct espconn *pUdp)
{
	os_printf("chip_udp_addr=0x%x\n", (uint32)pUdp);
	os_printf("Espconn DIP=%d.%d.%d.%d, Dport=%d\n", pUdp->proto.udp->remote_ip[0], pUdp->proto.udp->remote_ip[1], pUdp->proto.udp->remote_ip[2], pUdp->proto.udp->remote_ip[3], pUdp->proto.udp->remote_port);
	os_printf("Espconn SIP=%d.%d.%d.%d, Sport=%d\n", pUdp->proto.udp->local_ip[0], pUdp->proto.udp->local_ip[1], pUdp->proto.udp->local_ip[2], pUdp->proto.udp->local_ip[3], pUdp->proto.udp->local_port);

	return;
}

LOCAL void ICACHE_FLASH_ATTR
_sal_xxxx_udp_espconn_recv_callback(void *arg, char *pdata, unsigned short len)
{
	int32 ret;
	sal_xxxx_udp_info_t *pUdp = (sal_xxxx_udp_info_t*)arg;

	XXXX_PARA_CHK_VOID_RETURN((len>SAL_XXXX_UDP_DATA_MAX));
	
	os_memcpy(pUdp->rx_data, pdata, len);
	pUdp->rx_data[len]	=	'\0';
	pUdp->rx_data_len	=	len;

	_sal_xxxx_udp_dump((struct espconn *)arg);
	
	if(pUdp->rxDone_cb_func!=NULL)
		XXXX_ERR_CHK_VOID_RETURN(pUdp->rxDone_cb_func((void*)pUdp),	ret);
	
	return;
}

LOCAL void ICACHE_FLASH_ATTR
_sal_xxxx_udp_espconn_sent_callback(void *arg)
{
	int32 ret;
	sal_xxxx_udp_info_t *pUdp = (sal_xxxx_udp_info_t*)arg;

	_sal_xxxx_udp_dump((struct espconn *)arg);

	if(pUdp->txDone_cb_func!=NULL)
		XXXX_ERR_CHK_VOID_RETURN(pUdp->txDone_cb_func((void*)pUdp),	ret);
	
	return;	
}

int32 ICACHE_FLASH_ATTR 
sal_xxxx_udp_init(sal_xxxx_udp_info_t *pUdp)
{
	int32 ret;
	XXXX_PARA_CHK(pUdp==NULL,	XXXX_ERR_FAILED);

	os_memset(&pUdp->udp_conn, 0, sizeof(struct espconn));
	pUdp->udp_conn.type 		= 	ESPCONN_UDP;
	pUdp->udp_conn.proto.udp 	=	&pUdp->udp;

	pUdp->udp_conn.recv_callback	=	_sal_xxxx_udp_espconn_recv_callback;
	pUdp->udp_conn.sent_callback	=	_sal_xxxx_udp_espconn_sent_callback;
	
	return XXXX_ERR_OK;

}

int32 ICACHE_FLASH_ATTR 
sal_xxxx_udp_sync(sal_xxxx_udp_info_t *pUdp)
{
	XXXX_PARA_CHK(pUdp==NULL,	XXXX_ERR_FAILED);

	os_memcpy(pUdp->udp.remote_ip, 	pUdp->dip.octet, IPV4_ADDR_LEN);
	os_memcpy(pUdp->udp.local_ip, 	pUdp->sip.octet, IPV4_ADDR_LEN);
	pUdp->udp.remote_port		=	pUdp->dport;
	pUdp->udp.local_port		=	pUdp->sport;

	return XXXX_ERR_OK;

}

int32 ICACHE_FLASH_ATTR 
sal_xxxx_udp_cbFunc_register(sal_xxxx_udp_cbFunc_type_t type, SAL_XXXX_UDP_FUNC_CB cbFunc, sal_xxxx_udp_info_t *pUdp)
{
	switch(type)
	{
		case SAL_XXXX_UDP_CB_FUNC_TX_DONE:
			pUdp->txDone_cb_func	=		cbFunc;
			break;
		case SAL_XXXX_UDP_CB_FUNC_RX_DONE:
			pUdp->rxDone_cb_func	=		cbFunc;
			break;
		default:	
			RETURN(XXXX_ERR_FAILED);
	}
	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR 
sal_xxxx_udp_cbFunc_unregister(sal_xxxx_udp_cbFunc_type_t type, sal_xxxx_udp_info_t *pUdp)
{
	switch(type)
	{
		case SAL_XXXX_UDP_CB_FUNC_TX_DONE:
			pUdp->txDone_cb_func	=		NULL;
			break;
		case SAL_XXXX_UDP_CB_FUNC_RX_DONE:
			pUdp->txDone_cb_func	=		NULL;
			break;
		default:	
			RETURN(XXXX_ERR_FAILED);
	}
	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR 
sal_xxxx_udp_create(sal_xxxx_udp_info_t *pUdp)
{
	int32 ret;
	XXXX_PARA_CHK(pUdp==NULL,	XXXX_ERR_FAILED);
	
	XXXX_ERR_CHK_ERRCODE(espconn_create(&pUdp->udp_conn), ret, ESPCONN_OK);

	return XXXX_ERR_OK;

}

int32 ICACHE_FLASH_ATTR 
sal_xxxx_udp_delete(sal_xxxx_udp_info_t *pUdp)
{
	int32 ret;
	XXXX_PARA_CHK(pUdp==NULL,	XXXX_ERR_FAILED);

	XXXX_ERR_CHK_ERRCODE(espconn_delete(&pUdp->udp_conn), ret, ESPCONN_OK);
	
	return XXXX_ERR_OK;

}

int32 ICACHE_FLASH_ATTR 
sal_xxxx_udp_tx(sal_xxxx_udp_info_t *pUdp)
{
	int32 ret;

	XXXX_PARA_CHK(pUdp==NULL,	XXXX_ERR_FAILED);

	_sal_xxxx_udp_dump(&pUdp->udp_conn);
	XXXX_ERR_CHK_ERRCODE(espconn_sent(&pUdp->udp_conn, pUdp->tx_data, pUdp->tx_data_len), ret, ESPCONN_OK);
	
	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR  
sal_xxxx_udp_tx_string(sal_xxxx_udp_info_t *pUdp, char* string)
{
	XXXX_PARA_CHK(pUdp==NULL,	XXXX_ERR_FAILED);
	
	pUdp->tx_data_len	=	string==NULL ? 0 : (os_strlen(string)+1);
	XXXX_PARA_CHK(pUdp->tx_data_len>SAL_XXXX_UDP_DATA_MAX,	XXXX_ERR_FAILED);
	
	os_memcpy(pUdp->tx_data, string, pUdp->tx_data_len);
	pUdp->tx_data[pUdp->tx_data_len]	=	'\0';
	
	return sal_xxxx_udp_tx(pUdp);	
}


