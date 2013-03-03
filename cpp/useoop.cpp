#include "oop.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


class IntPoint : public Element {
public:
	int x, y;
	IntPoint(int _x, int _y) : x(_x), y(_y) {}; 	
};

class PointComparator : public Comparator {
public:
	int x, y;
	PointComparator(int _x, int _y) : x(_x) , y(_y) {};

	int compare(Element *ia, Element *ib) const {
		int ax, ay, bx, by;
		IntPoint *a, *b;
		a = static_cast<IntPoint *>(ia);
		b = static_cast<IntPoint *>(ib);
		ax = a->x - x;
		ay = a->y - y;
		bx = b->x - x;
		by = b->y - y;
		return ax * ax + ay * ay - bx * bx - by * by;
	}

};

static IntPoint** createArray(int cnt) {
	IntPoint **arr;
	arr = (IntPoint **)malloc(sizeof(IntPoint *) * cnt);
	if (arr != NULL) {
		while (cnt > 0) {
			cnt--;
			arr[cnt] = new IntPoint(rand() % (USHRT_MAX / 2) - USHRT_MAX / 4, rand() % (USHRT_MAX / 2) - USHRT_MAX / 4);
		}
	}
	return arr;
}

static void releaseArray(IntPoint **arr, int cnt) {
	while (cnt > 0) {
		cnt--;
		delete arr[cnt]; 
	}
	free(arr);
}

static void printArray(IntPoint* arr[], int cnt, IntPoint *base) {
	int x, y;
	int i;
	for (i = 0; i < cnt; i++) {
		x = arr[i]->x - base->x;
		y = arr[i]->y - base->y;
		printf("%02d) (%03d:%03d) : %d\n", i, arr[i]->x, arr[i]->y, x * x + y * y);
	}
}

int main(int argc, char const *argv[]) {
	int cnt;
	IntPoint **points;
	IntPoint base(1, 2);
	PointComparator cmp(base.x, base.y);
	if (argc > 1) {
		cnt = atoi(argv[1]);
	} else {
		cnt = 11;
	}
	if (cnt > 0) {
		points = createArray(cnt);
		if (points != NULL) {
			if (cnt < 20) {
				printArray(points, cnt, &base);
				printf("\n");
				oopSort(reinterpret_cast<Element **>(points), cnt, &cmp);
				printArray(points, cnt, &base);
			} else {
				oopSort(reinterpret_cast<Element **>(points), cnt, &cmp);
			}
			releaseArray(points, cnt);
		}
	}
	return 0;
}