#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;


int SortedMultiMap::computeHash(TKey key)
{
	return abs(key) % this->sizeHashTable;

	// theta(1)
} 

SortedMultiMap::Node::Node()
{
	this->element = NULL_TELEM;
	this->next = nullptr;

	// theta(1) -> Node struct default constructor
}

SortedMultiMap::Node::Node(TElem element, Node* next)
{
	this->element = element;
	this->next = next;

	// theta(1) -> Node struct constructor with parameters
}

SortedMultiMap::SLLElement::SLLElement(int hashPos, Node* node, SLLElement* nextElement)
{
	this->hashPos = hashPos;
	this->currentNode = node;
	this->nextElement = nextElement;

	// theta(1) -> Iterator SLL constructor with parameters
}


SortedMultiMap::SortedMultiMap(Relation r) 
{
	this->sizeHashTable = 10;
	this->compare = r;
	this->length = 0;
	this->loadFactor = 0;
	this->hashTable = new Node*[sizeHashTable];
	for (int i = 0; i < this->sizeHashTable; i++)
		this->hashTable[i] = nullptr;
	this->iteratorSLL = nullptr;

	// theta(1) -> Sorted Multi Map constructor with relation as parameter
}

void SortedMultiMap::resizeHash()
{
	Node** copyHashTable = this->hashTable;
	this->sizeHashTable *= 2;
	this->hashTable = new Node * [this->sizeHashTable];

	SLLElement* prevElem = nullptr;
	SLLElement* currentElem = this->iteratorSLL;

	while (currentElem != nullptr)
	{
		prevElem = currentElem;
		currentElem = currentElem->nextElement;
		delete prevElem;
	}
	this->iteratorSLL = nullptr;

	for (int i = 0; i < this->sizeHashTable; i++)
		this->hashTable[i] = nullptr;

	this->length = 0;
	for (int i = 0; i < this->sizeHashTable / 2; i++)
	{
		Node* node = copyHashTable[i];

		while (node != nullptr)
		{
			this->add(node->element.first, node->element.second);
			node = node->next;
		}
	}

	for (int i = 0; i < this->sizeHashTable / 2; i++)
	{
		Node* node = copyHashTable[i];
		while (node != nullptr)
		{
			Node* nextNode = node->next;
			delete node;
			node = nextNode;
		}
	}
	delete copyHashTable;

	// theta(size_of_hash_table) -> enlarges the hash table and rehashes all the elements.
}


void SortedMultiMap::add(TKey c, TValue v)
{
	if (this->length != 0)
	{
		this->loadFactor = double(this->length) / double(this->sizeHashTable);
		if (this->loadFactor > 0.50)
			this->resizeHash();
	}

	int hash = this->computeHash(c);

	TElem element;
	element.first = c;
	element.second = v;
	Node* node = new Node(element, nullptr);

	if (this->hashTable[hash] == nullptr)
	{
		if (this->hashTable[hash] == nullptr)
		{
			this->hashTable[hash] = node;
			SLLElement* el = new SLLElement(hash, node, nullptr);

			SLLElement* previousEl = nullptr;
			SLLElement* currentEl = this->iteratorSLL;
			while (currentEl != nullptr and compare(currentEl->currentNode->element.first, el->currentNode->element.first))
			{
				previousEl = currentEl;
				currentEl = currentEl->nextElement;
			}
			if (previousEl == nullptr)
			{
				el->nextElement = currentEl;
				this->iteratorSLL = el;
			}
			else
			{
				previousEl->nextElement = el;
				el->nextElement = currentEl;
			}
		}
	}

	else
	{
		Node* currentNode = this->hashTable[hash];
		Node* previousNode = nullptr;

		while (currentNode != nullptr and compare(c, currentNode->element.first))
		{
			previousNode = currentNode;
			currentNode = currentNode->next;
		}
		if (previousNode == nullptr)
		{
			node->next = currentNode;
			hashTable[hash] = node;

			SLLElement* el = this->iteratorSLL;
			while (el != nullptr and el->hashPos != hash)
				el = el->nextElement;

			if (el != nullptr)
				el->currentNode = node;
		}
		else
		{
			previousNode->next = node;
			node->next = currentNode;
		}
	}
	this->length += 1;

	// theta(1) amortized ; WC -> theta(nr_of_elements_having_the_same_hash) -> adds a pair (key, value)
}

