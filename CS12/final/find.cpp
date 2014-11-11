#include <iostream>
#include <cstring>

using namespace std;

int find(const char x[], char y)
{
	if (x[0] == '\0')
	{
		return -1;
	}
	
	if (x[0] == y)
	{
		return strlen(x) - 1;
	}
	else
	{
		return find (x + 1, y);
	}
}

int main()
{
	// char x[] = "a";
	// char y[] = "hello";
	
	// cout << find(x, 'a') << endl;
	// cout << find(y, 'l') << endl;
	// cout << find(y, 'w') << endl;
	
	char c = 'x'; 
	// char * s = "Hello world";
	char t[20] = "Goodnight Moon";
	char * u = new char [25];

// a. s = 0;
// b. s = &c;
// c. u = t;
// d. u[0] = t[0];
// e. t = &c;
// f. s = &u;

	// s = 0;
	// s = &c;
	// u = t;
	u[0] = t[0];
	
	// cout << s << endl;
	cout << u << endl;
	
}