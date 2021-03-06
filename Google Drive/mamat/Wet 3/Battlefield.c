#include "Battlefield.h"
#pragma warning(disable: 4996)
/**Funcs**/
typedef struct _Battlefield {
	PList Soldiers;
	PList APCs;
	PList Squads;
	PList Warzones;
} Battlefield;

static PSquad get_squad(char *W_id, char *S_id, PBattlefield battlefield) {
	PWarZone warzone = NULL;
	PList squads = NULL;
	PSquad squad = NULL;
	if ((W_id == NULL) || (S_id == NULL) || (battlefield == NULL)) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	warzone = List_Get_Elem(battlefield->Warzones, W_id);
	if (warzone == NULL) {
		printf("Error: No Such War Zone");
		return NULL;
	}
	squads = WarZone_Get_List(warzone);
	if (squads == NULL) {
		printf("Error: No Such Squad");
		return NULL;
	}
	squad = List_Get_Elem(squads, S_id);
	if (squad == NULL) {
		printf("Error: No Such Squad");
		return NULL;
	}
	return squad;
}

static Result move_squad_list(PWarZone S_warzone, PWarZone D_warzone, PBattlefield battlefield) {
	if ((S_warzone == NULL) || (D_warzone == NULL) || (battlefield == NULL)) {
		return FAILURE;
	}

	PSquad curr_squad = NULL;
	PList squad_list = NULL;
	Result res;

	squad_list = WarZone_Get_List(S_warzone);
	curr_squad = List_Get_First(squad_list);
	while (curr_squad != NULL)
	{
		res = WarZone_Move_Squad(S_warzone, D_warzone, curr_squad);
		if (res == FAILURE) {
			return FAILURE;
		}
		curr_squad = List_Get_Next(squad_list);
	}
	return SUCCESS;
}

static Result Battlefield_Remove_Soldier(PBattlefield battlefield,PSoldier soldier){
	char *id = NULL;

	if(battlefield == NULL || soldier == NULL){
		return FAILURE;
	}


	id = Soldier_Get_Id(soldier);
	List_Remove_Elem(battlefield->Soldiers,id);

	return SUCCESS;
}

static Result Battlefield_Remove_APC(PBattlefield battlefield,PAPC pAPC){
	PSoldier psoldier = NULL;
	char *id = NULL;

	if(battlefield == NULL || pAPC == NULL){
		return FAILURE;
	}

	psoldier = APC_Pop(pAPC);
	while (psoldier){
		id = Soldier_Get_Id(psoldier);
		List_Remove_Elem(battlefield->Soldiers,id);
		Soldier_Delete(psoldier);
		psoldier = APC_Pop(pAPC);
	}
	id = APC_Get_Id(pAPC);
	List_Remove_Elem(battlefield->APCs,id);

	return SUCCESS;
}

static Result Battlefield_Remove_Squad(PBattlefield battlefield,PSquad pSquad){
	PAPC pAPC = NULL;
	PSoldier psoldier = NULL;
	char *id = NULL;

	if(battlefield == NULL || pSquad== NULL){
		return FAILURE;
	}

	pAPC = Squad_Get_First_APC(pSquad);
	while (pAPC != NULL){
		Battlefield_Remove_APC(battlefield,pAPC);
		pAPC = Squad_Get_Next_APC(pSquad);
	}
	psoldier = Squad_Get_First_Soldier(pSquad);
	while (psoldier != NULL){
		Battlefield_Remove_Soldier(battlefield,psoldier);
		psoldier = Squad_Get_Next_Soldier(pSquad);
	}

	id = Squad_Get_ID(pSquad);
	List_Remove_Elem(battlefield->Squads,id);

	return SUCCESS;
}

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
		return;
	}

	List_Delete(battlefield->Soldiers);
	List_Delete(battlefield->APCs);
	List_Delete(battlefield->Squads);
	List_Delete(battlefield->Warzones);
	free(battlefield);
}

void Battlefield_Print(PBattlefield battlefield) {

	if (battlefield == NULL) {
		printf(NO_B_ERR);
		return;
	}

	printf("Battlefield\n");
	List_Print(battlefield->Warzones);
}

Result Battlefield_Add_WarZone(PBattlefield battlefield, char *id){
	PWarZone new_warzone = NULL;
	Result res;
	if (battlefield == NULL) {
		printf(NO_B_ERR);
		return FAILURE;
	}
	if(id == NULL){
		printf(NO_W_ERR);
		return FAILURE;
	}

	if(List_Get_Elem(battlefield->Warzones,id) != NULL ){
		printf("Error: War Zone Already Exists\n");
		return FAILURE;
	}

	new_warzone = Warzone_Create(id);
	if(new_warzone == NULL){
		return FAILURE;
	}

	res = List_Add_Elem(battlefield->Warzones,new_warzone);
	if(res == FAILURE){
		return FAILURE;
	}

	WarZone_Delete(new_warzone);

	return SUCCESS;
}

