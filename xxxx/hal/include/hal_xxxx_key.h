#ifndef __HAL_XXXX_KEY_H__
#define __HAL_XXXX_KEY_H__

#include <xxxx_comm.h>

#define HAL_XXXX_KEY_FUNC_PRESS_CB 	key_function

typedef enum hal_xxxx_key_idx_e
{
	HAL_XXXX_KEY_RESET_IDX = 0,
	HAL_XXXX_KEY_NUM	
}hal_xxxx_key_idx_t;

typedef enum hal_xxxx_key_press_type_e
{
	HAL_XXXX_KEY_PRESS_TYPE_SHORT,
	HAL_XXXX_KEY_PRESS_TYPE_LONG,
	HAL_XXXX_KEY_PRESS_TYPE_END
}hal_xxxx_key_press_type_t;

typedef struct hal_xxxx_key_info_e
{	
	uint32 key_idx;
	uint32 gpio_id;
	uint32 gpio_func;
	uint32 gpio_name;
}hal_xxxx_key_info_t;

#define HAL_XXXX_KEY_RESET_PIN_ID		13
#define HAL_XXXX_KEY_RESET_PIN_FUNC		FUNC_GPIO13
#define HAL_XXXX_KEY_RESET_PIN_NAME		PERIPHS_IO_MUX_MTDI_U	

extern int32 hal_xxxx_key_init(void);

extern int32 hal_xxxx_key_press_cb_register(hal_xxxx_key_idx_t keyIdx, hal_xxxx_key_press_type_t pressType, HAL_XXXX_KEY_FUNC_PRESS_CB func);
extern int32 hal_xxxx_key_press_cb_unregister(hal_xxxx_key_idx_t keyIdx, hal_xxxx_key_press_type_t pressType);



#endif

