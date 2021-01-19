#include <unordered_map>
#include <functional>
#include <iostream>
#include "HashMap.h"

using namespace std;

int hashInt (int x) {
    return x;
}

int main () {
    std::unordered_map<string,int> map1;
    std::unordered_map<int, double,std::function<int(int)> > map2(20, hashInt);
    HashMap<int,double,std::function<int(int)>> map3(hashInt);

    auto hf = [](int x){return x;};
    HashMap<int,double,decltype(hf)> map4(hf);

    map2[3] = 5.5;
    map2.insert(make_pair(4,1.0));
    map2.insert(make_pair(3,1.0)); //This should fail, key 3 already exists
    map2[3] = 4.5; //This should succeed

    cout<<map2[3]<<endl;
}
