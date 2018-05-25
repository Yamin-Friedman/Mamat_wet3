#include "APC.h"

typedef struct _APC {
	char ID[MAX_ID_LENGTH];
	PSoldier Soldiers[APC_MAX_Soldiers];
	int Stack_Top;
} APC;

static bool Check_Valid_Id(char *id) {
	if (id == NULL || *id != 'A' || strlen(id) != SOLDIER_ID_LEN)
		return false;
	return true;
}

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

Result APC_Insert_Soldier(PAPC APC, PSoldier Soldier){
	if ((APC == NULL) || (Soldier == NULL)) {
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	
	if (APC->Stack_Top >= APC_MAX_Soldiers) {
		printf(FULL_APC_MSG);
		return FAILURE;
	}
	APC->Soldiers[APC->Stack_Top] = Soldier;//I think we should use soldier duplicate here
	APC->Stack_Top++;
	return SUCCESS;
}

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

char* APC_Get_Id(PAPC pAPC){
    char id[MAX_ID_LENGTH];

    if(pAPC == NULL){
        printf(ARG_ERR_MSG);
        return NULL;
    }

    strcpy(id,pAPC->ID);

    return id;
}

int APC_Get_Num_Soldiers(PAPC pAPC){

	if(pAPC == NULL){
		printf(ARG_ERR_MSG);
		return 0;
	}

	return pAPC->Stack_Top;
}




