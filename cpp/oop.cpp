#include "oop.h"

#include <stdlib.h>
#include <limits.h>

extern void oopSort(Element *arr[], int cnt, Comparator *cmp) {
	int i, j;
	Element *a;
	for (i = 1; i < cnt; i++) {
		a = arr[i];
		j = i - 1;
		while (j >= 0 && cmp->compare(a, arr[j]) < 0) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = a;
	} 
}
