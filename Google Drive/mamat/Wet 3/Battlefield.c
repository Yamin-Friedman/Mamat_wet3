#include "Battlefield.h"

/**Funcs**/
typedef struct _Battlefield {
	PList Soldiers;
	PList APCs;
	PList Squads;
	PList Warzones;
} Battlefield;

PBattlefield Battlefield_Create() {
	PBattlefield new_battle = NULL;

	new_battle = (PBattlefield)malloc(sizeof(Battlefield));
	if(new_battle == NULL){
		printf(MALLOC_ERR_MSG);
		return NULL;
	}

	new_battle->Soldiers = List_Create(Soldier_Clone_Func,Soldier_Destroy_Func,Soldier_Compare_Keys_Func,Soldier_Print_Func,Soldier_Get_Key);
	new_battle->APCs = List_Create(APC_Clone_Func,APC_Destroy_Func,APC_Compare_Keys_Func,APC_Print_Func,APC_Get_Key);
	new_battle->Squads = List_Create(Squad_Clone_Func,Squad_Destroy_Func,Squad_Compare_Keys_Func,Squad_Print_Func,Squad_Get_Key_Func);
	new_battle->Warzones = List_Create(WarZone_Clone_Func,WarZone_Destroy_Func,WarZone_Compare_Keys_Func,WarZone_Print_Func,WarZone_Get_Key);

	if(new_battle->Warzones == NULL || new_battle->Squads == NULL || new_battle->APCs == NULL || new_battle->Soldiers == NULL){
		Battlefield_Delete(new_battle);
		return NULL;
	}

	return new_battle;
}

void Battlefield_Delete(PBattlefield battlefield){

	if(battlefield == NULL){
		printf(ARG_ERR_MSG);
		return;
	}

	List_Delete(battlefield->Soldiers);
	List_Delete(battlefield->APCs);
	List_Delete(battlefield->Squads);
	List_Delete(battlefield->Warzones);
	free(battlefield);

	return;
}

Result Battlefield_Add_WarZone()

/**User Functions**/
/**Warzone List Functions**/

PElem WarZone_Clone_Func(PElem pelem) {
	PWarZone new_WarZone;
	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	new_WarZone = WarZone_Duplicate((PWarZone)pelem);
	return new_WarZone;
}

void WarZone_Destroy_Func(PElem pelem) {
	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
	}
	WarZone_Delete((PWarZone)pelem);
}

bool WarZone_Compare_Keys_Func(PKey pkey1, PKey pkey2) {
	if (pkey1 == NULL || pkey2 == NULL) {
		printf(ARG_ERR_MSG);
		return false;
	}

	if (strcmp((char*)pkey1, (char*)pkey2) == 0) {
		return true;
	}
	return false;
}

void WarZone_Print_Func(PElem pelem) {
	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
	}
	WarZone_Print((PWarZone)pelem);
}

PKey WarZone_Get_Key(PElem pelem) {
	char id[MAX_ID_LENGTH];

	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	return WarZone_Get_Id((PWarZone)pelem, id);
}

