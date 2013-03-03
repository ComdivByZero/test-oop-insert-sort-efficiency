#include "oop.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


typedef struct {
	int x, y;
} Point;

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

static void printArray(Point* arr[], int cnt, Point *base) {
	int x, y;
	int i;
	for (i = 0; i < cnt; i++) {
		x = arr[i]->x - base->x;
		y = arr[i]->y - base->y;
		printf("%02d) (%03d:%03d) : %d\n", i, arr[i]->x, arr[i]->y, x * x + y * y);
	}
}

static int pointCompare(Point *ext, Point *a, Point *b) {
	int ax, ay, bx, by;
	ax = a->x - ext->x;
	ay = a->y - ext->y;
	bx = b->x - ext->x;
	by = b->y - ext->y;
	return ax * ax + ay * ay - bx * bx - by * by;
}

static void pointCmpRelease(void *ext) {
	(void)ext;
}

int main(int argc, char const *argv[]) {
	int cnt;
	Point **points;
	Comparator cmp;
	Point *base;
	if (argc > 1) {
		cnt = atoi(argv[1]);
	} else {
		cnt = 11;
	}
	if (cnt > 0) {
		points = createArray(cnt);
		if (points != NULL) {
			cmp = comparatorCreate(sizeof(Point), (void **)&base, (int (*)(void *ext, Element a, Element b))pointCompare, pointCmpRelease);
			if (cmp != NULL) {
				base->x = 1;
				base->y = 2;
				if (cnt < 20) {
					printArray(points, cnt, base);
					printf("\n");
					oopSort((Element *)points, cnt, cmp);
					printArray(points, cnt, base);
				} else {
					oopSort((Element *)points, cnt, cmp);
				}
				comparatorRelease(&cmp);
			}
			free(points);
		}
	}
	return 0;
}