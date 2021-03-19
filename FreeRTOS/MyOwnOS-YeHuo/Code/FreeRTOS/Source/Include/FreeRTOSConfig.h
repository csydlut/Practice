#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_16_BIT_TICKS  0

#ifdef  __NVIC_PRIO_BITS
#define configPRIO_BITS                         __NVIC_PRIO_BITS
#else
#define configPRIO_BITS                         4
#endif

#define configSUPPORT_STATIC_ALLOCATION         1

#define configMAX_PRIORITIES                    5
#define configMAX_TASK_NAME_LEN                 16
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY 15
#define configKERNEL_INTERRUPT_PRIORITY         ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << ( 8 - configPRIO_BITS ) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 		191 /* equivalent to 0xb0, or priority 11. */

#define xPortPendSVHandler      PendSV_Handler
#define xPortSysTickHandler     SysTick_Handler
#define xPortSVCHandler         SVC_Handler


#endif /* FREERTOS_CONFIG_H */