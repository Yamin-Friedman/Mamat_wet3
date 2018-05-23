#include "WarZone.h"



void WarZone_Delete(PWarZone WarZone) {
	if (WarZone == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	ListDestroy(WarZone->Squads);
	free(WarZone);
}

void WarZone_Print(PWarZone WarZone) {
		if (WarZone == NULL) {
			printf(ARG_ERR_MSG);
			return;
		}
		printf("WarZone: %s , Alert State: %d\n\n",WarZone->ID,WarZone->Alert_Level);
		ListPrint(WarZone->Squads);
}

