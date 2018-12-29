#ifndef __SAL_XXXX_TCP_H__
#define __SAL_XXXX_TCP_H__

#include <xxxx_comm.h>

#define SAL_XXXX_TCP_CONNECTION_TIME_OUT_MAX	7200


typedef int32 (* sal_xxxx_tcp_callback)(void *arg);
#define SAL_XXXX_TCP_FUNC_CB	sal_xxxx_tcp_callback

typedef enum sal_xxxx_tcp_idsConnetErr_e
{
	SAL_XXXX_TCP_DIS_CONNECT_ERR_TIMEOUT,		/*超时出错断开*/
	SAL_XXXX_TCP_DIS_CONNECT_ERR_ABRT,			/*TCP 连接异常断开*/
	SAL_XXXX_TCP_DIS_CONNECT_ERR_RST,			/*TCP 连接复位断开*/
	SAL_XXXX_TCP_DIS_CONNECT_ERR_CLSD,			/*TCP 连接在断开过程中出错，异常断开*/
	SAL_XXXX_TCP_DIS_CONNECT_ERR_CONN,			/*TCP 未连接成功*/
	SAL_XXXX_TCP_DIS_CONNECT_ERR_HANDSHAKE,		/*TCP SSL 握.手失败*/
	SAL_XXXX_TCP_DIS_CONNECT_ERR_PROTO_MSG,		/*SSL 应.用数据处理理异常*/
	SAL_XXXX_TCP_DIS_CONNECT_ERR_END
}sal_xxxx_tcp_idsConnetErr_t;

typedef enum sal_xxxx_tcp_cbFunc_type_e
{
	SAL_XXXX_TCP_CB_FUNC_TX_DONE,
	SAL_XXXX_TCP_CB_FUNC_RX_DONE,
	SAL_XXXX_TCP_CB_FUNC_CONNECT,
	SAL_XXXX_TCP_CB_FUNC_CONNECT_EXCEPTION,
	SAL_XXXX_TCP_CB_FUNC_DISCONNECT,
	SAL_XXXX_TCP_CB_FUNC_WRITE_FINISH_FN,
	SAL_XXXX_TCP_CB_FUNC_END
}sal_xxxx_tcp_cbFunc_type_t;

#define SAL_XXXX_TCP_DATA_MAX	2000

typedef struct sal_xxxx_tcp_info_s
{
	/*no need to config*/
	struct espconn 		tcp_conn;	/*must be the 1st variable in this struct*/
	esp_tcp 			tcp;

	xxxx_ipv4_addr_t	dip;
	xxxx_ipv4_addr_t	sip;
	uint32				dport;
	uint32				sport;

	uint8				tx_data[SAL_XXXX_TCP_DATA_MAX];
	uint32				tx_data_len;

	uint8				rx_data[SAL_XXXX_TCP_DATA_MAX];
	uint32				rx_data_len;

	sal_xxxx_tcp_idsConnetErr_t	connect_excepion_err;
	
	SAL_XXXX_TCP_FUNC_CB	rxDone_cb_func;
	SAL_XXXX_TCP_FUNC_CB	txDone_cb_func;
    SAL_XXXX_TCP_FUNC_CB 	connect_callback;
    SAL_XXXX_TCP_FUNC_CB 	connectException_callback;
    SAL_XXXX_TCP_FUNC_CB 	disconnect_callback;
	SAL_XXXX_TCP_FUNC_CB 	write_finish_fn;
}sal_xxxx_tcp_info_t;

extern int32
sal_xxxx_tcp_init(sal_xxxx_tcp_info_t *pTcp);
extern int32
sal_xxxx_tcp_sync(sal_xxxx_tcp_info_t *pTcp);	

extern int32
sal_xxxx_tcp_cbFunc_register(sal_xxxx_tcp_cbFunc_type_t type, SAL_XXXX_TCP_FUNC_CB cbFunc, sal_xxxx_tcp_info_t *pTcp);
extern int32
sal_xxxx_tcp_cbFunc_unregister(sal_xxxx_tcp_cbFunc_type_t type, sal_xxxx_tcp_info_t *pTcp);

extern int32 
sal_xxxx_tcp_server_create(sal_xxxx_tcp_info_t *pTcp, uint32 timeOut_sec);

extern int32 
sal_xxxx_tcp_client_connect(sal_xxxx_tcp_info_t *pTcp);

extern int32 
sal_xxxx_tcp_disconnect(sal_xxxx_tcp_info_t *pTcp);

extern int32 
sal_xxxx_tcp_tx(sal_xxxx_tcp_info_t *pTcp);

extern int32 
sal_xxxx_tcp_tx_string(sal_xxxx_tcp_info_t *pTcp, char* string);


#endif

