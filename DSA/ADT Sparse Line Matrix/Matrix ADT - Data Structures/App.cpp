#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <assert.h>

using namespace std;


void test()
{
	Matrix m = Matrix(4, 5);
	m.setElemsOnCol(1, 3);
	m.setElemsOnCol(2, 10);
	for (int i = 0; i < m.nrLines(); i++)
	{
		for (int j = 0; j < m.nrColumns(); j++)
		{
			if (j == 1)
				assert(m.element(i, j) == 3);
			if (j == 2)
				assert(m.element(i, j) == 10);
			//cout << m.element(i, j) << " ";
		}
		//cout << endl;
	}
	cout << "Test special funcitonality\n";
}


int main() {

	testAll();
	testAllExtended();
	test();
	cout << "Test End" << endl;
	system("pause");
}