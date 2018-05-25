#include "WarZone.h"


typedef struct _WarZone {
	PList Squads;
	int Alert_Level;
	char ID[MAX_ID_LENGTH];
} WarZone;




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

