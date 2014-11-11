#include <iostream>

using namespace std;

//constants for array sizes
const int Q = 2, R = 3, S = 3;

//arrays to test
int array1[Q][R];
int array2[R][S];
int arrayProduct[Q][S] = {0, 0, 0, 0, 0, 0};

//get input from user into array
void getInput(int a[][R], int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cin >> a[i][j];
		}
	}
	cout << endl;
}

//multiplies two arrays into product array
void matrixMult(const int a[][R], const int b[][S], int product[][S])
{
	//controls order when multiplaying elements in arrays
	for(int i = 0; i < Q; i++)
		{
			for (int j = 0; j < S; j++)
			{
				for (int x = 0; x < R; x++)
				{
					product[i][j] += a[i][x] * b[x][j];
				}
			}
		}
}

//display elements in an array
void displayArray(const int a[][R], int rows, int columns)
{
	cout << "Res:";
	for(int i = 0; i < rows; i++)
	{
		cout << endl;
		for (int j = 0; j < columns; j++)
		{
			cout << a[i][j] << " ";
		}
	}
	cout << endl;
}

int main()
{
	//ask user for array input and get input
	cout << "Enter Matrix A(size 2x3): "; 		// 2 5 1 0 3 -1
	getInput(array1, Q, R);
	
		//test 
		//displayArray(array1, Q, R);
	
	cout << "Enter Matrix B(size 3x3): ";		// 1 0 2 -1 4 -2 5 2 1
	getInput(array2, R, S);
	
		//test
		//displayArray(array2, R, S);
	
	//multiplies arrays
	matrixMult(array1, array2, arrayProduct);
	
	//display product array
	displayArray(arrayProduct, Q, S);
	
	return 0;
}
