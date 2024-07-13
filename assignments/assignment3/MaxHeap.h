#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>

using namespace std;

template <class Comparable>
class MaxHeap{
    public:
        MaxHeap(int capacity = 100): current_size(0), array(capacity + 1){}
        bool isEmpty() const {
            return current_size == 0;
        }
        const Comparable & findMax() const{return array[1];}
        void insert(const Comparable &x);
        Comparable deleteMax();

    private:
        int current_size;
        vector<Comparable> array;
        void percolateDown(int hole);
};

#endif //MAXHEAP.H