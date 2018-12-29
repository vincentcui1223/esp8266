#ifndef __PROTO_XXXX_SNTP_H__
#define __PROTO_XXXX_SNTP_H__

#include <xxxx_comm.h>

#define PROTO_XXXX_SNTP_SERVER_NUM_MAX 3

typedef struct sal_xxxx_sntp_realTime_s
{
	uint32 year;
	uint32 month;
	uint32 day;
	uint32 hour;
	uint32 minute;
	uint32 second;
}sal_xxxx_sntp_realTime_t;

extern int32
sal_xxxx_sntp_serverIp_get(uint32 serverIdx, xxxx_ipv4_addr_t *pServerIp);
extern int32
sal_xxxx_sntp_serverIp_set(uint32 serverIdx, xxxx_ipv4_addr_t *pServerIp);

extern int32
sal_xxxx_sntp_serverName_get(uint32 serverIdx, char** serverName);
extern int32
sal_xxxx_sntp_serverName_set(uint32 serverIdx, char* serverName);

extern int32 
sal_xxxx_sntp_start(void);
extern int32 
sal_xxxx_sntp_stop(void);

/*time zone is -11~13*/
extern int32 
sal_xxxx_sntp_timeZone_get(int32 *pTimeZone);
extern int32 
sal_xxxx_sntp_timeZone_set(int32 timeZone);

extern int32 
sal_xxxx_sntp_timeStamp_get(uint32 *pTimeStamp);
extern int32 
sal_xxxx_sntp_realTime_get(char* timeString);


#endif

