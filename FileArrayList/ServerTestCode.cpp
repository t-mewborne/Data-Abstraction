#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<cstring>
#include<string>
#include "FileArrayList.h"

using std::ofstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::rand;

struct Data {
	Data():i(rand()),d(rand()*0.1/RAND_MAX) {
		for(int j=0; j<19; ++j) str[j] = 'a'+rand()%26;
		str[19]=0;
	}
	bool operator==(const Data &that) {
		return i==that.i && d==that.d && std::strcmp(str,that.str)==0;
	}
	bool operator!=(const Data &that) {
		return !(*this==that);
	}
	int i;
	double d;
	char str[20];
};

template<typename T,typename V>
bool fillArray(const std::string &fname,vector<V> &data) {
	T lst(fname);
	lst.clear();
	for(int i=0; i<10000; ++i) {
		V v;
		data.push_back(v);
		lst.push_back(data.back());
	}
	if(lst.size() != static_cast<int>(data.size())) return false;
	auto iter = lst.begin();
	for(V &v:data) {
		if(*iter!=v) return false;
		++iter;
	}
	return true;
}

template<typename T,typename V>
bool checkEquality(const std::string &fname,vector<V> &data) {
	T lst(fname);
	if(lst.size() != static_cast<int>(data.size())) return false;
	auto iter = lst.begin();
	for(V &v:data) {
		if(*iter!=v) return false;
		++iter;
	}
	return true;
}

template<typename T>
bool simpleTest(T &lst1,const string &secondFile) {
	lst1.clear();
	lst1.push_back(5);
	if(lst1[0]!=5) { cout << "[0]' error after push_back 5, but got " <<lst1[0]<< endl; return false; }
	lst1.push_back(6);
	if(lst1[1]!=6) { cout << "[1]' error after push_back 5 6, but got "<<lst1[1] << endl; return false; }
	lst1.push_back(7);
	if(lst1[2]!=7) { cout << "[2]' error after push_back 5 6 7, but got "<<lst1[2] << endl; return false; }
	lst1.push_back(8);
	lst1.push_back(9);
	if(lst1[0]!=5) { cout << "[0] error after push_back 5 6 7 8 9." << endl; return false; }
	if(lst1[1]!=6) { cout << "[1] error after push_back 5 6 7 8 9." << endl; return false; }
	if(lst1[2]!=7) { cout << "[2] error after push_back 5 6 7 8 9." << endl; return false; }
	if(lst1[3]!=8) { cout << "[3] error after push_back 5 6 7 8 9." << endl; return false; }
	if(lst1[4]!=9) { cout << "[4] error after push_back 5 6 7 8 9." << endl; return false; }

	int cnt = 5;
	for(auto iter = lst1.begin(); iter!=lst1.end(); ++iter) {
		if(*iter!=cnt) {
			cout << "iter error: *iter should be " << cnt << " but got " << *iter << endl;
			return false;
		}
		++cnt;
	}
	cnt = 5;
	for(auto iter = lst1.cbegin(); iter!=lst1.cend(); ++iter) {
		if(*iter!=cnt) {
			cout << "const_iter error " << cnt << " but got " << *iter << endl;
			return false;
		}
		++cnt;
	}
	cnt = 9;
	for(auto iter = --lst1.end(); iter!=lst1.begin(); --iter) {
		if(*iter!=cnt) {
			cout << "--iter error " << cnt<< " but got " << *iter  << endl;
			return false;
		}
		--cnt;
	}
	lst1.set(99,2);
	if(lst1[2]!=99) {
		cout << "set error." << endl;
		return false;
	}
	T lst2(lst1.begin(),lst1.end(),secondFile);
    //lst1.printArray();
    //cout << *(++++lst1.begin()) << endl;
	lst1.erase(++++lst1.begin());
	if(lst1[0]!=5) { cout << "After erase lst1[0]." << endl; return false; }
	if(lst1[1]!=6) { cout << "After erase lst1[1]." << endl; return false; }
	if(lst1[2]!=8) { cout << "After erase lst1[2]." << endl; 
                        lst1.printArray();
                        return false; }
	if(lst1[3]!=9) { cout << "After erase lst1[3]." << endl; return false; }
	if(lst2[0]!=5) { cout << "After erase lst2[0]." << endl; return false; }
	if(lst2[1]!=6) { cout << "After erase lst2[1]." << endl; return false; }
	if(lst2[2]!=99) { cout << "After erase lst2[2]." << endl; return false; }
	if(lst2[3]!=8) { cout << "After erase lst2[3]." << endl; return false; }
	if(lst2[4]!=9) { cout << "After erase lst2[4]." << endl; return false; }
	lst2.insert(++++++lst2.begin(),98);
	if(lst2[0]!=5) { cout << "After insert lst2[0]." << endl; return false; }
	if(lst2[1]!=6) { cout << "After insert lst2[1]." << endl; return false; }
	if(lst2[2]!=99) { cout << "After insert lst2[2]." << endl; return false; }
	if(lst2[3]!=98) { cout << "After insert lst2[3]." << endl; return false; }
	if(lst2[4]!=8) { cout << "After insert lst2[4]." << endl; return false; }
	if(lst2[5]!=9) { cout << "After insert lst2[5]." << endl; return false; }
	lst2.pop_back();
	if(lst2.size()!=5) { cout << "bad size after pop_back." << endl; return false; }
	lst2.pop_back();
	if(lst2.size()!=4) { cout << "bad size after pop_back." << endl; return false; }
	lst2.pop_back();
	if(lst2.size()!=3) { cout << "bad size after pop_back." << endl; return false; }
	if(lst2[0]!=5) { cout << "After pop_back lst2[0]." << endl; return false; }
	if(lst2[1]!=6) { cout << "After pop_back lst2[1]." << endl; return false; }
	if(lst2[2]!=99) { cout << "After pop_back lst2[2]." << endl; return false; }
	return true;
}

