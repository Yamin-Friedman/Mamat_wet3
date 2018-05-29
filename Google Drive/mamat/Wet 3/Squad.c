#include "Squad.h"
#pragma warning(disable: 4996)

typedef struct _Squad {
	PList Soldiers;
	PList APCs;
	int Count;
	char ID[MAX_ID_LENGTH];
} Squad;

//**************************************************************************************************************************************
//* Function name: Check_Valid_Id
//* Function description: Checks if the string id is a valid squad id.
//* Parameters: id - a pointer to a char that holds the squad id.
//* Return value: true is the id is valid and false otherwise
//**************************************************************************************************************************************
static bool Check_Valid_ID(char *id){
	if(id == NULL || id[0] != 'S' || id[1] != 'q' || strlen(id) != SQUAD_ID_LEN){
		return false;
	}
	return true;
}

//**************************************************************************************************************************************
//* Function name: Squad_Create
//* Function description: Creates a squad.
//* Parameters: id - a pointer to a char that holds the squad id.
//* Return value: A pointer to the new squad.
//**************************************************************************************************************************************
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

//**************************************************************************************************************************************
//* Function name: Squad_Delete
//* Function description: Deletes a squad.
//* Parameters: psquad - a pointer to a squad.
//* Return value: void.
//**************************************************************************************************************************************
void Squad_Delete(PSquad psquad){

	if(psquad == NULL){
		printf(ARG_ERR_MSG);
		return;
	}

	List_Delete(psquad->Soldiers);
	List_Delete(psquad->APCs);
	free(psquad);
}

//**************************************************************************************************************************************
//* Function name: Squad_Print
//* Function description: Prints the squad information.
//* Parameters: psquad - a pointer to a squad.
//* Return value: void.
//**************************************************************************************************************************************
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

//**************************************************************************************************************************************
//* Function name: Squad_Duplicate
//* Function description: Creates an exact copy of a squad.
//* Parameters: old_squad - a pointer to a quad.
//* Return value: A pointer to a new squad.
//**************************************************************************************************************************************
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
	if(new_squad->APCs == NULL || new_squad->Soldiers == NULL){
		Squad_Delete(new_squad);
		return NULL;
	}
	new_squad->Count = old_squad->Count;
	return new_squad;
}

//**************************************************************************************************************************************
//* Function name: Squad_Add_Soldier
//* Function description: Adds a soldier to the squad.
//* Parameters: psquad - a pointer to a squad.
//* Parameters: id - a pointer to a char that holds the soldier id.
//* Parameters: pos - a pointer to a char that holds the soldier position.
//* Return value: The Result of the action.
//**************************************************************************************************************************************
Result Squad_Add_Soldier(PSquad psquad, char *id, char *pos) {
	PSoldier new_soldier;
	Result res;
	if (psquad == NULL) {
		printf(ARG_ERR_MSG);
		return FAILURE;
	}

    if(List_Get_Elem(psquad->Soldiers,id)){
        return FAILURE;
    }

	new_soldier = Soldier_Create(id, pos);
	if (new_soldier == NULL) {
		return FAILURE;
	}

	res = List_Add_Elem(psquad->Soldiers, new_soldier);
	if(res){
		psquad->Count++;
	}

	Soldier_Delete(new_soldier);

	return res;
}

//**************************************************************************************************************************************
//* Function name: Squad_Add_APC
//* Function description: Adds an APC to the squad.
//* Parameters: psquad - a pointer to a squad.
//* Parameters: id - a pointer to a char that holds the APC id.
//* Return value: The Result of the action.
//**************************************************************************************************************************************
Result Squad_Add_APC(PSquad psquad, char *id) {
	PAPC new_APC;
	Result res;
	if (psquad == NULL) {
		printf(ARG_ERR_MSG);
		return FAILURE;
	}

    if(List_Get_Elem(psquad->APCs,id)){
        return FAILURE;
    }

	new_APC = APC_Create(id);
	if (new_APC == NULL) {
		return FAILURE;
	}
	res = List_Add_Elem(psquad->APCs, new_APC);

	APC_Delete(new_APC);

	return res;
}