Result Battlefield_Delete_WarZone(PBattlefield battlefield, char *id){
	Result res;
	PWarZone pWarZone = NULL;
	PSquad pSquad = NULL;

	if (battlefield == NULL) {
		printf(NO_B_ERR);
		return FAILURE;
	}
	if (id == NULL) {
		printf(NO_W_ERR);
		return FAILURE;
	}

	pWarZone = WarZone_Duplicate(List_Get_Elem(battlefield->Warzones,id));
	if(pWarZone == NULL){
		printf(NO_W_ERR);
		return FAILURE;
	}
	pSquad = WarZone_Get_First_Squad(pWarZone);
	while (pSquad != NULL){
		Battlefield_Remove_Squad(battlefield,pSquad);
		pSquad = WarZone_Get_Next_Squad(pWarZone);
	}
	WarZone_Delete(pWarZone);


	res = List_Remove_Elem(battlefield->Warzones,id);
	if(res == FAILURE){
		return FAILURE;
	}

	return SUCCESS;
}

Result Battlefield_Add_Squad(PBattlefield battlefield, char *warzone_id, char *squad_id){
	PSquad new_squad = NULL;
	PWarZone warZone = NULL;
	Result res;
	if (battlefield == NULL) {
		printf(NO_B_ERR);
		return FAILURE;
	}
	if (warzone_id == NULL) {
		printf(NO_W_ERR);
		return FAILURE;
	}
	if (squad_id == NULL) {
		printf(NO_SQ_ERR);
		return FAILURE;
	}

	warZone = List_Get_Elem(battlefield->Warzones, warzone_id);
	if (warZone == NULL) {
		printf(NO_W_ERR);
		return FAILURE;
	}

	if(List_Get_Elem(battlefield->Squads,squad_id) != NULL ){
		printf("Error: Squad Already Exists\n");
		return FAILURE;
	}

	new_squad = Squad_Create(squad_id);
	if(new_squad == NULL){
		return FAILURE;
	}

	res = List_Add_Elem(WarZone_Get_List(warZone),new_squad);
	if(res == FAILURE){
		return FAILURE;
	}

	res = List_Add_Elem(battlefield->Squads,new_squad);
	if(res == FAILURE){
		return FAILURE;
	}

	Squad_Delete(new_squad);

	return SUCCESS;
}

Result Battlefield_Delete_Squad(PBattlefield battlefield, char *warzone_id, char *squad_id){
	PWarZone warZone = NULL;
	PSquad psquad = NULL;
	Result res;

	if (battlefield == NULL) {
		printf(NO_B_ERR);
		return FAILURE;
	}
	if (warzone_id == NULL) {
		printf(NO_W_ERR);
		return FAILURE;
	}
	if (squad_id == NULL) {
		printf(NO_SQ_ERR);
		return FAILURE;
	}
	
	warZone = List_Get_Elem(battlefield->Warzones,warzone_id);
	if(warZone == NULL){
		printf(NO_W_ERR);
		return FAILURE;
	}

	// This code is to remove the squad and all its contents from the battlefield lists
	psquad = Squad_Duplicate(List_Get_Elem(WarZone_Get_List(warZone),squad_id));
	if(psquad == NULL){
		printf(NO_SQ_ERR);
		return FAILURE;
	}
	Battlefield_Remove_Squad(battlefield,psquad);
	Squad_Delete(psquad);

	res = List_Remove_Elem(WarZone_Get_List(warZone),squad_id);
	if(res == FAILURE){
		return FAILURE;
	}
	return SUCCESS;
}

Result Battlefield_Add_APC(PBattlefield battlefield, char *warzone_id, char *squad_id, char *APC_id){
	PSquad squad = NULL;
	PAPC new_APC = NULL;
	PWarZone warZone = NULL;
	Result res;

	if (battlefield == NULL) {
		printf(NO_B_ERR);
		return FAILURE;
	}
	if (warzone_id == NULL) {
		printf(NO_W_ERR);
		return FAILURE;
	}
	if (squad_id == NULL) {
		printf(NO_SQ_ERR);
		return FAILURE;
	}
	if (APC_id == NULL) {
		printf(NO_A_ERR);
		return FAILURE;
	}

	if(List_Get_Elem(battlefield->APCs,APC_id) != NULL ){
		printf("Error: APC Already Exists\n");
		return FAILURE;
	}


	warZone = List_Get_Elem(battlefield->Warzones,warzone_id);
	if(warZone == NULL){
		printf(NO_W_ERR);
		return FAILURE;
	}

	squad = List_Get_Elem(WarZone_Get_List(warZone),squad_id);
	if(squad == NULL){
		printf(NO_SQ_ERR);
		return FAILURE;
	}

	res = Squad_Add_APC(squad,APC_id);
	if(res == FAILURE){
		return FAILURE;
	}

	new_APC = APC_Create(APC_id);

	res = List_Add_Elem(battlefield->APCs,new_APC);
	if(res == FAILURE){
		return FAILURE;
	}

	APC_Delete(new_APC);

	return SUCCESS;
}

