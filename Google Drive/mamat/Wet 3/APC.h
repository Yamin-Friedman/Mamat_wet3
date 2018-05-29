#ifndef _APC_h
#define _APC_h

/*includes & defines*/
#include "defs.h"
#include "Soldier.h"
#define FULL_APC_MSG "Error: APC is Full\n"
#define EMPTY_APC_MSG "Error: APC is Empty\n"

typedef struct _APC *PAPC;

//**************************************************************************************************************************************
//* Function name: APC_Create
//* Function description: Creates an APC.
//* Parameters: id - a pointer to a char that holds the APC id.
//* Return value: A pointer to the new APC.
//**************************************************************************************************************************************
PAPC APC_Create(char*);
//**************************************************************************************************************************************
//* Function name: APC_Delete
//* Function description: Deletes an APC.
//* Parameters: APC - a pointer to an APC.
//* Return value: void.
//**************************************************************************************************************************************
void APC_Delete(PAPC);
//**************************************************************************************************************************************
//* Function name: APC_Print
//* Function description: Prints the APC information.
//* Parameters: APC - a pointer to an APC.
//* Return value: void.
//**************************************************************************************************************************************
void APC_Print(PAPC);
//**************************************************************************************************************************************
//* Function name: APC_Duplicate
//* Function description: Creates an exact copy of an APC.
//* Parameters: APC - a pointer to an APC.
//* Return value: A pointer to the new APC.
//**************************************************************************************************************************************
PAPC APC_Duplicate(PAPC);
//**************************************************************************************************************************************
//* Function name: APC_Insert_Soldier
//* Function description: Places a soldier into an APC.
//* Parameters: APC - a pointer to an APC.
//* Parameters: Soldier - a pointer to a Soldier.
//* Return value: The Result of the action.
//**************************************************************************************************************************************
Result APC_Insert_Soldier(PAPC, PSoldier);
//**************************************************************************************************************************************
//* Function name: APC_Pop
//* Function description: Removes the top Soldier from the APC.
//* Parameters: APC - a pointer to an APC.
//* Return value: A pointer to the Soldier removed from the APC.
//**************************************************************************************************************************************
PSoldier APC_Pop(PAPC);
//**************************************************************************************************************************************
//* Function name: APC_Get_Id
//* Function description: returns a pointer to the id of the APC.
//* Parameters: pAPC - a pointer to an APC.
//* Return value: A pointer to the APC id.
//**************************************************************************************************************************************
char *APC_Get_Id(PAPC);
//**************************************************************************************************************************************
//* Function name: APC_Get_Num_Soldiers
//* Function description: Returns the number of soldiers in the APC.
//* Parameters: pAPC - a pointer to an APC.
//* Return value: Number of soldiers in the APC.
//**************************************************************************************************************************************
int APC_Get_Num_Soldiers(PAPC);

#endif
