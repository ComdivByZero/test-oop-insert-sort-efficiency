typedef struct {
	void ***element;
}* Element;

typedef struct {
	void ***comparator;
}* Comparator;

extern Comparator comparatorCreate(int extSize, void **ext, 
					int (*compare)(void *ext, Element a, Element b),
					void (*release)(void *ext));
extern void comparatorRelease(Comparator *cmp);
extern int compare(Comparator cmp, Element a, Element b);

extern void oopSort(Element arr[], int cnt, Comparator cmp);