//**************************************************************************************************************************************
//* Function name: Squad_Insert_Sold_APC
//* Function description: Inserts a soldier that is in the squad into an APC that is in the squad.
//* Parameters: psquad - a pointer to a squad.
//* Parameters: sold_id - a pointer to a char that holds the soldier id.
//* Parameters: APC_id - a pointer to a char that holds the APC id.
//* Return value: The Result of the action.
//**************************************************************************************************************************************
Result Squad_Insert_Sold_APC(PSquad psquad, char *sold_id, char *APC_id) {
	PSoldier soldier;
	PAPC APC;
	Result res;
	if (psquad == NULL) {
		printf(ARG_ERR_MSG);
		return FAILURE;
	}

	soldier = Soldier_Duplicate(List_Get_Elem(psquad->Soldiers, sold_id));
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

//**************************************************************************************************************************************
//* Function name: Squad_APC_Pop
//* Function description: Removes the top soldier from an APC that is in the squad and places him as a soldier in the squad.
//* Parameters: psquad - a pointer to a squad.
//* Parameters: APC_id - a pointer to a char that holds the APC id.
//* Return value: The Result of the action.
//**************************************************************************************************************************************
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

//**************************************************************************************************************************************
//* Function name: Squad_Delete_Soldier
//* Function description: Removes a soldier from the squad.
//* Parameters: psquad - a pointer to a squad.
//* Parameters: soldier_id - a pointer to a char that holds the soldier id.
//* Return value: The Result of the action.
//**************************************************************************************************************************************
Result Squad_Delete_Soldier(PSquad psquad, char *soldier_id){
    Result res;

    if(psquad == NULL || soldier_id == NULL){
        printf(ARG_ERR_MSG);
        return FAILURE;
    }

    res = List_Remove_Elem(psquad->Soldiers,soldier_id);
	if(res){
		psquad->Count--;
	}

    return res;
}

//**************************************************************************************************************************************
//* Function name: Squad_Delete_APC
//* Function description: Removes an APC from the squad.
//* Parameters: psquad - a pointer to a squad.
//* Parameters: APC_id - a pointer to a char that holds the APC id.
//* Return value: The Result of the action.
//**************************************************************************************************************************************
Result Squad_Delete_APC(PSquad psquad, char *APC_id){
	Result res;
	PAPC APC = NULL;
	int num_soldiers = 0;

	if(psquad == NULL || APC_id == NULL){
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	APC = List_Get_Elem(psquad->APCs,APC_id);
	if(APC == NULL){
		return FAILURE;
	}

	num_soldiers = APC_Get_Num_Soldiers(APC);
	psquad->Count -= num_soldiers;

    res = List_Remove_Elem(psquad->APCs,APC_id);

    return res;
}

//**************************************************************************************************************************************
//* Function name: Squad_Get_Id
//* Function description: copies into id the id of the squad.
//* Parameters: psquad - a pointer to a squad.
//* Parameters: id - a pointer to a string.
//* Return value: void.
//**************************************************************************************************************************************
void Squad_Get_ID(PSquad psquad,char *id){

	if(psquad == NULL){
		printf(ARG_ERR_MSG);
		return;
	}

	strcpy(id,psquad->ID);

}

//**************************************************************************************************************************************
//* Function name: Squad_Get_APC
//* Function description: Returns a pointer to an APC based on id if the APC is in the squad.
//* Parameters: psquad - a pointer to a squad.
//* Parameters: id - a pointer to a string with the APC id.
//* Return value: A pointer to an APC.
//**************************************************************************************************************************************
PAPC Squad_Get_APC(PSquad psquad,char *id){
	PAPC APC = NULL;

	if(psquad == NULL || id == NULL){
		printf(ARG_ERR_MSG);
		return NULL;
	}

	APC = List_Get_Elem(psquad->APCs,id);

	return APC;
}

//**************************************************************************************************************************************
//* Function name: Squad_Get_First_APC
//* Function description: Returns a pointer to the first APC in the squad list.
//* Parameters: psquad - a pointer to a squad.
//* Return value: A pointer to an APC.
//**************************************************************************************************************************************
PAPC Squad_Get_First_APC(PSquad psquad){
	PAPC APC = NULL;

	if(psquad == NULL){
		printf(ARG_ERR_MSG);
		return NULL;
	}

	APC = List_Get_First(psquad->APCs);

	return APC;
}

//**************************************************************************************************************************************
//* Function name: Squad_Get_Next_APC
//* Function description: Returns a pointer to the next APC in the squad list.
//* Parameters: psquad - a pointer to a squad.
//* Return value: A pointer to an APC.
//**************************************************************************************************************************************
PAPC Squad_Get_Next_APC(PSquad psquad){
	PAPC APC = NULL;

	if(psquad == NULL){
		printf(ARG_ERR_MSG);
		return NULL;
	}

	APC = List_Get_Next(psquad->APCs);

	return APC;
}

//**************************************************************************************************************************************
//* Function name: Squad_Get_First_Soldier
//* Function description: Returns a pointer to the first soldier in the squad list.
//* Parameters: psquad - a pointer to a squad.
//* Return value: A pointer to a soldier.
//**************************************************************************************************************************************
PSoldier Squad_Get_First_Soldier(PSquad psquad){
	PSoldier soldier = NULL;

	if(psquad == NULL){
		printf(ARG_ERR_MSG);
		return NULL;
	}

	soldier = List_Get_First(psquad->Soldiers);

	return soldier;
}

//**************************************************************************************************************************************
//* Function name: Squad_Get_Next_Soldier
//* Function description: Returns a pointer to the next soldier in the squad list.
//* Parameters: psquad - a pointer to a squad.
//* Return value: A pointer to a soldier.
//**************************************************************************************************************************************
PSoldier Squad_Get_Next_Soldier(PSquad psquad){
	PSoldier soldier = NULL;

	if(psquad == NULL){
		printf(ARG_ERR_MSG);
		return NULL;
	}

	soldier = List_Get_Next(psquad->Soldiers);

	return soldier;
}

/**Soldier list functions**/
//**************************************************************************************************************************************
//* Function name: Soldier_Clone_Func
//* Function description: User clone function for using the list ADT with soldiers.
//* Parameters: pelem - a pointer to a list element.
//* Return value: A pointer to a list element.
//**************************************************************************************************************************************
PElem Soldier_Clone_Func(PElem pelem){
	PSoldier new_soldier = NULL;

    if(pelem == NULL){
        printf(ARG_ERR_MSG);
        return NULL;
    }

    new_soldier = Soldier_Duplicate((PSoldier)pelem);
	return new_soldier;
}

//**************************************************************************************************************************************
//* Function name: Soldier_Destroy_Func
//* Function description: User destroy function for using the list ADT with soldiers.
//* Parameters: pelem - a pointer to a list element.
//* Return value: Void.
//**************************************************************************************************************************************
void Soldier_Destroy_Func(PElem pelem){

    if(pelem == NULL){
        printf(ARG_ERR_MSG);
    }

    Soldier_Delete((PSoldier)pelem);
}

//**************************************************************************************************************************************
//* Function name: Soldier_Compare_Keys_Func
//* Function description: User compare keys function for using the list ADT with soldiers.
//* Parameters: key1 - a pointer to a list key.
//* Parameters: key2 - a pointer to a list key.
//* Return value: A bool that is true if the keys are the same.
//**************************************************************************************************************************************
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

//**************************************************************************************************************************************
//* Function name: Soldier_Print_Func
//* Function description: User print function for using the list ADT with soldiers.
//* Parameters: pelem - a pointer to a list element.
//* Return value: Void.
//**************************************************************************************************************************************
void Soldier_Print_Func(PElem pelem){

    if(pelem == NULL){
        printf(ARG_ERR_MSG);
    }

    Soldier_Print((PSoldier)pelem);
}

//**************************************************************************************************************************************
//* Function name: Soldier_Get_Key
//* Function description: User get key function for using the list ADT with soldiers.
//* Parameters: pelem - a pointer to a list element.
//* Return value: A pointer to a list key.
//**************************************************************************************************************************************

PKey Soldier_Get_Key(PElem pelem) {
	PKey key = NULL;

	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	Soldier_Get_Id((PSoldier)pelem, key);

	return key;
}
/**APC list functions**/

//**************************************************************************************************************************************
//* Function name: APC_Clone_Func
//* Function description: User clone function for using the list ADT with APCs.
//* Parameters: pelem - a pointer to a list element.
//* Return value: A pointer to a list element.
//**************************************************************************************************************************************
PElem APC_Clone_Func(PElem pelem) {
	PAPC new_APC;
	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	new_APC = APC_Duplicate((PAPC)pelem);
	return new_APC;
}

//**************************************************************************************************************************************
//* Function name: APC_Destroy_Func
//* Function description: User destroy function for using the list ADT with APCs.
//* Parameters: pelem - a pointer to a list element.
//* Return value: Void.
//**************************************************************************************************************************************
void APC_Destroy_Func(PElem pelem) {
	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
	}
	APC_Delete((PAPC)pelem);
}

//**************************************************************************************************************************************
//* Function name: APC_Compare_Keys_Func
//* Function description: User compare keys function for using the list ADT with APCs.
//* Parameters: pelem - a pointer to a list element.
//* Return value: A bool that is true if the keys are the same.
//**************************************************************************************************************************************
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

//**************************************************************************************************************************************
//* Function name: APC_Print_Func
//* Function description: User print function for using the list ADT with APCs.
//* Parameters: pelem - a pointer to a list element.
//* Return value: Void.
//**************************************************************************************************************************************
void APC_Print_Func(PElem pelem) {
	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
	}
	APC_Print((PAPC)pelem);
}

//**************************************************************************************************************************************
//* Function name: APC_Get_Key
//* Function description: User get key function for using the list ADT with APCs.
//* Parameters: pelem - a pointer to a list element.
//* Return value: A pointer to a list key.
//**************************************************************************************************************************************

PKey APC_Get_Key(PElem pelem) {
	PKey key = NULL;

	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	APC_Get_Id((PAPC)pelem, key);

	return key;
}

