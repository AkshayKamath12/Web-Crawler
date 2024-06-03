#include "pagedir.h"

bool pagedir_init(const char *pageDirectory) {	
	char direct[strlen(pageDirectory)];
	strcpy(direct, pageDirectory);
	if(fopen(direct, "r")==NULL){
		return 0;
	}else{
		if(fopen(strcat(direct, "/crawl.crawler"), "w")==NULL){
			return 0;
		}
		return 1;
	}
}

void pagedir_save(const webpage_t *page, const char *pageDirectory, const int documentID) {
	if(page!=NULL && page->url != NULL && page->html != NULL){
		int testId = documentID;
		int digits = 1;
		while(testId > 9){
			testId/=10;
			digits++;
		}
		char direct[strlen(pageDirectory)];
		char id[digits + 1];
		snprintf(id, digits+1, "%d", documentID);
		strcpy(direct, pageDirectory);
		FILE *fp = fopen(strcat(strcat(direct, "/"), id), "w");
		char depthStr[3];
		snprintf(depthStr, 3, "%d", page->depth);
		if(page->url != NULL){
			fputs(page->url, fp);
			fputs("\n", fp);
		}
		fputs(depthStr, fp);
		fputs("\n", fp);
		if(page->html != NULL){
			fputs(page->html, fp);
		}
	}
}
