#include <iostream>
#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <crtdbg.h>
#include <assert.h>

bool relation(TKey c1, TKey c2)
{
	return c1 <= c2;
}

int addValue(TKey key, TValue value)
{
	return key + value;
}

void test()
{
	SortedMultiMap smm = SortedMultiMap(&relation);
	smm.add(1, 2);
	smm.add(1, 3);
	smm.add(2, 3);
	smm.add(3, 4);
	smm.replaceAll(&addValue);
	SMMIterator smmi = smm.iterator();
	smmi.first();
	assert(smmi.getCurrent().first == 3);
	assert(smmi.getCurrent().second == 2);
	smmi.next();
	assert(smmi.getCurrent().first == 4);
	assert(smmi.getCurrent().second == 3);
	smmi.next();
	assert(smmi.getCurrent().first == 5);
	assert(smmi.getCurrent().second == 3);
	smmi.next();
	assert(smmi.getCurrent().first == 7);
	assert(smmi.getCurrent().second == 4);
	cout << "Test special functionality\n";
}

int main(){
	test();
    testAll();
	testAllExtended();

    std::cout<<"Finished SMM Tests!"<<std::endl;

	_CrtDumpMemoryLeaks();

	system("pause");
}
