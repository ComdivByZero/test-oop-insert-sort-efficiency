#include "oop.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


typedef struct ElementRealization {
	int x, y;
} Point;

struct ComparatorContextRealization {
	Point p;
};

static Point** createArray(int cnt) {
	Point *els;
	Point **arr;
	arr = (Point **)malloc((sizeof(Point **) + sizeof(Point)) * cnt);
	if (arr != NULL) {
		els = (Point *)(arr + cnt);
		while (cnt > 0) {
			cnt--;
			arr[cnt] = els + cnt;
			els[cnt].x = rand() % (USHRT_MAX / 2) - USHRT_MAX / 4;
			els[cnt].y = rand() % (USHRT_MAX / 2) - USHRT_MAX / 4;
		}
	}
	return arr;
}

static void printArray(Point* arr[], int cnt, ComparatorContext *base) {
	int x, y;
	int i;
	for (i = 0; i < cnt; i++) {
		x = arr[i]->x - base->p.x;
		y = arr[i]->y - base->p.y;
		printf("%02d) (%03d:%03d) : %d\n", i, arr[i]->x, arr[i]->y, x * x + y * y);
	}
}

static int pointCompare(ComparatorContext *ext, Point *a, Point *b) {
	int ax, ay, bx, by;
	ax = a->x - ext->p.x;
	ay = a->y - ext->p.y;
	bx = b->x - ext->p.x;
	by = b->y - ext->p.y;
	return ax * ax + ay * ay - bx * bx - by * by;
}

static void pointCmpRelease(ComparatorContext *ext) {
	(void)ext;
}

int main(int argc, char const *argv[]) {
	int cnt;
	Point **points;
	Comparator *cmp;
	ComparatorContext *base;
	if (argc > 1) {
		cnt = atoi(argv[1]);
	} else {
		cnt = 11;
	}
	if (cnt > 0) {
		points = createArray(cnt);
		if (points != NULL) {
			cmp = comparatorCreate(sizeof(ComparatorContext), &base, pointCompare, pointCmpRelease);
			if (cmp != NULL) {
				base->p.x = 1;
				base->p.y = 2;
				if (cnt < 20) {
					printArray(points, cnt, base);
					printf("\n");
					oopSort(points, cnt, cmp);
					printArray(points, cnt, base);
				} else {
					oopSort(points, cnt, cmp);
				}
				comparatorRelease(&cmp);
			}
			free(points);
		}
	}
	return 0;
}
