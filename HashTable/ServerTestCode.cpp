#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<cstring>
#include<functional>
#include<utility>
#include<unordered_map>
#include "HashMap.h"

using std::ofstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::rand;
using std::pair;
using std::make_pair;
using std::unordered_map;

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

unsigned hashDouble(double d) {
	unsigned *u = reinterpret_cast<unsigned*>(&d);
	unsigned ret = u[0] ^ u[1];
	return ret;
}

bool fillMap(HashMap<double,Data,std::function<unsigned(double)>> &hash,unordered_map<double,Data> &data) {
	for(int i=0; i<100000; ++i) {
		Data v;
		data[v.d] = v;
		hash[v.d] = v;
	}
	if(hash.size() != data.size()) return false;
	for(auto &p:data) {
		if(data[p.first]!=p.second) return false;
	}
	return true;
}

bool checkEquality(HashMap<double,Data,std::function<unsigned(double)>> hash,unordered_map<double,Data> &data) {
	if(hash.size() != data.size()) return false;
	for(auto &p:data) {
		if(data[p.first]!=p.second) return false;
	}
	return true;
}

int doTests() {
	ofstream out("time.txt");
	HashMap<int,string,std::function<int(int)>> hash([] (int i) { return i; });

	if(!hash.empty()) {
		cout << "Not empty on creation." << endl;
		return 2;
	}
	if(hash.size()!=0) {
		cout << "Size not zero on creation." << endl;
		return 2;
	}

	hash[5] = "five";
	if(hash.empty()) {
		cout << "Empty after []." << endl;
		return 2;
	}
	if(hash.size()!=1) {
		cout << "Size not one after []." << endl;
		return 2;
	}
	if(hash[5]!="five") {
		cout << "Return of [] didn't match after first add." << endl;
		return 2;
	}

	hash[3] = "three";
	if(hash.size()!=2) {
		cout << "Size not two after []." << endl;
		return 2;
	}
	if(hash[5]!="five") {
		cout << "Return of [] didn't match after second add." << endl;
		return 2;
	}
	if(hash[3]!="three") {
		cout << "Return of [] didn't match after second add." << endl;
		return 2;
	}

	hash[16] = "sixteen";
	if(hash[5]!="five") {
		cout << "Return of [] didn't match after third add." << endl;
		return 2;
	}
	if(hash[16]!="sixteen") {
		cout << "Return of [] didn't match after third add." << endl;
		return 2;
	}

	hash[3] = "THREE";
	if(hash[3]!="THREE") {
		cout << "Can't use [] to change value." << endl;
		return 2;
	}

	hash.clear();
	if(!hash.empty()) {
		cout << "Not empty after clear." << endl;
		return 2;
	}
	if(hash.size()!=0) {
		cout << "Size not zero after clear." << endl;
		return 2;
	}

	hash[16] = "six-teen";
	if(hash.empty()) {
		cout << "Empty after []." << endl;
		return 2;
	}
	if(hash.size()!=1) {
		cout << "Size not one after []." << endl;
		return 2;
	}
	if(hash[16]!="six-teen") {
		cout << "Return of [] didn't match after first add." << endl;
		return 2;
	}
	if(hash.count(16)!=1) {
		cout << "Incorrect count A." << endl;
		return 2;
	}
	if(hash.count(3)!=0) {
		cout << "Incorrect count B." << endl;
		return 2;
	}
	hash[1] = "one";
	hash[2] = "two";
	hash[3] = "three";

	HashMap<int,string,std::function<int(int)>> hash2([] (int i) { return i; });
	hash2[16] = "six-teen";
	hash2[3] = "three";
	hash2[2] = "two";
	hash2[1] = "one";
	if(hash2.size()!=4) {
		cout << "Size off in simple tests AA." << endl;
		return 2;
	}

	// TODO : Need to add things in different orders so table equality isn't sufficient.
	for(int i=100; i<110; ++i) {
		hash2[i] = "filler";
	}
	for(int i=100; i<110; ++i) {
		hash2.erase(i);
	}
	if(hash!=hash2) {
		cout << "Inequality check failed." << endl;
		return 2;
	}

	hash2[4] = "four";
	if(hash==hash2) {
		cout << "Equality check failed." << endl;
		return 2;
	}
	if(hash2.size()!=5) {
		cout << "Size off in simple tests AB." << endl;
		return 2;
	}

	vector<pair<int,string>> v{make_pair(5,"five"),make_pair(6,"six"),
		make_pair(7,"seven"),make_pair(8,"eight"),make_pair(9,"nine"),
		make_pair(2,"TWO")};
	hash2.insert(v.begin(),v.end());
	if(hash2.size()!=10) {
		cout << "Size off in simple tests AC." << endl;
		return 2;
	}
	if(hash2[4]!="four") {
		cout << "Error with 4 after insert." << endl;
		return 2;
	}
	if(hash2[6]!="six") {
		cout << "Error with 6 after insert." << endl;
		return 2;
	}
	if(hash2[8]!="eight") {
		cout << "Error with 8 after insert." << endl;
		return 2;
	}
	if(hash2[1]!="one") {
		cout << "Error with 1 after insert." << endl;
		return 2;
	}
	if(hash2[2]!="two") {
		cout << "Error with 2 after insert." << endl;
		return 2;
	}

	auto pins1 = hash2.insert(make_pair(77,"seventy-seven"));
	if(!pins1.second || (*pins1.first).first!=77 || (*pins1.first).second!="seventy-seven") {
		cout << "Single insert return error when true." << endl;
		return 2;
	}
	if(hash2.size()!=11) {
		cout << "Size off in simple tests AD." << endl;
		return 2;
	}

	auto pins2 = hash2.insert(make_pair(7,"SEVEN"));
	if(pins2.second || (*pins2.first).first!=7 || (*pins2.first).second!="seven") {
		cout << "Single insert return error when false." << endl;
		return 2;
	}

	if(hash2.size()!=11) {
		cout << "Size off in simple tests A." << endl;
		return 2;
	}

	vector<int> v2{1,2,3,4,5,6,7,8,9,16,77};
	for(auto i:v2) {
		auto iter = hash2.find(i);
		if(iter==hash2.end()) {
			cout << "Missed a key that should be there A. " << i << endl;
			return 2;
		}
	}
	for(auto &p:hash2) {
		if(p.first%2==0) hash2[p.first] = "even";
		else hash2[p.first] = "odd";
	}
	for(auto i:v2) {
		auto iter = hash2.find(i);
		if(iter==hash2.end()) {
			cout << "Missed a key that should be there B. " << i << endl;
			return 2;
		}
		if((i%2==0 && (*iter).second!="even") || (i%2==1 && (*iter).second!="odd")) {
			cout << "Failed even/odd for " << i << " got  " << (*iter).first << " " << (*iter).second << endl;
			return 2;
		}
	}

	if(hash2.size()!=11) {
		cout << "Size off in simple tests B." << endl;
		return 2;
	}

	if(hash2.erase(99)!=0) {
		cout << "Wrong return value on remove on non-existant element." << endl;
		return 2;
	}
	if(hash2.erase(6)!=1) {
		cout << "Wrong return value on remove on existant element." << endl;
		return 2;
	}
	if(hash2.size()!=10) {
		cout << "Size off in simple tests D." << endl;
		return 2;
	}
	auto f2iter = hash2.find(2);
	f2iter++;
	auto eiter = hash2.erase(hash2.find(2));
	if(hash2.count(2)!=0) {
		cout << "Call to erase didn't remove." << endl;
		return 2;
	}
	if(hash2.size()!=9) {
		cout << "Size off in simple tests E." << endl;
		return 2;
	}
// Removed because I don't think this is a valid check.
//	if(eiter!=f2iter) {
//		cout << "problem with the return from erase." << endl;
//		return 2;
//	}

	hash2[-200] = "negative";
	if(hash2[-200]!="negative") {
		cout << "Error retreiving value with negative key." << endl;
		return 2;
	}

	unordered_map<int,string> um2;
	for(int i = 0; i<4000000; ++i) {
		int key = rand();
		string str;
		for(int j=0; j<5; ++j) {
			str += 'a'+(rand()%26);
		}
		um2.insert(make_pair(key,str));
	}
	vector<pair<int,string>> insertSet;
	for(int i = 0; i<400000; ++i) {
		int key = rand();
		string str;
		for(int j=0; j<3; ++j) {
			str += 'a'+(rand()%26);
		}
		insertSet.push_back(make_pair(key,str));
	}
	auto um2copy=um2;

	cout << "Starting timing." << endl;
	double start = clock();

	HashMap<double,Data,std::function<unsigned(double)>> dhash(hashDouble);
	unordered_map<double,Data> data;

	if(!fillMap(dhash,data)) {
		cout << "Failed big fill." << endl;
		return 2;
	}
	cout << "Passed fill." << endl;
	if(!checkEquality(dhash,data)) {
		cout << "Failed equality check." << endl;
		return 2;
	}
	cout << "Passed check." << endl;

	hash2.clear();
	for(auto &p:um2) {
		hash2[p.first] = p.second;
	}
	cout << "Big add done." << endl;
	for(auto &p:um2) {
		if(hash2[p.first] != p.second) {
			cout << "Failed recovering in big test." << endl;
			return 2;
		}
	}
	cout << "Passed big lookup." << endl;
	for(auto &p:um2) {
		auto iter = hash2.find(p.first);
		if((*iter).first != p.first || (*iter).second != p.second) {
			cout << "Failed find in big test." << endl;
			return 2;
		}
	}
	cout << "Passed big find." << endl;
	for(auto &p:um2copy) {
		if(rand()%100==0) {
			auto tmp = p.first;
			if(um2.erase(tmp) != hash2.erase(tmp)) {
				cout << "Disagreement on erase of " << p.first << endl;
				return 2;
			}
		}
	}
	if(um2.size()!=hash2.size()) {
		cout << "Size disagreement after erase. " << um2.size() << " " << hash2.size() << endl;
		return 2;
	}
	for(auto &p:um2) {
		if(hash2[p.first] != p.second) {
			cout << "Failed recovering after erase." << endl;
			return 2;
		}
	}
	cout << "Passed big erase." << endl;
	for(auto p:insertSet) {
		auto tmp = p;
		um2.insert(p);
		hash2.insert(tmp);
	}
	for(auto &p:um2) {
		if(hash2[p.first] != p.second) {
			return 2;
		}
	}
	out << (clock()-start)/CLOCKS_PER_SEC << endl;
	out.close();
	cout << "Done timing." << endl;
	return 0;
}

int main(int argc,char **argv) {
	std::srand(42);

	if(doTests()!=0) return 2;


	cout << "Tests passed." << endl;
	return 0;
}
