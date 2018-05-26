#ifndef _Battlefield_h
#define _Battlefield_h

/*includes & defines*/
#include "WarZone.h"
typedef struct _Battlefield *PBattlefield;

PBattlefield Battlefield_Create();

/**Warzone List Functions**/
PElem WarZone_Clone_Func(PElem);
void WarZone_Destroy_Func(PElem);
bool WarZone_Compare_Keys_Func(PKey, PKey);
void WarZone_Print_Func(PElem);
PKey WarZone_Get_Key(PElem);

#endif
