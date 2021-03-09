
/* Let FrreeRTOS.h work as main.h */
#include "FreeRTOS.h"

portCHAR flag1, flag2;

extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ];

TaskHandle_t Task1_Handle;
StackType_t  Task1Stack[ TASK1_STACK_SIZE ];
TCB_t        Task1TCB;

TaskHandle_t Task2_Handle;
StackType_t  Task2Stack[ TASK2_STACK_SIZE ];
TCB_t        Task2TCB;

void delay(uint32_t count);
void Task1_Entry( void *p_arg );
void Task2_Entry( void *p_arg );

int main( void )
{
    /* 初始化与任务相关的列表，如就绪列表 */
    prvInitialiseTaskLists();

    /* 创建任务 */
    Task1_Handle = xTaskCreateStatic( (TaskFunction_t)Task1_Entry,
                                      (char *)        "Task1",
                                      (uint32_t)      TASK1_STACK_SIZE,
                                      ( void *)       NULL,
                                      ( StackType_t *)Task1Stack,
                                      ( TCB_t *)      &Task1TCB    );
    /* 将任务添加到就绪列表 */
    vListInsertEnd( &( pxReadyTasksLists[1] ),
                    &( ((TCB_t *)(&Task1TCB))->xStateListItem ) );

    /* 创建任务 */
    Task2_Handle = xTaskCreateStatic( (TaskFunction_t)Task2_Entry,
                                      (char *)        "Task2",
                                      (uint32_t)      TASK2_STACK_SIZE,
                                      ( void *)       NULL,
                                      ( StackType_t *)Task2Stack,
                                      ( TCB_t *)      &Task2TCB    );
    /* 将任务添加到就绪列表 */
    vListInsertEnd( &( pxReadyTasksLists[2] ),
                    &( ((TCB_t *)(&Task2TCB))->xStateListItem ) );

    /* 启动调度器，开始多任务调度，启动成功则不返回 */
    vTaskStartScheduler();

    for(;;)
    {
        /* We wont be here unless the kernel failed to start. */
    }
}

void delay ( uint32_t count)
{
    for (; count!=0; count--);
}

void Task1_Entry( void *p_arg )
{
    for( ;; )
    {
        flag1 = 1;
        delay( 100 );
        flag1 = 0;
        delay( 100 );

        /* Trig the task switch manually. */
        taskYIELD();
    }
}

void Task2_Entry( void *p_arg )
{
    for( ;; )
    {
        flag2 = 1;
        delay( 100 );
        flag2 = 0;
        delay( 100 );

        /* Trig the task switch manually. */
        taskYIELD();
    }
}