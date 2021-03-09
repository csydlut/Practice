
#include "list.h"

/* Init a node. */
void vListInitialiseItem( ListItem_t * const pxItem )
{
    /*  */
    pxItem->pvContainer = NULL;
}

/* Init a List. */
void vListInitialise( List_t * const pxList )
{
    /* Step1: Point the index to the last node. */
    pxList->pxIndex = ( ListItem_t * ) &( pxList->xListEnd );

    /* Step2: Change the assist value of last node to max value. 
       Ensure the node is the last node of list. */
    pxList->xListEnd.xItemValue = portMAX_DELAY;

    /* Step3: Point the next and previous node of last node to itself. 
       Represent the list is null. */
    pxList->xListEnd.pxNext = ( ListItem_t * ) &( pxList->xListEnd );
    pxList->xListEnd.pxPrevious = ( ListItem_t * ) &( pxList->xListEnd );

    /* Step4: Init list counter to zero. 
       Represent the list is null. */
    pxList->uxNumberOfItems = ( UBaseType_t ) 0U;
}

/* Insert a node to the end of a list. */
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem )
{
    ListItem_t * const pxIndex = pxList->pxIndex;

    pxNewListItem->pxNext     = pxIndex;
    pxNewListItem->pxPrevious = pxIndex->pxPrevious;

    pxIndex->pxPrevious->pxNext = pxNewListItem;
    pxIndex->pxPrevious         = pxNewListItem;

    /* Step1: Remember the owner of this node. */
    pxNewListItem->pvContainer = ( void * ) pxList;

    /* Step2: Increse list node counter. */
    ( pxList->uxNumberOfItems )++;
}

/* Insert a node into a list with ascending order. */
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem )
{
    ListItem_t *pxIterator;

    /* Step1: Obtain the assist value of this node. */
    const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;

    /* Step2: Find the location for insertion. */
    if ( xValueOfInsertion == portMAX_DELAY )
    {
        pxIterator = pxList->xListEnd.pxPrevious;
    }
    else
    {
        for( pxIterator = ( ListItem_t * ) &( pxList->xListEnd );
             pxIterator->pxNext->xItemValue <= xValueOfInsertion;
             pxIterator = pxIterator->pxNext )
        {
            /* Do nothing here. 
               Iterating only in order to find the insert location. */
        }
    }
    
    /* Step3: Insert node with ascending order. */
    pxNewListItem->pxNext             = pxIterator->pxNext;
    pxNewListItem->pxNext->pxPrevious = pxNewListItem;
    pxNewListItem->pxPrevious         = pxIterator;
    pxIterator->pxNext                = pxNewListItem;

    /* Step4: Remember the node owner. */
    pxNewListItem->pvContainer = ( void * ) pxList;

    /* Step5: Increase the list node counter. */
    ( pxList->uxNumberOfItems )++;
}

/* Brief:  Remove a node from a list.
   Param:  
   Return: Remain quantity of list. */
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove )
{
    /* Step1: Obtain the node owner. */
    List_t * const pxList = ( List_t * ) pxItemToRemove->pvContainer;

    /* Step2: Remove specify node from list. */
    pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
    pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;

    /* Step3: Adjust index pointer of the node. */
    if ( pxList->pxIndex == pxItemToRemove)
    {
        pxList->pxIndex = pxItemToRemove->pxPrevious;
    }
    
    /* Step4: Adjust the owner of node into null. 
       Represent the node didnt insert into any list */
    pxItemToRemove->pvContainer = NULL;

    /* Step5: Decrease list node counter. */
    ( pxList->uxNumberOfItems )--;
    
    return pxList->uxNumberOfItems;
}