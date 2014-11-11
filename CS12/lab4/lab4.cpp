
#include <iostream>

using namespace std;

class Rational
{
	private:
		int numer;
		int denom; 
	public:
		Rational();
		Rational(int); 
		Rational(int, int); 
		const Rational add(const Rational &) const; 
		const Rational subtract(const Rational &) const; 
		const Rational multiply(const Rational &) const; 
		const Rational divide(const Rational &) const; 
		void display() const; 
};

//default constructor
Rational::Rational()
{
	numer = 0;
	denom = 1;
	return;
}

//int constructor
Rational::Rational(int a)
{
	numer = a;
	denom = 1;
	return;
}

//fraction constructor
Rational::Rational(int a, int b)
{
	numer = a;
	denom = b;
	return;
}

//add numbers
//add: (a/b) + (c/d) = (a*d + b*c) / (b*d)
const Rational Rational::add(const Rational& a) const
{
	Rational answer;
	answer.numer = (numer * a.denom + denom * a.numer);
	answer.denom = (denom * a.denom);
	return answer;
}

//subtract numbers
//subtract: (a/b) - (c/d) = (a*d - b*c) / (b*d)
const Rational Rational::subtract(const Rational& a) const
{
	Rational answer;
	answer.numer = (numer * a.denom - denom * a.numer);
	answer.denom = (denom * a.denom);
	return answer;
}

//multiply numbers
//multiply: (a/b) * (c/d) = (a*c) / (b*d)
const Rational Rational::multiply(const Rational& a) const
{
	Rational answer;
	answer.numer = (numer * a.numer);
	answer.denom = (denom * a.denom);
	return answer;
}

//divide numbers
//divide: (a/b) / (c/d) = (a*d) / (c*b)
const Rational Rational::divide(const Rational& a) const
{
	Rational answer;
	answer.numer = (numer * a.denom);
	answer.denom = (a.numer * denom);
	return answer;
}

//displays fraction
void Rational::display() const
{
	cout << numer << " / " << denom;
	return;
}

int main()
{
	//declare class instance
	//Rational numb1;
	//Rational numb2;
	
	Rational numb1(725, 74);
	Rational numb2(862, 864);
	Rational answer;
	
	//display values
	numb1.display();
	cout << endl;
	numb2.display();
	cout << endl;
	answer.display();
	cout << endl;
	
	return 0;
}
