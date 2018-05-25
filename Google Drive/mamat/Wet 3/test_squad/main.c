#include <stdio.h>
#include "../Squad.h"

int main() {
    PSquad squad1 = NULL;
    PSquad squad2 = NULL;
    char id1[MAX_ID_LENGTH] = "Sq243";
    char id2[MAX_ID_LENGTH] = "S111";
    char pos[MAX_ID_LENGTH] = "MED";
    char id3[MAX_ID_LENGTH] = "S222";
    char pos2[MAX_ID_LENGTH] = "GUNNER";
    char APC_id[MAX_ID_LENGTH] = "A123";
    Result res;
    squad1 = Squad_Create(id1);
    res = Squad_Add_Soldier(squad1,id2,pos);
    if(!res){
        printf("Add error\n");
    }
    res = Squad_Add_Soldier(squad1,id3,pos2);
    if(!res){
        printf("Add error\n");
    }
    res = Squad_Add_Soldier(squad1,id3,pos2);
    if(!res){
        printf("Add error\n");
    }
    res = Squad_Delete_Soldier(squad1,id2);
    if(!res){
        printf("Delete error\n");
    }
    res = Squad_Delete_Soldier(squad1,id2);
    if(!res){
        printf("Delete error\n");
    }
    res = Squad_Add_APC(squad1,APC_id);
    if(!res){
        printf("Add error\n");
    }
    res = Squad_Add_APC(squad1,APC_id);
    if(!res){
        printf("Add error\n");
    }
    Squad_Insert_Sold_APC(squad1,id3,APC_id);
    squad2 = Squad_Duplicate(squad1);
    res = Squad_Add_Soldier(squad2,id2,pos);
    if(!res){
        printf("Add error\n");
    }
    res = Squad_APC_Pop(squad1,APC_id);
    if(!res){
        printf("Pop error\n");
    }
    res = Squad_Delete_Soldier(squad2,id3);
    if(!res){
        printf("Delete error\n");
    }
    res = Squad_Delete_APC(squad1,APC_id);
    if(!res){
        printf("Delete error\n");
    }
    res = Squad_Delete_APC(squad2,APC_id);
    if(!res){
        printf("Delete error\n");
    }
    Squad_Print(squad1);
    Squad_Print(squad2);
    Squad_Delete(squad1);
    Squad_Delete(squad2);
    return 0;
}