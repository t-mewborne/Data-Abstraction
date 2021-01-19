#include "FileArrayList.h"
#include <iostream>

using namespace std;

int main () {
    FileArrayList<int> al1("al1.bin");
    al1.clear();

    if (al1.size() != 0) {
        cout <<"Failed clear() or size()\n";
        al1.printArray();
        return 0;
    }

    //al1.printArray();

    for (int i = 1; i <= 100; i++) al1.push_back(i);

    //al1.printArray();

    for (int i = 0; i < 100; i++) {
        if (al1[i] != i+1) {
            cout <<"\n\nFailed push_back or []\n";
            cout <<"Expected: "<<(i+1)<<" But got: "<<al1[i]<<'\n';
            al1.printArray();
            return 0;
        }
    }

    if (*al1.begin() != 1) {
        cout <<"begin() failed\n";
        return 0;
    }

    if (*(--al1.end()) != 100) {
        cout <<"end() failed\n";
        return 0;
    }

    al1.set(5000, 1);

    if (*(++al1.begin()) != 5000) {
        cout<<"Failed set";
        al1.printArray();
        return 0;
    }

    auto insertLoc = ++++al1.begin();
    al1.insert(insertLoc, 3000);

    if (*(insertLoc) != 3000 || al1.size() != 101) {
        cout<<"Failed insert\n";
        al1.printArray();
        return 0;
    }

    al1.clear();
    al1.set(1,0);

    cout<<"Success!\n";
    return 1;
}
