#include <iostream>

using namespace std;

const int NROWS = 4;
const int NCOLS = 4;

int arr[NROWS][NCOLS] = {1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 1, 8, 1, 1, 1, 1};

class Student 
{ 
  private: 
    string name; 
    int total_score;
    unsigned num_scores; 
  public: 
    Student( const string &name )
		:name(name){};
    Student( const string &name, int quiz_score )
		:name(name), total_score(quiz_score), num_scores(1){};
    double get_average_score() const; 
    void add_quiz( int quiz_score ); 
};

void Student::add_quiz(int quiz_score)
{
	total_score +=  quiz_score;
	num_scores++;
}

double Student::get_average_score() const
{
	return static_cast<double>(total_score) / num_scores;
}

int maxQuadSum(int arr[NROWS][NCOLS])
{
	int large = 0;
	int sum = 0;
	for(int i = 0; i < NROWS - 1; i++)
	{
		for (int j = 0; j < NCOLS - 1; j++)
		{
			sum += arr[i][j] + arr[i][j+1] + arr[i+1][j] + arr[i+1][j+1];
			if (sum > large)
			{
				large = sum;
			}
			sum = 0;
		}
	}
	return large;
}

void strcrazycat(char a[], const char b[])
{
	int i = 0;
	while (a[i] != '\0')
	{
		i++;
	}
	int visit = i;
	cout << "max a" << i << endl;
	for (int j = 0; b[j] != '\0'; j++)
	{
		cout << i << endl;
		a[i] = b[j];
		i++;
	}
	
	for (int x = 0; x < visit; x++)
	{
		a[i] = a[x];
		i++;
	}
	a[i] = '\0';
}

int main()
{
	char a[] = "Mom";
	char b[] = "Dad";
	
	strcrazycat(a, b);
	for (int i = 0; i < 20; i++)
	{
		cout << a[i];
	}
	cout << endl;
	
}