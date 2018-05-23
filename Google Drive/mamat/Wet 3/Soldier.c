#include "Soldier.h"

static const char * const POSITIONS[NUM_POSITIONS] = {"DRIVER", "MED", "ENG", "INT", "GUNNER"};

typedef struct _Soldier {
	char Pos[MAX_ID_LENGTH];
	char ID[MAX_ID_LENGTH];
} Soldier;

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

static bool Check_Valid_Id(char *id){
	if (id == NULL ||*id != 'S' || strlen(id) != SOLDIER_ID_LEN)
		return false;
	return true;
}


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

void Soldier_Delete(PSoldier psoldier){
	if (psoldier == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	free(psoldier);
}

void Soldier_Print(PSoldier Soldier) {
	if (Soldier == NULL) {
		printf(ARG_ERR_MSG);
		return ;
	}
	printf("%s , %s\n", Soldier->ID, Soldier->Pos);
}

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

char* Soldier_Get_Id(PSoldier psoldier){

    if(psoldier == NULL){
        printf(ARG_ERR_MSG);
        return NULL;
    }

    return psoldier->ID;//not sure if this is the right way to do this
}



