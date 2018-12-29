
#include <hal_xxxx_key.h>
#include <app_xxxx_reboot.h>


LOCAL ICACHE_FLASH_ATTR void
_app_xxxx_reboot_sysReboot_cb(void)
{
	int32 ret;
	XXXX_ERR_CHK_VOID_RETURN(hal_xxxx_sys_reboot(), ret);
	return;
}

int32 ICACHE_FLASH_ATTR
app_xxxx_reboot_init(void)
{
	int32 ret;
	
	XXXX_ERR_CHK(hal_xxxx_key_press_cb_register(HAL_XXXX_KEY_RESET_IDX, HAL_XXXX_KEY_PRESS_TYPE_SHORT, _app_xxxx_reboot_sysReboot_cb), ret);

	return XXXX_ERR_OK;
}

