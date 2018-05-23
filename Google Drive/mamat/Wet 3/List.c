#include "List.h"


typedef struct Node_ 
{
    PNode next_node;
    PList plist;
    PElem pelem;
} NODE;




typedef struct List_ 
{
	PNode first_node;
    PNode curr_node;

    CLONE_FUNC clone_func;
    DESTROY_FUNC destroy_func;
    COMPARE_KEYS_FUNC compare_keys_func;
    PRINT_FUNC print_func;
    GET_KEY get_key;

} LIST;

PList List_Create(CLONE_FUNC clone_func, DESTROY_FUNC destroy_func, COMPARE_KEYS_FUNC compare_keys_func, PRINT_FUNC print_func , GET_KEY get_key){
    PList new_list = NULL;

    if (clone_func == NULL || destroy_func == NULL || compare_keys_func == NULL || print_func == NULL){
        printf(ARG_ERR_MSG);
        return NULL;
    }

    new_list = (PList)malloc(sizeof(LIST));
    if(new_list == NULL){
        printf(MALLOC_ERR_MSG);
        return NULL;
    }

    new_list->print_func = print_func;
    new_list->clone_func = clone_func;
    new_list->compare_keys_func = compare_keys_func;
    new_list->destroy_func = destroy_func;
    new_list->get_key = get_key;
    new_list->first_node = NULL;
    new_list->curr_node = NULL;

    return new_list;
}

void List_Delete(PList plist) {
	PNode curr_node;
	if (plist == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}

	while (plist->first_node)
	{
		curr_node = plist->first_node;
		plist->first_node = curr_node->next_node;
		free(curr_node);
	}
	free(plist);
}

void List_Print(PList plist){
    PNode curr_node = NULL;

    if (plist == NULL){
        printf(ARG_ERR_MSG);
        return;
    }

    curr_node = plist->first_node;

    while(curr_node){
        plist->print_func(curr_node->pelem);
        curr_node = curr_node->next_node;
    }
}

Result List_Add_Elem(PList plist, PElem pelem) {
	PNode new_node;
	PNode curr_node;
	if (plist == NULL || pelem == NULL) {
		printf(ARG_ERR_MSG);
		return FAILURE;
	}

	new_node = (PNode)malloc(sizeof(NODE));
	if (new_node == NULL) {
		printf(MALLOC_ERR_MSG);
		return FAILURE;
	}

	new_node->plist = plist;
	new_node->pelem = pelem;
	new_node->next_node = NULL;

	curr_node = plist->first_node;
	if (plist->first_node == NULL)
	{
		plist->first_node = new_node;
		plist->curr_node = plist->first_node;
		return SUCCESS;
	}
	else
	{
		curr_node = plist->first_node;
		while (curr_node)
		{
			if (curr_node->next_node == NULL)
			{
				curr_node->next_node = new_node;
				return SUCCESS;
			}
			curr_node = curr_node->next_node;
		}
	}
	return FAILURE;
}

Result List_Remove_Elem(PList plist, PKey pkey){
    PNode curr_node = NULL;
    PNode prev_node = NULL;

    if(plist == NULL || pkey == NULL){
        printf(ARG_ERR_MSG);
        return FAILURE;
    }
    curr_node = plist->first_node;
    while (curr_node){
        if(plist->compare_keys_func(plist->get_key(curr_node->pelem),pkey)) {
            if (prev_node == NULL) {
                plist->first_node = curr_node->next_node;
            } else {
                prev_node->next_node = curr_node->next_node;
            }
            plist->destroy_func(curr_node->pelem);
            free(curr_node);
			plist->curr_node = plist->first_node; // It will make sure we have the most up to date curr_node
            return SUCCESS;
        }
        prev_node = curr_node;
        curr_node = curr_node->next_node;
    }
    return FAILURE;
}

PElem List_Get_First(PList plist) {
	if (plist == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	plist->curr_node = plist->first_node;
	return plist->first_node->pelem;
}

PElem List_Get_Next(PList plist){
    if(plist == NULL){
        printf(ARG_ERR_MSG);
        return NULL;
    }

    
    if(plist->curr_node != NULL){
        plist->curr_node = plist->curr_node->next_node;
    } else{
        return NULL;
    }
    return  plist->curr_node->pelem;
}

void List_Duplicate(PList psrc_list, PList pdst_list) {
	PNode s_curr_node;
	Result r;
	if (psrc_list == NULL || pdst_list == NULL || pdst_list->first_node != NULL) {
		printf(ARG_ERR_MSG);
		return;
	}

	pdst_list->print_func = psrc_list->print_func;
	pdst_list->clone_func = psrc_list->clone_func;
	pdst_list->compare_keys_func = psrc_list->compare_keys_func;
	pdst_list->destroy_func = psrc_list->destroy_func;
	pdst_list->get_key = psrc_list->get_key;

	s_curr_node = psrc_list->first_node;
	while (s_curr_node)
	{
		r = List_Add_Elem(pdst_list, s_curr_node->pelem);
		// Don't know if this part is necessary
		if (r == FAILURE)
		{
			List_Delete(pdst_list);
			printf("List duplication has failed");
			return;
		}
		s_curr_node = s_curr_node->next_node;
	}
	pdst_list->curr_node = pdst_list->first_node;
}

PElem List_Get_Elem(PList plist, PKey pkey){
    PNode curr_node = NULL;

    if(plist == NULL || pkey == NULL){
        printf(ARG_ERR_MSG);
        return NULL;
    }

    curr_node = plist->first_node;
    while (curr_node){
        if(plist->compare_keys_func(plist->get_key(curr_node->pelem),pkey)) {
            return curr_node->pelem;
        }
        curr_node = curr_node->next_node;
    }
    return NULL;
}