#include <iostream>

using namespace std;

//constants for array sizes
const int M = 2, N = 3;

//arrays to test
int array1[M][N];
int array2[M][N];
int arraySum[M][N];

//adds two arrays into array sum
void matrixAdd (const int a[][N], const int b[][N], int sum[][N])
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			sum[i][j] = a[i][j] + b[i][j];
		}
	}
}

//get input from user into array
void getInput(int a[][N], int rows, int columns)
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

//display elements in an array
void displayArray(const int a[][N])
{
	cout << "Res:";
	for(int i = 0; i < M; i++)
	{
		cout << endl;
		for (int j = 0; j < N; j++)
		{
			cout << a[i][j] << " ";
		}
	}
	cout << endl;
}

int main()
{
	//ask user for input and receive input
	cout << "Enter Matrix A: ";
	getInput(array1, M, N);
	
	cout << "Enter Matrix A: ";
	getInput(array2, M, N);
	
	//add array1 and array2 into arraySum
	matrixAdd(array1, array2, arraySum);
	//display arraySum
	displayArray(arraySum);
	return 0;
}
