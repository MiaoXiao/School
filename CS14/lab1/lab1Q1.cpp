#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template <typename T1>
vector < pair<int, T1> > listVector(vector<T1> sample)
{
	vector < pair<int,T1> > finished;
	int count = 1;
	//loop through all elements and compare first position to position + 1
	for(int i = 0; i < sample.size() - 1; i++)
	{
		if(sample.at(i) == sample.at(i + 1))
		{
			count++;
		}
		else
		{
			finished.push_back(make_pair(count, sample.at(i)));
			count = 1;
		}
		//check if last element, then add final pair
		if(i + 1 >= sample.size() - 1)
		{
			int j = i + 1;
			finished.push_back(make_pair(count, sample.at(j)));
		}
	}
	return finished;
}

int main()
{
	//sample vectors
	vector<int> sample = {1, 1, 2, 2, 3, 4, 5, 6, 6, 6, 6, 6, 7, 7};
	//vector<char> sample = {'a', 'a', 'b', 'c', 'd', 'd', 'e', 'e', 'f', 'f', 'e'};

	//hold final vector
	vector <pair<int, int>> test = listVector(sample);

	//display answer
	cout << "[";
	for(int i = 0; i < test.size(); i++)
	{
		//display int pair
		cout << "(" << test[i].first << "," << test[i].second;
		//check if last element
		if(i + 1 >= test.size())
		{
			cout << ")]" << endl;
		}
		else
		{
			cout << "),";
		}
	}
	
	return 0;
}