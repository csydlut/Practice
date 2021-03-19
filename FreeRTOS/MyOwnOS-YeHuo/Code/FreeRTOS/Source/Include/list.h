#ifndef LIST_H
#define LIST_H

#include "portmacro.h"

struct xLIST_ITEM
{
        TickType_t xItemValue;              /* Assist Value. Helping List to sorting node. */
        struct     xLIST_ITEM * pxNext;     /* Pointing to next node. */
        struct     xLIST_ITEM * pxPrevious; /* Pointing to previous node */
        void       * pvOwner;               /* Pointing to the owner of the List. Often owned by TCB */
        void       * pvContainer;           /* Pointing to the owner of this node. */
};

struct xMINI_LIST_ITEM
{
        TickType_t          xItemValue;  /* Assist Value. Helping List to sorting node. */
        struct xLIST_ITEM * pxNext;      /* Pointing to next node. */
        struct xLIST_ITEM * pxPrevious;  /* Pointing to previous node */
};
typedef struct xMINI_LIST_ITEM MiniListItem_t; /* Rename the Mini node Type. */

typedef struct xLIST_ITEM ListItem_t;       /* Rename the Node Type. */

typedef struct xLIST
{
        UBaseType_t    uxNumberOfItems; /* Node quantity counter. */
        ListItem_t   * pxIndex;         /* Node index pointer. */
        MiniListItem_t xListEnd;        /* The last Node of List. */
}List_t;



/* Init Node Owner. */
#define listSET_LIST_ITEM_OWNER( pxListItem, pxOwner )  \
        ( ( pxListItem )->pvOwner = ( void * ) ( pxOwner ) )

/* Obtain Node Owner. */
#define listGET_LIST_ITEM_OWNER( pxListItem )  \
        ( ( pxListItem )->pvOwner )

/* Init Node Assist Value. */
#define listSET_LIST_ITEM_VALUE( pxListItem, xValue )   \
        ( ( pxListItem )->xItemValue )

/* Obtain Node Assist Value. */
#define listGET_LIST_ITEM_VALUE( pxListItem )  \
        ( ( pxListItem )->xItemValue )

/* Obtain node counter value of the root node. */
#define listGET_ITEM_VALUE_OF_HEAD_ENTRY( pxList )  \
        ( ( ( pxList )->xListEnd ).pxNext->xItemValue )

/* Obtain the entry node of list. */
#define listGET_HEAD_ENTRY( pxList )  \
        ( ( ( pxList )->xListEnd ).pxNext )

/* Obtain the next node of specify node. */
#define listGET_NEXT( pxListItem )  \
        ( ( pxListItem )->pxNext )

/* Obtain the last node of list. */
#define listGET_END_MARKER( pxList ) \
        ( ( ListItem_t const * ) ( &( ( pxList )->xListEnd ) ) )

/* Judge whether the list is null. */
#define listLIST_IS_EMPTY( pxList )  \
        ( ( UBaseType_t ) ( ( pxList )->uxNumberOfItems == ( UBaseType_t )0 ) )

/* Obtain node quan */
#define listCURRENT_LIST_LENGTH( pxList )  \
        ( ( pxList )->uxNumberOfItems )

/*  */
#define listGET_OWNER_OF_NEXT_ENTRY( pxTCB, pxList )																						\
{																																																\
        List_t * const pxConstList = ( pxList );																								\
        ( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;														\
        if ( ( void * ) ( pxConstList )->pxIndex == ( void * ) &( ( pxConstList )->xListEnd ) )	\
        {																																												\
                ( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;										\
        }																																												\
        ( pxTCB ) = ( pxConstList )->pxIndex->pvOwner;																					\
}																																																\

/* Function Prototype. */
void vListInitialiseItem( ListItem_t * const pxItem );
void vListInitialise( List_t * const pxList );
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem );
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem );
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove );

#endif /* LIST_H */
