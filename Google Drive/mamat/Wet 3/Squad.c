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
	APC_list = List_Create(APC_Clone_Func,APC_Destroy_Func,APC_Compare_Keys_Func,APC_Print_Func,APC_Get_Key);


}

PSquad Squad_Duplicate(PSquad Squad) {
	if (Squad == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PList Soldiers = Squad_Get_Soldiers(Squad);
	PList APCs = Squad_Get_APCs(Squad);
	PSquad New_Squad = Squad_Create(Squad->ID, List_Get_Clone_Func(Soldiers), List_Get_Des_Func(Soldiers), List_Get_Cmp_Func(Soldiers), List_Get_Print_Func(Soldiers),
												List_Get_Clone_Func(APCs), List_Get_Des_Func(APCs), List_Get_Cmp_Func(APCs), List_Get_Print_Func(APCs));
	if (New_Squad == NULL) {
		return NULL;
	}
	List_Duplicate(Squad->APCs, New_Squad->APCs);
	List_Duplicate(Squad->Soldiers, New_Squad->Soldiers);
	New_Squad->Count = Squad->Count;
	return New_Squad;
}


/**User Functions**/
void Squad_Print_Func(PElem Data) {
	if (Data == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	Squad_Print((PSquad)Data);
}

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