Result Battlefield_Delete_APC(PBattlefield battlefield, char *warzone_id, char *squad_id, char *APC_id){
	PSquad squad = NULL;
	PAPC pAPC = NULL;
	PWarZone warZone = NULL;
	Result res;

	if (battlefield == NULL) {
		printf(NO_B_ERR);
		return FAILURE;
	}
	if (warzone_id == NULL) {
		printf(NO_W_ERR);
		return FAILURE;
	}
	if (squad_id == NULL) {
		printf(NO_SQ_ERR);
		return FAILURE;
	}
	if (APC_id == NULL) {
		printf(NO_A_ERR);
		return FAILURE;
	}

	warZone = List_Get_Elem(battlefield->Warzones,warzone_id);
	if(warZone == NULL){
		printf(NO_W_ERR);
		return FAILURE;
	}

	squad = List_Get_Elem(WarZone_Get_List(warZone),squad_id);
	if(squad == NULL){
		printf(NO_SQ_ERR);
		return FAILURE;
	}
	// This code is to remove the APC and all it's contents from the battlefield list
	pAPC = APC_Duplicate(Squad_Get_APC(squad,APC_id));
	if(pAPC == NULL) {
		printf(NO_A_ERR);
		return FAILURE;
	}
	Battlefield_Remove_APC(battlefield,pAPC);
	APC_Delete(pAPC);



	res = Squad_Delete_APC(squad,APC_id);
	if(res == FAILURE){
		return FAILURE;
	}

	return SUCCESS;
}

