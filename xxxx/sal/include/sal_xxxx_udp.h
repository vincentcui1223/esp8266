#ifndef __SAL_XXXX_UDP_H__
#define __SAL_XXXX_UDP_H__

#include <xxxx_comm.h>

typedef int32 (* sal_xxxx_udp_callback)(void *arg);
#define SAL_XXXX_UDP_FUNC_CB	sal_xxxx_udp_callback

typedef enum sal_xxxx_udp_cbFunc_type_e
{
	SAL_XXXX_UDP_CB_FUNC_TX_DONE,
	SAL_XXXX_UDP_CB_FUNC_RX_DONE,
	SAL_XXXX_UDP_CB_FUNC_END
}sal_xxxx_udp_cbFunc_type_t;

#define SAL_XXXX_UDP_DATA_MAX	2000

typedef struct sal_xxxx_udp_info_s
{
	/*no need to config*/
	struct espconn 		udp_conn;	/*must be the 1st variable in this struct*/
	esp_udp 			udp;

	/*config*/
	xxxx_ipv4_addr_t	dip;
	xxxx_ipv4_addr_t	sip;
	uint32				dport;
	uint32				sport;

	uint8				tx_data[SAL_XXXX_UDP_DATA_MAX];
	uint32				tx_data_len;

	uint8				rx_data[SAL_XXXX_UDP_DATA_MAX];
	uint32				rx_data_len;

	SAL_XXXX_UDP_FUNC_CB	rxDone_cb_func;
	SAL_XXXX_UDP_FUNC_CB	txDone_cb_func;
}sal_xxxx_udp_info_t;

extern int32
sal_xxxx_udp_init(sal_xxxx_udp_info_t *pUdp);
extern int32
sal_xxxx_udp_sync(sal_xxxx_udp_info_t *pUdp);

extern int32 
sal_xxxx_udp_cbFunc_register(sal_xxxx_udp_cbFunc_type_t type, SAL_XXXX_UDP_FUNC_CB cbFunc, sal_xxxx_udp_info_t *pUdp);
extern int32 
sal_xxxx_udp_cbFunc_unregister(sal_xxxx_udp_cbFunc_type_t type, sal_xxxx_udp_info_t *pUdp);

extern int32 
sal_xxxx_udp_create(sal_xxxx_udp_info_t *pUdp);
extern int32 
sal_xxxx_udp_delete(sal_xxxx_udp_info_t *pUdp);

extern int32 
sal_xxxx_udp_tx(sal_xxxx_udp_info_t *pUdp);

extern int32 
sal_xxxx_udp_tx_string(sal_xxxx_udp_info_t *pUdp, char* string);


#endif

