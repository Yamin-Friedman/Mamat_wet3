#include "WarZone.h"
#pragma warning(disable: 4996)

typedef struct _WarZone {
	PList Squads;
	int Alert_Level;
	char ID[MAX_ID_LENGTH];
} WarZone;

static bool Check_Valid_ID(char *id){
	if(id == NULL || id[0] != 'W' || strlen(id) != WARZONE_ID_LEN){
		return false;
	}
	return true;
}

PWarZone Warzone_Create(char *id){
	PWarZone new_warzone = NULL;
	PList squad_list = NULL;

	if(Check_Valid_ID(id) == false){
		printf(ARG_ERR_MSG);
		return NULL;
	}

	new_warzone = malloc(sizeof(WarZone));
	if(new_warzone == NULL){
		printf(MALLOC_ERR_MSG);
		return NULL;
	}

	squad_list = List_Create(Squad_Clone_Func,Squad_Destroy_Func,Squad_Compare_Keys_Func,Squad_Print_Func,Squad_Get_Key_Func);
	if(squad_list == NULL){
		free(new_warzone);
		return NULL;
	}

	new_warzone->Squads = squad_list;
	new_warzone->Alert_Level = 0;
	strcpy(new_warzone->ID,id);

	return new_warzone;
}


void WarZone_Delete(PWarZone WarZone) {
	if (WarZone == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	List_Delete(WarZone->Squads);
	free(WarZone);
}

void WarZone_Print(PWarZone WarZone) {
		if (WarZone == NULL) {
			printf(ARG_ERR_MSG);
			return;
		}
		printf("WarZone: %s , Alert State: %d\n\n",WarZone->ID,WarZone->Alert_Level);
		List_Print(WarZone->Squads);
}

PWarZone WarZone_Duplicate(PWarZone old_warzone){
	PWarZone new_warzone = NULL;

	if(old_warzone == NULL){
		printf(ARG_ERR_MSG);

		return NULL;
	}

	new_warzone = Warzone_Create(old_warzone->ID);
	if(new_warzone == NULL){
		return NULL;
	}

	List_Duplicate(old_warzone->Squads,new_warzone->Squads);
	if(new_warzone->Squads == NULL){
		WarZone_Delete(new_warzone);
		return NULL;
	}
	new_warzone->Alert_Level = old_warzone->Alert_Level;
	strcpy(new_warzone->ID,old_warzone->ID);

	return new_warzone;
}

int WarZone_Raise_Alert(PWarZone pWarZone){

	if (pWarZone == NULL) {
		printf(ARG_ERR_MSG);
		return -1;
	}

	pWarZone->Alert_Level++;
	if(pWarZone->Alert_Level == 3){
		pWarZone->Alert_Level = 0;
	}

	return pWarZone->Alert_Level;
}

Result WarZone_Move_Squad(PWarZone S_warzone,PWarZone D_warzone,PSquad psquad){ // this function duplicates the squad instead of moving it
	Result res;
	char* squad_id;
	if(S_warzone == NULL || D_warzone == NULL || psquad == NULL){
		printf(ARG_ERR_MSG);
		return FAILURE;
	}

	res = List_Add_Elem(D_warzone->Squads,psquad);
	if(res == FAILURE){
		return FAILURE;
	}
	squad_id = Squad_Get_ID(psquad);
	res = List_Remove_Elem(S_warzone->Squads,squad_id);
	if(res == FAILURE){
		return  FAILURE;
	}

	return SUCCESS;

}

char *WarZone_Get_ID(PWarZone pwarzone){

	if(pwarzone == NULL){
		printf(ARG_ERR_MSG);
		return NULL;
	}

	return  pwarzone->ID;
}

PSquad WarZone_Get_First_Squad(PWarZone warZone){
	PSquad squad = NULL;

	if(warZone == NULL){
		return  NULL;
	}

	squad = List_Get_First(warZone->Squads);

	return squad;
}

PSquad WarZone_Get_Next_Squad(PWarZone warZone){
	PSquad squad = NULL;

	if(warZone == NULL){
		return NULL;
	}

	squad = List_Get_Next(warZone->Squads);

	return squad;
}

PList WarZone_Get_List(PWarZone pwarzone){

	if(pwarzone == NULL){
		printf(ARG_ERR_MSG);
		return NULL;
	}

	return pwarzone->Squads;
}

/**Squad list functions**/
PElem Squad_Clone_Func(PElem pelem){
	PSquad new_squad = NULL;

	if(pelem == NULL){
		printf(ARG_ERR_MSG);
		return NULL;
	}

	new_squad = Squad_Duplicate((PSquad)pelem);
	return new_squad;
}

void Squad_Destroy_Func(PElem pelem){

	if(pelem == NULL){
		printf(ARG_ERR_MSG);
	}

	Squad_Delete((PSquad)pelem);
}

bool Squad_Compare_Keys_Func(PKey key1, PKey key2){

	if(key1 == NULL || key2 == NULL){
		printf(ARG_ERR_MSG);
		return false;
	}

	if(strcmp((char*)key1,(char*)key2) == 0){
		return true;
	}
	return false;
}

void Squad_Print_Func(PElem pelem){

	if(pelem == NULL){
		printf(ARG_ERR_MSG);
	}

	Squad_Print((PSquad)pelem);
}

PKey Squad_Get_Key_Func(PElem pelem) {
	PKey key = NULL;

	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	key = Squad_Get_ID((PSquad)pelem);

	return key;
}