Result Battlefield_Add_Soldier(PBattlefield battlefield, char *warzone_id, char *squad_id, char *soldier_id, char *soldier_pos){
	PSquad squad = NULL;
	PSoldier new_soldier = NULL;
	PWarZone warZone = NULL;
	Result res;

	if (battlefield == NULL) {
		printf(NO_B_ERR);
		return FAILURE;
	}
	if (warzone_id == NULL) {
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	if (squad_id == NULL) {
		printf(ARG_ERR_MSG);;
		return FAILURE;
	}
	if (soldier_id == NULL) {
		printf(ARG_ERR_MSG);
		return FAILURE;
	}

	if(soldier_pos == NULL){
		printf(ARG_ERR_MSG);
		return FAILURE;
	}

	if(List_Get_Elem(battlefield->Soldiers,soldier_id) != NULL ){
		printf("Error: Soldier Already Exists\n");
		return FAILURE;
	}


	warZone = List_Get_Elem(battlefield->Warzones,warzone_id);
	if(warZone == NULL){
		printf(NO_W_ERR);
		return FAILURE;
	}

	squad = List_Get_Elem(WarZone_Get_List(warZone),squad_id);
	if(squad == NULL){
		printf(NO_SQ_ERR);
		return FAILURE;
	}

	res = Squad_Add_Soldier(squad,soldier_id,soldier_pos);
	if(res == FAILURE){
		return FAILURE;
	}

	new_soldier = Soldier_Create(soldier_id,soldier_pos);

	res = List_Add_Elem(battlefield->Soldiers,new_soldier);
	if(res == FAILURE){
		return FAILURE;
	}

	Soldier_Delete(new_soldier);

	return SUCCESS;
}

Result Battlefield_Delete_Soldier(PBattlefield battlefield, char *warzone_id, char *squad_id, char *soldier_id){
	PSquad squad = NULL;
	PWarZone warZone = NULL;
	Result res;

	if (battlefield == NULL) {
		printf(NO_B_ERR);
		return FAILURE;
	}
	if (warzone_id == NULL) {
		printf(NO_W_ERR);
		return FAILURE;
	}
	if (squad_id == NULL) {
		printf(NO_SQ_ERR);
		return FAILURE;
	}
	if (soldier_id == NULL) {
		printf(NO_S_ERR);
		return FAILURE;
	}

	warZone = List_Get_Elem(battlefield->Warzones,warzone_id);
	if(warZone == NULL){
		printf("Error: No Such War Zone\n");
		return FAILURE;
	}

	squad = List_Get_Elem(WarZone_Get_List(warZone),squad_id);
	if(squad == NULL){
		printf("Error: No Such Squad\n");
		return FAILURE;
	}

	res = Squad_Delete_Soldier(squad,soldier_id);
	if(res == FAILURE){
		printf("Error: No Such Soldier\n");
		return FAILURE;
	}

	res = List_Remove_Elem(battlefield->Soldiers,soldier_id);
	if(res == FAILURE){
		return FAILURE;
	}

	return SUCCESS;
}

Result Battlefield_APC_Insert_Soldier(char *W_id, char *S_id, char *A_id, char *Sold_id, PBattlefield battlefield) {
	PSquad squad = NULL;
	Result res;

	if (battlefield == NULL) {
		printf(NO_B_ERR);
		return FAILURE;
	}
	if (W_id == NULL) {
		printf(NO_W_ERR);
		return FAILURE;
	}
	if (S_id == NULL) {
		printf(NO_SQ_ERR);
		return FAILURE;
	}
	if (Sold_id == NULL) {
		printf(NO_S_ERR);
		return FAILURE;
	}
	
	squad = get_squad(W_id, S_id, battlefield);
	res = Squad_Insert_Sold_APC(squad, Sold_id, A_id);
	return res;
}

Result Battlefield_APC_Pop(char *W_id, char *S_id, char *A_id, PBattlefield battlefield) {
	PSquad squad = NULL;
	Result res;

	if (battlefield == NULL) {
		printf(NO_B_ERR);
		return FAILURE;
	}
	if (W_id == NULL) {
		printf(NO_W_ERR);
		return FAILURE;
	}
	if (S_id == NULL) {
		printf(NO_SQ_ERR);
		return FAILURE;
	}
	if (A_id == NULL) {
		printf(NO_A_ERR);
		return FAILURE;
	}
	squad = get_squad(W_id, S_id, battlefield);
	res = Squad_APC_Pop(squad, A_id);
	return res;
}

void Battlefield_Warzone_Raise_Alert(char *W_id, PBattlefield battlefield) {
	PWarZone warzone = NULL;
	PWarZone curr_warzone = NULL;
	Result res;
	int alert_level;
	if (battlefield == NULL) {
		printf(NO_B_ERR);
		return;
	}
	if (W_id == NULL) {
		printf(NO_W_ERR);
		return ;
	}
	warzone = List_Get_Elem(battlefield->Warzones, W_id);
	if (warzone == NULL) {
		printf(NO_W_ERR);
		return;
	}
	alert_level = WarZone_Raise_Alert(warzone);
	if (alert_level == 0) {
		curr_warzone = List_Get_First(battlefield->Warzones);
		while (curr_warzone != NULL)
		{
			if (curr_warzone != warzone) {
				res = move_squad_list(curr_warzone, warzone, battlefield);
				if (res == FAILURE)
					return;
			}
			curr_warzone = List_Get_Next(battlefield->Warzones);
		}
	}
}

Result Batllefield_Move_Squad(PBattlefield battlefield, char *src_warzone_id, char *dst_warzone_id, char *squad_id){
	PWarZone src_warzone = NULL;
	PWarZone dst_warzone = NULL;
	PSquad squad = NULL;

	if (battlefield == NULL) {
		printf(NO_B_ERR);
		return FAILURE;
	}
	if (src_warzone_id == NULL) {
		printf("Error: No Such Origin War Zone\n");
		return FAILURE;
	}
	if (dst_warzone_id == NULL) {
		printf("Error: No Such Dest War Zone\n");
		return FAILURE;
	}
	if (squad_id == NULL) {
		printf(NO_SQ_ERR);
		return FAILURE;
	}

	src_warzone = List_Get_Elem(battlefield->Warzones,src_warzone_id);
	if( src_warzone == NULL){
		printf("Error: No Such Origin War Zone\n");
		return FAILURE;
	}

	dst_warzone = List_Get_Elem(battlefield->Warzones,dst_warzone_id);
	if(dst_warzone == NULL){
		printf("Error: No Such Dest War Zone\n");
		return FAILURE;
	}

	squad = List_Get_Elem(WarZone_Get_List(src_warzone),squad_id);
	if(squad == NULL){
		printf("Error: No Such Squad\n");
		return FAILURE;
	}

	List_Add_Elem(WarZone_Get_List(dst_warzone),squad);
	List_Remove_Elem(WarZone_Get_List(src_warzone),squad_id);

	return SUCCESS;
}



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
	PKey key = NULL;

	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	key = WarZone_Get_ID((PWarZone)pelem);

	return key;
}

