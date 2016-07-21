#include "oop.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

struct ComparatorClosedRealization {
	int (*compare)(ComparatorContext *ext, Element *a, Element *b);
	void (*release)(ComparatorContext *ext);
	ComparatorContext *ext;
};

extern Comparator* comparatorCreate(int extSize, ComparatorContext **ext, 
					int compare(ComparatorContext *ext, Element *a, Element *b),
					void release(ComparatorContext *ext)) {

	Comparator *cmp;
	cmp = (Comparator *)malloc(sizeof(Comparator) + extSize);
	if (cmp != NULL) {
		cmp->compare = compare;
		cmp->release = release;
		*ext = (ComparatorContext *)(cmp + 1);
		cmp->ext = *ext;
	}
	return cmp;
}

extern int compare(Comparator *cmp, Element *a, Element *b) {
	return cmp->compare(cmp->ext, a, b);
}

extern void comparatorRelease(Comparator **cmp) {
	if (*cmp != NULL) {
		(*cmp)->release((*cmp)->ext);
		free(*cmp);
		*cmp = NULL;
	}
}

extern void oopSort(Element *arr[], int cnt, Comparator *cmp) {
	int i, j;
	Element *a;
	int (*compare)(ComparatorContext *ext, Element *a, Element *b) = cmp->compare;
	ComparatorContext *ext = cmp->ext;
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
