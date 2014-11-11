#include <iostream>
#include <vector>
#include <cstdlib>
#include <direct.h>

using namespace std;

int main() {
    vector<char> path(512);
    _getcwd(&path[0], path.size());
    cout << &path[0] << endl;
}