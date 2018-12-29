#ifndef __XXXX_COMM_H__
#define __XXXX_COMM_H__

#include "c_types.h"
#include "ets_sys.h"
#include "osapi.h"
#include "user_interface.h"

#include <driver/key.h>
#include <driver/uart.h>

#include <espconn.h>
#include <sntp.h>

#include <smartconfig.h>

typedef enum dbg_print_level_e
{
	DEB_PRINTF_LEVEL_FUNCTION_TRACK = 	(1<<0), //track function call
	DEB_PRINTF_LEVEL_FUNCTION_TBD 	= 	(1<<1), //track function call
	DEB_PRINTF_LEVEL_COMM			=	(1<<31),
	DEB_PRINTF_LEVEL_ALL 			=  	0xffffffff
}dbg_print_level_t;

extern dbg_print_level_t xxxx_dbg_level;

typedef enum xxxx_err_e
{
	XXXX_ERR_FAILED	= -1, 
	XXXX_ERR_OK = 0,
	XXXX_ERR_END
}xxxx_err_t;

#define osal_printf os_printf

#define VOID_RETURN()	\
    do{ \
        osal_printf("Error!...FILE:%s---FUN:%s---LINE:%d\n", __FILE__, __FUNCTION__ , __LINE__);  \
        return;    \
    }while(0)


#define RETURN(errCode) \
    do{ \
        osal_printf("Error!...FILE:%s---FUN:%s---LINE:%d, ret=0x%x\n", __FILE__, __FUNCTION__ , __LINE__, errCode);  \
        return errCode;    \
    }while(0)

#define XXXX_ERR_CHK(op, ret)	\
	do {\
		if ((ret=op)!=XXXX_ERR_OK) \
			RETURN(ret);	\
	} while(0)
#define XXXX_ERR_CHK_VOID_RETURN(op, ret)	\
	do {\
		if ((ret=op)!=XXXX_ERR_OK) \
			VOID_RETURN();	\
	} while(0)	
#define XXXX_ERR_CHK_ERRCODE(op, ret, errCode)	\
	do {\
		if ((ret=op)!=errCode) \
			RETURN(XXXX_ERR_FAILED);	\
	} while(0)


#define XXXX_PARA_CHK(op, ret)	\
	do {\
		if (op) \
			RETURN(ret);	\
	} while(0)
#define XXXX_PARA_CHK_VOID_RETURN(op)	\
	do {\
		if (op) \
			VOID_RETURN();	\
	} while(0)


#define     IPV4_ADDR_LEN   4
typedef struct xxxx_ipv4_addr_s
{
	uint8	octet[IPV4_ADDR_LEN];
}xxxx_ipv4_addr_t;


#define     MAC_ADDR_LEN   6
typedef struct xxxx_mac_addr_s
{
	uint8	octet[MAC_ADDR_LEN];
}xxxx_mac_addr_t;


#define DBG_PRINT(x, level)   	\
	do{	\
		if(xxxx_dbg_level&(level))	\
		{	\
			osal_printf("%s:%u: in %s():", __FILE__, __LINE__, __FUNCTION__); \
			osal_printf x; \
		}	\
	}while(0)

#define	DBG_PRINT_FUNC_ENTER() 		DBG_PRINT(("Entering.......\n"), DEB_PRINTF_LEVEL_FUNCTION_TRACK)
#define	DBG_PRINT_FUNC_LEAVE() 		DBG_PRINT(("Leaving.......\n"), DEB_PRINTF_LEVEL_FUNCTION_TRACK)
#define	DBG_PRINT_FUNC_TBD() 		DBG_PRINT(("TBD.......\n"), DEB_PRINTF_LEVEL_FUNCTION_TBD)

typedef enum comm_xxxx_config_type_e
{
	COMM_XXXX_CONFIG_TYPE_CURRENT,
	COMM_XXXX_CONFIG_TYPE_FLASH,
	COMM_XXXX_CONFIG_TYPE_END
}comm_xxxx_config_type_t;

typedef enum comm_xxxx_enable_e
{
	DISABLED 	= 	0,
	ENABLED  	=	1,
}comm_xxxx_enable_t;


#define BYTE_MASK(x)	((1<<((x)*8))-1)
#define BIT_MASK(x)		((1<<((x)))-1)

#define IPV4_UINT32(a,b,c,d)	(((a)<<0) | ((b)<<8) | ((c)<<16) | ((d)<<24))

#define IPV4_ADDR_TO_UINT32(ipv4, data32)	\
	do {\
		data32 = ((ipv4).octet[0]<<0) | ((ipv4).octet[1]<<8) | ((ipv4).octet[2]<<16) | ((ipv4).octet[3]<<24);	\
	} while(0)
#define UINT32_TO_IPV4_ADDR(ipv4, data32)	\
	do {\
		(ipv4).octet[0] = (data32>>0) & 0xff;	\
		(ipv4).octet[1] = (data32>>8) & 0xff;	\
		(ipv4).octet[2] = (data32>>16) & 0xff;		\
		(ipv4).octet[3] = (data32>>24) & 0xff;		\
	} while(0)


#define TEST_UDP_ROUT_XIAOMI 	1
#define TEST_UDP_BC_IF 			1

#endif	

