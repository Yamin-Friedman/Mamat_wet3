#include "Soldier.h"
#pragma warning(disable: 4996)

static const char * const POSITIONS[NUM_POSITIONS] = {"DRIVER", "MED", "ENG", "INT", "GUNNER"};

typedef struct _Soldier {
	char Pos[MAX_ID_LENGTH];
	char ID[MAX_ID_LENGTH];
} Soldier;


//**************************************************************************************************************************************
//* Function name: Check_Valid_Pos
//* Function description: Checks if the string pos is a valid soldier position.
//* Parameters: pos - a pointer to a char that holds the soldier position.
//* Return value: true is the position is valid and false otherwise
//**************************************************************************************************************************************
static  bool Check_Valid_Pos(char *pos){
	int i;
	if (pos == NULL)
		return false;
	for(i = 0; i < NUM_POSITIONS; i++){
		if (strcmp(pos, POSITIONS[i]) == 0)
			return true;
	}
	return false;
}

//**************************************************************************************************************************************
//* Function name: Check_Valid_Id
//* Function description: Checks if the string id is a valid soldier id.
//* Parameters: id - a pointer to a char that holds the soldier id.
//* Return value: true is the id is valid and false otherwise
//**************************************************************************************************************************************
static bool Check_Valid_Id(char *id){
	if (id == NULL ||*id != 'S' || strlen(id) != SOLDIER_ID_LEN)
		return false;
	return true;
}

//**************************************************************************************************************************************
//* Function name: Soldier_Create
//* Function description: Creates a soldier.
//* Parameters: id - a pointer to a char that holds the soldier id.
//* Parameters: pos - a pointer to a char that holds the soldier position.
//* Return value: A pointer to the new Soldier.
//**************************************************************************************************************************************
PSoldier Soldier_Create(char *id, char *pos){
	PSoldier new_soldier = NULL;

	if (!Check_Valid_Id(id) || !Check_Valid_Pos(pos)) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	new_soldier = (PSoldier)malloc(sizeof(Soldier));
	if (new_soldier == NULL) {
		printf(MALLOC_ERR_MSG);
		return NULL;
	}

	strcpy(new_soldier->ID, id);
	strcpy(new_soldier->Pos, pos);
	return new_soldier;
}

//**************************************************************************************************************************************
//* Function name: Soldier_Delete
//* Function description: Deletes a soldier.
//* Parameters: psoldier - a pointer to a soldier.
//* Return value: void.
//**************************************************************************************************************************************
void Soldier_Delete(PSoldier psoldier){
	if (psoldier == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	free(psoldier);
}

//**************************************************************************************************************************************
//* Function name: Soldier_Print
//* Function description: Prints the soldier information.
//* Parameters: psoldier - a pointer to a soldier.
//* Return value: void.
//**************************************************************************************************************************************
void Soldier_Print(PSoldier Soldier) {
	if (Soldier == NULL) {
		printf(ARG_ERR_MSG);
		return ;
	}
	printf("%s , %s\n", Soldier->ID, Soldier->Pos);
}

//**************************************************************************************************************************************
//* Function name: Soldier_Duplicate
//* Function description: Creates an exact copy of a soldier.
//* Parameters: Soldier - a pointer to a soldier.
//* Return value: A pointer to a new soldier.
//**************************************************************************************************************************************
PSoldier Soldier_Duplicate(PSoldier Soldier) {
	PSoldier new_soldier = NULL;

	if (Soldier == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	new_soldier = Soldier_Create(Soldier->ID, Soldier->Pos);
	if (new_soldier == NULL) {
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	return new_soldier;
}

//**************************************************************************************************************************************
//* Function name: Soldier_Get_Id
//* Function description: copies into id the id of the soldier.
//* Parameters: Soldier - a pointer to a soldier.
//* Parameters: id - a pointer to a string.
//* Return value: void.
//**************************************************************************************************************************************
void Soldier_Get_Id(PSoldier psoldier, char *id){

    if(psoldier == NULL){
        printf(ARG_ERR_MSG);
        return;
    }

    strcpy(id,psoldier->ID);
}



