#ifndef _Soldier_h
#define _Soldier_h


/*includes & defines*/
#include "defs.h"

typedef struct _Soldier *PSoldier;

//**************************************************************************************************************************************
//* Function name: Soldier_Create
//* Function description: Creates a soldier.
//* Parameters: id - a pointer to a char that holds the soldier id.
//* Parameters: pos - a pointer to a char that holds the soldier position.
//* Return value: A pointer to the new Soldier.
//**************************************************************************************************************************************
PSoldier Soldier_Create(char*, char*);
//**************************************************************************************************************************************
//* Function name: Soldier_Delete
//* Function description: Deletes a soldier.
//* Parameters: psoldier - a pointer to a soldier.
//* Return value: void.
//**************************************************************************************************************************************
void Soldier_Delete(PSoldier);
//**************************************************************************************************************************************
//* Function name: Soldier_Print
//* Function description: Prints the soldier information.
//* Parameters: psoldier - a pointer to a soldier.
//* Return value: void.
//**************************************************************************************************************************************
void Soldier_Print(PSoldier);
//**************************************************************************************************************************************
//* Function name: Soldier_Duplicate
//* Function description: Creates an exact copy of a soldier.
//* Parameters: Soldier - a pointer to a soldier.
//* Return value: A pointer to a new soldier.
//**************************************************************************************************************************************
PSoldier Soldier_Duplicate(PSoldier);
//**************************************************************************************************************************************
//* Function name: Soldier_Get_Id
//* Function description: returns a pointer to the id of the soldier.
//* Parameters: Soldier - a pointer to a soldier.
//* Return value: a pointer to the soldier id.
//**************************************************************************************************************************************
char *Soldier_Get_Id(PSoldier);


#endif
