/* Travis Mewborne (Pledged)
 * HashMap Assignment (Dr. Albert Xin Jiang)
 * Due 11/11/19
 *
 * Compiler error- make sure g++ is up to date! (should be v4.9+)
 * to get the current version: "g++ -v"
 * to update: "module load gcc-latest"
 * then use "g++ -v" to make sure it has been updated
 */


#include <vector>
#include <utility>

using namespace std;

template<typename K,typename V,typename Hash>
class HashMap {
    Hash hashFunction; 
    int sz; 
    vector<vector<pair<K,V>>> table;

    public:
        typedef K key_type;
        typedef V mapped_type;
        typedef std::pair<K,V> value_type;

        class const_iterator;

        class iterator {
            // AJ NOTE: These might be different depending on how you store your table.
            private:
                typename std::remove_reference<decltype(table.begin())>::type mainIter;
                typename std::remove_reference<decltype(table.begin())>::type mainEnd;
                typename std::remove_reference<decltype(table[0].begin())>::type subIter; 
            public:
                friend class const_iterator;
                friend class HashMap;

                // AJ NOTE: These might be different depending on how you store your table.
                iterator(const decltype(mainIter) mi,const decltype(mainEnd) me):mainIter(mi),mainEnd(me) {
                    if(mainIter!=mainEnd) subIter = mainIter->begin();
                    while(mainIter!=mainEnd && subIter == mainIter->end()) {
                        ++mainIter;
                        if(mainIter!=mainEnd) subIter = mainIter->begin();
                    }
                }

                // AJ NOTE: These might be different depending on how you store your table.
                iterator(const decltype(mainIter) mi, 
                         const decltype(mainEnd) me, 
                         const decltype(subIter) si):
                    mainIter(mi),mainEnd(me),subIter(si) {}

                bool operator==(const iterator &i) const {
                    return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); 
                }

                bool operator!=(const iterator &i) const {
                    return !(*this==i); 
                }
                
                std::pair<K,V> &operator*() {
                    return *subIter; 
                }
                
                iterator &operator++() {
                    ++subIter;
                    while(mainIter!=mainEnd && subIter==mainIter->end()) {
                        ++mainIter;
                        if(mainIter!=mainEnd) subIter = mainIter->begin();
                    }
                    return *this;
                }

