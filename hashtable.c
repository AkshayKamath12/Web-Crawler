#include <stddef.h>
#include "hashtable.h"
#include "set.h"

hashtable_t *hashtable_new(const int num_slots){
	set_t **arr;
	arr = (set_t**)malloc(sizeof(set_t *) * num_slots);
	if(arr == NULL){
		return NULL;
	}
	for(int i = 0; i<num_slots; i++){
		arr[i] = set_new();
	}
	
	hashtable_t* ht = malloc(sizeof(hashtable_t));
	if(ht == NULL){
		return NULL;
	}
	ht->ptr = arr;
	ht->count = num_slots;
	return ht;
}

bool hashtable_insert(hashtable_t *ht, const char *key, void *item){
	if(ht == NULL || key == NULL || item == NULL){
		return 0;
	}
	int sum = 0;
	for(long unsigned int i =0;i<strlen(key);i++){
		sum += key[i];
	}
	int bin = sum%(ht->count);
	return set_insert((ht->ptr)[bin], key, item);	
}

void *hashtable_find(hashtable_t *ht, const char *key){
	if(ht == NULL || key == NULL){
		return NULL;
	}
	int sum = 0;
	for(long unsigned int i =0;i<strlen(key);i++){
		sum += key[i];
	}
	return set_find((ht->ptr)[sum%(ht->count)], key);
}

void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)){
	for(int i = 0; i< ht->count; i++){
		set_t* ptr = (ht->ptr)[i];
		set_print(ptr, fp, itemprint);
	}
}

void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)){
	if(ht != NULL && itemfunc != NULL){
		for(int i = 0; i< ht->count; i++){
			set_t* ptr = (ht->ptr)[i];
			set_iterate(ptr, arg, itemfunc);
		}
	}
}

void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item)){
	if(ht != NULL){
		for(int i = 0; i< ht->count; i++){
			set_t* ptr = (ht->ptr)[i];
			set_delete(ptr, itemdelete);
		}
		free(ht->ptr);
		free(ht);
	}
}

