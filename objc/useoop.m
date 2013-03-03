#include "oop.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#import <Foundation/Foundation.h>


@interface IntPoint: NSObject<Element> {
@public
	int x, y;
}

+create:(int)x :(int)y;

@end

@implementation IntPoint 

+create:(int)x :(int)y {
	IntPoint *p;
	p = [[IntPoint alloc] init];
	if (p != nil) {
		p->x = x;
		p->y = y;
	} 
	return p;
}

@end

@interface PointComparator: NSObject<Comparator> {
@public	
	int x, y;
}

+ create:(int)x :(int)y;

@end;

@implementation PointComparator

+ create:(int)x :(int)y; {
	PointComparator *cmp;
	cmp = [[PointComparator alloc] init];
	if (cmp != nil) {
		cmp->x = x;
		cmp->y = y;
	}
	return cmp;
}

-(int)compare:(id<Element>)ia :(id<Element>)ib {
	int ax, ay, bx, by;
	IntPoint *a, *b;
	a = (IntPoint *)ia;
	b = (IntPoint *)ib;
	ax = a->x - x;
	ay = a->y - y;
	bx = b->x - x;
	by = b->y - y;
	return ax * ax + ay * ay - bx * bx - by * by;
}

@end

static IntPoint** createArray(int cnt) {
	IntPoint **arr;
	arr = (IntPoint **)malloc(sizeof(IntPoint *) * cnt);
	if (arr != NULL) {
		while (cnt > 0) {
			cnt--;
			arr[cnt] = [IntPoint create:rand() % (USHRT_MAX / 2) - USHRT_MAX / 4 :rand() % (USHRT_MAX / 2) - USHRT_MAX / 4];
		}
	}
	return arr;
}

static void releaseArray(IntPoint **arr, int cnt) {
	while (cnt > 0) {
		cnt--;
		[arr[cnt] release];
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
	IntPoint *base;
	PointComparator *cmp;
	if (argc > 1) {
		cnt = atoi(argv[1]);
	} else {
		cnt = 11;
	}
	if (cnt > 0) {
		points = createArray(cnt);
		if (points != NULL) {
			cmp = [PointComparator create:1 :2];
			if (cmp != NULL) {
				if (cnt < 20) {
					base = [IntPoint create:cmp->x :cmp->y];
					printArray(points, cnt, base);
					printf("\n");
					oopSort(points, cnt, cmp);
					printArray(points, cnt, base);
					[base release];
				} else {
					oopSort(points, cnt, cmp);
				}
				[cmp release];
			}
			releaseArray(points, cnt);
		}
	}
	return 0;
}
