#ifndef CRAWLER_H
#define CRAWLER_H

#include <stddef.h>
#include <stdbool.h>
typedef struct {
	char *url;
	char *html;
	size_t length;
	int depth;
} webpage_t;

typedef struct bag_t{
	webpage_t* ptr;
	struct bag_t* next;
} bag_t;



bag_t* bag_new(void);

bool bag_insert(bag_t* bag, webpage_t *ptr);
void bag_delete(bag_t* bag);
#endif
