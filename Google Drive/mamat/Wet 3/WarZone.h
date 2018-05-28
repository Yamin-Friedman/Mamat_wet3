#ifndef _WarZone_h
#define _WarZone_h


/*includes & defines*/
#include "defs.h"
#include "Soldier.h"
#include "APC.h"
#include "List.h"
#include "Squad.h"

typedef struct _WarZone *PWarZone;


/*WarZone Function Declarations*/

PWarZone Warzone_Create(char*);
void WarZone_Delete(PWarZone);
void WarZone_Print(PWarZone);
PWarZone WarZone_Duplicate(PWarZone);
int WarZone_Raise_Alert(PWarZone);
Result WarZone_Move_Squad(PWarZone,PWarZone,PSquad);
void WarZone_Get_ID(PWarZone, char*);
PList WarZone_Get_List(PWarZone);
PSquad WarZone_Get_First_Squad(PWarZone);
PSquad WarZone_Get_Next_Squad(PWarZone);

/*Squad list Function Declarations*/

PElem Squad_Clone_Func(PElem);
void Squad_Destroy_Func(PElem);
bool Squad_Compare_Keys_Func(PKey , PKey);
void Squad_Print_Func(PElem);
PKey Squad_Get_Key_Func(PElem);


#endif
