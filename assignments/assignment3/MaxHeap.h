#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>
#include <iostream>

using namespace std;

template <class Comparable>
class MaxHeap{
    public:
        //constructor with default capacity
        MaxHeap(int capacity = 100): current_size(0), array(capacity + 1){}

        //checks if heap is empty
        bool isEmpty() const {
            return current_size == 0;
        }
        
        //returns max item in heap(root)
        const Comparable & findMax() const{
            return array[1];
        }
        // insert new element
        void insert(const Comparable &x){
            //resizes if heap is full
           if (current_size == array.size() - 1){
             array.resize(array.size() * 2);
           }
        
        //start with new hole pos
            
            int hole = ++current_size;
            Comparable copy = x;
            array[0] = std::move(copy);
        
        //percolate up
        for(; x > array[hole/2]; hole /= 2){
            array[hole] = std::move(array[hole/2]);
        }
        array[hole] = std::move(array[0]); //place x in its position
        
        }
        //remove and return max item from heap
        Comparable deleteMax(){
            if(isEmpty()){
                throw underflow_error("Heap is empty");
            }
            Comparable maxItem = array[1]; //root
            array[1] = array[current_size--]; //move last item 
            percolateDown(1); //restore order 
            return maxItem;
            
        }

    private:
        int current_size;
        vector<Comparable> array;
        void percolateDown(int hole){
            int child;
            Comparable tmp = std::move(array[hole]);

            //move down tree
            for(; hole * 2 <= current_size; hole = child)
            {
                child = hole * 2;
                //find larger child 
                if(child != current_size && array[child+1] >  array[child]){
                    ++child;
                }
                //move larger child up is greater than tmp
                if(array[child] > tmp){
                    array[hole] = array[child];
                }else{
                    break;
                }
                array[hole] = std::move(tmp); // put tmp in final position
            }
        }
           
};

#endif //MAXHEAP.H