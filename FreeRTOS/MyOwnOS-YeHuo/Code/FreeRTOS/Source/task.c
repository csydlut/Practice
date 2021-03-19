
#include "task.h"
#include "list.h"

/* Define a task ready list. */
List_t pxReadyTasksLists[ configMAX_PRIORITIES ];

TCB_t * volatile pxCurrentTCB = NULL;

extern TaskHandle_t Task1_Handle, Task2_Handle;
extern TCB_t        Task1TCB, Task2TCB;

#if( configSUPPORT_STATIC_ALLOCATION  == 1 )
/* Create Task. Allocate statically. */
TaskHandle_t xTaskCreateStatic( TaskFunction_t      pxTaskCode,
                                const char * const  pcName,
                                const uint32_t      ulStackDepth,
                                void * const        pvParameters,
                                StackType_t * const puxStackBuffer,
                                TCB_t * const       pxTaskBuffer )
{
    TCB_t *pxNewTCB;
    TaskHandle_t xReturn;

    if ( ( pxTaskBuffer != NULL ) && ( puxStackBuffer != NULL ) )
    {
        pxNewTCB          = ( TCB_t * ) pxTaskBuffer;
        pxNewTCB->pxStack = ( StackType_t * ) puxStackBuffer;

        /* Create a new task. */
        prvInitialiseNewTask( pxTaskCode,    /* Task Entry. */
                              pcName,        /* Task name. String name. */
                              ulStackDepth,  /* Task stack quantity. */
                              pvParameters,  /* Task Param. */
                              &xReturn,      /* Task Handler */
                              pxNewTCB);     /* Start Addr of Task stack. */
    }
    else
    {
        xReturn = NULL;
    }

    /* Return Task handler.
       If the task already created, xReturn should point to TCB. */
    return xReturn;
}
#endif /* configSUPPORT_STATIC_ALLOCATION */

void prvInitialiseTaskLists( void )
{
    UBaseType_t uxPriority;

    for( uxPriority = ( UBaseType_t ) 0U;
         uxPriority < ( UBaseType_t ) configMAX_PRIORITIES;
         uxPriority++ )
    {
        vListInitialise( &( pxReadyTasksLists[ uxPriority ] ) );
    }
}

static void prvInitialiseNewTask( 			TaskFunction_t 			 pxTaskCode,
                                  const char* 				 const pcName,
                                  const uint32_t       			 ulStackDepth,
																				void*          const pvParameters,
																				TaskHandle_t*  const pxCreatedTask,
																				TCB_t*               pxNewTCB )
{
    StackType_t *pxTopOfStack;
    UBaseType_t  x;

    /* Obtain the addr of the top location of the stack. */
    pxTopOfStack = pxNewTCB->pxStack + ( ulStackDepth - ( uint32_t ) 1 );
    
    /* Align downward. */
    pxTopOfStack = ( StackType_t * ) ( ( ( uint32_t ) pxTopOfStack ) & ( ~( ( uint32_t ) 0x0007 ) ) );

    /* Store the task name in TCB. */
    for ( x = ( UBaseType_t ) 0; x < ( UBaseType_t ) configMAX_TASK_NAME_LEN; x++)
    {
        pxNewTCB->pcTaskName[ x ] = pcName[ x ];

        if ( pcName[ x ] == 0x00 )
        {
            break;
        }
    }

    /* Make the task handler point to TCB.
       Length of the task name couldnt longer than
       configMAX_TASK_NAME_LEN */
    pxNewTCB->pcTaskName[ configMAX_TASK_NAME_LEN - 1 ] = '\0';

    /* Init xStateListItem node of the TCB. */
    vListInitialiseItem( &( pxNewTCB->xStateListItem ) );

    /* Set up the owner of xStateListItem node. */
    listSET_LIST_ITEM_OWNER( &( pxNewTCB->xStateListItem ) ,pxNewTCB );

    /* Init task stack. */
    pxNewTCB->pxTopOfStack = pxPortInitialiseStack( pxTopOfStack, 
                                                    pxTaskCode, 
                                                    pvParameters );

    /* Make the task handler point to TCB. */
    if ( ( void * ) pxCreatedTask != NULL )
    {
        *pxCreatedTask = ( TaskHandle_t ) pxNewTCB;
    }
    
}



void vTaskStartScheduler( void )
{
    /* Point out the first task manually. */
    pxCurrentTCB = &Task1TCB;

    /* Start the scheduler. */
    if ( xPortStartScheduler() != pdFALSE )
    {
        /* If scheduler started successfully.
           We wont never be here. */
    }
}

void vTaskSwitchContext( void )
{
    if ( pxCurrentTCB == &Task1TCB )
    {
        pxCurrentTCB = &Task2TCB;
    }
    else
    {
        pxCurrentTCB = &Task1TCB;
    }
}

BaseType_t xPortStartScheduler( void )
{
    /* Set the PendSV and Systick INT Priority to lowest */
    portNVIC_SYSPRI2_REG |= portNVIC_PENDSV_PRI;
    portNVIC_SYSPRI2_REG |= portNVIC_SYSTICK_PRI;

    /* Start first task and never return. */
    prvStartFirstTask();

    /* Should never be here. */
    return 0;
}