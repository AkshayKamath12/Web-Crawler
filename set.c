#include <stddef.h>
#include "set.h"

set_t* set_new(void){
	set_t* ptr = (set_t *) malloc(sizeof(set_t));
	if(ptr == NULL){
		return NULL;
	}
	ptr->key=NULL;
	ptr->value=NULL;
	ptr->next=NULL;
	return ptr;
}

bool set_insert(set_t *set, const char *key, void *item){
	if(set==NULL || key == NULL || item == NULL){
		return 0;
	}
	set_t* temp = set;
	
	for(;set!=NULL&&set->key!=NULL;set=set->next){
		if(set->key!=NULL && strcmp(set->key, key) == 0){
			return 0;
		}
		temp=set;
	}
	
	set=temp;
	if(set->key==NULL){
		set->key=key;
		set->value=item;
		set->next=NULL;
		return 1;
	}else{
		set_t* ptr = (set_t *) malloc(sizeof(set_t));
		ptr->key = key;
		ptr->value = item;
		ptr->next = NULL;
		set->next = ptr;
		return 1;
	}
	
	
}

void *set_find(set_t *set, const char *key){
	if(set == NULL || key == NULL){
		return NULL;
	}
	for(;set!=NULL;set=set->next){	
		if(set->key!=NULL && strcmp(key, set->key)==0){
			return set->value;
		}
		if(set->next==NULL){
			break;
		}
	}
	
	return NULL;
}

void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)){
	if(set != NULL && fp != NULL){
		while(set!=NULL){
			itemprint(fp, set->key, set->value);			
			set = set->next;
		}
	}
}

void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)){
	if(set != NULL && itemfunc != NULL){
		while(set!=NULL){
			itemfunc(arg, set->key, set->value);			
			set = set->next;
		}
	}     
}

void set_delete(set_t *set, void (*itemdelete)(void *item)){
	set_t* temp;
	for(;set!=NULL;set=temp){
		temp = set->next;
		if(itemdelete!=NULL){
			itemdelete(set->value);
		}
		free(set);
		
	}
}

