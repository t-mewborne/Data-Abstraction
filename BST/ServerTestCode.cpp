#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<cstring>
#include<functional>
#include<utility>
#include<map>
#include "BSTMap.h"

using std::ofstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::rand;
using std::pair;
using std::make_pair;
using std::map;

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

bool fillMap(BSTMap<double,Data> &bst,map<double,Data> &data) {
	for(int i=0; i<100000; ++i) {
		Data v;
		data[v.d] = v;
		bst[v.d] = v;
	}
	if(bst.size() != data.size()) return false;
	for(auto &p:data) {
		if(data[p.first]!=p.second) return false;
	}
	return true;
}

bool checkEquality(BSTMap<double,Data> bst,map<double,Data> &data) {
	if(bst.size() != data.size()) return false;
	for(auto &p:data) {
		if(bst[p.first]!=p.second) return false;     //bst[] instead of data
	}
	return true;
}

bool checkRemove(BSTMap<int,string> bst,vector<int> &v,BSTMap<int,string> &orig,int remKey) {
	for(auto k:v) {
		if(bst[k]!=orig[k]) {
			cout << "Copy failed on " << k << endl;
			return false;
		}
	}
	if(bst!=orig) {
		cout << "Equality failed on copy.\n";
		return false;
	}

	for(auto &p:bst) {
		if(p.second!=orig[p.first]) {
			cout << "Traversal problem first remove." << endl;
			return false;
		}
	}

	bst.erase(remKey);
	if(bst.find(remKey)!=bst.end()) {
		cout << "Found " << remKey << " after remove." << endl;
		return false;
	}

	for(auto k:v) {
		if(k!=remKey && bst[k]!=orig[k]) {
			cout << k << " not found after removing " << remKey << endl;
			return false;
		}
	}

	for(auto &p:bst) {
		if(p.second!=orig[p.first]) {
			cout << "Traversal problem after remove." << endl;
			return false;
		}
	}
	return true;
}

