//Your name: Rica Feng
//Your UCR student ID number: 861061334
//The date: 11/4/14
//The course (CS 14)
//The assignment number (PS 4)

#ifndef QSORT_H
#define QSORT_H

#include <vector>
#include <iostream>
#include <utility>

template<typename T>
void boundedinsertionsort(std::vector<T> &v,int l,int r) {
	for(int i=l+1;i<=r;i++) {
		T tmp = std::move(v[i]);
		int j = i;
		for(j=i;j>l && tmp<v[j-1]; --j)
			v[j] = std::move(v[j-1]);
		v[j] = std::move(tmp);
	}
}

template<typename T>
void insertionsort(std::vector<T> &v) {
	boundedinsertionsort(v,0,v.size()-1);
}

// you may add helper functions, if desired

// do not rename this function or its arguments
template<typename T>
void boundedquicksort(std::vector<T> &v, int l, int r) 
{
	static const int minsize = 5;
	
	//count++;
	//std::cout << count << std::endl;
	
	int pivot = (r + l) / 2;
	
	//std::cout << "size: " << size << std::endl;
	//std::cout << "pivot: " << pivot << std::endl;
	
	//base case: less then size 5 
	if (r - l < minsize)
	{
		boundedinsertionsort(v, l, r);
	}
	else
	{
		std::vector<T> less;
		std::vector<T> more;
		std::vector<T> pivotv;
		
		//std::cout << "huajf" << std::endl;
		for(int i = l; i < r + 1; i++)
		{
			if (v[i] < v[pivot])
			{
				less.push_back(v[i]);
			}
			else if (v[pivot] < v[i])
			{
				more.push_back(v[i]);
			}
			else
			{
				pivotv.push_back(v[i]);
			}
		}
		
		/*
		//std::cout << pivotv.size() << std::endl;
		for (int i = 0; i < more.size() - 1; i++)
		{
			std::cout << more[i] << std::endl;
		}
		*/
		int pos = l;
		for (int i = 0; i < less.size(); pos++, i++)
		{
			v[pos] = less[i];
		}
		for (int i = 0; i < pivotv.size(); pos++, i++)
		{
			v[pos] = pivotv[i];
		}
		for (int i = 0; i < more.size(); pos++, i++)
		{
			v[pos] = more[i];
		}
		//std::cout << "hudjf" << std::endl;
		boundedquicksort(v, l, l + less.size() - 1);
		boundedquicksort(v, r - more.size() + 1, r);
	}
}

/*
//partition
		while (i < j)
		{
			while(v[i] < v[pivot])
			{
				i++;
			}
			while (v[pivot] < v[j])
			{
				j--;
			}
			//if i is less than j switch the elements
			if (i <= j)
			{
				//switch elements
				T temp = v[i];
				v[i] = v[j];
				v[j] = temp;
				
				i++;
				j--;
			}
		}
		//sort the left and the right side
		if (l < j)
		{
			boundedquicksort(v, l, j);
		}
		if (i < r)
		{
			boundedquicksort(v, i, r);
		}
*/

// do not rename this function or its arguments
template<typename T>
void quicksort(std::vector<T> &v) {
	boundedquicksort(v,0,v.size()-1);
}
	/*
		while (i <= j)
		{
			//increment i if less than pivot
			while (v[i] < v[pivot])
			{
				i++;
				//std::cout << "i: " << i << std::endl;
			}
			//increment j if less than pivot
			while (v[pivot] < v[j])
			{
				j--;
				//std::cout << "j: " << j << std::endl;
			}
			if (v[i] < v[j] || (!(v[i] < v[j]) && !(v[j] < v[i])))
			{
				T temp = v[i];
				v[i] = v[j];
				v[j] = temp;		
			}
			
			i++;
			j--;
		}
		//recursion
		//boundedquicksort(v, l, j);
		//boundedquicksort(v, i, r);
	}
	*/
#endif