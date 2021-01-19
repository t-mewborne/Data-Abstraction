#include "ArrayList.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    /*
    ArrayList<int> pushTest;
    pushTest.printArray();
    pushTest.push_back(3);
    pushTest.printArray();
    */

    ArrayList<int> al;
    //al.printArray();
    int testSize = 100;
    for (int i = 1; i <= testSize; i++) {
        al.push_back(i);  //;
        //cout<<"After pushing "<<i<<":  ";
        //al.printArray();
        //cout<<'\n';
    }
   
    if (al.size() != testSize) {
        cout<<"Failed when testing size\nShould have been: "<<testSize<<" But got: "<<al.size()<<'\n';
        al.printArray();
        return 0;
    }

    auto secToLast = al.end();
    secToLast--;
    secToLast--;

    if (al[al.size() - 2] != *secToLast) {
        cout<<"Failed when testing index\n";
        cout<<"Expected: "<<*secToLast<<" But got: "<<al[al.size() - 2]<<'\n';
        al.printArray();
        return 0;
    }

    auto iter = al.begin();

    for (int i = 1; i < 100 && iter != al.end(); i++) {
        if (*iter!=i) {
            cout<<"Failed when incrementing the iterator"<<'\n';
            cout<<"Should have been: "<<i<<"\nBut Got: "<<*iter<<'\n';
            al.printArray();
            return 0;
        }
        iter++;
    }

    for (int i = 100; i >= 1 && iter != al.begin(); i--) {
        if (*iter!=i) {
            cout<<"Failed when decrementing the iterator"<<'\n';
            cout<<"Should have been: "<<i<<"\nBut Got: "<<*iter<<'\n';
            al.printArray();
            return 0;
        }
        iter--;
    }

    auto citer = al.cbegin();
 

    for (int i = 1; i < 100 && citer != al.cend(); i++) {
        if (*citer!=i) {
            cout<<"Failed when incrementing the const iterator"<<'\n';
            cout<<"Should have been: "<<i<<"\nBut Got: "<<*citer<<'\n';
            al.printArray();
            return 0;
        }
        citer++;
    }

    for (int i = 100; i >= 1 && citer != al.cbegin(); i--) {
        if (*citer!=i) {
             cout<<"Failed when decrementing the const iterator"<<'\n';
            cout<<"Should have been: "<<i<<"\nBut Got: "<<*citer<<'\n';
            al.printArray();
            return 0;
        }
        citer--;
    }

    ArrayList<int> al1;
    al1.push_back(1);
    al1.push_back(2);
    al1.push_back(3);
    al1.push_back(4); 
    ArrayList<int> al2{al1};
    al1.pop_back();
    if(al2[al2.size()-1]!=4) {
        cout <<"Failed copy test 1." << endl;
        cout <<"Should have been: 4\nBut got: "<<al2[al2.size()-1]<<'\n';
        return 0;
    }
    
    if(al1[al1.size()-1]!=3) {
        cout << "Failed copy test 2." << endl;
        return 0;
    }   

    
    /*correct val ++ */
        
    //if (*it != n)

   
    cout<<"Everyting passed! Run valgrind.\n";
    return 1;
}
