#include <iostream>
#include "LinkedList.h"

using namespace std;

int main () {
    LinkedList<int> ll;
    //ll.printList();
    for (int i = 1; i <= 3; i++) ll.push_back(i);
    //ll.printList();
    ll.push_back(4);

    if (ll[3] != 4) {
        ll.printList();
        cout<<"Failed push_back(), !=, or indexing.";
        cout<<"\nExpected: 4 But Got: "<<ll[3]<<'\n';
        return 0;
    }

    ll.pop_back();
    if (ll[2] != 3) {
        cout<<"Failed pop_back()";
        cout<<"\nExpected: 3 But Got: "<<ll[2]<<'\n';
        return 0;
    }
    
    if (ll.size() != 3) {
        ll.printList();
        cout<<"Failed size()";
        cout<<"\nExpected: 3 But Got: "<<ll.size()<<'\n';
        return 0;
    }

    ll.clear();
    if (ll.size() != 0) {
        ll.printList();
        cout<<"Failed clear()\n";
        cout<<"Expected: 0 But Got: "<<ll.size()<<'\n';
        return 0;
    }

    for (int i = 0; i <= 100; i++) ll.push_back(i);

    auto it = ll.begin();
    auto itc = ll.cbegin();

    if (ll[0] != *it) {
    ll.printList();
    cout<<"Failed iterator begin()\n";
    cout<<"Expected: "<<ll[0]<<" But Got: "<<ll.size()<<'\n';
    return 0;

    }

    for (int i = 0; i <= 100; i++){
        if (*it != i) {
            ll.printList();
            cout<<"Failed incrementing iterator\n";
            cout<<"Expected: "<<i<<" But Got: "<<*it<<'\n';
            return 0;
        }
        it++;
    }
    it--;

    for (int i = 100; i >= 1; i--){
        if (*it != i) {
            ll.printList();
            cout<<"Failed decrementing the iterator\n";
            cout<<"Expected: "<<i<<" But Got: "<<*it<<'\n';
            return 0;
        }
        it--;
    }

    for (int i = 0; i < 80; i++) ll.pop_back();   
    for (int i = 0; i < 10; i++) it--;

    it = ll.erase(it);

    if (*it != 13) {
        ll.printList();
        cout<<"Failed erasing an element\n";
        cout<<"Expected: 13 But Got: "<<*it<<'\n';
        return 0;
    }

    it = ll.insert(it, 12);

    if (*it != 12) {
       ll.printList();
       cout<<"Failed inserting an element\n";
       cout<<"Expected: 12 But Got: "<<*it<<'\n';
       return 0;
    }

    it = ll.erase(it);
    it = ll.erase(it);

    ll.clear();
    for (int i = 1; i <= 10; i++) ll.push_back(i);

    LinkedList<int> ll2 = ll;
    LinkedList<int> ll3 {ll};
    
    if (ll.begin() == ll2.begin()) {
        ll.printList();
        ll2.printList();
        cout<<"Failed copy test 1\n";
        return 0;
    }

    if (ll2.begin() == ll3.begin()) {
        ll.printList();
        ll2.printList();
        cout<<"Failed copy test 2\n";
        return 0;
    }

    it = ll.begin();
    it++;
    it = ll.erase(it);

    if (ll[1] == ll2[1]){
        ll.printList();
        ll2.printList();
        cout<<"Failed copy test 3\n";
        return 0;
    }

    if (ll[1] == ll3[1]) {
        ll.printList();
        ll2.printList();
        cout<<"Failed copy test 4\n";
        return 0;
    }

    cout<<"Success! Run valgrind.\n";
    return 1;
}
