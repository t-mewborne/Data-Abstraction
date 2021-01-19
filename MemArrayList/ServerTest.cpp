#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include "ArrayList.h"

using std::ofstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::rand;

// TODO put in a bigger test for a longer total runtime. 1.7 secs is not enough.
/*
void fillRandomIntStack(int numElems,ArrayStack<int> &s,vector<int> &v) {
	for(int i=0; i<numElems; ++i) {
		v.push_back(rand());
		s.push(v.back());
	}
}

void fillRandomStringStack(int numElems,ArrayStack<string> &s,vector<string> &v) {
	for(int i=0; i<numElems; ++i) {
		string str(1+rand()%10,32+rand()%70);
		v.push_back(str);
		s.push(v.back());
	}
}
*/

template<typename T>
bool passByValue(T lst) {
	auto tmp = lst.size();
	lst.push_back(5);
	return lst.size()==tmp+1 && lst[tmp]==5;
}

ArrayList<int> returnLittleAL() {
	ArrayList<int> ret;
	ret.push_back(1);
	ret.push_back(2);
	ret.push_back(3);
	return ret;
}

ArrayList<int> add3AndReturn(ArrayList<int> al) {
	al.push_back(9);
	al.push_back(8);
	al.push_back(7);
	return al;
}

template<typename T>
bool simpleTest(T &lst1) {
	lst1.push_back(5);
	lst1.push_back(6);
	lst1.push_back(7);
	lst1.push_back(8);
	lst1.push_back(9);
	if(lst1[0]!=5) { cout << "[0] error." << endl; return false; }
	if(lst1[1]!=6) { cout << "[1] error." << endl; return false; }
	if(lst1[2]!=7) { cout << "[2] error." << endl; return false; }
	if(lst1[3]!=8) { cout << "[3] error." << endl; return false; }
	if(lst1[4]!=9) { cout << "[4] error." << endl; return false; }

	int cnt = 5;
	for(auto iter = lst1.begin(); iter!=lst1.end(); ++iter) {
		if(*iter!=cnt) {
			cout << "iter error " << cnt << endl;
			return false;
		}
		--(*iter);
		++cnt;
	}
	cnt = 4;
	for(auto iter = lst1.cbegin(); iter!=lst1.cend(); ++iter) {
		if(*iter!=cnt) {
			cout << "const_iter error " << cnt << endl;
			return false;
		}
		++cnt;
	}
	cnt = 8;
	for(auto iter = --lst1.end(); iter!=lst1.begin(); --iter) {
		if(*iter!=cnt) {
			cout << "--iter error " << cnt << endl;
			cout<<"Expected: "<<cnt<<" But got: "<<*iter<<'\n';
            lst1.printArray();
            return false;
		}
		--cnt;
	}
	lst1[2] = 99;
	if(lst1[2]!=99) {
		cout << "[] error." << endl;
		return false;
	}
	T lst2(lst1);
	lst1.remove(2);
	if(lst1[0]!=4) { cout << "After remove lst1[0]." << endl; return false; }
	if(lst1[1]!=5) { cout << "After remove lst1[1]." << endl; return false; }
	if(lst1[2]!=7) { cout << "After remove lst1[2]." << endl; return false; }
	if(lst1[3]!=8) { cout << "After remove lst1[3]." << endl; return false; }
	if(lst2[0]!=4) { cout << "After remove lst2[0]." << endl; return false; }
	if(lst2[1]!=5) { cout << "After remove lst2[1]." << endl; return false; }
	if(lst2[2]!=99) { cout << "After remove lst2[2]." << endl; return false; }
	if(lst2[3]!=7) { cout << "After remove lst2[3]." << endl; return false; }
	if(lst2[4]!=8) { cout << "After remove lst2[4]." << endl; return false; }
	lst2.insert(98,3);
	if(lst2[0]!=4) { cout << "After insert lst2[0]." << endl; return false; }
	if(lst2[1]!=5) { cout << "After insert lst2[1]." << endl; return false; }
	if(lst2[2]!=99) { cout << "After insert lst2[2]." << endl; return false; }
	if(lst2[3]!=98) { cout << "After insert lst2[3]." << endl; return false; }
	if(lst2[4]!=7) { cout << "After insert lst2[4]." << endl; return false; }
	if(lst2[5]!=8) { cout << "After insert lst2[5]." << endl; return false; }
	lst2.pop_back();
	if(lst2.size()!=5) { cout << "bad size after pop_back." << endl; return false; }
	lst2.pop_back();
	if(lst2.size()!=4) { cout << "bad size after pop_back." << endl; return false; }
	lst2.pop_back();
	if(lst2.size()!=3) { cout << "bad size after pop_back." << endl; return false; }
	if(lst2[0]!=4) { cout << "After pop_back lst2[0]." << endl; return false; }
	if(lst2[1]!=5) { cout << "After pop_back lst2[1]." << endl; return false; }
	if(lst2[2]!=99) { cout << "After pop_back lst2[2]." << endl; return false; }
	return true;
}

