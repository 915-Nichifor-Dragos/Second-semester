#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;


int SortedMultiMap::computeHash(TKey key)
{
	if (this->compare(1, 2) == true)
		return abs(key) % this->sizeHashTable;
	return abs(this->sizeHashTable - abs(key) % this->sizeHashTable - 2);
}

SortedMultiMap::Node::Node()
{
	this->element = NULL_TELEM;
	this->next = nullptr;
}

SortedMultiMap::Node::Node(TElem element, Node* next)
{
	this->element = element;
	this->next = next;
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
}

void SortedMultiMap::resizeHash()
{
	Node** copyHashTable = this->hashTable;
	this->sizeHashTable *= 2;
	this->hashTable = new Node * [this->sizeHashTable];
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
		this->hashTable[hash] = node;

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
		}
		else
		{
			previousNode->next = node;
			node->next = currentNode;
		}
	}
	this->length += 1;
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
				}
				else
				{
					this->hashTable[hash] = nullptr;
				}

				delete currentNode;
				this->length -= 1;
				return true;
			}

		}
		currentNode = currentNode->next;
	}

    return false;
}

int SortedMultiMap::size() const
{
	return this->length;
}

bool SortedMultiMap::isEmpty() const 
{
	if (this->length == 0)
		return true;
	return false;
}

SMMIterator SortedMultiMap::iterator() const
{
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap()
{
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
	delete this->hashTable;

}