#ifndef _Battlefield_h
#define _Battlefield_h

/*includes & defines*/
#include "WarZone.h"
typedef struct _Battlefield *PBattlefield;

PBattlefield Battlefield_Create();
void Battlefield_Delete(PBattlefield);
Result Battlefield_Add_WarZone(PBattlefield, char*);
Result Battlefield_Delete_WarZone(PBattlefield, char*);
Result Battlefield_Add_Squad(PBattlefield, char*, char*);
Result Battlefield_Delete_Squad(PBattlefield, char*, char*);
Result Battlefield_Add_APC(PBattlefield, char*, char*, char*);
Result Battlefield_Delete_APC(PBattlefield, char*, char*, char*);
Result Battlefield_Add_Soldier(PBattlefield, char*, char*, char*, char*);
Result Battlefield_Delete_Soldier(PBattlefield, char*, char*, char*);

/**Warzone List Functions**/
PElem WarZone_Clone_Func(PElem);
void WarZone_Destroy_Func(PElem);
bool WarZone_Compare_Keys_Func(PKey, PKey);
void WarZone_Print_Func(PElem);
PKey WarZone_Get_Key(PElem);

#endif
