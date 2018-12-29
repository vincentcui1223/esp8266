
#include <hal_xxxx_uart.h>

LOCAL hal_xxxx_uart_baudrate_t uart_baudrate[HAL_XXXX_UARTID_END]={HAL_XXXX_UART_BAUDRATE_9600};

int32 ICACHE_FLASH_ATTR 
hal_xxxx_uart_init(hal_xxxx_uart_baudrate_t *pRate)
{
	int32 ret;
	XXXX_PARA_CHK((pRate==NULL), XXXX_ERR_FAILED);
	UartBautRate chipRate[2];

	HAL_XXXX_UART_BAUDRATE_XLATE_TO_CHIP(*pRate, chipRate[0], ret);
	if(ret!=XXXX_ERR_OK)
		RETURN(ret);
	HAL_XXXX_UART_BAUDRATE_XLATE_TO_CHIP(*(pRate+1), chipRate[1], ret);
	if(ret!=XXXX_ERR_OK)
		RETURN(ret);
	
	uart_init(chipRate[0], chipRate[1]);

	os_delay_us(100000);

	return XXXX_ERR_OK;
}

int32 ICACHE_FLASH_ATTR 
hal_xxxx_uart_baudrate_get(hal_xxxx_uartId_t id, hal_xxxx_uart_baudrate_t *pRate)
{
	int32 ret;

	XXXX_PARA_CHK((id>=HAL_XXXX_UARTID_END), XXXX_ERR_FAILED);
	XXXX_PARA_CHK((pRate==NULL), XXXX_ERR_FAILED);

	*pRate = uart_baudrate[id];

	return XXXX_ERR_OK;
}


int32 ICACHE_FLASH_ATTR 
hal_xxxx_uart_baudrate_set(hal_xxxx_uartId_t id, hal_xxxx_uart_baudrate_t rate)
{
	int32 ret;
	UartBautRate chipRate;
	uint32 		 chipUartId;

	HAL_XXXX_UART_ID_XLATE_TO_CHIP(id, chipUartId, ret);
	if(ret!=XXXX_ERR_OK)
		RETURN(ret);
	HAL_XXXX_UART_BAUDRATE_XLATE_TO_CHIP(rate, chipRate, ret);
	if(ret!=XXXX_ERR_OK)
		RETURN(ret);

	UART_SetBaudrate(chipUartId, chipRate);

	return XXXX_ERR_OK;
}


