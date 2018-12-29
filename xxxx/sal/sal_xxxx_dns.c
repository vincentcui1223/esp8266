#include <sal_xxxx_dns.h>

int32 ICACHE_FLASH_ATTR
sal_xxxx_dns_serverIp_get(uint32 serverIdx, xxxx_ipv4_addr_t *pServerIp)
{
	ip_addr_t ipAddr;

	XXXX_PARA_CHK((serverIdx>=PROTO_XXXX_DNS_SERVER_NUM_MAX), XXXX_ERR_FAILED);
	XXXX_PARA_CHK((pServerIp==NULL), XXXX_ERR_FAILED);

	ipAddr = espconn_dns_getserver((uint8)serverIdx);
	UINT32_TO_IPV4_ADDR(*pServerIp, ipAddr.addr);

	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_dns_serverIp_set(uint32 serverIdx, xxxx_ipv4_addr_t *pServerIp)
{
	ip_addr_t ipAddr;

	XXXX_PARA_CHK((serverIdx>=PROTO_XXXX_DNS_SERVER_NUM_MAX), XXXX_ERR_FAILED);
	XXXX_PARA_CHK((pServerIp==NULL), XXXX_ERR_FAILED);

	IPV4_ADDR_TO_UINT32(*pServerIp, ipAddr.addr);
	espconn_dns_setserver((uint8)serverIdx, &ipAddr);

	return XXXX_ERR_OK;
}

