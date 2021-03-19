#ifndef PORT_H
#define PORT_H

#include "portmacro.h"
#include "projdefs.h"

#define portINITIAL_XPSR       ( 0x01000000 )
#define portSTART_ADDRESS_MASK ( ( StackType_t ) 0xfffffffeUL )

#define portNVIC_SYSPRI2_REG (*(( volatile uint32_t *) 0xe000ed20))
#define portNVIC_PENDSV_PRI  ( ( (uint32_t) configKERNEL_INTERRUPT_PRIORITY ) << 16UL )
#define portNVIC_SYSTICK_PRI ( ( (uint32_t) configKERNEL_INTERRUPT_PRIORITY ) << 24UL )

static void prvTaskExitError( void );
StackType_t *pxPortInitialiseStack( StackType_t    * pxTopOfStack,
                                    TaskFunction_t   pxCode,
                                    void           * pvParameters );
void prvStartFirstTask( void );
void vPortSVCHandler( void );
void xPortPendSVHandler( void );

#endif /* PORT_H */