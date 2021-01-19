/* Travis Mewborne (Pledged) 
 * November 20, 2019
 * Binary Search Tree
 */

#include <utility> //For pair (TODO maybe don't need std::?)
#include <iostream>

using namespace std;

template<typename K,typename V>
class BSTMap {
private:
    struct Node{
        std::pair<K,V> data;
        Node* right;
        Node* left;
        Node* parent;
    };

    int sz;
    Node* root = nullptr;

    static Node* successor (Node* node, Node* rt) { //Notebook page 94

        if (node == nullptr) return minNode(rt);

        //if (node == maxNode(rt)) return nullptr; //Notebook page 100

        if (node -> right != nullptr) { //If the node has a right child
            auto s = node -> right;
            while (s -> left != nullptr) s = s -> left;
            return s;
        } else { //If the node does not have a right child
            auto s = node;
            while (s -> parent != nullptr && s -> parent -> data.first < s -> data.first) s = s -> parent;
            return s -> parent;
        }
    }

    static Node* predecessor (Node* node, Node* rt) { //Notebook page 98
        if (node == nullptr) return maxNode(rt); 
        if (node -> left != nullptr) { //If the node has a left child
            auto p = node -> left;
            while (p -> right != nullptr) p = p -> right;
            return p;
        } else if (node -> parent -> right == node) { //If the node is a right child
            return node -> parent;
        } else return nullptr; //Notebook page 100; If the node is a left child with no left children
    }

    static Node* maxNode(Node* rt) { //Notebook pg 100
        Node* rover = rt;
        if (rover != nullptr) while (rover -> right != nullptr) rover = rover -> right; 
        return rover;
    }

    static Node* minNode(Node* rt) {
        Node* rover = rt;
        if (rover != nullptr) while (rover -> left != nullptr) rover = rover -> left;
        return rover;
    }

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
        // TODO: Iterator data. 
        //Need to be able to go back from end, i.e. --end() should 
        //give last element.
        //One approach is to keep a Node* and a bool that tells me if 
        //it is at end.
        //If just keeping Node* and use nullptr to indicate end(), then
        //operator-- need a case for nullptr, in which case to get the 
        //maximum element. But to get the maximum element, we need to 
        //store information about the tree, e.g. the root pointer, as member.
    private:
        Node* ptr;
        Node* rt;
    public:
        friend class const_iterator;
        iterator(Node *p,Node *r):ptr{p},rt{r} {}
        iterator():ptr(nullptr),rt(nullptr) {} //TODO change this to root?
        iterator(const iterator &iter):ptr{iter.ptr},rt{iter.rt} {}
        
        bool operator==(const iterator &i) const { 
            return ptr == i.ptr; //TODO is this comparing pointers or nodes?
        }

        bool operator!=(const iterator &i) const { 
            return !(*this==i); 
        }

        std::pair<K,V> &operator*() {
            return ptr -> data;
        }

        iterator &operator++() {
            ptr = successor(ptr,rt);
            return *this;
        }

