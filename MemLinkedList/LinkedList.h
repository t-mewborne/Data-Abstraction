#include <iostream>

using namespace std;

template<typename T>
class LinkedList {
    private:
        struct Node { 
            T data; 
            Node* prev;
            Node* next;
        };
        Node* sentinel;
        int sz;

    public:
        typedef T value_type;

        class iterator {
            private:        
                Node* ptr;
            public:
                iterator(Node *l):ptr{l} {}
                iterator():ptr(nullptr) {}

                iterator(const iterator &i) {
                    ptr = i.ptr;
                }


                T &operator*() { 
                    return ptr -> data; 
                }

                bool operator==(const iterator &other) const { 
                    return ptr == other.ptr;
                }

                bool operator!=(const iterator &other) const { 
                    return ptr != other.ptr; 
                }

                iterator &operator=(const iterator &other) { 
                    ptr = other.ptr;
                    return *this;
                }

                iterator &operator++() { 
                    ptr = ptr -> next;
                    return *this;
                }

                iterator &operator--() { 
                    ptr = ptr -> prev;
                    return *this;
                }

                iterator operator++(int) {
                    auto ret = *this;
                    ptr = ptr -> next;
                    return ret;
                }

                iterator operator--(int) {
                    auto ret = *this;
                    ptr = ptr -> prev;
                    return ret;
                }

                friend class const_iterator;

                friend class LinkedList;
        };

        class const_iterator {
            private:
                Node* ptr;
            public:
                const_iterator(Node *l):ptr{l} {}
                const_iterator():ptr(nullptr) {}

                const_iterator(const const_iterator &i) {
                    ptr = i.ptr;
                }


                const T &operator*() const {
                    return ptr -> data;
                }

                bool operator==(const const_iterator &other) const {
                    return ptr == other.ptr;
                }

                bool operator!=(const const_iterator &other) const {
                    return ptr != other.ptr;
                }

                const_iterator &operator=(const const_iterator &other) {
                    ptr = other.ptr;
                    return *this;

                }

                const_iterator &operator++() {
                    ptr = ptr -> next;
                    return *this;
                }

                const_iterator &operator--() {
                    ptr = ptr -> prev;
                    return *this;
                }

                const_iterator operator++(int) {
                    auto ret = *this;
                    ptr = ptr -> next;
                    return ret;
                }

                const_iterator operator--(int) {
                    auto ret = *this;
                    ptr = ptr -> prev;
                    return ret;
                }
        };             

        // General Methods
        // Constructors
        LinkedList() {
            sz = 0;
            sentinel = new Node;
            sentinel -> prev = sentinel;
            sentinel -> next = sentinel;
        }

        //copy constructor
        LinkedList(const LinkedList &other) {
            /*sentinel = new Node;
            sz = other.sz; 
            auto newPrev = sentinel;
            auto rover = other.begin();
            while (rover != other.end()) {
                auto newNode = new Node{rover -> data, newPrev, nullptr};
                newPrev -> next = newNode;
                newPrev = newNode;
                rover++;
            }   
            newPrev -> next = sentinel;
            sentinel -> prev = newPrev;*/
            sz = 0;
            sentinel = new Node;
            sentinel -> prev = sentinel;
            sentinel -> next = sentinel;
            for (auto x:other) push_back(x);
        }

        //copy assignment
        LinkedList &operator=(const LinkedList &other) {
        /*    sentinel = new Node;
            sz = other.sz; 
            auto newPrev = sentinel;
            for (int i = 0; i < sz; i++) {
                auto newNode = new Node{other[i], newPrev, nullptr};
                newPrev -> next = newNode;
                newPrev = newNode;
            }
            newPrev -> next = sentinel;
            sentinel -> prev = newPrev;
        */
            clear();
            for (auto x: other) push_back(x); 
        }

        ~LinkedList() {
            clear();
            delete sentinel;
        }

        void push_back(const T &t) {           // add to the end.
            auto n = new Node {t, sentinel -> prev, sentinel};
            n -> prev -> next = n;
            sentinel -> prev = n;
            sz++;
        }


        void pop_back() {                      // remove last element.
            auto lastElem = sentinel -> prev;
            lastElem -> prev -> next = sentinel;
            sentinel -> prev = lastElem -> prev;
            sz--;
            delete lastElem;
        }

        int size() const {
            return sz;
        }

        void clear() {
            auto rover = sentinel -> next; 
            while (rover != sentinel) {
                auto temp = rover -> next;
                delete rover;
                rover = temp;
            }
            sz = 0;
            sentinel -> next = sentinel;
            sentinel -> prev = sentinel;
        }

        iterator insert(iterator position,const T &t) {    // insert this element before the given index.
            auto node = position.ptr;
            auto newNode = new Node {t, node -> prev, node};
            node -> prev -> next = newNode;
            node -> prev = newNode; 
            sz++;
            return iterator(newNode);
        }

        const T &operator[](int index) const { // get the element at index.
            auto rover = sentinel;
            for (int i = 0; i <= index; i++) rover = rover -> next;
            return rover -> data;
        }

        T &operator[](int index) {             // get the element at index.
            auto rover = sentinel;
            for (int i = 0; i <= index; i++) rover = rover -> next;
            return rover -> data;
        }

        iterator erase(iterator position) {              // remove the item at the given index.
            auto temp = position.ptr -> next;
            auto node = position.ptr;
            node -> prev -> next = node -> next;
            node -> next -> prev = node -> prev;
            sz--;
            delete node;
            return iterator(temp); 
        }

        iterator begin() {
            return iterator(sentinel -> next);
        }

        iterator end()  {
            return iterator(sentinel);
        }
 
       const_iterator begin() const  {
            return const_iterator(sentinel -> next);
        }

        const_iterator end() const  {
            return const_iterator(sentinel);
        }

        const_iterator cbegin() const  {
            return const_iterator(sentinel -> next);
        }

        const_iterator cend() const  {
            return const_iterator(sentinel);
        }

        void printList() const {
            cout<<"\n[";
            auto printMe = sentinel -> next;
            for(int i = 0; i < size(); i++) {
                cout<<printMe -> data;
                if (i < size()-1) cout<<',';
                printMe = printMe -> next;
            }   
            //delete printMe;    
            cout<<"]\nsize()= "<<size();
            cout<<"\n(sentinel -> next) -> data= "<<(sentinel -> next) -> data;
            cout<<"\n(sentinel -> prev) -> data= "<<(sentinel -> prev) -> data;
            cout<<"\n\n";
        }
};
