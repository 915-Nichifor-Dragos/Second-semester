#include <iostream>
#include "PriorityQueue.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <crtdbg.h>
#include <assert.h>

using namespace std;


bool relation(TPriority p1, TPriority p2) {
	if (p1 <= p2) {
		return true;
	}
	else {
		return false;
	}
}



void test_special_functionality()
{
	PriorityQueue p = PriorityQueue(relation);
	p.push(1, 2);
	p.push(2, 2);
	p.push(3, 4);
	p.push(10, 5);
	p.push(321, 4);
	p.push(-3, 5);
	assert(p.increasePriority(10, 6) == 5);
}


int main() {

	//test_special_functionality();
	testAll();
	testAllExtended();

	cout << "End" << endl;

	_CrtDumpMemoryLeaks();

	system("pause");

}