vector<TValue> SortedMultiMap::search(TKey c)
{
	int hash = this->computeHash(c);
	vector<TValue> values;

	if (hash > this->sizeHashTable)
		return values;
	
	Node* currentNode = this->hashTable[hash];
	while (currentNode != nullptr and compare(c, currentNode->element.first))
	{
		if (currentNode->element.first == c)
			values.push_back(currentNode->element.second);
		currentNode = currentNode->next;
	}
	return values;
	
	// theta(1) amortized ; WC -> theta(nr_of_elements_having_the_same_hash) -> searches for all values having a key given as parameter
}

bool SortedMultiMap::remove(TKey c, TValue v)
{
	int hash = this->computeHash(c);
	
	if (hash > this->sizeHashTable)
		return false;

	Node* previousNode = nullptr;
	Node* currentNode = this->hashTable[hash];
	TElem elem;
	elem.first = c;
	elem.second = v;

	while (currentNode != nullptr and compare(c, currentNode->element.first))
	{
		if (currentNode->element == elem)
		{
			if (previousNode != nullptr)
			{
				previousNode->next = currentNode->next;
				delete currentNode;
				this->length -= 1;
				return true;
			}
			else
			{
				if (currentNode->next != nullptr)
				{
					this->hashTable[hash] = currentNode->next;

					SLLElement* el = this->iteratorSLL;
					while (el != nullptr and el->hashPos != hash)
						el = el->nextElement;

					if (el != nullptr)
						el->currentNode = currentNode->next;
				}
				else
				{
					this->hashTable[hash] = nullptr;

					SLLElement* elPrev = nullptr;
					SLLElement* el = this->iteratorSLL;
					while (el != nullptr and el->hashPos != hash)
					{
						elPrev = el;
						el = el->nextElement;
					}

					if (el != nullptr)
					{
						if (elPrev == nullptr)
							this->iteratorSLL = el->nextElement;
						else
							elPrev->nextElement = el->nextElement;
					}

					delete el;
				}

				delete currentNode;
				this->length -= 1;
				return true;
			}

		}
		currentNode = currentNode->next;
	}

    return false;

	// theta(1) amortized ; WC -> theta(nr_of_elements_having_the_same_hash) -> removes a pair (key, value)
}

int SortedMultiMap::size() const
{
	return this->length;

	// theta(1) -> returns the length of the list
}

bool SortedMultiMap::isEmpty() const 
{
	if (this->length == 0)
		return true;
	return false;

	// theta(1) -> checks if the list is empty
}

SMMIterator SortedMultiMap::iterator() const
{
	return SMMIterator(*this);

	// theta(1) -> returns the iterator object
}

void SortedMultiMap::replaceAll(Transformer t)
{
	Node** copyHashTable = this->hashTable;
	this->hashTable = new Node * [this->sizeHashTable];

	SLLElement* prevElem = nullptr;
	SLLElement* currentElem = this->iteratorSLL;

	while (currentElem != nullptr)
	{
		prevElem = currentElem;
		currentElem = currentElem->nextElement;
		delete prevElem;
	}
	this->iteratorSLL = nullptr;

	for (int i = 0; i < this->sizeHashTable; i++)
		this->hashTable[i] = nullptr;

	this->length = 0;
	for (int i = 0; i < this->sizeHashTable; i++)
	{
		Node* node = copyHashTable[i];

		while (node != nullptr)
		{
			auto newKey = t(node->element.first, node->element.second);
			node->element.first = newKey;
			this->add(node->element.first, node->element.second);
			node = node->next;
		}
	}

	for (int i = 0; i < this->sizeHashTable; i++)
	{
		Node* node = copyHashTable[i];
		while (node != nullptr)
		{
			Node* nextNode = node->next;
			delete node;
			node = nextNode;
		}
	}
	delete copyHashTable;
}

SortedMultiMap::~SortedMultiMap()
{

	SLLElement* prevElem = nullptr;
	SLLElement* currentElem = this->iteratorSLL;

	while (currentElem != nullptr)
	{
		prevElem = currentElem;
		currentElem = currentElem->nextElement;
		delete prevElem;
	}

	for (int i = 0; i < this->sizeHashTable; i++)
	{
		Node* node = hashTable[i];
		while (node != nullptr)
		{
			Node* nextNode = node->next;
			delete node;
			node = nextNode;
		}
	}

	delete[] this->hashTable;

	// destructor of the Sorted Multi Map
}

