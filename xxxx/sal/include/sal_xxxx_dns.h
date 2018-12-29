#ifndef __SAL_XXXX_DNS_H__
#define __SAL_XXXX_DNS_H__

#include <xxxx_comm.h>

#define PROTO_XXXX_DNS_SERVER_NUM_MAX 2

extern int32
sal_xxxx_dns_serverIp_get(uint32 serverIdx, xxxx_ipv4_addr_t *pServerIp);
extern int32
sal_xxxx_dns_serverIp_set(uint32 serverIdx, xxxx_ipv4_addr_t *pServerIp);


#endif

