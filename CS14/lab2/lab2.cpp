#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

//check if 2 numbers are coprime
bool coprime(int i, int j) 
{
	if (i%j == 0 || j%i==0) return false;
	for(int k=2;k*k<=i && k*k<=j;k++) 
	{
		if(i%k==0) 
		{
			if(j%k==0) return false;
			int k2 = i/k;
			if(j%k2==0) return false;
		}
		else
		if(j%k==0) 
		{
			int k2 = j/k;
			if(i%k2==0) return false;
		}
	}
	return true;
}

//generate random vector
template <typename randT >
vector <int> makerandvec(int n, randT &rand) 
{
	vector <int> ret;
	uniform_int_distribution <int> uniform(0, numeric_limits <int>::max());
	for(int i=0;i<n;i++) ret.push_back(uniform(rand));
	return ret;
}

//count coprime pairs, returns number of pairs
int countcoprime(vector<int> sample)
{
	int count = 0;
	for(int i = 0; i < sample.size(); i++)
	{
		for(int j = i + 1; j < sample.size(); j++)
		{
			if(coprime(sample.at(i), sample.at(j))) count++;
		}
	}
	return count;
}

int main()
{
	random_device rd;
	default_random_engine rand(rd());
	
	int vsize = 30000;
	int answer;
	
	vector<int> sample;
	
	ofstream datainsert;
	datainsert.open("data.txt");
	
	vector<int> vanswer;
	int average;
	
	while (vsize <= 300000)
	{
		average = 0;
		sample = makerandvec(vsize, rand);
		
		for(int i = 0;i < 5 ;i++)
		{
			//start clock and end clock
			auto starttime = high_resolution_clock().now();
			//answer = countcoprime(sample);
			sort(sample.begin(), sample.end());
			auto endtime = high_resolution_clock().now();
			
			//get final time
			auto finaltime = endtime - starttime;
			
			vanswer.push_back(duration_cast<microseconds>(finaltime).count());
		}
		
		//get average of vector
		for(int i = 0; i < vanswer.size(); i++)
		{
			average += vanswer.at(i);
		}
		average = average / vanswer.size();
		
		//display time
			cout << "Size: " << vsize << endl;
			cout << "Time: " << average << endl; 
			cout << "# of Coprimes: " << answer << endl << endl;
		
		datainsert << vsize << " " << average << endl;
		
		vsize += 30000;
		vanswer.clear();
	}

	return 0;
}
