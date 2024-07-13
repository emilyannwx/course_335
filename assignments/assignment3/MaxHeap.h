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
        void insert(const Comparable &x){
          if (current_size == array.size() - 1){
            array.resize(array.size() * 2);
          }
          int hole = ++current_size;
          Comparable copy = x;
          array[0] = move(copy);
          for(; x > array[hole/2]; hole/=2){
            array[hole] = move(array[hole/2]);
          }
          array[hole]= move(array[0]);
        }
        Comparable deleteMax(){
            if(isEmpty()){
                throw runtime_error("Heap is empty");
                Comparable maxItem = move(array[1]);
                array[1] = move(array[current_size--]);
                percolateDown(1);
                return maxItem;
            }
        }

    private:
        int current_size;
        vector<Comparable> array;
        void percolateDown(int hole){
            int child;
            Comparable tmp = move(array[hole]);
            for(; hole * 2 <= current_size; hole = child){
                child = hole *2;
                if(child != current_size && array[child+1] > array[child]){
                    ++childl
                }
                if(array[child] > tmp){
                    array[hole] = move(array[child]);
                }else{
                    break;
                }
                array[hole] = move(tmp);
            }
        }
};

#endif //MAXHEAP.H