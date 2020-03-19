#include "linkedlist.h"
#include <stdlib.h>

int pomLinkedListInit( PomLinkedListCtx *_ctx ){
    _ctx->head = NULL;
    _ctx->tail = NULL;
    _ctx->size = 0;

    return 0;
}

int pomLinkedListClear( PomLinkedListCtx *_ctx ){
    // Iterate over the list, clearing nodes as we go
    PomLinkedListNode *cNode = _ctx->head;
    while( cNode ){
        PomLinkedListNode *nNode = cNode->next;
        free( cNode );
        cNode = nNode;
    }
    return 0;
}

int pomLinkedListAdd( PomLinkedListCtx *_ctx, PllKeyType key ){
    PomLinkedListNode *newNode = (PomLinkedListNode*) malloc( sizeof( PomLinkedListNode ) );
    newNode->key = key;
    newNode->next = NULL;
    if( !_ctx->head ){
        newNode->prev = NULL;
        _ctx->head = newNode;
        _ctx->tail = newNode;
        _ctx->size = 1;
        return 0;
    }
    newNode->prev = _ctx->tail;
    _ctx->tail->next = newNode;
    _ctx->tail = newNode;
    return 0;
}

PomLinkedListNode * pomLinkedListFind( PomLinkedListCtx *_ctx, PllKeyType _key ){
    for( PomLinkedListNode *node = _ctx->head; node; node=node->next ){
        if( _key == node->key ){
            return node;
        }
    }
    return NULL;
}

int pomLinkedListPopFront( PomLinkedListCtx *_ctx, PllKeyType *_keyValue ){
    if( _ctx->size == 0 ){
        return 0;
    }
    if( _ctx->head == NULL ){
        // Some error, size should have been 0
        return 0;
    }

    if( _ctx->head == _ctx->tail ){
        // Last time in list
        *_keyValue = _ctx->head->key;
        free( _ctx->head );
        _ctx->head = _ctx->tail = NULL;
    }else{
        *_keyValue = _ctx->head->key;
        PomLinkedListNode *nNode = _ctx->head->next;
        free( _ctx->head );
        _ctx->head = nNode;
    }
    return 1;


}