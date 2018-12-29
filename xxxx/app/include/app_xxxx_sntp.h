#ifndef __APP_XXXX_SNTP_H__
#define __APP_XXXX_SNTP_H__

#include <xxxx_comm.h>
#include <sal_xxxx_timer.h>
#include <sal_xxxx_sntp.h>


#define APP_XXXX_SNTP_SYS_TIME_STRING_LEN_MAX 		30
#define APP_XXXX_SNTP_SYS_TIME_PRINT_INTERVER_MS	60000

extern char				sysTime[APP_XXXX_SNTP_SYS_TIME_STRING_LEN_MAX];
extern uint32			sysTimeStamp[2];
extern sal_xxxx_timer_t	app_xxxx_sntp_timer;


extern int32
app_xxxx_sntp_init(void);

#endif

