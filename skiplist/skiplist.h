// -*- c++ -*-

class SkipList {
     struct D;
     D *d;
public:
     SkipList();		    // O(1)
     ~SkipList();		    // O(n)
     void put(int key, int val);    // O(log n)
     void del(int key);		    // O(log n)
     bool get(int key, int *val);   // O(log n)
     unsigned len(void);	    // O(n)
};
