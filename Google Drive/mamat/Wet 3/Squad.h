#ifndef _Squad_h
#define _Squad_h


/*includes & defines*/
#include "defs.h"
#include "Soldier.h"
#include "APC.h"
#include "List.h"

typedef struct _Squad *PSquad;

PElem Soldier_Clone_Func(PElem);
void Soldier_Destroy_Func(PElem);
bool Soldier_Compare_Keys_Func(PKey , PKey);
void Soldier_Print_Func(PElem);
PKey Soldier_Get_Key(PElem);



#endif