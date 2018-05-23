#ifndef _Soldier_h
#define _Soldier_h


/*includes & defines*/
#include "defs.h"

typedef struct _Soldier *PSoldier;


PSoldier Soldier_Create(char*, char*);
void Soldier_Delete(PSoldier);
void Soldier_Print(PSoldier);
PSoldier Soldier_Duplicate(PSoldier);
char* Soldier_Get_Id(PSoldier);


#endif
