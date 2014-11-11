#include "selectionsort.h"
#include <iostream>
#include <vector>
#include <list>
#include <array>

using namespace std;

struct pt {
	int x,y;
	bool operator<(const pt &p) const {
		return x<p.x ;//|| (x==p.x && y<p.y);
	}
// ignore from HERE
	pt(int xx, int yy) noexcept : x(xx), y(yy) {}
	pt(const pt &p) noexcept : x(p.x), y(p.y) { copycount++; }
	pt(pt &&p) noexcept : x(p.x), y(p.y) { movecount++; }
	pt &operator=(pt &&p) noexcept { x=p.x; y=p.y; movecount++; }
	pt &operator=(const pt &p) noexcept { x=p.x; y=p.y; copycount++; }

	static int copycount,movecount,movecount2;
// to HERE... just a way to count number of times copied and moved
};
// ignore the next two lines too (part of the above machinery to write copies
int pt::copycount = 0;
int pt::movecount = 0;

ostream &operator<<(ostream &os, const pt &p) {
	return os << '(' << p.x << ',' << p.y << ')';
}

template<typename L>
void printlist(const L &l) {
	for(auto &x : l) cout << x << ' ';
	cout << endl;
}

template<typename L>
void runsort(L &l) {
	pt::copycount=pt::movecount=0;
	cout << "pre:  "; printlist(l);
	selectionsort(l);
	cout << "post: "; printlist(l);
	cout << pt::copycount << " copies and " << pt::movecount << " moves" << endl;
}

template<typename L>
void runsortplain(L &l) {
	cout << "pre:  "; printlist(l);
	selectionsort(l);
	cout << "post: "; printlist(l);
}
int main(int argc, char **argv) {
	vector<int> iv{2,4,5,1,8,9};
	vector<int> v0{};

	runsortplain(iv);
	runsortplain(v0);

	vector<pt> v{{1,2},{3,-1},{-1,3},{0,0},{2,3},{1,2},{1,-2},{8,10}};
	list<pt> l{{10,2},{-3,-1},{-8,0},{1,1},{1,1},{0,0},{10,2},
			{5,5},{5,-5},{0,0},{10,2}};
	array<pt,8> a{{{-1,3},{0,0},{1,-2},{1,2},{1,2},{2,3},{3,-1},{8,10}}};

	runsort(v);
	runsort(l);
	runsort(a);
}
