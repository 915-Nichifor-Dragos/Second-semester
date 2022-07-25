#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d)
{
	this->first();
}

void SMMIterator::findFirstIterator()
{
	while (this->currentNode == nullptr and this->currentHashPosition < this->map.sizeHashTable - 1)
	{
		this->currentHashPosition += 1;
		this->currentNode = this->map.hashTable[this->currentHashPosition];
	}
}

void SMMIterator::first()
{
	this->currentNode = map.hashTable[0];
	this->currentHashPosition = 0;
	this->findFirstIterator();
}

void SMMIterator::next()
{

	this->findFirstIterator();

	if (this->currentNode == nullptr)
		throw exception();

	if (this->currentNode->next != nullptr)
	{
		this->currentNode = this->currentNode->next;
	}
	else
	{
		this->currentHashPosition += 1;
		this->currentNode = this->map.hashTable[this->currentHashPosition];
	}
}

bool SMMIterator::valid() const
{
	if (this->currentNode == nullptr)
		return false;
	return true;
}

TElem SMMIterator::getCurrent() const
{
	if (this->valid())
		return this->currentNode->element;
	throw exception();
}