        iterator &operator--() {
            ptr = predecessor(ptr,rt);
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        iterator operator--(int) {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };

    class const_iterator {
    private:
        Node* ptr;
        Node* rt;
    public:
        friend class BSTMap<K,V>;  // You might not need this in your code, but it helped me.
        const_iterator(Node *p,Node *r):ptr{p},rt{r} {}
        const_iterator():ptr(nullptr),rt{nullptr} {} //TODO change this to root?       
        const_iterator(const iterator &iter):ptr{iter.ptr},rt{iter.rt} {}
        const_iterator(const const_iterator &iter):ptr{iter.ptr},rt{iter.rt} {}

        bool operator==(const const_iterator &i) const { 
            return ptr == i.ptr; //TODO is this comparing pointers or nodes?
        }

        bool operator!=(const const_iterator &i) const { 
            return !(*this==i); 
        }

        const std::pair<K,V> &operator*() {
            return ptr -> data;
        }

        const_iterator &operator++() {
            ptr = successor(ptr,rt);
            return *this;
        }

        const_iterator &operator--() {
            ptr = predecessor(ptr,rt);
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        const_iterator operator--(int) {
            const_iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };



    BSTMap() {
        sz = 0;
        root = nullptr;
    }

    ~BSTMap() {
        clear();
    }

    BSTMap(const BSTMap<K,V> &other) {
        sz = other.size();
        root = buildTree(other.root);
    }

    BSTMap &operator=(const BSTMap<K,V> &other) {
        clear();
        sz = other.size();
        root = buildTree(other.root);
    }

    Node* buildTree (Node* node) {
        if (node == nullptr) return nullptr;
        auto newN = new Node;
        newN -> left = buildTree(node->left);
        if (newN -> left != nullptr) newN -> left -> parent = newN;
        newN -> right = buildTree(node->right);
        if (newN -> right != nullptr) newN -> right -> parent = newN;
        newN -> data = node -> data;
        //sz++;
        return newN;
    }

    bool empty() const { return size() == 0; }

    unsigned size() const { return sz; } //TODO ACM: should this return an unsigned int?

    iterator find(const key_type& k) {
        auto rover = root;
        while (rover != nullptr) {
            if (k == rover -> data.first) return iterator (rover,root);
            else if (k > rover -> data.first) rover = rover -> right;
            else rover = rover -> left;
        }
        return end();
    }

    const_iterator find(const key_type& k) const {
        auto rover = root;
        while (rover != nullptr) {
            if (k == rover -> data.first) return const_iterator (rover,root);
            else if (k > rover -> data.first) rover = rover -> right;
            else rover = rover -> left;
        }
        return cend();   
    }

    unsigned int count(const key_type& k) const { 
        if(find(k)!=cend()) return 1;
        else return 0;
    }

    std::pair<iterator,bool> insert(const value_type& newData) { 
        Node* curr = root;
        Node* newN = new Node;
        newN -> data = newData;
        newN -> left = nullptr;
        newN -> right = nullptr;
        newN -> parent = nullptr;
        if (curr == nullptr) {
            root = newN;
            sz++;
            return make_pair(iterator(newN,root),true);
        }
        while (true) {
            if (newData.first == curr -> data.first) { //The key already exists, insert fails
                delete newN;
                return make_pair(iterator(curr,root),false); 
            }
            else if (newData.first > curr -> data.first) {
                //go right
                if (curr->right==nullptr) { 
                    curr -> right = newN;
                    newN -> parent = curr;
                    sz++;
                    return  make_pair(iterator(newN,root),true);
                }
                else curr=curr->right;
            }
            else {
                //go left 
                 if (curr->left==nullptr) { 
                    curr -> left = newN;
                    newN -> parent = curr;
                    sz++;
                    return  make_pair(iterator(newN,root),true);
                }
                else curr=curr->left;
            }
        }
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(auto i = first; i!=last; ++i) insert(*i);
    }

    iterator erase(const_iterator position) { //Notebook page 95
        Node* current = position.ptr;
        iterator ret (current,root); //TODO
        ++ret; //Hold return value (the value after the erased value).
        bool leftChild = current -> parent != nullptr && current -> parent -> left == current;
        if (current -> left == nullptr && current->right == nullptr) { //No child case
            //Need to remove parent's pointer
            if (current -> parent == nullptr) root = nullptr;
            else if (leftChild) current -> parent -> left = nullptr;
            else current -> parent -> right = nullptr;
            delete current;
        } else if (current->left==nullptr) { //Only right
            current -> right -> parent = current -> parent;
            if (current -> parent == nullptr) root = current -> right;
            else if (leftChild) current -> parent -> left = current -> right;
            else current -> parent -> right = current -> right;
            delete current;
        } else if (current->right == nullptr) { //Only a left
            current -> left -> parent = current -> parent;
            if (current -> parent == nullptr) root = current -> left;
            else if (leftChild) current -> parent -> left = current -> left;
            else current -> parent -> right = current -> left;
            delete current;
        }
          else { //two children case
            auto s = successor(current,root);
            current->data = s->data;
            erase(const_iterator(s,root));
            return iterator(current,root);
        }
        sz--;
        return ret;
    }

    unsigned int erase(const key_type& k){
        const_iterator it = find(k);
        if (it != cend()) {
            erase(it);
            return 1;
        }
        else return 0;
    }

    void clear() {
        deleteTree(root);
        sz = 0;
        root = nullptr;
    }

    void deleteTree (Node* node) { //Recursive helper function for clear() 
        if (node == nullptr) return; //Base case
        else {
            deleteTree(node -> left);
            deleteTree(node -> right);
            delete node;
        }
    }

    mapped_type &operator[](const K &key){
        auto position = find(key);
        if (position == end()) return (*insert(make_pair(key, V())).first).second;
        return (*position).second;
    }

    bool operator==(const BSTMap<K,V>& rhs) const {
        //compare two trees
        if (size() != rhs.size()) return false;
        for (auto i = rhs.cbegin(); i != rhs.cend(); i++) {
             auto j = find((*i).first);
             //cout<<(*i).first<<"=="<<(*j).first<<" "<<(*i).second<<"=="<<(*j).second<<endl;
             if (j == end() || (*i).first != (*j).first || (*i).second != (*j).second ) return false;
        }
        return true;
    }

    bool operator!=(const BSTMap<K,V>& rhs) const { 
        return ! (*this == rhs); 
    }

    void printTree() const {
        cout<<"[";
        for (auto i = cbegin(); i != cend(); i++) {
            // bool lft = (*i)->left != nullptr;
            // bool rgt = (*i)->right != nullptr;
            printPair(*i);
            //cout<<"[L:"<<lft<<"][R:"<<rgt<<"]";
            cout<<",";
        }
        cout<<"]\nSize: "<<size()<<"      Begin: ";
        printPair(*begin());
        cout<<"      --end(): ";
        printPair(*(--end()));
        cout<<endl;
    }

    void printPair(const value_type& p) const {
        cout<<"("<<p.first<<","<<p.second<<")";
    }

    iterator begin()              { return iterator(minNode(root),root);       } //TODO
    iterator end()                { return iterator(nullptr,root);             } //TODO
    const_iterator begin()  const { return const_iterator(minNode(root),root); } //TODO
    const_iterator end()    const { return const_iterator(nullptr,root);       } //TODO
    const_iterator cbegin() const { return const_iterator(minNode(root),root); } //TODO
    const_iterator cend()   const { return const_iterator(nullptr,root);       } //TODO
};
