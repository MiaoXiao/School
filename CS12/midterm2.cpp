#include <iostream>

using namespace std;

const unsigned ROWS = 3;
const unsigned COLUMNS = 3;

class Matrix3x3
{
	public:
		Matrix3x3();
			//:matrix[ROWS][COLUMNS] = {0, 0, 0, 0, 0, 0}{}
		Matrix3x3(const double m[ROWS][COLUMNS]);
		void  set_matrix(const double m[ROWS][COLUMNS]);
		const double get_elem(unsigned i, unsigned j) const;
		const Matrix3x3 mult(const Matrix3x3 & rhs) const;
		const Matrix3x3 operator*(const Matrix3x3 & rhs) const;
		const Matrix3x3 square() const;
	private:
		double matrix[ROWS][COLUMNS];
};