template<typename T>
bool stringTest(T &lst1) {
	lst1.push_back("5");
	lst1.push_back("6");
	lst1.push_back("7");
	lst1.push_back("8");
	lst1.push_back("9");
	if(lst1[0]!="5") { cout << "[0] error." << endl; return false; }
	if(lst1[1]!="6") { cout << "[1] error." << endl; return false; }
	if(lst1[2]!="7") { cout << "[2] error." << endl; return false; }
	if(lst1[3]!="8") { cout << "[3] error." << endl; return false; }
	if(lst1[4]!="9") { cout << "[4] error." << endl; return false; }

	lst1[2] = "99";
	if(lst1[2]!="99") {
		cout << "[] error." << endl;
		return false;
	}
	T lst2(lst1);
	lst1.remove(2);
	if(lst1[0]!="5") { cout << "After remove lst1[0]." << endl; return false; }
	if(lst1[1]!="6") { cout << "After remove lst1[1]." << endl; return false; }
	if(lst1[2]!="8") { cout << "After remove lst1[2]." << endl; return false; }
	if(lst1[3]!="9") { cout << "After remove lst1[3]." << endl; return false; }
	if(lst2[0]!="5") { cout << "After remove lst2[0]." << endl; return false; }
	if(lst2[1]!="6") { cout << "After remove lst2[1]." << endl; return false; }
	if(lst2[2]!="99") { cout << "After remove lst2[2]." << endl; return false; }
	if(lst2[3]!="8") { cout << "After remove lst2[3]." << endl; return false; }
	if(lst2[4]!="9") { cout << "After remove lst2[4]." << endl; return false; }
	lst2.insert("98",3);
	if(lst2[0]!="5") { cout << "After insert lst2[0]." << endl; return false; }
	if(lst2[1]!="6") { cout << "After insert lst2[1]." << endl; return false; }
	if(lst2[2]!="99") { cout << "After insert lst2[2]." << endl; return false; }
	if(lst2[3]!="98") { cout << "After insert lst2[3]." << endl; return false; }
	if(lst2[4]!="8") { cout << "After insert lst2[4]." << endl; return false; }
	if(lst2[5]!="9") { cout << "After insert lst2[5]." << endl; return false; }
	lst2.pop_back();
	if(lst2.size()!=5) { cout << "bad size after pop_back." << endl; return false; }
	lst2.pop_back();
	if(lst2.size()!=4) { cout << "bad size after pop_back." << endl; return false; }
	lst2.pop_back();
	if(lst2.size()!=3) { cout << "bad size after pop_back." << endl; return false; }
	if(lst2[0]!="5") { cout << "After pop_back lst2[0]." << endl; return false; }
	if(lst2[1]!="6") { cout << "After pop_back lst2[1]." << endl; return false; }
	if(lst2[2]!="99") { cout << "After pop_back lst2[2]." << endl; return false; }
	return true;
}

int main(int argc,char **argv) {
	ofstream out("time.txt");
	std::srand(42);

	ArrayList<int> al1;
	if(!simpleTest(al1)) return 2;
	if(!passByValue(al1)) {
		cout << "Failed ArrayList pass-by-value." << endl;
		return 2;
	}
	ArrayList<int> al2 = returnLittleAL();
	if(al2[0]!=1 || al2[1]!=2 || al2[2]!=3) {
		cout << "Failed return by value ArrayList." << endl;
		return 2;
	}
	al1 = returnLittleAL();
	if(al1[0]!=1 || al1[1]!=2 || al1[2]!=3) {
		cout << "Failed return by value-assign ArrayList." << endl;
		return 2;
	}

	long long n = 50000;
	long long ans1 = n*(n-1)/2;
	long long ans2 = 624975000L;

	cout << "Starting timing." << endl;
	double start = clock();

	ArrayList<int> al3;
	vector<int> v3;
	for(int i=0; i<n; ++i) {
		al3.push_back(i);
		v3.push_back(i);
	}
	long long sum = 0;
	for(auto i:al3) sum += i;
	if(sum!=ans1) {
		cout << "Failed AL big 1." << endl;
		return 2;
	}
	cout << "Passed big 1 set." << endl;
	for(int i = 1; i<al3.size(); ++i) {
		al3.remove(i);
		v3.erase(v3.begin()+i);
	}
	sum = 0;
	for(auto i:al3) sum += i;
	if(sum!=ans2) {
		cout << sum << " " << ans2 << endl;
		cout << "Failed AL big 2." << endl;
		return 2;
	}
	cout << "Passed big 2 set." << endl;

	for(int i=0; i<10000000; ++i) {
		int tmp = rand()%100;
		al3.push_back(tmp);
		v3.push_back(tmp);
	}
	ArrayList<int> al4 = add3AndReturn(al3);
	long long sum1 = 0;
	long long sum2 = 0;
	for(auto i:al4) sum1 += i;
	for(auto i:v3) sum2 += i;
	if(sum1!=sum2+24) {
		cout << "Failed big test 3. " << sum1 << " " << sum2 << endl;
		return 2;
	}

	out << (clock()-start)/CLOCKS_PER_SEC << endl;
	out.close();
	cout << "Done timing." << endl;

	cout << "Tests passed." << endl;
	return 0;
}
