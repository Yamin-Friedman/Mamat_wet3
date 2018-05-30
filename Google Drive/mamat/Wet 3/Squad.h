#ifndef _Squad_h
#define _Squad_h


/*includes & defines*/
#include "defs.h"
#include "Soldier.h"
#include "APC.h"
#include "List.h"

typedef struct _Squad *PSquad;

/*Squad Function Declarations*/
//**************************************************************************************************************************************
//* Function name: Squad_Create
//* Function description: Creates a squad.
//* Parameters: id - a pointer to a char that holds the squad id.
//* Return value: A pointer to the new squad.
//**************************************************************************************************************************************
PSquad Squad_Create(char*);
//**************************************************************************************************************************************
//* Function name: Squad_Delete
//* Function description: Deletes a squad.
//* Parameters: psquad - a pointer to a squad.
//* Return value: void.
//**************************************************************************************************************************************
void Squad_Delete(PSquad);
//**************************************************************************************************************************************
//* Function name: Squad_Print
//* Function description: Prints the squad information.
//* Parameters: psquad - a pointer to a squad.
//* Return value: void.
//**************************************************************************************************************************************
void Squad_Print(PSquad);
//**************************************************************************************************************************************
//* Function name: Squad_Duplicate
//* Function description: Creates an exact copy of a squad.
//* Parameters: old_squad - a pointer to a quad.
//* Return value: A pointer to a new squad.
//**************************************************************************************************************************************
PSquad Squad_Duplicate(PSquad);
//**************************************************************************************************************************************
//* Function name: Squad_Add_Soldier
//* Function description: Adds a soldier to the squad.
//* Parameters: psquad - a pointer to a squad.
//* Parameters: id - a pointer to a char that holds the soldier id.
//* Parameters: pos - a pointer to a char that holds the soldier position.
//* Return value: The Result of the action.
//**************************************************************************************************************************************
Result Squad_Add_Soldier(PSquad, char*, char*);
//**************************************************************************************************************************************
//* Function name: Squad_Add_APC
//* Function description: Adds an APC to the squad.
//* Parameters: psquad - a pointer to a squad.
//* Parameters: id - a pointer to a char that holds the APC id.
//* Return value: The Result of the action.
//**************************************************************************************************************************************
Result Squad_Add_APC(PSquad, char*);
//**************************************************************************************************************************************
//* Function name: Squad_Insert_Sold_APC
//* Function description: Inserts a soldier that is in the squad into an APC that is in the squad.
//* Parameters: psquad - a pointer to a squad.
//* Parameters: sold_id - a pointer to a char that holds the soldier id.
//* Parameters: APC_id - a pointer to a char that holds the APC id.
//* Return value: The Result of the action.
//**************************************************************************************************************************************
Result Squad_Insert_Sold_APC(PSquad, char*, char*);
//**************************************************************************************************************************************
//* Function name: Squad_APC_Pop
//* Function description: Removes the top soldier from an APC that is in the squad and places him as a soldier in the squad.
//* Parameters: psquad - a pointer to a squad.
//* Parameters: APC_id - a pointer to a char that holds the APC id.
//* Return value: The Result of the action.
//**************************************************************************************************************************************
Result Squad_APC_Pop(PSquad, char*);
//**************************************************************************************************************************************
//* Function name: Squad_Delete_Soldier
//* Function description: Removes a soldier from the squad.
//* Parameters: psquad - a pointer to a squad.
//* Parameters: soldier_id - a pointer to a char that holds the soldier id.
//* Return value: The Result of the action.
//**************************************************************************************************************************************
Result Squad_Delete_Soldier(PSquad, char*);
//**************************************************************************************************************************************
//* Function name: Squad_Delete_APC
//* Function description: Removes an APC from the squad.
//* Parameters: psquad - a pointer to a squad.
//* Parameters: APC_id - a pointer to a char that holds the APC id.
//* Return value: The Result of the action.
//**************************************************************************************************************************************
Result Squad_Delete_APC(PSquad, char*);
//**************************************************************************************************************************************
//* Function name: Squad_Get_Id
//* Function description: returns a pointer to the id of the squad.
//* Parameters: psquad - a pointer to a squad.
//* Return value: A pointer to a string with the squad ID.
//**************************************************************************************************************************************
char *Squad_Get_ID(PSquad);
//**************************************************************************************************************************************
//* Function name: Squad_Get_APC
//* Function description: Returns a pointer to an APC based on id if the APC is in the squad.
//* Parameters: psquad - a pointer to a squad.
//* Parameters: id - a pointer to a string with the APC id.
//* Return value: A pointer to an APC.
//**************************************************************************************************************************************
PAPC Squad_Get_APC(PSquad,char*);
//**************************************************************************************************************************************
//* Function name: Squad_Get_First_APC
//* Function description: Returns a pointer to the first APC in the squad list.
//* Parameters: psquad - a pointer to a squad.
//* Return value: A pointer to an APC.
//**************************************************************************************************************************************
PAPC Squad_Get_First_APC(PSquad);
//**************************************************************************************************************************************
//* Function name: Squad_Get_Next_APC
//* Function description: Returns a pointer to the next APC in the squad list.
//* Parameters: psquad - a pointer to a squad.
//* Return value: A pointer to an APC.
//**************************************************************************************************************************************
PAPC Squad_Get_Next_APC(PSquad);
//**************************************************************************************************************************************
//* Function name: Squad_Get_First_Soldier
//* Function description: Returns a pointer to the first soldier in the squad list.
//* Parameters: psquad - a pointer to a squad.
//* Return value: A pointer to a soldier.
//**************************************************************************************************************************************
PSoldier Squad_Get_First_Soldier(PSquad);
//**************************************************************************************************************************************
//* Function name: Squad_Get_Next_Soldier
//* Function description: Returns a pointer to the next soldier in the squad list.
//* Parameters: psquad - a pointer to a squad.
//* Return value: A pointer to a soldier.
//**************************************************************************************************************************************
PSoldier Squad_Get_Next_Soldier(PSquad);

