#include <stdio.h>
#include <stdlib.h>

#include "crawler.h"
#include "curl.h"
#include "hashtable.h"
#include "pagedir.h"
#include "url.h"
#include <unistd.h>
/**
 * Parses command-line arguments, placing the corresponding values into the pointer arguments seedURL,
 * pageDirectory and maxDepth. argc and argv should be passed in from the main function.
 */
static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth) {
	if(argc != 4){
		exit(1);
	}else{
		seedURL = &argv[1];
		pageDirectory = &argv[2];
		int* depth = (int *)malloc(sizeof(int));
		*depth = atoi(argv[3]);
		maxDepth = depth;
		if(seedURL == NULL || pageDirectory == NULL || maxDepth == NULL|| !pagedir_init(*pageDirectory) || *maxDepth <= 0 || *maxDepth >= 10){
			exit(1);
		}
		return;
	}
}

/**
 * Crawls webpages given a seed URL, a page directory and a max depth.
 */
 
static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen) {
	size_t size;
	char* begin = page->html;
	char* end;
	char* normalBase = normalizeURL(page->url, page->url);
	if(begin!=NULL){
		while ((begin=strstr(begin, "<a")) != NULL) {
			begin = strstr(begin, "href=");
			begin += 5;
			if(begin[0]==39){
				begin++;
				end = strchr(begin, 39);
			}else if(begin[0]=='"'){
				begin++;
				end = strchr(begin, '"');
			}	
			
			if (end != NULL) {
				char url[(int)(end-begin)];
				sprintf(url, "%.*s", (int)(end-begin), begin);
				if(url[0]!='#'){
					char* normalURL = normalizeURL(page->url, url);
					printf("found: %s\n", normalURL);
					if(normalURL!=NULL && normalBase!= NULL && isInternalURL(normalBase, normalURL)){
						if(hashtable_insert(pagesSeen, normalURL, normalURL)){
							webpage_t *ptr = (webpage_t *)malloc(sizeof(webpage_t));
							size_t sizeURL;
							char* html = download(normalURL, &sizeURL);
							ptr->html = html;
							ptr->url = normalURL;
							ptr->depth = page->depth + 1;
							bag_insert(pagesToCrawl,ptr);
							printf("added to bag: %s\n", normalURL);
						}else{
							free(normalURL);
						}
					}else{
						free(normalURL);
					}
					
				}
				
				begin = end + 1;
			}else {
				break;
			}
		}
	}
	printf("scanned page\n");
	free(normalBase);
}

static void crawl(char *seedURL, char *pageDirectory, const int maxDepth) {
	
	hashtable_t* hTable = hashtable_new(200);
	
	char* seed = normalizeURL(seedURL, seedURL);
	if(seed == NULL){
		exit(1);
	}
	
	hashtable_insert(hTable, seed, seed);
	bag_t* bag = bag_new();
	
	webpage_t* ptr = malloc(sizeof(webpage_t));
	ptr->url = seed;
	char* html;
	size_t size;
	
	html = download(seed, &size);
	if(html == NULL){
		exit(1);
	}
	
	ptr->html = html;
	ptr->length = (int)(size);
	ptr->depth = 0;
	bag_insert(bag, ptr);
	
	int id = 1;
	bag_t* temp = bag;
	while(bag!= NULL){
		webpage_t* webpage = bag->ptr;
		
		char* htmlURL = webpage->html;
		if(htmlURL != NULL){
			pagedir_save(webpage, pageDirectory, id);
			id++;
		}
		if(webpage->depth < maxDepth){
			pageScan(webpage, bag, hTable);
		}
		
		bag = bag->next;
	}
	hashtable_delete(hTable, NULL);
	bag_delete(temp);
	
}

/**
 * Scans a webpage for URLs.
 */


int main(const int argc, char *argv[]) {	
	char **seedURL;
	char **pageDirectory;
	int *maxDepth;
	if(argc != 4){
		exit(1);
	}else{
		seedURL = &argv[1];
		pageDirectory = &argv[2];
		int depth = (atoi(argv[3]));
		maxDepth = &depth;
		if(seedURL == NULL || pageDirectory == NULL || maxDepth == NULL|| !pagedir_init(*pageDirectory) || *maxDepth <= 0 || *maxDepth >= 10){
			exit(1);
		}
	}
	crawl(*seedURL, *pageDirectory, *maxDepth);
	exit(0);
}