int main(int argc,char **argv) {
	ofstream out("time.txt");
	std::srand(42);

	FileArrayList<int> al1("al1.bin");
	if(!simpleTest(al1,"alst.bin")) return 2;
	cout << "Array passed simple." << endl;

	vector<Data> v;
	if(!fillArray<FileArrayList<Data>,Data>("data.bin",v)) {
		cout << "Array failed on fill." << endl;
		return 2;
	}
	if(!checkEquality<FileArrayList<Data>,Data>("data.bin",v)) {
		cout << "ArrayList failed equality test." << endl;
		return 2;
	}
	v.clear();

	long long n = 20000;
	long long ans1 = n*(n-1)/2;
	long long ans2 = 199970790;

	cout << "Starting timing." << endl;
	double start = clock();

	FileArrayList<int> al3("al3.bin");
	al3.clear();
	vector<int> ll3;
	ll3.clear();
	for(int i=0; i<n; ++i) {
		al3.push_back(i);
		ll3.push_back(i);
	}
	long long sum = 0;
	for(auto i:al3) sum += i;
	if(sum!=ans1) {
		cout << "Failed AL big 1." << endl;
		return 2;
	}
	sum = 0;
	for(auto i:ll3) sum += i;
	if(sum!=ans1) {
		cout << "Failed LL big 1." << endl;
		return 2;
	}
	cout << "Passed big 1 set." << endl;
	auto iter2 = ++ll3.begin();
	auto iter = ++al3.begin();
	for(int i = 0; i<al3.size()/10; i+=100) {
		al3.erase(iter);
		ll3.erase(iter2);
		for(int j = 0; j<100; ++j) {
			++iter;
			++iter2;
		}
//		if(i%100==0) cout << i << " " << al3.size() << endl;
	}
	cout << "Done removing." << endl;
	sum = 0;
	for(auto i:al3) sum += i;
	if(sum!=ans2) {
		cout << sum << " " << ans2 << endl;
		cout << "Failed AL big 2." << endl;
		return 2;
	}
	sum = 0;
	for(auto i:ll3) sum += i;
	if(sum!=ans2) {
		cout << "Failed LL big 2." << endl;
		return 2;
	}
	cout << "Passed big 2 set." << endl;

	for(int i=0; i<300000; ++i) {
		int tmp = rand()%100;
		al3.push_back(tmp);
		ll3.push_back(tmp);
	}
	long long sum1 = 0;
	long long sum2 = 0;
	for(auto i:al3) sum1 += i;
	for(auto i:ll3) sum2 += i;
	cout << sum1 << endl;
	if(sum1!=sum2) {
		cout << "Failed big test 3." << endl;
		return 2;
	}
	cout << "Passed big test 3." << endl;

	out << (clock()-start)/CLOCKS_PER_SEC << endl;
	out.close();
	cout << "Done timing." << endl;

	cout << "Tests passed." << endl;
	return 0;
}
