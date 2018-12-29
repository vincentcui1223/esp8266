#include <sal_xxxx_timer.h>

int32 ICACHE_FLASH_ATTR  
sal_xxxx_timer_init(sal_xxxx_timer_t *pTimer, SAL_XXXX_TIMER_CB_FUNC cb_func, void* pArg)
{
	XXXX_PARA_CHK(pTimer==NULL, XXXX_ERR_FAILED);
	XXXX_PARA_CHK(cb_func==NULL, XXXX_ERR_FAILED);
	os_timer_setfn(pTimer, cb_func, pArg);
	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR  
sal_xxxx_timer_enable(sal_xxxx_timer_t *pTimer, uint32 intervel, uint32 repeat_if)
{
	XXXX_PARA_CHK(pTimer==NULL, XXXX_ERR_FAILED);
	XXXX_PARA_CHK(intervel==0, XXXX_ERR_FAILED);
	os_timer_arm(pTimer, intervel, (repeat_if?TRUE:FALSE));
	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR  
sal_xxxx_timer_disable(sal_xxxx_timer_t *pTimer)
{
	XXXX_PARA_CHK(pTimer==NULL, XXXX_ERR_FAILED);
	os_timer_disarm(pTimer);
	return XXXX_ERR_OK;
}



