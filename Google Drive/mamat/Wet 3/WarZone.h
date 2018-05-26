#ifndef _WarZone_h
#define _WarZone_h


/*includes & defines*/
#include "defs.h"
#include "Soldier.h"
#include "APC.h"
#include "List.h"
#include "Squad.h"

typedef struct _WarZone *PWarZone;

/*Squad Function Declarations*/


/*List Functions*/

PElem Squad_Clone_Func(PElem);
void Squad_Destroy_Func(PElem);
bool Squad_Compare_Keys_Func(PKey , PKey);
void Squad_Print_Func(PElem);
PKey Squad_Get_Key_Func(PElem);


#endif
