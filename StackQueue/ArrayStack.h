#include "Stack.h"
#include <iostream>
#include <stdexcept> //For throwing exceptions

using namespace std;

template<typename T>
class ArrayStack: public Stack<T> {
    private:
        T* arr;
        int capacity;
        int top;

        void growArray() { //Most helper funtions should be private
            T* newArr = new T[capacity * 2];
            for(int i = 0; i <= top; i++) newArr[i] = arr[i];
            delete[] arr; //Delete old content of arr
            arr = newArr; //Set the empty array arr equal to newArr
            capacity *= 2; //Double the capacity
        }

    public:
        ArrayStack ()
        {
            arr = new T[10];
            top = -1;
            capacity = 10;
        }
        ~ArrayStack() {
            delete [] arr;
        }


        //copy constructor
        ArrayStack(const ArrayStack& other){
            capacity = other.capacity;
            top = other.top;
            arr = new T[capacity];
            for (int i = 0; i <= top; i++) {
                arr[i] = other.arr[i]; 
            }
        }
        
        //copy assignment
        ArrayStack& operator= (const ArrayStack& other) {
            int length = other.capacity;
            T *p = new T[length];
            for (int i = 0; i < length; i++) p[i] = other.arr[i];
            delete[] arr;
            arr = p;
            return ArrayStack();
        }



        void push(const T &value) {
            top++;
            if (top == (capacity - 1)) growArray(); //threw a seg fault w/o - 1 from capacity (only strings)
            arr[top] = value;
        }

        T pop() {
            if (isEmpty()) throw std::out_of_range("(ArrayStack.h/pop) The stack is empty");
            top--;
            return arr[top+1];
        }

        T peek() const {
            if (isEmpty()) throw std::out_of_range("(ArrayStack.h/peek) The stack is empty");
            return arr[top];
        }

        bool isEmpty() const {
            return top == -1;
        }

        void printArray() {
            if (isEmpty()) cout<<"The array is empty. Top: "<<top<<" Capacity: "<<capacity<<'\n';
            else {
                cout<<'[';
                for(int i = 0; i <= top; i++) {
                    cout<<arr[i];
                    if (i < top) cout<<',';
                }
                cout<<"] Top: "<<top<<"  Capacity: "<<capacity<<'\n';
            }
        }
};
