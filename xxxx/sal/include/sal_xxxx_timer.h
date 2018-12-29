#ifndef __SAL_XXXX_TIMER_H__
#define __SAL_XXXX_TIMER_H__

#include <xxxx_comm.h>

#define	sal_xxxx_timer_t os_timer_t


typedef void ETSTimerFunc(void *timer_arg);
#define SAL_XXXX_TIMER_CB_FUNC	ETSTimerFunc


extern int32  
sal_xxxx_timer_init(sal_xxxx_timer_t *pTimer, SAL_XXXX_TIMER_CB_FUNC cb_func, void* pArg);
extern int32  
sal_xxxx_timer_enable(sal_xxxx_timer_t *pTimer, uint32 intervel, uint32 repeat_if);
extern int32  
sal_xxxx_timer_disable(sal_xxxx_timer_t *pTimer);


#endif

