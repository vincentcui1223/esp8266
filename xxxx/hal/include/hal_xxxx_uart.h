#ifndef __HAL_XXXX_UART__
#define __HAL_XXXX_UART__

#include <xxxx_comm.h>

typedef enum hal_xxxx_uartId_e
{
	HAL_XXXX_UARTID_0,
	HAL_XXXX_UARTID_1,
	HAL_XXXX_UARTID_END
}hal_xxxx_uartId_t;

#define HAL_XXXX_UART_ID_XLATE_TO_CHIP(halId, chipId, ret) \
	do{	\
		ret = XXXX_ERR_OK;	\
		switch(halId)	\
		{	\
			case HAL_XXXX_UARTID_0:			\
				chipId	=	UART0; 			break;	\
			case HAL_XXXX_UARTID_1:			\
				chipId	=	UART1; 			break;	\
			default:	\
				ret = XXXX_ERR_FAILED;	\
		}	\
	}while(0)


typedef enum hal_xxxx_uart_baudrate_e
{
	HAL_XXXX_UART_BAUDRATE_300,
	HAL_XXXX_UART_BAUDRATE_600,
	HAL_XXXX_UART_BAUDRATE_1200,
	HAL_XXXX_UART_BAUDRATE_2400,
	HAL_XXXX_UART_BAUDRATE_4800,
	HAL_XXXX_UART_BAUDRATE_9600,
	HAL_XXXX_UART_BAUDRATE_19200,
	HAL_XXXX_UART_BAUDRATE_38400,
	HAL_XXXX_UART_BAUDRATE_57600,
	HAL_XXXX_UART_BAUDRATE_74880,
	HAL_XXXX_UART_BAUDRATE_115200,
	HAL_XXXX_UART_BAUDRATE_230400,
	HAL_XXXX_UART_BAUDRATE_460800,
	HAL_XXXX_UART_BAUDRATE_921600,
	HAL_XXXX_UART_BAUDRATE_1843200,
	HAL_XXXX_UART_BAUDRATE_3686400,
	HAL_XXXX_UART_BAUDRATE_END
}hal_xxxx_uart_baudrate_t;

#define HAL_XXXX_UART_BAUDRATE_XLATE_TO_CHIP(halRate, chipRate, ret) \
	do{	\
		ret = XXXX_ERR_OK;	\
		switch(halRate)	\
		{	\
			case HAL_XXXX_UART_BAUDRATE_300:			\
				chipRate	=	BIT_RATE_300; 			break;	\
			case HAL_XXXX_UART_BAUDRATE_600:			\
				chipRate	=	BIT_RATE_600; 			break;	\
			case HAL_XXXX_UART_BAUDRATE_1200:			\
				chipRate	=	BIT_RATE_1200; 			break;	\
			case HAL_XXXX_UART_BAUDRATE_2400:			\
				chipRate	=	BIT_RATE_2400;			break;	\
			case HAL_XXXX_UART_BAUDRATE_4800:			\
				chipRate	=	BIT_RATE_4800;			break;	\
			case HAL_XXXX_UART_BAUDRATE_9600:			\
				chipRate	=	BIT_RATE_9600; 			break;	\
			case HAL_XXXX_UART_BAUDRATE_19200:			\
				chipRate	=	BIT_RATE_19200; 		break;	\
			case HAL_XXXX_UART_BAUDRATE_38400:			\
				chipRate	=	BIT_RATE_38400; 		break;	\
			case HAL_XXXX_UART_BAUDRATE_57600:			\
				chipRate	=	BIT_RATE_57600;			break;	\
			case HAL_XXXX_UART_BAUDRATE_74880:			\
				chipRate	=	BIT_RATE_74880;			break;	\
			case HAL_XXXX_UART_BAUDRATE_115200:			\
				chipRate	=	BIT_RATE_115200; 		break;	\
			case HAL_XXXX_UART_BAUDRATE_230400:			\
				chipRate	=	BIT_RATE_230400;		break;	\
			case HAL_XXXX_UART_BAUDRATE_460800: 		\
				chipRate	=	BIT_RATE_460800;		break;	\
			case HAL_XXXX_UART_BAUDRATE_921600: 		\
				chipRate	=	BIT_RATE_921600;		break;	\
			case HAL_XXXX_UART_BAUDRATE_1843200: 		\
				chipRate	=	BIT_RATE_1843200;		break;	\
			case HAL_XXXX_UART_BAUDRATE_3686400: 		\
				chipRate	=	BIT_RATE_3686400;		break;	\
			default:	\
				ret = XXXX_ERR_FAILED;	\
		}	\
	}while(0)


extern int32 hal_xxxx_uart_init(hal_xxxx_uart_baudrate_t *pRate);
			
extern int32 hal_xxxx_uart_baudrate_get(hal_xxxx_uartId_t id, hal_xxxx_uart_baudrate_t *pRate);
extern int32 hal_xxxx_uart_baudrate_set(hal_xxxx_uartId_t id, hal_xxxx_uart_baudrate_t rate);

#endif

