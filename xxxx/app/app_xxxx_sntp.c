#include <app_xxxx_sntp.h>


char				sysTime[APP_XXXX_SNTP_SYS_TIME_STRING_LEN_MAX];
uint32				sysTimeStamp[2];
sal_xxxx_timer_t	app_xxxx_sntp_timer;

LOCAL void ICACHE_FLASH_ATTR
_app_xxxx_sntp_timer_cb(void *arg)
{
	int32 ret;
	
	XXXX_ERR_CHK_VOID_RETURN(sal_xxxx_sntp_timeStamp_get(sysTimeStamp), ret);
	XXXX_ERR_CHK_VOID_RETURN(sal_xxxx_sntp_realTime_get(sysTime), ret);
	os_printf("sntp: time=%d-%d, realType=%s\n", sysTimeStamp[0], sysTimeStamp[1], sysTime);

	return;
}


int32 ICACHE_FLASH_ATTR
app_xxxx_sntp_init(void)
{
	int32 ret;

	XXXX_ERR_CHK(sal_xxxx_sntp_stop(), ret);

	XXXX_ERR_CHK(sal_xxxx_sntp_timeZone_set(8), ret);	/*for china*/
	XXXX_ERR_CHK(sal_xxxx_sntp_serverName_set(0, "0.cn.pool.ntp.org"), ret);
	XXXX_ERR_CHK(sal_xxxx_sntp_serverName_set(1, "1.cn.pool.ntp.org"), ret);
	XXXX_ERR_CHK(sal_xxxx_sntp_serverName_set(2, "2.cn.pool.ntp.org"), ret);

	XXXX_ERR_CHK(sal_xxxx_sntp_start(), ret);

	sal_xxxx_timer_disable(&app_xxxx_sntp_timer);
	sal_xxxx_timer_init(&app_xxxx_sntp_timer, _app_xxxx_sntp_timer_cb , NULL);
	sal_xxxx_timer_enable(&app_xxxx_sntp_timer,	APP_XXXX_SNTP_SYS_TIME_PRINT_INTERVER_MS,	1);
	
	return XXXX_ERR_OK;
}


