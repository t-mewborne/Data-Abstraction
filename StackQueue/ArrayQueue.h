#include "Queue.h"
#include <stdexcept> //For throwing exceptions
#include <iostream>

using namespace std;

template<typename T>
class ArrayQueue: public Queue<T> {
private:

    T*arr;
    int capacity;
    int head;
    int tail;

    void growArray() { //Most helper funtions should be private
        T* newArr = new T[capacity * 2];
        for(int i = 0; i <= capacity; i++) newArr[i] = arr[(head + i) % capacity];
        head = 0;
        tail = capacity - 1;
        delete[] arr; //Delete old content of arr
        arr = newArr; //Set the empty array arr equal to newArr
        capacity *= 2; //Double the capacity
    }

    void shiftArray() {
        for(int i = 0; i < tail; i++) arr[i] = arr[i+1];
        tail--;
    }


public:
    ArrayQueue ()
    {
        arr = new T[10];
        capacity = 10;
        head = 0;
        tail = 0;
    }
    
    ~ArrayQueue() {
        delete [] arr;
    }
    

  
    //copy constructor
    ArrayQueue(const ArrayQueue& other){
        capacity = other.capacity;
        head = other.head;
        tail = other.tail;
        arr = new T[capacity];
        for (int i = 0; i <= capacity; i++) {
            arr[i] = other.arr[i]; 
        }   
    }
                    
    //copy assignment
    ArrayQueue& operator= (const ArrayQueue& other) {
        int length = other.capacity;
        T *p = new T[length];
        for (int i = 0; i < length; i++) p[i] = other.arr[i];
        delete[] arr;
        arr = p; 
        return ArrayQueue();
    }   



    void enqueue(const T &value) {
        if ((tail + 1) % capacity == head) growArray();
        arr[tail] = value;
        tail = (tail + 1) % capacity;
    }
    
    T dequeue() {
        if (isEmpty()) throw std::out_of_range("(ArrayQueue.h/dequeue The queue is empty");
        T value = arr[head];
        head = (head + 1) % capacity;
        return value;
    }
    
   T peek() const {
        if (isEmpty()) throw std::out_of_range("(ArrayQueue.h/peek) The queue is empty");
        else return arr[head];
   }
    
   bool isEmpty() const {return head == tail;}

   void printArray() {
       if (isEmpty()) cout<<"The Queue is empty. Capacity: "<<capacity<<'\n';
       else {
           cout<<'[';
           for(int i = head; i < tail; i++) {
               cout<<arr[i];
               if (i < tail - 1) cout<<',';
              }
              cout<<"] Head: "<<head<<" Tail: "<<tail<<" Capacity: "<<capacity<<'\n';
       }
   }

};
