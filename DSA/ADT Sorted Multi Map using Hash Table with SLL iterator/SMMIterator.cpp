#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d)
{
	this->first();

	// theta(1) -> constructor of the iterator
}

void SMMIterator::first()
{
	this->currentElement = this->map.iteratorSLL;
	if (this->currentElement != nullptr)
		this->currentNode = this->currentElement->currentNode;

	// theta(1) -> sets the iterator to point at the first element in the sorted multimap
}

void SMMIterator::next()
{

	if (this->currentElement == nullptr)
		throw exception();

	if (this->currentNode->next != nullptr)
		this->currentNode = this->currentNode->next;
	else
	{
		if (this->currentElement->nextElement != nullptr)
		{
			this->currentElement = this->currentElement->nextElement;
			this->currentNode = this->currentElement->currentNode;
		}
		else
			this->currentElement = nullptr;
	}

	// theta(1) -> the iterator will point at the next element after the current one in the sorted multimap
}

bool SMMIterator::valid() const
{
	if (this->currentElement == nullptr)
		return false;
	return true;

	// theta(1) -> checks if the iterator is valid
}

TElem SMMIterator::getCurrent() const
{
	if (this->valid())
		return this->currentNode->element;
	throw exception();

	// theta(1) -> returns the (key, value) pair to which the iterator currently points
}


