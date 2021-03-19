#ifndef TASK_H
#define TASK_H

#include "list.h"

#include "projdefs.h"
#include "portmacro.h"
#include "FreeRTOS.h"

#include "FreeRTOSConfig.h"

#define TASK1_STACK_SIZE      128
//StackType_t Task1Stack[TASK1_STACK_SIZE];

#define TASK2_STACK_SIZE      128
//StackType_t Task2Stack[TASK2_STACK_SIZE];

#define taskYIELD()           portYIELD()

/*
 * 参考资料《STM32F10xxx Cortex-M3 programming manual》 4.4.3，百度搜索“PM0056”即可找到这个文档
 * 在 Cortex-M 中，内核外设 SCB 中 SHPR3 寄存器用于设置 SysTick 和 PendSV 的异常优先级
 * System handler priority register 3 (SCB_SHPR3) SCB_SHPR3： 0xE000 ED20
 * Bits 31:24 PRI_15[7:0]: Priority of system handler 15, SysTick exception
 * Bits 23:16 PRI_14[7:0]: Priority of system handler 14, PendSV
 */
#define portNVIC_SYSPRI2_REG  ( *( ( volatile uint32_t * ) 0xe000ed20 ) )
#define portNVIC_PENDSV_PRI   ( ( ( uint32_t ) configKERNEL_INTERRUPT_PRIORITY ) << 16UL )
#define portNVIC_SYSTICK_PRI  ( ( ( uint32_t ) configKERNEL_INTERRUPT_PRIORITY ) << 24UL )

typedef struct tskTaskControlBlock
{
    volatile StackType_t *pxTopOfStack;
    ListItem_t            xStateListItem; //List node of the task
    StackType_t          *pxStack;
    char                  pcTaskName[ configMAX_TASK_NAME_LEN ];
}tskTCB;

typedef tskTCB TCB_t;

/* Task Handler*/
typedef void * TaskHandle_t;

TaskHandle_t xTaskCreateStatic( 			TaskFunction_t    	 pxTaskCode,
                                const char*    			 const pcName,
                                const uint32_t     	 			 ulStackDepth,
																			void* 			   const pvParameters,
																			StackType_t* 	 const puxStackBuffer,
																			TCB_t* 				 const pxTaskBuffer );
																			
static void prvInitialiseNewTask( 			TaskFunction_t 			 pxTaskCode,
                                  const char*	 				 const pcName,
                                  const uint32_t      			 ulStackDepth,
																				void* 				 const pvParameters,
																				TaskHandle_t*  const pxCreatedTask,
																				TCB_t*							 pxNewTCB );

void prvInitialiseTaskLists( void );
void vTaskStartScheduler( void );
void vTaskSwitchContext( void );
BaseType_t xPortStartScheduler( void );

#endif /* TASK_H */