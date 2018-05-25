#ifndef _Squad_h
#define _Squad_h


/*includes & defines*/
#include "defs.h"
#include "Soldier.h"
#include "APC.h"
#include "List.h"

typedef struct _Squad *PSquad;

/*Squad Function Declarations*/
PSquad Squad_Create(char*);
void Squad_Delete(PSquad);
void Squad_Print(PSquad);
PSquad Squad_Duplicate(PSquad);
Result Squad_Add_Soldier(PSquad, char*, char*);
Result Squad_Add_APC(PSquad, char*);
Result Squad_Insert_Sold_APC(PSquad, char*, char*);
Result Squad_APC_Pop(PSquad, char*);
Result Squad_Delete_Soldier(PSquad, char*);
Result Squad_Delete_APC(PSquad, char*);
char* Squad_Get_ID(PSquad,char*);

/*List Functions*/

void Squad_Print_Func(PElem Data);

PElem Soldier_Clone_Func(PElem);
void Soldier_Destroy_Func(PElem);
bool Soldier_Compare_Keys_Func(PKey , PKey);
void Soldier_Print_Func(PElem);
PKey Soldier_Get_Key(PElem);

PElem APC_Clone_Func(PElem);
void APC_Destroy_Func(PElem);
bool APC_Compare_Keys_Func(PKey, PKey);
void APC_Print_Func(PElem);
PKey APC_Get_Key(PElem);


#endif