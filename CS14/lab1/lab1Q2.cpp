#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

template <class T, int size>
class vectr
{
	//private var
	private:
		T array[size];
		int pos = 0;
	public:
		//display all elements [USED FOR TESTING]
		/*
		void display()
		{
			for(int i = 0; i < pos; i++)
			{
				std::cout << array[i] << " ";
			}
			std::cout << std::endl;
		}
		*/
		vectr<T,size> operator+(const vectr<T, size>& a)
		{
			vectr<T, size> final;
			final.pos = 0;
			for(int i = 0; i < pos; i++)
			{
				final.push_back(array[i] + a[i]);
			}
			return final;
		}
		vectr<T,size> operator-(const vectr<T, size>& a)
		{
			vectr<T, size> final;
			final.pos = 0;
			for(int i = 0; i < pos; i++)
			{
				final.push_back(array[i] - a[i]);
			}
			return final;
		}
		void operator+=(const vectr<T, size>& a)
		{
			for(int i = 0; i < pos; i++)
			{
				array[i] = array[i] + a[i];
			}
		}
		
		void operator-=(const vectr<T, size>& a)
		{
			for(int i = 0; i < pos; i++)
			{
				array[i] = array[i] - a[i];
			}
		}
		const T& operator[](int sample) const
		{
			//std::cout << "const" << std::endl;
			return array[sample];
		}
		T& operator[](int sample)
		{
			//std::cout << "normal" << std::endl;
			return array[sample];
		}
		//cout (display entire vectr)
		friend std::ostream &operator<<(std::ostream &os, const vectr<T, size> &a)
		{
			for (int i = 0; i < size; i++)
			{
				os << a.array[i] << " ";
			}
			return os;
		}
		//cin (rewrite vectr)
		friend std::istream &operator>>(std::istream &is, vectr<T, size> &a)
		{
			for (int i = 0; i < size; i++)
			{
				is >> a.array[i];
				//when user enters more numbers than the vectr currently had, pos is increased
				if(i >= a.pos)
				{
					a.pos++;
				}
			}
			return is;
		}
	private:
		//HELPER
		//push back an element to the array
		void push_back(T element)
		{
			array[pos] = element;
			pos++;
		}
};

int main()
{
	vectr<int, 3> test1;
	vectr<int, 3> test2;
	vectr<int, 3> final;
	
	std::cout << "Enter: ";
	std::cin >> test1;
	
	std::cout << "Enter: ";
	std::cin >> test2;
	
	std::cout << "Enter: ";
	std::cin >> final;
	
	//Test cases
	//final = test1 + test2;
	//final = test1 - test2;
	//final += test1;
	//final -= test1;
	//std::cout << final[0] << std::endl;
	
	std::cout << test1 << std::endl;
	std::cout << test2 << std::endl;
	std::cout << final << std::endl;
	return 0;
}