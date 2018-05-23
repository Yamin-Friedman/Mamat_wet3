#ifndef _LIST_H_
#define _LIST_H_

/**Includes**/
#include "defs.h"

typedef struct Node_ *PNode;
typedef struct List_ *PList;
typedef void *PElem;
typedef void *PKey;

typedef PElem (*CLONE_FUNC)(PElem);
typedef void  (*DESTROY_FUNC)(PElem);
typedef bool  (*COMPARE_KEYS_FUNC)(PKey,PKey);
typedef void  (*PRINT_FUNC)(PElem);
typedef PKey  (*GET_KEY)(PElem);

PList List_Create(CLONE_FUNC, DESTROY_FUNC, COMPARE_KEYS_FUNC, PRINT_FUNC, GET_KEY);
void List_Delete(PList);
void List_Print(PList);
Result List_Add_Elem(PList, PElem);
Result List_Remove_Elem(PList, PKey);
PElem List_Get_First(PList);
PElem List_Get_Next(PList);
void List_Duplicate(PList, PList);
PElem List_Get_Elem(PList, PKey);


#endif
