#include "Squad.h"

typedef struct _Squad {
	PList Soldiers;
	PList APCs;
	int Count;
	char ID[MAX_ID_LENGTH];
} Squad;

bool Check_Valid_ID(char *id){
	if(id == NULL || id[0] != 'S' || id[1] != 'q' || strlen(id) != SQUAD_ID_LEN){
		return false;
	}
	return true;
}

PSquad Squad_Create(char *id){
	PSquad new_squad = NULL;
	PList soldier_list = NULL;
	PList APC_list = NULL;

	if(Check_Valid_ID(id)){
		printf(ARG_ERR_MSG);
		return NULL;
	}

	new_squad = (PSquad)malloc(sizeof(Squad));
	if(new_squad == NULL){
		printf(MALLOC_ERR_MSG);
		return NULL;
	}

	soldier_list = List_Create(Soldier_Clone_Func,Soldier_Destroy_Func,Soldier_Compare_Keys_Func,Soldier_Print_Func,Soldier_Get_Key);
    if(soldier_list == NULL){
        printf(MALLOC_ERR_MSG);
        free(new_squad);
        return NULL;
    }
	APC_list = List_Create(APC_Clone_Func,APC_Destroy_Func,APC_Compare_Keys_Func,APC_Print_Func,APC_Get_Key);
    if(APC_list == NULL){
        printf(MALLOC_ERR_MSG);
        free(new_squad);
        List_Delete(APC_list);
        return NULL;
    }

    strcpy(new_squad->ID,id);
    new_squad->APCs = APC_list;
    new_squad->Soldiers = soldier_list;
    new_squad->Count = 0;

    return new_squad;
}


void Squad_Delete(PSquad psquad){

	if(psquad == NULL){
		printf(ARG_ERR_MSG);
		return;
	}

	List_Delete(psquad->Soldiers);
	List_Delete(psquad->APCs);
	free(psquad);
}

void Squad_Print(PSquad psquad){

	if(psquad == NULL){
		printf(ARG_ERR_MSG);
		return;
	}

	printf("Squad: %s , Total troops: %d\n",psquad->ID,psquad->Count);
	printf("APCs:\n");
	List_Print(psquad->APCs);
	printf("Soldiers:\n");
	List_Print(psquad->Soldiers);
}

PSquad Squad_Duplicate(PSquad old_squad){
	PSquad new_squad = NULL;

	if(old_squad == NULL){
		printf(ARG_ERR_MSG);
		return NULL;
	}

	new_squad = Squad_Create(old_squad->ID);
	if(new_squad == NULL){
		return NULL;
	}

	List_Duplicate(old_squad->Soldiers,new_squad->Soldiers);
	List_Duplicate(old_squad->APCs,new_squad->APCs);
	new_squad->Count = old_squad->Count;
	return new_squad;
}



/**User Functions**/
void Squad_Print_Func(PElem Data) {
	if (Data == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	Squad_Print((PSquad)Data);
}


/**Soldier list functions**/
PElem Soldier_Clone_Func(PElem pelem){
	PSoldier new_soldier = NULL;

    if(pelem == NULL){
        printf(ARG_ERR_MSG);
        return NULL;
    }

    new_soldier = Soldier_Duplicate((PSoldier)pelem);
	return new_soldier;
}

void Soldier_Destroy_Func(PElem pelem){

    if(pelem == NULL){
        printf(ARG_ERR_MSG);
    }

    Soldier_Delete((PSoldier)pelem);
}

bool Soldier_Compare_Keys_Func(PKey key1, PKey key2){

    if(key1 == NULL || key2 == NULL){
        printf(ARG_ERR_MSG);
        return NULL;
    }

    if(strcmp((char*)key1,(char*)key2) == 0){
        return true;
    }
    return false;
}

void Soldier_Print_Func(PElem pelem){

    if(pelem == NULL){
        printf(ARG_ERR_MSG);
    }

    Soldier_Print((PSoldier)pelem);
}

PKey Soldier_Get_Key(PElem pelem){

    if(pelem == NULL){
        printf(ARG_ERR_MSG);
        return NULL;
    }

    return Soldier_Get_Id((PSoldier)pelem);
}


