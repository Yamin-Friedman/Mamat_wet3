#ifndef _APC_h
#define _APC_h

/*includes & defines*/
#include "defs.h"
#include "Soldier.h"
#define FULL_APC_MSG "Error: APC is Full\n"
#define EMPTY_APC_MSG "Error: APC is Empty\n"

typedef struct _APC *PAPC;

PAPC APC_Create(char*);
void APC_Delete(PAPC);
void APC_Print(PAPC);
PAPC APC_Duplicate(PAPC);
Result APC_Insert_Soldier(PAPC, PSoldier);
PSoldier APC_Pop(PAPC);
char* APC_Get_Id(PAPC, char*);
int APC_Get_Num_Soldiers(PAPC);

#endif