int helper() {
	ofstream out("time.txt");
	std::srand(42);

	BSTMap<int,string> bst;

	if(!bst.empty()) {
		cout << "Not empty on creation." << endl;
		return 2;
	}
	if(bst.size()!=0) {
		cout << "Size not zero on creation." << endl;
		return 2;
	}

	bst[5] = "five";
	if(bst.empty()) {
		cout << "Empty after []." << endl;
		return 2;
	}
	if(bst.size()!=1) {
		cout << "Size not one after []." << endl;
		return 2;
	}
	if(bst[5]!="five") {
		cout << "Return of [] didn't match after first add." << endl;
		return 2;
	}

	bst[3] = "three";
	if(bst.size()!=2) {
		cout << "Size not two after []." << endl;
		return 2;
	}
	if(bst[5]!="five") {
		cout << "Return of [] didn't match after second add." << endl;
		return 2;
	}
	if(bst[3]!="three") {
		cout << "Return of [] didn't match after second add." << endl;
		return 2;
	}

	bst[16] = "sixteen";
	if(bst[5]!="five") {
		cout << "Return of [] didn't match after third add." << endl;
		return 2;
	}
	if(bst[16]!="sixteen") {
		cout << "Return of [] didn't match after third add." << endl;
		return 2;
	}

	bst[3] = "THREE";
	if(bst[3]!="THREE") {
		cout << "Can't use [] to change value." << endl;
		return 2;
	}

	bst.clear();
	if(!bst.empty()) {
		cout << "Not empty after clear." << endl;
		return 2;
	}
	if(bst.size()!=0) {
		cout << "Size not zero after clear." << endl;
		return 2;
	}

	bst[16] = "six-teen";
	if(bst.empty()) {
		cout << "Empty after []." << endl;
		return 2;
	}
	if(bst.size()!=1) {
		cout << "Size not one after []." << endl;
		return 2;
	}
	if(bst[16]!="six-teen") {
		cout << "Return of [] didn't match after first add after clear." << endl;
		return 2;
	}
	if(bst.count(16)!=1) {
		cout << "Incorrect count A." << endl;
		return 2;
	}
	if(bst.count(3)!=0) {
		cout << "Incorrect count B." << endl;
		return 2;
	}
	bst[1] = "one";
	bst[2] = "two";
	bst[3] = "three";

	BSTMap<int,string> bst2;
	bst2[16] = "six-teen";
	bst2[3] = "three";
	bst2[2] = "two";
	bst2[1] = "one";
	if(bst2.size()!=4) {
		cout << "Size off in simple tests AA." << endl;
		return 2;
	}
	// cout<<"bst:\n";
    // bst.printTree();
	// cout<<"bst2:\n";
	// bst2.printTree();
	cout<<"Inequality check: ";
	if(bst!=bst2) {
		cout << "Inequality check failed." << endl;
		return 2;
	}
    cout << "Passed." << endl;

	cout<<"Equality check: ";
	bst2[4] = "four";
	if(bst==bst2) {
		cout << "Equality check failed." << endl;
		return 2;
	}
	cout << "Passed." << endl;

	cout<<"Size check: ";
	if(bst2.size()!=5) {
		cout << "Size off in simple tests AB." << endl;
		return 2;
	}
	bst[75] = "seventy-five";
	cout << "Passed." << endl;

	cout<<"Equality check B: ";
	if(bst==bst2) {
		cout << "Equality check failed B." << endl;
		return 2;
	}
	cout << "Passed." << endl;

	vector<pair<int,string>> v{make_pair(5,"five"),make_pair(6,"six"),
		make_pair(7,"seven"),make_pair(8,"eight"),make_pair(9,"nine"),
		make_pair(2,"TWO")};

	cout << "Insert: ";
	bst2.insert(v.begin(),v.end());
	if(bst2.size()!=10) {
		cout << "Size off in simple tests AC." << endl;
		return 2;
	}
	cout << "Passed 1, ";

	if(bst2[4]!="four") {
		cout << "Error with 4 after insert." << endl;
		return 2;
	}
	if(bst2[6]!="six") {
		cout << "Error with 6 after insert." << endl;
		return 2;
	}
	if(bst2[8]!="eight") {
		cout << "Error with 8 after insert." << endl;
		return 2;
	}
	if(bst2[1]!="one") {
		cout << "Error with 1 after insert." << endl;
		return 2;
	}
	if(bst2[2]!="two") {
		cout << "Error with 2 after insert." << endl;
		return 2;
	}

	cout << "Passed 2. " <<endl;

	cout << "Test Copy: ";
	auto pins1 = bst2.insert(make_pair(77,"seventy-seven"));
	cout << "Passed."<<endl;

	if(!pins1.second || (*pins1.first).first!=77 || (*pins1.first).second!="seventy-seven") {
		cout << "Single insert return error when true." << endl;
		return 2;
	}
	if(bst2.size()!=11) {
		cout << "Size off in simple tests AD." << endl;
		return 2;
	}

	auto pins2 = bst2.insert(make_pair(7,"SEVEN"));
	if(pins2.second || (*pins2.first).first!=7 || (*pins2.first).second!="seven") {
		cout << "Single insert return error when false." << endl;
		return 2;
	}

	if(bst2.size()!=11) {
		cout << "Size off in simple tests A." << endl;
		return 2;
	}
	cout << "Find: ";
	vector<int> v2{1,2,3,4,5,6,7,8,9,16,77};
	for(auto i:v2) {
		auto iter = bst2.find(i);
		if(iter==bst2.end()) {
			cout << "Missed a key that should be there A. " << i << endl;
			return 2;
		}
	}
	cout <<"Passed."<<endl;

	cout<<"Check Remove: ";
 	for(auto i:v2) {
		if(!checkRemove(bst2,v2,bst2,i)) {
			cout << "Failed checkRemove on " << i << endl;
			return 2;
		}
	}
	cout <<"Passed."<<endl;

	cout<<"[] assign: ";
	for(auto &p:bst2) {
		if(p.first%2==0) bst2[p.first] = "even";
		else bst2[p.first] = "odd";
	}
	cout <<"Passed."<<endl;

	cout<<"Equality check C: ";
	for(auto i:v2) {
		auto iter = bst2.find(i);
		if(iter==bst2.end()) {
			cout << "Missed a key that should be there B. " << i << endl;
			return 2;
		}
		if((i%2==0 && (*iter).second!="even") || (i%2==1 && (*iter).second!="odd")) {
			cout << "Failed even/odd for " << i << " got  " << (*iter).first << " " << (*iter).second << endl;
			return 2;
		}
	}
	cout <<"Passed."<<endl;

	cout<<"Check --: ";
	for(auto iter = --bst2.end(); iter!=bst2.begin(); --iter) {
		if((*iter).first!=v2.back()) {
			cout << "Wrong value using -- on iterator. " << (*iter).first << " " << v2.back() << endl;
			return 2;
		}
		v2.pop_back();
	}
	cout <<"Passed."<<endl;

	cout<<"Check Size: ";
	if(bst2.size()!=11) {
		cout << "Size off in simple tests B." << endl;
		return 2;
	}
	cout <<"Passed."<<endl;

	cout<<"Check erase return value on remove on non-existant element: ";
	if(bst2.erase(99)!=0) {
		cout << "Wrong return value on remove on non-existant element." << endl;
		return 2;
	}
	cout <<"Passed."<<endl;

	cout<<"Check erase return value on remove on existant element: ";
	if(bst2.erase(6)!=1) {
		cout << "Wrong return value on remove on existant element." << endl;
		return 2;
	}
	cout <<"Passed."<<endl;

	cout<<"Check Size: ";
	if(bst2.size()!=10) {
		cout << "Size off in simple tests D." << endl;
		return 2;
	}


	auto f2iter = bst2.find(2);
	f2iter++;
	auto eiter = bst2.erase(bst2.find(2));
	if(bst2.count(2)!=0) {
		cout << "Call to erase didn't remove." << endl;
		return 2;
	}
	if(bst2.size()!=9) {
		cout << "Size off in simple tests E." << endl;
		return 2;
	}
	if(eiter!=f2iter) {
		cout << "problem with the return from erase." << endl;
		return 2;
	}

	bst2[-200] = "negative";
	if(bst2[-200]!="negative") {
		cout << "Error retreiving value with negative key." << endl;
		return 2;
	}

	map<int,string> um2;
	vector<pair<int,string>> originalValues;
	for(int i = 0; i<2000000; ++i) {
		int key = rand();
		string str;
		for(int j=0; j<5; ++j) {
			str += 'a'+(rand()%26);
		}
		um2[key] = str;
		originalValues.push_back(make_pair(key,str));
	}
	vector<pair<int,string>> insertSet;
	for(int i = 0; i<200000; ++i) {
		int key = rand();
		string str;
		for(int j=0; j<5; ++j) {
			str += 'a'+(rand()%26);
		}
		insertSet.push_back(make_pair(key,str));
	}

	auto um2copy=um2;

	cout << "Starting timing." << endl;
	double start = clock();

	BSTMap<double,Data> dbst;
	map<double,Data> data;

	if(!fillMap(dbst,data)) {
		cout << "Failed big fill." << endl;
		return 2;
	}
	cout << "Passed fill." << endl;
	if(!checkEquality(dbst,data)) {
		cout << "Failed equality check." << endl;
		return 2;
	}
	cout << "Passed check." << endl;

	bst2.clear();
	for(auto &p:originalValues) {
		bst2[p.first] = p.second;
	}
	cout << "Big add done." << endl;
	for(auto &p:um2) {
		if(bst2[p.first] != p.second) {
			cout << "Failed recovering in big test." << endl;
			return 2;
		}
	}
	cout << "Passed big lookup." << endl;
	for(auto &p:um2) {
		auto iter = bst2.find(p.first);
		if((*iter).first != p.first || (*iter).second != p.second) {
			cout << "Failed find in big test." << endl;
			return 2;
		}
	}
	cout << "Passed big find." << endl;
	for(auto &p:um2copy) {
		if(rand()%100==0) {
			int tmp = p.first;
			if(um2.erase(tmp) != bst2.erase(tmp)) {
				cout << "Disagreement on erase of " << p.first << endl;
				return 2;
			}
		}
	}
	if(um2.size()!=bst2.size()) {
		cout << "Size disagreement after erase. " << um2.size() << " " << bst2.size() << endl;
		return 2;
	}
	for(auto &p:um2) {
		//cout << p.first << " " << p.second << " " << bst2[p.first] << endl;
		if(bst2[p.first] != p.second) {
			cout << "Failed recovering after erase." << endl;
			return 2;
		}
	}
	cout << "Passed big erase." << endl;
	for(auto &p:insertSet) {
		um2.insert(p);
		bst2.insert(p);
	}
	for(auto &p:um2) {
		if(bst2[p.first] != p.second) {
			cout << "Failed recovering after insert." << endl;
			return 2;
		}
	}

	out << (clock()-start)/CLOCKS_PER_SEC << endl;
	out.close();
	cout << "Done timing." << endl;

	return 0;
}

int main(int argc,char **argv) {
	if(helper()!=0) return 2;
	cout << "Tests passed." << endl;
	return 0;
}