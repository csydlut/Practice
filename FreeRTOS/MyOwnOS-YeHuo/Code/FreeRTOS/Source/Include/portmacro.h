#ifndef PORTMACRO_H
#define PORTMACRO_H

#include "stdint.h"
#include "stddef.h"

#include "FreeRTOSConfig.h"

/* Data type redefinition */
#define portCHAR               char
#define portFLOAT              float
#define portDOUBLE             double
#define portLONG               long
#define portSHORT              short
#define portSTACK_TYPE         uint32_t
#define portBASE_TYPE          long
/*
 * 中断控制状态寄存器： 0xe000ed04
 * Bit 28 PENDSVSET: PendSV 悬起位
 */
#define portNVIC_INT_CTRL_REG  (*(( volatile uint32_t * )0xe000ed04))
#define portNVIC_PENDSVSET_BIT ( 1UL << 28UL )
#define portSY_FULL_READ_WRITE ( 15 )

#define portYIELD()                                 \
{                                                   \
    /* 触发 PendSV，产生上下文切换 */                 \
    portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
    __dsb( portSY_FULL_READ_WRITE );                \
    __isb( portSY_FULL_READ_WRITE );                \
}                                                   \

typedef portSTACK_TYPE StackType_t;
typedef long           BaseType_t;
typedef unsigned long  UBaseType_t;

#if( configUSE_16_BIT_TICKS == 1 )
    typedef uint16_t TickType_t;   /* TickType_t Represent 16bits. */
    #define portMAX_DELAY ( TickType_t ) 0xffff
#else
    typedef uint32_t TickType_t;   /* TickType_t Represent 32bits. */
    #define portMAX_DELAY ( TickType_t ) 0xffffffffUL
#endif

#endif /* PORTMACRO_H */