#pragma once
//DO NOt INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TElem;
typedef bool (*Relation)(TElem, TElem);
#define NULL_TCOMP -11111


class SortedIteratedList {
private:
	friend class ListIterator;
private:
	struct Node {
		TElem value;
		Node* previous;
		Node* next;

		Node(TElem value);

	};

	typedef bool (*operation)(TElem, TElem);

	Node* head;
	Node* tail;
	operation comparator;

	void push_back(TElem element);
	void push_front(TElem element);
	void pop_back();
	void pop_front();

public:
	// constructor
	SortedIteratedList(Relation r);

	// returns the number of elements from the list
	int size() const;

	// verifies if the list is empty
	bool isEmpty() const;

	// returns the first position from the list
	ListIterator first() const;

	// returns the element from the given position
	//throws an exception if the position is not valid
	TElem getElement(ListIterator pos) const;

	// adds a new element to the list
	void add(TElem e);

	// removes the element from position pos
	//returns the removed element
	//after removal pos is positioned on the next element (the one after the removed one) or it is invalid if the last element was removed
	//throws an exception if the position is not valid
	TElem remove(ListIterator& poz);

	// searches for the first occurrence of an element 
	//returns an iterator that points to the element, if it appear in the list, or an invalid iterator if the element is not in the list
	ListIterator search(TElem e) const;

	// returns the last index of a given element
	// if the element is not in the list returns an invalid TPosition
	ListIterator lastIndexOf(TElem elem) const;

	//destructor
	~SortedIteratedList();

};
