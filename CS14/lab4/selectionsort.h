#ifndef SELECTIONSORT_H 
#define SELECTIONSORT_H 

// 3 4 3 2
// 2 4 3 3
// 2 3 4 3
// 2 3 3 4

#include <iostream>
#include <utility>
template<typename L>
void selectionsort(L &l) 
{
	auto k = end(l);
	for(auto i = begin(l); i != end(l); i++)
	{
		auto minnumber = i;
		auto j = i;
		j++;
		//std::cout << "jbefore" << *j << std::endl;
		for(j; j != end(l); j++) 
		{
			//std::cout << "compare i and j: " << *i << " " << *j << std::endl;
			if(*j < *minnumber)
			{
				minnumber = j;
				//std:: cout << "new min: " << *min << std::endl;
			}
		}
		//std::cout << "i" << *i << std::endl;
		//std::cout << "min" << min << std::endl;
		if(*minnumber < *i)
		{
			//std::cout << "bswitch" << *i << " " << *j << std::endl;
			std::swap( *i, *minnumber );
			//std::cout << "aswitch" << *i << " " << *j << std::endl;
		}
	}
}
#endif