/*List Functions*/


//**************************************************************************************************************************************
//* Function name: Soldier_Clone_Func
//* Function description: User clone function for using the list ADT with soldiers.
//* Parameters: pelem - a pointer to a list element.
//* Return value: A pointer to a list element.
//**************************************************************************************************************************************
PElem Soldier_Clone_Func(PElem);
//**************************************************************************************************************************************
//* Function name: Soldier_Destroy_Func
//* Function description: User destroy function for using the list ADT with soldiers.
//* Parameters: pelem - a pointer to a list element.
//* Return value: Void.
//**************************************************************************************************************************************
void Soldier_Destroy_Func(PElem);
//**************************************************************************************************************************************
//* Function name: Soldier_Compare_Keys_Func
//* Function description: User compare keys function for using the list ADT with soldiers.
//* Parameters: key1 - a pointer to a list key.
//* Parameters: key2 - a pointer to a list key.
//* Return value: A bool that is true if the keys are the same.
//**************************************************************************************************************************************
bool Soldier_Compare_Keys_Func(PKey , PKey);
//**************************************************************************************************************************************
//* Function name: Soldier_Print_Func
//* Function description: User print function for using the list ADT with soldiers.
//* Parameters: pelem - a pointer to a list element.
//* Return value: Void.
//**************************************************************************************************************************************
void Soldier_Print_Func(PElem);
//**************************************************************************************************************************************
//* Function name: Soldier_Get_Key
//* Function description: User get key function for using the list ADT with soldiers.
//* Parameters: pelem - a pointer to a list element.
//* Return value: A pointer to a list key.
//**************************************************************************************************************************************
PKey Soldier_Get_Key(PElem);

//**************************************************************************************************************************************
//* Function name: APC_Clone_Func
//* Function description: User clone function for using the list ADT with APCs.
//* Parameters: pelem - a pointer to a list element.
//* Return value: A pointer to a list element.
//**************************************************************************************************************************************
PElem APC_Clone_Func(PElem);
//**************************************************************************************************************************************
//* Function name: APC_Destroy_Func
//* Function description: User destroy function for using the list ADT with APCs.
//* Parameters: pelem - a pointer to a list element.
//* Return value: Void.
//**************************************************************************************************************************************
void APC_Destroy_Func(PElem);
//**************************************************************************************************************************************
//* Function name: APC_Compare_Keys_Func
//* Function description: User compare keys function for using the list ADT with APCs.
//* Parameters: pelem - a pointer to a list element.
//* Return value: A bool that is true if the keys are the same.
//**************************************************************************************************************************************
bool APC_Compare_Keys_Func(PKey, PKey);
//**************************************************************************************************************************************
//* Function name: APC_Print_Func
//* Function description: User print function for using the list ADT with APCs.
//* Parameters: pelem - a pointer to a list element.
//* Return value: Void.
//**************************************************************************************************************************************
void APC_Print_Func(PElem);
//**************************************************************************************************************************************
//* Function name: APC_Get_Key
//* Function description: User get key function for using the list ADT with APCs.
//* Parameters: pelem - a pointer to a list element.
//* Return value: A pointer to a list key.
//**************************************************************************************************************************************
PKey APC_Get_Key(PElem);


#endif