                iterator operator++(int) {
                    iterator tmp(*this);
                    ++(*this);
                    return tmp;
                }
        };

        class const_iterator {
            // AJ NOTE: These might be different depending on how you store your table.
            private:
                typename std::remove_reference<decltype(table.cbegin())>::type mainIter;
                typename std::remove_reference<decltype(table.cbegin())>::type mainEnd;
                typename std::remove_reference<decltype(table[0].cbegin())>::type subIter; 
            public:
                friend class HashMap;
                // AJ NOTE: These might be different depending on how you store your table.
                const_iterator(const decltype(table.cbegin()) mi,const decltype(table.cbegin()) me):mainIter(mi),mainEnd(me) {
                    if(mainIter!=mainEnd) subIter = mainIter->begin();
                    while(mainIter!=mainEnd && subIter == mainIter->end()) {
                        ++mainIter;
                        if(mainIter!=mainEnd) subIter = mainIter->begin();
                    }
                }
                // AJ NOTE: These might be different depending on how you store your table.
                const_iterator(const decltype(table.cbegin()) mi, 
                        const decltype(table.cbegin()) me,
                        const decltype(table[0].cbegin()) si):
                    mainIter(mi),mainEnd(me),subIter(si) {}

                const_iterator(const decltype(table.begin()) mi,
                        const decltype(table.begin()) me,
                        const decltype(table[0].begin()) si):
                    mainIter(mi),mainEnd(me),subIter(si) {}

                // AJ NOTE: These might be different depending on how you store your table.
                const_iterator(const iterator &i):mainIter(i.mainIter),mainEnd(i.mainEnd),subIter(i.subIter) {}

                bool operator==(const const_iterator &i) const {
                    return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); 
                }
                
                bool operator!=(const const_iterator &i) const {
                    return !(*this==i); 
                }
                
                const std::pair<K,V> &operator*() const {
                    return *subIter; 
                }
                
                const_iterator &operator++() {
                    ++subIter;
                    while(mainIter!=mainEnd && subIter==mainIter->end()) {
                        ++mainIter;
                        if(mainIter!=mainEnd) subIter = mainIter->begin();
                    }
                    return *this;
                }
                
                const_iterator operator++(int) { 
                    const_iterator tmp(*this);
                    ++(*this);
                    return tmp;
                }
        };

        HashMap(const Hash &hf) { //can also use ":table(n)" before "{" instead of "table.resize(n);"
            hashFunction = hf;
            table.resize(1000000); //TODO Change this if "growTableAndRehash" is implemented
            sz = 0;
        }

        bool empty() const { //This function should return whether or not the container is empty
            return sz == 0;
        }

        unsigned int size() const { //This function should return the current size of the container
            return sz;
        }

        iterator find(const key_type& k){ //This function should return an iterator position of the location of a given key 
            int index = hashFunction(k) % table.size();
            auto main = table.begin() + index;
            for (auto i = table[index].begin(); i != table[index].end(); i++) {
                if ((*i).first == k) return iterator(main,table.end(),i);
            }
            //If the key is not found, return end()
            return end();
        }

        const_iterator find(const key_type& k) const {
            int index = hashFunction(k) % table.size();
            auto main = table.begin() + index;
            for (auto i = table[index].begin(); i != table[index].end(); i++) {
                if ((*i).first == k) return const_iterator(main,table.end(),i);
            }
            return end();
        }

        int count(const key_type& k) const {
            //http://www.cplusplus.com/reference/unordered_map/unordered_map/count/
            //return 1 if a key equivalent to k is found, otherwise 0
            int index = hashFunction(k) % table.size();
            int x = 0;
            for (auto i = table[index].begin(); i != table[index].end(); i++) {
                if ((*i).first == k) x++;
            }
            return x;
        }

        std::pair<iterator,bool> insert(const value_type& val) {
            int index=hashFunction(val.first)%table.size();
            for (auto it=table[index].begin();it!=table[index].end();++it) {
                if (val.first == (*it).first) {
                    return make_pair(iterator(table.begin()+index,
                                              table.end(),
                                              it),                false);
                }
            }
            table[index].push_back(val);
            sz++;
            return make_pair(iterator(table.begin() + index, 
                                      table.end(), 
                                      (--(*(table.begin() + index)).end())) , true); //When the value is not found
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last) {
            for (auto i = first; i != last; i++) insert(*i);
        }

        iterator erase(const_iterator position) { 
            auto i = find((*position).first);
            auto ret = i;
            ret++;
            i.mainIter -> erase(i.subIter);
            sz--;
            return ret;
        }

        int erase(const key_type& k) {
            int x = count(k);
            if (x == 1) erase(find(k));
            return x; 
        }

        void clear() {
            for(auto& x:table) x.clear();
            sz = 0;
        }

        mapped_type &operator[](const K &k){
            //Read & Write Access
            //User should be able to redefine value at index of given key (hm["hello"] = 3)
            auto position = find(k);
            if (position == end()) return (*insert(make_pair(k,V())).first).second; //write access
            return (*position).second;
        }

        bool operator==(const HashMap<K,V,Hash>& rhs) const { //returns true if the hashmaps have the same value pairs
            if (size() != rhs.size()) return false;
            for (auto i = rhs.begin(); i != rhs.end(); i++) {
                auto j = find((*i).first);
                if (j == end() || *j != *i) return false;
            }
            return true;
        }

        bool operator!=(const HashMap<K,V,Hash>& rhs) const {return !(*this==rhs);}

        // AJ NOTE: These might be different depending on how you store your table
        iterator begin()              {return iterator(table.begin(),table.end());      }
        iterator end()                {return iterator(table.end(),table.end());        }
        const_iterator begin()  const {return const_iterator(table.begin(),table.end());}
        const_iterator end()    const {return const_iterator(table.end(),table.end());  }
        const_iterator cbegin() const {return const_iterator(table.begin(),table.end());}
        const_iterator cend()   const {return const_iterator(table.end(),table.end());  }

    private:
        void growTableAndRehash(){
            //TODO Optional
        }
};
