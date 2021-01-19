#include "ArrayStack.h"
#include "ArrayQueue.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    ArrayStack<int> x;
    
    //Test 1
    x.printArray();
    if (x.isEmpty()) cout<<"Test 1 Passed (array is empty)"<<'\n'<<'\n';
    else {
        cout<<"Test 1 Failed (array is empty)"<<'\n'<<'\n';
        return 0;
    }
    //cout<<"Peek should crash: "<<x.peek()<<'\n'; //crash test

    //Test 2
    x.push(1);
    x.printArray();
    if (x.peek() == 1) cout<<"Test 2 Passed (push & peek 1)"<<'\n'<<'\n';
    else {
        cout<<"Test 2 Failed (push & peek 1)"<<'\n'<<'\n';
        return 0;
    }
    x.push(4);
    x.push(8);
    x.push(3);
    x.printArray();
    cout<<"Push 4, 8, 3"<<'\n'<<'\n';

    //Test 3
    int y = x.pop();
    x.printArray();
    if (y == 3) cout<<"Test 3 Passed (pop 3)"<<'\n'<<'\n';
    else {
        cout<<"Test 3 Failed (pop 3)"<<'\n'<<'\n';
        return 0;
    }
    for(int i = 9; i < 15; i++) x.push(i);
    while (!x.isEmpty()) {
        x.pop();
        x.printArray();
    }

    cout<<'\n';

    for(int i = 30; i < 37; i++) {
        x.push(i);
        x.printArray();
        cout<<"Peek: "<<x.peek()<<'\n';

    }

    cout<<'\n';

    ArrayStack<char> z;

    //Test 4
    z.printArray();
    if (z.isEmpty()) cout<<"Test 4 Passed (array is empty)"<<'\n'<<'\n';
    else {
        cout<<"Test 4 Failed (array is empty)"<<'\n'<<'\n';
        return 0;
    }
    //Test 5
    z.push('a');
    z.printArray();
    if (z.peek() == 'a') cout<<"Test 5 Passed (push & peek a)"<<'\n'<<'\n';
    else {
        cout<<"Test 5 Failed (push & peek a)"<<'\n'<<'\n';
        return 0;
    }
    z.push('y');
    z.push('r');
    z.push('w');
    z.printArray();
    cout<<"Push y, r, w"<<'\n'<<'\n';

    //Test 6
    char charPop = z.pop();
    z.printArray();
    if (charPop == 'w') cout<<"Test 6 Passed (pop w)"<<'\n'<<'\n';
    else {
        cout<<"Test 6 Failed (pop w)"<<'\n'<<'\n';
        return 0;
    }
    for (int i = 10; i < 30; i++) {
        x.push(i);
    }

    ArrayStack<string> strArr;

    strArr.push("Hello");
    strArr.printArray();
    strArr.push("Coffee");
    strArr.printArray();
    strArr.push("Hi");
    strArr.printArray();
    strArr.push("Travis");
    strArr.printArray();
    strArr.push("Backpack");
    strArr.printArray();
    strArr.push("Test");
    strArr.printArray();
    strArr.push("ab");
    strArr.printArray();
    strArr.push("gkfdlgjfdsjgkfl;sdjgkfld;vkf;ld");
    strArr.printArray();
    strArr.push("Hello");
    strArr.printArray();
    strArr.push("Phone");
    strArr.printArray();
    strArr.push("Computer Science");
    strArr.printArray();
    cout<<'\n';
    
    x.printArray();
    cout<<"Test 7 (test grow code)"<<'\n';

    //for (int i = 2; i < 1000; i++) x.push(i);
    //x.printArray();

    cout<<"--------------------------------------------------------------"<<'\n'<<'\n';

    ArrayQueue<int> arrQ;
    arrQ.printArray();
    if (arrQ.isEmpty()) cout<<"Test 8 Passed (queue is empty)"<<'\n'<<'\n';
    else {
        cout<<"Test 8 Failed (queue is empty)"<<'\n'<<'\n';
        return 0;
    }

    arrQ.enqueue(3);
    arrQ.enqueue(4);
    arrQ.printArray();
    cout<<"Peek: "<<arrQ.peek()<<'\n';
    if (arrQ.peek() == 3) cout<<"Test 9 Passed (enqueue and peek)"<<'\n'<<'\n';
    else {
        cout<<"Test 9 Failed (enqueue and peek)"<<'\n'<<'\n';
        return 0;
    }

    for (int i = 0; i < 10; i++) arrQ.enqueue(i);
    arrQ.printArray();
    cout<<"Test 10 (grow code)"<<'\n'<<'\n';

    int tstDQ = arrQ.dequeue();
    arrQ.printArray();
    cout<<"Dequeue: "<<tstDQ<<'\n';
    if (tstDQ == 3) cout<<"Test 11 Passed (dequeue)"<<'\n'<<'\n';
    else {
        cout<<"Test 11 Failed (dequeue)"<<'\n'<<'\n';
        return 0;
    }
    for (int i = 0; i < 3; i++) tstDQ = arrQ.dequeue();
    arrQ.printArray();
    cout<<"Dequeue: "<<tstDQ<<'\n';


    ArrayQueue<char> arrQC;
    arrQC.printArray();
    if (arrQC.isEmpty()) cout<<"Test 12 Passed (queue is empty)"<<'\n'<<'\n';
    else {
        cout<<"Test 12 Failed (queue is empty)"<<'\n'<<'\n';
        return 0;
    }

    arrQC.enqueue('a');
    arrQC.enqueue('b');
    arrQC.printArray();
    cout<<"Peek: "<<arrQC.peek()<<'\n';
    if (arrQC.peek() == 'a') cout<<"Test 13 Passed (enqueue and peek)"<<'\n'<<'\n';
    else {
        cout<<"Test 13 Failed (enqueue and peek)"<<'\n'<<'\n';
        return 0;
    }

    arrQC.enqueue('a');
    arrQC.enqueue('b');
    arrQC.enqueue('c');
    arrQC.enqueue('d');
    arrQC.enqueue('e');
    arrQC.enqueue('f');
    arrQC.enqueue('g');
    arrQC.enqueue('h');
    arrQC.enqueue('i');
    arrQC.enqueue('j');

    arrQC.printArray();
    cout<<"Test 14 (grow code)"<<'\n'<<'\n';

    char tstDQC = arrQC.dequeue();
    arrQC.printArray();
    cout<<"Dequeue: "<<tstDQC<<'\n';
    if (tstDQC == 'a') cout<<"Test 15 Passed (dequeue)"<<'\n'<<'\n';
    else {
        cout<<"Test 15 Failed (dequeue)"<<'\n'<<'\n';
        return 0;
    }

    for (int i = 0; i < 3; i++) tstDQC = arrQC.dequeue();
    arrQC.printArray();
    cout<<"Dequeue: "<<tstDQC<<'\n'<<'\n';
    
    while (!arrQC.isEmpty()) {
        tstDQC = arrQC.dequeue();
        arrQC.printArray();
    }

    //Copy tests:
    
    ArrayStack<int> as1;
    as1.push(1);
    as1.push(2);
    as1.push(3);
    as1.push(4);
    ArrayStack<int> as2{as1};
    if(as2.pop()!=4) {
        cout << "Failed copy test 1." << endl;
        return 2;
    }
    as2.push(99);
    if(as1.pop()!=4) {
        cout << "Failed copy test 2." << endl;
        return 2;
    }

    ArrayQueue<int> aq1;
    aq1.enqueue(1);
    aq1.enqueue(2);
    aq1.enqueue(3);
    aq1.enqueue(4);
    ArrayQueue<int> aq2{aq1};
    if(aq2.dequeue()!=1) {
        cout << "Failed copy test 3." << endl;
        return 2;
    }
    if(aq1.dequeue()!=1) {
        cout << "Failed copy test 4." << endl;
        return 2;
    }



    cout<<'\n'<<"Run 'valgrind ./a.out' to check for leaks!"<<'\n';
    
    //Crash cases:
    //for (int i = 0; i<100; i++) arrQ.dequeue();
    //arrQC.dequeue();
    //arrQC.peek();
    return 0;
}
