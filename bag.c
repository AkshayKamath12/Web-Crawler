#include <stddef.h>
#include "crawler.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
bag_t* bag_new(void){
	bag_t* bag = (bag_t *) malloc(sizeof(bag_t));
	if(bag == NULL){
		return NULL;
	}
	bag->ptr = NULL;
	bag->next = NULL;
	return bag;
}

bool bag_insert(bag_t* bag, webpage_t *ptr){
	if(bag == NULL || ptr == NULL){
		return 0;
	}
	while(bag->next != NULL){
		bag = bag->next;
	}
	if(bag->ptr == NULL){
		bag->ptr = ptr;
	}else{
		bag->next = (bag_t *) malloc(sizeof(bag_t));
		bag = bag->next;
		bag->ptr = ptr;
		bag->next = NULL;
	}
}

void bag_delete(bag_t* bag){
	bag_t* temp;
	for(;bag!=NULL;bag=temp){
		webpage_t *webpage = bag->ptr;
		if(webpage->url != NULL){
			free(webpage->url);
		}
		if(webpage->html != NULL){
			free(webpage->html);
		}
		free(webpage);
		temp = bag->next;
		free(bag);
	}
}
