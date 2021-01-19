#include <iostream>

using namespace std;


template<typename T>
class ArrayList {
    private:
        T* arr;
        int sz;
        int capacity; 
 
        void growArray() { //Most helper funtions should be private
            T* newArr = new T[capacity * 2]; 
            for(int i = 0; i < sz; i++) newArr[i] = arr[i];
            delete[] arr; //Delete old content of arr
            arr = newArr; //Set the empty array arr equal to newArr
            capacity *= 2; //Double the capacity
        }

    public:
        // Types
        // value_type
        typedef T value_type;

        // iterator
        // e.g. class iterator { .... };
        class iterator {
            //iterator should be able to read and write to the array
            private:
                T* ptr;
            public:
                iterator(T *l):ptr{l} {}
                iterator():ptr(nullptr) {}
                
                iterator(const iterator &i) {
                    ptr = i.ptr;
                }

                T &operator*() {
                    return *ptr;
                }

               
                bool operator==(const iterator &i) const{
                    return ptr==i.ptr;
                }
                
                bool operator!=(const iterator &i) const{
                    return ptr != i.ptr;
                }

                
                iterator &operator=(const iterator &i){
                    return ptr = i.ptr;
                }
                

                iterator &operator++(){
                    ptr++;
                    return *this;
                }
                
                iterator &operator--(){
                    ptr--;
                    return *this;
                }


                iterator operator++(int){
                    auto ret = *this;
                    ptr++;
                    return ret;
                }

                iterator operator--(int){
                    auto ret = *this;
                    ptr--;
                    return ret;
                }
        };

        class const_iterator {
            //const_iterator should only be able to read the array
            private:
                T* ptr;
            public:
                const_iterator(T *l):ptr{l} {}
                const_iterator():ptr(nullptr) {}
                
                const_iterator(const const_iterator &i) {
                    ptr = i.ptr;
                }

                const T &operator*() const {
                    return *ptr;
                }

                bool operator==(const const_iterator &i) const{
                    return ptr==i.ptr;
                }

                bool operator!=(const const_iterator &i) const{
                    return ptr != i.ptr;
                }

 
                const_iterator &operator=(const const_iterator &i){
                    return ptr = i.ptr;
                }
                

                const_iterator &operator++(){
                    ptr++;
                    return *this;
                }
                
                const_iterator &operator--(){
                    ptr--;
                    return *this;
                }


                const_iterator operator++(int){
                    auto ret = *this;
                    ptr++;
                    return ret;
                }

                const_iterator operator--(int){
                    auto ret = *this;
                    ptr--;
                    return ret;
                }

        };

        // General Methods
        
        ArrayList() {
            capacity = 10;
            sz = 0;
            arr = new T[capacity];
        }

        //copy constructor
        ArrayList(const ArrayList &other) {
            capacity = other.capacity;
            sz = other.sz;
            arr = new T[capacity];
            for (int i = 0; i <= sz; i++) {
                arr[i] = other.arr[i]; 
            }
        }

        //copy assignment 
        ArrayList<T> &operator=(const ArrayList<T> &other) {
            T *p = new T[other.capacity];
            for (int i = 0; i <= other.sz; i++) p[i] = other.arr[i];
            delete[] arr;
            arr = p;
            capacity = other.capacity;
            sz = other.sz;
            return *this;
        }
        
        ~ArrayList() {
            delete [] arr;
        }

        //add to the end
        void push_back(const T &value){ 
            //cout<<"A: "<<sz<<'\n';
            sz++;
            //cout<<"B: "<<sz<<'\n';
            if (sz == capacity) growArray();
            arr[sz-1] = value;
            //cout<<"C: "<<sz-1<<'\n';
        }

        //remove the last element
        void pop_back() {
            sz--;
        }

        //return the size
        int size() const {
            return sz;
        }
        
        void clear() {
            capacity = 10;
            sz = 0;
            T* newArr = new T[capacity];
            delete [] arr;
            arr = newArr;
        }
        
        void insert(const T &t,int index) {    // insert this element before the given index.
            for (int i = sz - 1; i >= index; i--) arr[i+1] = arr[i];
            arr[index] = t;
            sz++;
        }

        const T &operator[](int index) const { // get the element at index.
            return arr[index];
        }

        T &operator[](int index) {             // get the element at index.
            return arr[index];
        }

        void remove(int index) {              // remove the item at the given index.
            if (size() > 0) {
                for (int i=index+1; i < sz; i++) arr[i-1]=arr[i];
                sz--;
            }
        }

        iterator begin(){
            return iterator( & (arr[0]));
        }
        
        iterator end(){
            return iterator(arr+size());
        }

        const_iterator begin() const {
            return const_iterator (& (arr[0]));
        }

        const_iterator end() const {
            return const_iterator(arr+size());
        }

        const_iterator cbegin() const {
            return const_iterator( & (arr[0]));
        }

        const_iterator cend() const {
            return const_iterator(arr+size());
        }

        void printArray() const {
            cout<<'[';
            for(int i = 0; i < size(); i++) {
                cout<<arr[i];
                if (i < size()-1) cout<<',';
            }
            cout<<"]\nSize="<<size()<<" Capacity="<<capacity<<" Begin="<<*begin();
            cout<<" arr[0]="<<arr[0]<<" arr[size()]="<<arr[size()]<<'\n';
        }
};
