#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list){
	currentElement = list.head;

	// time complexity: theta(1) -> iterator constructor
}

void ListIterator::first(){
	currentElement = list.head;

	// time complexity: theta(1)
}

void ListIterator::next(){
	if (this->currentElement == nullptr)
		throw std::exception();
	this->currentElement = this->currentElement->next;

	// time complexity: theta(1)
}

bool ListIterator::valid() const{
	if (this->currentElement == nullptr)
		return false;
	return true;

	// time complexity: theta(1)
}

TElem ListIterator::getCurrent() const{
	if (currentElement == nullptr)
		throw std::exception();
	return currentElement->value;

	// time complexity: theta()
}


