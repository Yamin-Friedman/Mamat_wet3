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

	if(Check_Valid_ID(id) == false){// I added "== false" because before it returned an error for a correct id.
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
		List_Delete(soldier_list);//Don't know if necessary
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

Result Squad_Add_Soldier(PSquad psquad, char *id, char *pos) {
	PSoldier new_soldier;
	Result res;
	if (psquad == NULL) {
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	new_soldier = Soldier_Create(id, pos);
	if (new_soldier == NULL) {
		return FAILURE;
	}
	res = List_Add_Elem(psquad->Soldiers, new_soldier);
	return res;
}

Result Squad_Add_APC(PSquad psquad, char *id) {
	PAPC new_APC;
	Result res;
	if (psquad == NULL) {
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	new_APC = APC_Create(id);
	if (new_APC == NULL) {
		return FAILURE;
	}
	res = List_Add_Elem(psquad->APCs, new_APC);
	return res;
}

Result Squad_Insert_Sold_APC(PSquad psquad, char *sold_id, char *APC_id) {
	PSoldier soldier;
	PAPC APC;
	Result res;
	if (psquad == NULL) {
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	soldier = List_Get_Elem(psquad->Soldiers, sold_id);
	APC = List_Get_Elem(psquad->APCs, APC_id);
	if ((soldier == NULL) || (APC == NULL)) {
		return FAILURE;
	}
	res = APC_Insert_Soldier(APC, soldier);
    if(res){
        List_Remove_Elem(psquad->Soldiers,sold_id); //Soldiers are either in the soldier list or in APCs
    }
	return res;
}


Result Squad_APC_Pop(PSquad psquad, char *APC_id){
    PSoldier soldier = NULL;
    PAPC APC = NULL;
    Result res;

    if(psquad == NULL || APC_id == NULL){
        printf(ARG_ERR_MSG);
        return FAILURE;
    }

    APC = List_Get_Elem(psquad->APCs,APC_id);
    soldier = APC_Pop(APC);
    if(soldier == NULL){
        // Maybe print message
        return FAILURE;
    }
    res = List_Add_Elem(psquad->Soldiers,soldier);

    return res;
}

Result Squad_Delete_Soldier(PSquad psquad, char *soldier_id){
    Result res;

    if(psquad == NULL || soldier_id == NULL){
        printf(ARG_ERR_MSG);
        return FAILURE;
    }

    res = List_Remove_Elem(psquad->Soldiers,soldier_id);

    return res;
}


// So far I wrote this on the assumption that you can't delete an APC that has soldiers in it
Result Squad_Delete_APC(PSquad psquad, char *APC_id){
	Result res;
	PAPC APC = NULL;

	if(psquad == NULL || APC_id == NULL){
		printf(ARG_ERR_MSG);
		return FAILURE;
	}

	APC = List_Get_Elem(psquad->APCs,APC_id);
	if(APC == NULL){
        return FAILURE;
	}

	if(APC_Get_Num_Soldiers(APC)){
        // maybe print message
        return FAILURE;
	}

    res = List_Remove_Elem(psquad->APCs,APC_id);

    return res;
}

char* Squad_Get_ID(PSquad psquad){
	char id[MAX_ID_LENGTH];

	if(psquad == NULL){
		printf(ARG_ERR_MSG);
		return FAILURE;
	}

	strcpy(id,psquad->ID);

	return id;
}



/**User Functions**/

//Why define Squad functions here and not in WarZone?
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
        return false; // hope this is right
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

/**APC list functions**/

PElem APC_Clone_Func(PElem pelem) {
	PAPC new_APC;
	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	new_APC = APC_Duplicate((PAPC)pelem);
	return new_APC;
}

void APC_Destroy_Func(PElem pelem) {
	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
	}
	APC_Delete((PAPC)pelem);
}

bool APC_Compare_Keys_Func(PKey pkey1, PKey pkey2) {
	if (pkey1 == NULL || pkey2 == NULL) {
		printf(ARG_ERR_MSG);
		return false;
	}

	if (strcmp((char*)pkey1, (char*)pkey2) == 0) {
		return true;
	}
	return false;
}

void APC_Print_Func(PElem pelem) {
	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
	}
	APC_Print((PAPC)pelem);
}

PKey APC_Get_Key(PElem pelem) {
	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	return APC_Get_Id((PAPC)pelem);
}

