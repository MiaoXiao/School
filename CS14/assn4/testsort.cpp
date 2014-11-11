#include "qsort.h"
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


// a structure to be sorted:
struct idname {
	idname(int i, const char *n) : id(i), name(n) {}
	int id;
	std::string name;
};

std::ostream &operator<<(std::ostream &os, const idname &x) {
	return os << x.id << ":" << x.name;
}

// the comparison for sorting:
bool operator<(const idname &x1, const idname &x2) {
	return x1.name < x2.name;
}

// code to check a sorting:
// general method to check equality to make sure the
// output is a permutation of the input
template<typename T>
bool checkeq(const T &t1, const T &t2) {
	return t1==t2;
}

// specialization of the above for the case of idname
template<>
bool checkeq(const idname &x1, const idname &x2) {
	return x1.id==x2.id && x1.name==x2.name;
}


template<typename L>
void check(L &l) {
	L l2(l);
	for(auto &x : l) cout << x << ' ';
	cout << endl;
	quicksort(l);
	for(auto &x : l) cout << x << ' ';
	cout << endl;
	if (is_sorted(begin(l),end(l)) &&
		end(l)-begin(l) == end(l2)-begin(l2) &&
		is_permutation(begin(l),end(l),begin(l2),
			checkeq<typename remove_reference<
					decltype(*(begin(l)))>::type>))
			cout << "PASS" << endl;
	else cout << "FAIL" << endl;
}

// driver:
int main(int argc, char **argv) {
	vector<int> vi {1,3,2,4,5,3,4,1,4,4,5,2};
	vector<int> vi2 {3,2,1,2,1,2,1,2,3,2,2,1};
	vector<int> vi3 {1,1,1,1,1,1,1,1,1,1,1,1};
	vector<int> vi4 {1,3,2,4,1,2,2,3,1,1,2,3,4,1,2,3,1,
	                 5,1,3,3,6,5,3,4,2,1,2,3,4,1,2,3,1,
	                 2,9,3,4,1,9};

	check(vi);
	check(vi2);
	check(vi3);
	check(vi4);

	vector<idname> vn {{34,"B"},{22,"A"},{13,"B"},{33,"B"},{10,"C"},{45,"C"},{8,"A"},{9,"C"},{13,"C"},{22,"A"}};
	check(vn);
}
