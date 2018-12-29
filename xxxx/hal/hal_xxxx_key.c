

#include <hal_xxxx_key.h>

LOCAL struct keys_param keys;
LOCAL struct single_key_param *pSinglekey[HAL_XXXX_KEY_NUM];

LOCAL hal_xxxx_key_info_t key_list[HAL_XXXX_KEY_NUM] =
{
	{
		.key_idx	=	HAL_XXXX_KEY_RESET_IDX,
		.gpio_id	=	GPIO_ID_PIN(HAL_XXXX_KEY_RESET_PIN_ID),
		.gpio_func	=	HAL_XXXX_KEY_RESET_PIN_FUNC,
		.gpio_name	=	HAL_XXXX_KEY_RESET_PIN_NAME,
	},
};


int32 ICACHE_FLASH_ATTR
hal_xxxx_key_init(void)
{
	uint32 i;

	for(i=0;i<HAL_XXXX_KEY_NUM; i++)
	{
		pSinglekey[i] = NULL;
		pSinglekey[i] = key_init_single(key_list[i].gpio_id, key_list[i].gpio_name, key_list[i].gpio_func, NULL, NULL);
		if(NULL==pSinglekey[i])
			RETURN(XXXX_ERR_FAILED);
	}

	/*init all system key*/
	keys.key_num 		= HAL_XXXX_KEY_NUM;
	keys.single_key	= pSinglekey;
	key_init(&keys);

	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR
hal_xxxx_key_press_cb_register(hal_xxxx_key_idx_t keyIdx, hal_xxxx_key_press_type_t pressType, HAL_XXXX_KEY_FUNC_PRESS_CB func)
{
	XXXX_PARA_CHK((keyIdx>=HAL_XXXX_KEY_NUM), XXXX_ERR_FAILED);
	
	switch(pressType)
	{
		case HAL_XXXX_KEY_PRESS_TYPE_SHORT:
			keys.single_key[keyIdx]->short_press	= func; break;
		case HAL_XXXX_KEY_PRESS_TYPE_LONG:
			keys.single_key[keyIdx]->long_press 	= func; break;
		default:
			RETURN(XXXX_ERR_FAILED);
	}
	
	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR
hal_xxxx_key_press_cb_unregister(hal_xxxx_key_idx_t keyIdx, hal_xxxx_key_press_type_t pressType)
{
	XXXX_PARA_CHK((keyIdx>=HAL_XXXX_KEY_NUM), XXXX_ERR_FAILED);

	switch(pressType)
	{
		case HAL_XXXX_KEY_PRESS_TYPE_SHORT:
			keys.single_key[keyIdx]->short_press	= NULL; break;
		case HAL_XXXX_KEY_PRESS_TYPE_LONG:
			keys.single_key[keyIdx]->long_press 	= NULL; break;
		default:
			RETURN(XXXX_ERR_FAILED);
	}
	return XXXX_ERR_OK;
}


