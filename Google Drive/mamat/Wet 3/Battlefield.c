#include "Battlefield.h"

/**Funcs**/
typedef struct _Battlefield {
	PList Soldiers;
	PList APCs;
	PList Squads;
	PList Warzones;
} Battlefield;

PBattlefield Battlefield_Create() {

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
	char id[MAX_ID_LENGTH];

	if (pelem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	return WarZone_Get_Id((PWarZone)pelem, id);
}

