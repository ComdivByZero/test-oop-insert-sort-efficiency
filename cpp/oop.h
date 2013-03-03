
class Element {

};

class Comparator {

public: virtual int compare(Element *a, Element *b) const = 0;

};

void oopSort(Element *arr[], int cnt, Comparator *cmp);