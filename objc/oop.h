
@protocol Element 
@end

@protocol Comparator
-(int)compare:(id<Element>)a :(id<Element>)b;

@end

extern void oopSort(id<Element> arr[], int cnt, id<Comparator> cmp);