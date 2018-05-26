#include "APC.h"
#pragma warning(disable: 4996)

typedef struct _APC {
	char ID[MAX_ID_LENGTH];
	PSoldier Soldiers[APC_MAX_Soldiers];
	int Stack_Top;
} APC;

//**************************************************************************************************************************************
//* Function name: Check_Valid_Id
//* Function description: Checks if the string id is a valid APC id.
//* Parameters: id - a pointer to a char that holds the APC id.
//* Return value: true is the id is valid and false otherwise
//**************************************************************************************************************************************
static bool Check_Valid_Id(char *id) {
	if (id == NULL || *id != 'A' || strlen(id) != SOLDIER_ID_LEN)
		return false;
	return true;
}

//**************************************************************************************************************************************
//* Function name: APC_Create
//* Function description: Creates an APC.
//* Parameters: id - a pointer to a char that holds the APC id.
//* Return value: A pointer to the new APC.
//**************************************************************************************************************************************
PAPC APC_Create(char *ID) {
	PAPC new_APC;
	if (!Check_Valid_Id(ID)) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	new_APC = (PAPC)malloc(sizeof(APC));
	if (new_APC == NULL) {
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	for (int i = 0; i <= APC_MAX_Soldiers; i++) {
		new_APC->Soldiers[i] = NULL;
	}
	strcpy(new_APC->ID, ID);
	new_APC->Stack_Top = 0;
	return new_APC;
}

//**************************************************************************************************************************************
//* Function name: APC_Delete
//* Function description: Deletes an APC.
//* Parameters: APC - a pointer to an APC.
//* Return value: void.
//**************************************************************************************************************************************
void APC_Delete(PAPC APC) {
	if (APC == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	while (APC->Stack_Top > 0)
	{
		Soldier_Delete(APC->Soldiers[APC->Stack_Top-1]);
		APC->Stack_Top--;
	}
	free(APC);
}

//**************************************************************************************************************************************
//* Function name: APC_Print
//* Function description: Prints the APC information.
//* Parameters: APC - a pointer to an APC.
//* Return value: void.
//**************************************************************************************************************************************
void APC_Print(PAPC APC) {
	if (APC == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	printf("%s , Occupancy: %d/%d\n", APC->ID, APC->Stack_Top, APC_MAX_Soldiers);
	if (APC->Stack_Top > 0) {
		for (int i = 0; i < APC->Stack_Top; i++) {
			printf("Seat %d: ", i + 1);
			Soldier_Print(APC->Soldiers[i]);
		}
	}
}

//**************************************************************************************************************************************
//* Function name: APC_Duplicate
//* Function description: Creates an exact copy of an APC.
//* Parameters: APC - a pointer to an APC.
//* Return value: A pointer to the new APC.
//**************************************************************************************************************************************
PAPC APC_Duplicate(PAPC APC) {
	PAPC new_APC = NULL;
	if (APC == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	new_APC = APC_Create(APC->ID);
	if (new_APC == NULL) {
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	int i = 0;
	while (i<=APC->Stack_Top-1)
	{
		new_APC->Soldiers[i] = Soldier_Duplicate(APC->Soldiers[i]);
		i++;
	}
	new_APC->Stack_Top = APC->Stack_Top;

	return new_APC;
}

//**************************************************************************************************************************************
//* Function name: APC_Insert_Soldier
//* Function description: Places a soldier into an APC.
//* Parameters: APC - a pointer to an APC.
//* Parameters: Soldier - a pointer to a Soldier.
//* Return value: The Result of the action.
//**************************************************************************************************************************************
Result APC_Insert_Soldier(PAPC APC, PSoldier Soldier){
	if ((APC == NULL) || (Soldier == NULL)) {
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	
	if (APC->Stack_Top >= APC_MAX_Soldiers) {
		printf(FULL_APC_MSG);
		return FAILURE;
	}
	APC->Soldiers[APC->Stack_Top] = Soldier;
	APC->Stack_Top++;
	return SUCCESS;
}

//**************************************************************************************************************************************
//* Function name: APC_Pop
//* Function description: Removes the top Soldier from the APC.
//* Parameters: APC - a pointer to an APC.
//* Return value: A pointer to the Soldier removed from the APC.
//**************************************************************************************************************************************
PSoldier APC_Pop(PAPC APC) {
	if (APC == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	if (APC->Stack_Top == 0)
	{
		printf(EMPTY_APC_MSG);
		return NULL;
	}
	PSoldier Soldier = APC->Soldiers[APC->Stack_Top - 1];
	APC->Stack_Top--;
	return Soldier;
}

//**************************************************************************************************************************************
//* Function name: APC_Get_Id
//* Function description: copies into id the id of the APC.
//* Parameters: pAPC - a pointer to an APC.
//* Parameters: id - a pointer to a string.
//* Return value: void.
//**************************************************************************************************************************************
void APC_Get_Id(PAPC pAPC, char* id){

    if(pAPC == NULL){
        printf(ARG_ERR_MSG);
        return;
    }

    strcpy(id,pAPC->ID);
}

//**************************************************************************************************************************************
//* Function name: APC_Get_Num_Soldiers
//* Function description: Returns the number of soldiers in the APC.
//* Parameters: pAPC - a pointer to an APC.
//* Return value: Number of soldiers in the APC.
//**************************************************************************************************************************************
int APC_Get_Num_Soldiers(PAPC pAPC){

	if(pAPC == NULL){
		printf(ARG_ERR_MSG);
		return 0;
	}

	return pAPC->Stack_Top;
}




