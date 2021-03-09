
#include "port.h"

static void prvTaskExitError( void )
{
    /* Func stop here. */
    for(;;);
}

StackType_t *pxPortInitialiseStack( StackType_t    * pxTopOfStack,
                                    TaskFunction_t   pxCode,
                                    void           * pvParameters )
{
    /* Auto load into CPU Regs when exception occurs. */
    pxTopOfStack--;
    *pxTopOfStack = portINITIAL_XPSR;
    pxTopOfStack--;
    *pxTopOfStack = ( ( StackType_t ) pxCode ) & portSTART_ADDRESS_MASK;
    pxTopOfStack--;
    *pxTopOfStack = ( StackType_t ) prvTaskExitError;
    pxTopOfStack -= 5;
    *pxTopOfStack = ( StackType_t ) pvParameters;

    /* Load into CPU Regs manually when exception occurs. */
    pxTopOfStack -= 8;

    /* This pointer should point to a null stack. */
    return pxTopOfStack;
}

/*
 * 参考资料《STM32F10xxx Cortex-M3 programming manual》 4.4.3，百度搜索“PM0056”即可找到这个文档
 * 在 Cortex-M 中，内核外设 SCB 的地址范围为： 0xE000ED00-0xE000ED3F
 * 0xE000ED008 为 SCB 外设中 SCB_VTOR 这个寄存器的地址，里面存放的是向量表的起始地址，即 MSP 的地址
 */
__asm void prvStartFirstTask( void )
{
    PRESERVE8

    /* 
     * 在 Cortex-M 中， 0xE000ED08 是 SCB_VTOR 这个寄存器的地址,
     * 里面存放的是向量表的起始地址,即 MSP 的地址
     */
    ldr r0, =0xe000ed08
    ldr r0, [r0]
    ldr r0, [r0]

    /*
     * 设置主堆栈指针 msp 的值 
     */
    msr msp, r0

    /* 使能全局中断 */
    cpsie i
    cpsie f
    dsb
    isb

    /* 调用 SVC 去启动第一个任务 */
    svc 0
    nop
    nop
}

__asm void vPortSVCHandler( void )
{
    extern pxCurrentTCB;

    PRESERVE8

    ldr   r3, =pxCurrentTCB
    ldr   r1, [r3]
    ldr   r0, [r1]
    ldmia r0!, {r4-r11}
    msr   psp, r0
    isb
    mov   r0, #0
    msr   basepri, r0
    orr   r14, #0xd

    bx    r14
}

__asm void xPortPendSVHandler( void )
{
    extern pxCurrentTCB;
    extern vTaskSwitchContext;

    PRESERVE8

    mrs   r0, psp
    isb

    ldr   r3, =pxCurrentTCB
    ldr   r2, [r3]

    stmdb sp!, {r3, r14}
    mov   r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
    msr   basepri, r0
    dsb
    isb
    bl    vTaskSwitchContext
    mov   r0, #0
    msr   basepri, r0
    ldmia sp!, {r3,r14}

    ldr   r1, [r3]
    ldr   r0, [r1]
    ldmia r0!, {r4-r11}
    msr   psp, r0
    isb
    bx    r14
    nop
}