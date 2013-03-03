#include "oop.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct {
	int (*compare)(void *ext, Element a, Element b);
	void (*release)(void *ext);
	void *ext;
} RComparator;

extern Comparator comparatorCreate(int extSize, void **ext, 
					int (*compare)(void *ext, Element a, Element b),
					void (*release)(void *ext)) {

	RComparator *cmp;
	cmp = (RComparator *)malloc(sizeof(RComparator) - sizeof(void *) + extSize);
	if (cmp != NULL) {
		cmp->compare = compare;
		cmp->release = release;
		*ext = (void *)&cmp->ext;
	}
	return (Comparator)cmp;
}

extern int compare(Comparator cmp, Element a, Element b) {
	return ((RComparator *)cmp)->compare((void *)&((RComparator *)cmp)->ext, a, b);
}

extern void comparatorRelease(Comparator *cmp) {
	RComparator *rc = (RComparator *)*cmp;
	if (rc != NULL) {
		rc->release((void *)&rc->ext);
		free(rc);
		*cmp = NULL;
	}
}

extern void oopSort(Element arr[], int cnt, Comparator cmp) {
	int i, j;
	Element a;
	int (*compare)(void *ext, Element a, Element b) = ((RComparator *)cmp)->compare;
	void *ext = (void *)&((RComparator *)cmp)->ext;
	for (i = 1; i < cnt; i++) {
		a = arr[i];
		j = i - 1;
		while (j >= 0 && compare(ext, a, arr[j]) < 0) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = a;
	} 
}
