/* Travis Mewborne
 * 10/23/19 (ext. 10/25/19)
 * File Based Array List
 */

#include <cstdio>
#include <string>
//#include <cassert> 
#include <iostream>

using namespace std;

template<typename T>
class FileArrayList {
    private:
        FileArrayList(const FileArrayList<T> &that) = delete;
        FileArrayList<T> operator=(const FileArrayList<T> &that) = delete;

        FILE* file;
        int sz;
        
        void saveSize(){ //Record the current size to the file
            fseek(file, 0, SEEK_SET);
            fwrite(&sz, sizeof(int), 1, file);
        }
        
        void readSize(){ //Read the size value from the file
             fseek(file, 0, SEEK_SET);
             fread(&sz,sizeof(int),1,file);
        }
        
        void writeData(int index, const T& t){ //Write data to a file at a given index
            fseek(file, sizeof(int)+sizeof(T)*index, SEEK_SET);
            fwrite(&t, sizeof(T), 1, file);
        }

        T readData(int index) const { //Read data from a file at a given index
            T t; //new value
            fseek(file,sizeof(int)+sizeof(T)*index,SEEK_SET);
            fread(&t,sizeof(T),1,file);
            return t;
        }

    public:
        typedef T value_type;

        class const_iterator {
            private:
                FILE* file;
                int index;
            public:
                const_iterator(int i,FILE *f){ //Constructor
                    index = i;
                    file = f;
                }
                
                const_iterator(const const_iterator &i) { //Copy constructor
                    index = i.index;
                    file = i.file;
                }

                T operator*(){
                    T ret;
                    fseek(file,sizeof(int)+ index*sizeof(T), SEEK_SET);
                    fread(&ret, sizeof(T),1,file);
                    return ret;
                }
                
                bool operator==(const const_iterator &i) const{
                    return (index==i.index && file==i.file);
                }

                bool operator!=(const const_iterator &i) const{
                    return !(*this==i);
                }
                
                const_iterator &operator=(const const_iterator &i){
                    index=i.index;
                    file=i.file;
                }
                const_iterator &operator++() {
                    index++;
                    return *this;
                }
                
                const_iterator &operator--(){
                    index--;
                    return *this;
                }
                
                const_iterator operator++(int) {
                    auto ret = *this;
                    index++;
                    return ret;
                }
                
                const_iterator operator--(int) {
                    auto ret = *this;
                    index--;
                    return ret;
                }

                friend class FileArrayList;
        };

        // General Methods
        FileArrayList(const std::string &fname){
            file = fopen(fname.c_str(), "r+");
            if(file==nullptr){
                file=fopen(fname.c_str(),"w+");
                sz=0;
                saveSize();
            } else{
                readSize();
            }
        }

        template<typename I>  // The type I will be an iterator.
        FileArrayList(I begin,I end,const std::string &fname) { 
            file = fopen(fname.c_str(), "w+");
            sz = 0;
            while (begin != end) {
                push_back(*begin);
                begin++;
            }
        }

        ~FileArrayList(){ //Don't need to delete anything
            saveSize();   //Write the size
            fclose(file); //Close the file
        }
        void push_back(const T &t){
            writeData(sz, t);
            sz++;
        }

        void pop_back() {sz--;}
        
        int size() const {return sz;}
        
        void clear() {sz=0;}//reset size to zero, don't need to delete anything

        const_iterator insert(const_iterator position, const T &t){
            auto rover = cend();
            while (rover != position) {
                int tmp = rover.index;
                rover--;
                writeData(tmp,*rover);
            }
            writeData(rover.index,t);
            sz++;
            return rover;
        }

        T operator[](int index) const {
            return readData(index);
        }

        const_iterator erase(const_iterator position) {
           for (auto i = (++position); i.index < sz; i++) { 
              writeData(i.index - 1, *i);
           }
           sz--;
           return position;
        }

        void set(const T &value,int index) {
             if (index > sz || index < 0) {
                cout << "Cannot set value at requested index: Index too large or too small\n";
                cout << "Requirements: 0 <= index ("<<index<<") < size ("<<sz<<")\n";
             }
             else writeData(index,value);
        }
        
        const_iterator begin() {
            return const_iterator(0, file);
        }
        const_iterator begin() const {
            return const_iterator(0, file);
        }
        const_iterator end() {
            return const_iterator(sz, file);
        }
        const_iterator end() const {
            return const_iterator(sz, file);
        }
        const_iterator cbegin() const {
            return const_iterator(0, file);
        }
        const_iterator cend() const {
            return const_iterator(sz, file);
        }

        void printArray() {
            cout<<"[";
            for(int i = 0; i < sz; i++) cout<<readData(i)<<",";
            cout<<"]\n";
            cout<<"Written size: "<<readData(-1)<<'\n';
            cout<<"Current size: "<<sz<<'\n';
        }
    
    };

