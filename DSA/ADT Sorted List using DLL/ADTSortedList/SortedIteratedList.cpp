#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

// ================ EXTRA ================

SortedIteratedList::Node::Node(TElem value)
{
	this->value = value;
	this->next = nullptr;
	this->previous = nullptr;
}


void SortedIteratedList::push_back(TElem element)
{
	Node* new_node = new Node(element);

	if (head == nullptr and tail == nullptr)
	{
		tail = new_node;
		head = new_node;
	}
	else
	{
		tail->next = new_node;
		new_node->previous = tail;
		tail = new_node;
	}

	// time complexity: theta(1)
}

void SortedIteratedList::push_front(TElem element)
{
	Node* new_node = new Node(element);

	if (tail == nullptr and head == nullptr)
	{
		tail = new_node;
		head = new_node;
	}
	else
	{
		head->previous = new_node;
		new_node->next = head;
		head = new_node;
	}

	// time complexity: theta(1)
}

void SortedIteratedList::pop_back()
{
	if (tail == nullptr)
		return;

	if (tail->previous == nullptr)
	{
		delete tail;
		head = nullptr;
		tail = nullptr;
		return;
	}

	tail = tail->previous;
	delete tail->next;
	tail->next = nullptr;

	// time complexity: theta(1)
}

void SortedIteratedList::pop_front()
{
	if (head == nullptr)
		return;

	if (head->next == nullptr)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		return;
	}

	head = head->next;
	delete head->previous;
	head->previous = nullptr;

	// time complexity: theta(1)
}

// ============= DONE EXTRA =============

SortedIteratedList::SortedIteratedList(Relation r) {
	this->head = nullptr;
	this->tail = nullptr;
	this->comparator = r;

	// time complexity: theta(1) -> constructor
}

int SortedIteratedList::size() const {
	ListIterator poz = this->first();
	int position = 0;
	while (poz.valid())
	{
		poz.next();
		position++;
	}
	return position;

	// time complexity: theta(n+1), where n is the number of elements in the list 
}

bool SortedIteratedList::isEmpty() const {
	if (head != nullptr and tail != nullptr)
		return false;
	return true;

	// // time complexity: theta(1)
}

ListIterator SortedIteratedList::first() const {
	return ListIterator(*this);

	// time complexity: theta(1) -> calls iterator constructor
}

TElem SortedIteratedList::getElement(ListIterator poz) const {
	if (poz.valid() == false)
		throw std::exception();
	return poz.getCurrent();

	// time complexity: theta(1)
}

TElem SortedIteratedList::remove(ListIterator& poz) {
	if (poz.valid() == false)
		throw exception();
	TElem element = poz.getCurrent();
	Node* current_node = poz.currentElement;
	poz.next();
	if (size() == 1)
		pop_back();
	else
	{
		if (poz.currentElement == nullptr)
			pop_back();
		else {
			if (current_node->previous == nullptr)
				pop_front();
			else
			{
				poz.currentElement->previous = current_node->previous;
				current_node->previous->next = poz.currentElement;
				delete current_node;
			}
		}
	}
	return element;

	// time complexity: O(1) best case -> if the element is first one or last one in the list we call pop_front or pop_back function
	//                  O(n-1) worst case -> if the element is the last but one
	//                  O(n/2) average case
	//                  Overall complexity: theta(n)
}

ListIterator SortedIteratedList::search(TElem e) const{
	ListIterator iter = first();
	while (iter.valid() and iter.getCurrent() != e)
		iter.next();
	return iter;

	// time complexity: O(1) best case -> if the element is first one in the list
	//                  O(n+1) worst case -> if the element is not in the list
	//                  O((n+1)*(n+2)/(2*n)) average case
	//                  Overall complexity: theta(n)
}

void SortedIteratedList::add(TElem e) {
	if (head == nullptr and tail == nullptr)
	{
		push_back(e);
		return;
	}

	if (head != nullptr and this->comparator(e, head->value))
	{
		push_front(e);
		return;
	}

	if (tail != nullptr and this->comparator(tail->value, e))
	{
		push_back(e);
		return;
	}

	Node* current_node = this->head;
	while (current_node != nullptr and this->comparator(current_node->value, e))
	{
		current_node = current_node->next;
	}
	if (current_node == nullptr)
		return;
	else
	{
		Node* new_node = new Node(e);
		Node* previous_current_node = current_node->previous;

		new_node->value = e;
		new_node->next = current_node;
		new_node->previous = previous_current_node;

		current_node->previous = new_node;
		previous_current_node->next = new_node;
	}

	// time complexity: O(1) best case -> if the element is less than the first one or greater than the last one in the list 
	//					                  we call push_front or push_back function
	//                  O(n-1) worst case -> if the element is greater than the the last but one and less than the last element
	//                  O(n/2) average case
	//                  Overall complexity: theta(n)
}

ListIterator SortedIteratedList::lastIndexOf(TElem elem) const
{
	ListIterator iter2 = this->first();
	ListIterator iter = this->first();
	int ok = 0;
	while (iter.valid())
	{
		iter.next();
		if (iter.getCurrent() == elem)
		{
			ok = 1;
			while (iter2.valid() and iter2.getCurrent() != elem)
				iter2.next();
		}
	}
	if (ok == 1)
		return iter2;
	else
		return iter;
}

SortedIteratedList::~SortedIteratedList() {
	while (isEmpty() == false)
	{
		pop_back();
	}
	delete head;
	delete tail;

	// time complexity : theta(n) -> function destructor has to empty the list containing 'n' elements
}
