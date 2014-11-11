// Name: Michael Uy
// SID: 861064409
// Date: 10/14/14
// Course: CS14
// Assn#: PS1
#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>
#include "fmt.h"
using namespace std;

struct spreadsheetcell{
	spreadsheetcell(string c, int r) : col(c), row(r) {}
	string col;
	int row;
};

string converttostring ( const spreadsheetcell & ssc ) {
return ssc . col + to_string ( ssc . row );
}

int main( int argc, char **argv){
	
	vector<spreadsheetcell> v;
	for(int i=1;i<=4;++i){
		v.emplace_back("A",i);
		v.emplace_back("AZ", i);
		v.emplace_back("BBD",i);
		v.emplace_back("Z",i);
	}
	formatparagraph(cout,v,18);
}


