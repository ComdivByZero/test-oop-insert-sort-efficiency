
typedef struct ElementRealization Element;

typedef struct ComparatorClosedRealization Comparator;
typedef struct ComparatorContextRealization ComparatorContext;

extern Comparator* comparatorCreate(int extSize, ComparatorContext **ext, 
					int compare(ComparatorContext *ext, Element *a, Element *b),
					void release(ComparatorContext *ext));
extern void comparatorRelease(Comparator **cmp);
extern int compare(Comparator *cmp, Element *a, Element *b);

extern void oopSort(Element *arr[], int cnt, Comparator *cmp);
