#include <sal_xxxx_sntp.h>

int32 ICACHE_FLASH_ATTR
sal_xxxx_sntp_serverIp_get(uint32 serverIdx, xxxx_ipv4_addr_t *pServerIp)
{
	ip_addr_t ipAddr;

	XXXX_PARA_CHK((serverIdx>=PROTO_XXXX_SNTP_SERVER_NUM_MAX), XXXX_ERR_FAILED);
	XXXX_PARA_CHK((pServerIp==NULL), XXXX_ERR_FAILED);

	ipAddr = sntp_getserver((uint8)serverIdx);
	UINT32_TO_IPV4_ADDR(*pServerIp, ipAddr.addr);

	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_sntp_serverIp_set(uint32 serverIdx, xxxx_ipv4_addr_t *pServerIp)
{
	ip_addr_t ipAddr;

	XXXX_PARA_CHK((serverIdx>=PROTO_XXXX_SNTP_SERVER_NUM_MAX), XXXX_ERR_FAILED);
	XXXX_PARA_CHK((pServerIp==NULL), XXXX_ERR_FAILED);

	IPV4_ADDR_TO_UINT32(*pServerIp, ipAddr.addr);
	sntp_setserver((uint8)serverIdx, &ipAddr);

	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR
sal_xxxx_sntp_serverName_get(uint32 serverIdx, char** serverName)
{
	XXXX_PARA_CHK((serverIdx>=PROTO_XXXX_SNTP_SERVER_NUM_MAX), XXXX_ERR_FAILED);
	XXXX_PARA_CHK((serverName==NULL), XXXX_ERR_FAILED);

	char* name = sntp_getservername((uint8)serverIdx);
	*serverName = name;

	return XXXX_ERR_OK;
}
int32 ICACHE_FLASH_ATTR
sal_xxxx_sntp_serverName_set(uint32 serverIdx, char* serverName)
{
	XXXX_PARA_CHK((serverIdx>=PROTO_XXXX_SNTP_SERVER_NUM_MAX), XXXX_ERR_FAILED);
	XXXX_PARA_CHK((serverName==NULL), XXXX_ERR_FAILED);

	sntp_setservername((uint8)serverIdx, serverName);

	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR 
sal_xxxx_sntp_start(void)
{
	sntp_init();
	return XXXX_ERR_OK;
}
int32 ICACHE_FLASH_ATTR 
sal_xxxx_sntp_stop(void)
{
	sntp_stop();
	return XXXX_ERR_OK;
}

/*time zone is -11~13*/
int32 ICACHE_FLASH_ATTR 
sal_xxxx_sntp_timeZone_get(int32 *pTimeZone)
{
	XXXX_PARA_CHK((pTimeZone==NULL), XXXX_ERR_FAILED);

	*pTimeZone = sntp_get_timezone();
	return XXXX_ERR_OK;
}
int32 ICACHE_FLASH_ATTR 
sal_xxxx_sntp_timeZone_set(int32 timeZone)
{
	int32 ret;
	XXXX_PARA_CHK(((timeZone>13)||(timeZone<-11)), XXXX_ERR_FAILED);
	
	XXXX_ERR_CHK_ERRCODE(sntp_set_timezone((sint8)timeZone), ret, TRUE);
	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR 
sal_xxxx_sntp_timeStamp_get(uint32 *pTimeStamp)
{
	XXXX_PARA_CHK((pTimeStamp==NULL), XXXX_ERR_FAILED);
	
	uint64 time = sntp_get_current_timestamp();
	pTimeStamp[0]	=	(time>>32)&0xffffffff;
	pTimeStamp[1]	=	time&0xffffffff;
	return XXXX_ERR_OK;
}
int32 ICACHE_FLASH_ATTR 
sal_xxxx_sntp_realTime_get(char* pRealTime)
{
	char *time;

	XXXX_PARA_CHK((pRealTime==NULL), XXXX_ERR_FAILED);

	time = sntp_get_real_time(sntp_get_current_timestamp());
	os_strcpy(pRealTime, time);

	/*Sample: Thu Apr 28 13:55:22 2016*/

	return XXXX_ERR_OK;
}


