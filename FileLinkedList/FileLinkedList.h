/* Travis Mewborne
 * 10/29/19
 * File Based Linked List
 */

#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

template<typename T>
class FileLinkedList {
private:
    FileLinkedList(const FileLinkedList<T> &that) = delete;
    FileLinkedList<T> operator=(const FileLinkedList<T> &that) = delete;

	struct Node{
		T data;
		int prev;
		int next;
	};


	FILE* file;
	int sz;
    // TODO - Private helper functions. (Maybe file IO with an index.)


    void saveSize() {
        fseek(file,sizeof(Node),SEEK_SET);
        fwrite(&sz,sizeof(int),1,file);
    }

    void readSize() {
        fseek(file,sizeof(Node),SEEK_SET);
        fread(&sz,sizeof(int),1,file);
    }

    static int readPrev(int node, FILE* file){
        fseek(file,node+sizeof(T),SEEK_SET);
		int ret;
		fread(&ret, sizeof(int), 1, file);
		return ret;
	}
	
    static void  writePrev(int node, int value, FILE* file){
        fseek(file,node+sizeof(T),SEEK_SET);
        fwrite(&value,sizeof(T),1,file);
	}

    static int readNext(int node, FILE* file) {
        fseek(file,node+sizeof(T)+sizeof(int),SEEK_SET);
        int ret;
        fread(&ret,sizeof(int),1,file);
        return ret;
    }

    static void writeNext(int node, int value, FILE* file) {
        fseek(file,node+sizeof(T)+sizeof(int),SEEK_SET);
        fwrite(&value,sizeof(int),1,file);
    }
	
    static void writeData (int node, const T& t, FILE* file) {
        fseek(file,node,SEEK_SET); 
        fwrite(&t,sizeof(T),1,file);
    }

    static T readData(int node, FILE* file){
	    fseek(file,node,SEEK_SET);
        T ret;
        fread(&ret,sizeof(T),1,file);
        return ret;
    }

public:
    typedef T value_type;

    class const_iterator {
        private:        // TODO - Your private data.
            FILE* file;
            int ptr;
        public:
            const_iterator(int i,FILE *f) {
                ptr = i;
                file = f;
            }

            const_iterator(const const_iterator &i) {
                ptr = i.ptr;
                file = i.file;
            }
            
            T operator*(){
                return readData(ptr, file);
            }

            bool operator==(const const_iterator &i) const {
                return (ptr == i.ptr && file == i.file);
            }
            
            bool operator!=(const const_iterator &i) const {
                return !(*this==i);
            }
            
            const_iterator &operator=(const const_iterator &i) {
                file = i.file;
                ptr = i.ptr;
                return *this;
            }
            
            const_iterator &operator++(){
                ptr=readNext(ptr, file);
                return *this;
            }

            const_iterator &operator--() {
                ptr=readPrev(ptr,file);
                return *this;
            }
            
            const_iterator operator++(int) {
                auto ret = *this;
                ptr=readNext(ptr, file);
                return ret;
            }
            
            const_iterator operator--(int) {
                auto ret = *this;
                ptr=readPrev(ptr,file);
                return ret;
            }

            friend class FileLinkedList;
    };

    // General Methods
    FileLinkedList(const std::string &fname){
        file = fopen(fname.c_str(), "r+");
        if(file==nullptr){
            file=fopen(fname.c_str(),"w+");

            //create sentinel
            writePrev(0, 0, file);
            writeNext(0, 0, file);
            sz=0;
            fseek(file, sizeof(Node), SEEK_SET);
            fwrite(&sz, sizeof(int), 1, file);
            int freelist=-1;
            fwrite(&freelist, sizeof(int), 1, file);


        }else{

        }

    }

    template<typename I>  // The type I will be an iterator.
    FileLinkedList(I begin,I end,const std::string &fname) {
        file = fopen(fname.c_str(),"w+");
        sz = 0;
        for (auto i = begin; i != end; i++) {push_back(*i);} 
    }

    ~FileLinkedList() {
        saveSize();
        fclose(file);
    }

    void push_back(const T &t) { 
        insert(end(),t); 
        sz++;
    }
    
    void pop_back() { 
        erase(--end()); 
        sz--;
    }

    int size() const {sz;}

    void clear() {
        cout<<"Array before clear: ";
        printArray();
        while (size()>0) {
            pop_back(); 
            sz--;
        }
        cout<<"Array after clear: ";
        printArray(); 

    }

    const_iterator insert(const_iterator position, const T &t){
        int node=position.ptr;
        //newnode= new Node{t, node->prev, node}
        fseek(file, sizeof(Node)+sizeof(int), SEEK_SET);
        int freelist;
        fread(&freelist,sizeof(int),1,file); //read the current free list
        int newnode;
        if(freelist==-1){
            newnode = sizeof(Node) * (sz+1) + 2 * sizeof(int);
        }
        else{
            newnode=freelist;
            freelist= readNext(newnode,file);
            fseek(file, sizeof(Node)+sizeof(int), SEEK_SET);
            fwrite(&freelist,sizeof(int),1,file); //Save freelist to the file
        }		

        writeData(newnode,t, file);
        writePrev(newnode, readPrev(node,file), file);
        writeNext(newnode, node,file);
        //TODO rest of insert

        sz++;
    }
    T operator[](int index) const{
        auto itr=begin();
        for (int i=0;i<index;++i) ++itr;
        return *itr;
    }

    const_iterator erase(const_iterator position) {
        int index = position.ptr;
        
        //prev -> next = pos -> next
        int prevNext = readNext(readPrev(index,file),file); //address of previous' next
        int pstnNext = readNext(index,file); //address of position's next
        writeNext(prevNext,pstnNext,file); //write previous' next to position's next
        
        //next -> prev = pos -> prev
        int nextPrev = readPrev(readNext(index,file),file); //index of next's previous
        int pstnPrev = readPrev(index,file); //index of position's previous
        writePrev(nextPrev,pstnPrev,file); //write next's previous to position's previous

        //Reassign freelist
        fseek(file, sizeof(Node)+sizeof(int), SEEK_SET);
        int freelist;
        fread(&freelist,sizeof(int),1,file); //read the current free list
        writeNext(index,freelist,file);
        freelist = index;

        fseek(file, sizeof(Node)+sizeof(int), SEEK_SET);
        fwrite(&freelist,sizeof(int),1,file); //Save freelist to the file
        //TODO
    }
    
    void set(const T &value,int index) {
        fseek(file,sizeof(Node)+index,SEEK_SET);
        fwrite(&value,sizeof(T),1,file);
        //TODO
    }
    
    void set(const T &value,const_iterator position){
        int index = position.ptr;
        fseek(file,sizeof(Node)+index,SEEK_SET);
        fwrite(&value,sizeof(T),1,file);
        //TODO
    }

    const_iterator begin(){
        return const_iterator(0,file);
    }
    
    const_iterator begin() const {
         return const_iterator(0,file);
    }
     
    const_iterator cbegin() const {
         return const_iterator(0,file);
    }
 
    const_iterator end() {
         return const_iterator(sz,file);
    }
    
    const_iterator end() const {
         return const_iterator(sz,file);
    }
      const_iterator cend() const {
         return const_iterator(sz,file);
    }

    void printArray() {
        cout<<"[";
        for(auto i = begin(); i != end(); i++) {
            auto tmp = *i;
            cout<<(tmp)<<",";
        }
        cout<<"]\n"; 
        cout<<"Current size: "<<sz<<'\n';
    }
};
