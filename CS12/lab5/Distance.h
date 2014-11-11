#ifndef DISTANCE_H
#define DISTANCE_H

#include <string>
using namespace std;

class Distance
{
	private:
		unsigned feet;
		double inches;
	public:
		Distance()
			:feet(0), inches(0.0){}
		Distance(unsigned ft, double inc)
			:feet(ft), inches(inc){}
		Distance(double inc)
			:feet(0), inches(inc){}
		double convertToInches() const;
		const Distance operator+(const Distance &) const;
		const Distance operator-(const Distance &) const;
		void display() const;
	private:
		void init();
};
#endif