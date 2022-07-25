#pragma once
#include <vector>
#include <utility>

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool (*Relation)(TPriority p1, TPriority p2);
#define NULL_TELEM pair<TElem, TPriority> (-11111,-11111);

class PriorityQueue {

private:
	struct Node
	{
		Element information;
		int previous;
		int next;
		int index;

		Node(Element value, int index);

		Node();

	};

	int capacity;
	int size;

	int head;
	int tail;
	Node* vectorNode;
	Relation relation;

	void resize();

public:
	//implicit constructor
	PriorityQueue(Relation r);

	//pushes an element with priority to the queue
	void push(TElem e, TPriority p);

	//returns the element with the highest priority with respect to the order relation
	//throws exception if the queue is empty
	Element top()  const;

	//removes and returns the element with the highest priority
	//throws exception if the queue is empty
	Element pop();

	//checks if the queue is empty
	bool isEmpty() const;

	//increases the priority of an element
	//returns the old priority of "elem" if "elem" is not in the PriorityQueue return -1
	//if the new priority is "less than" (considering the relation) the old one, throw an exception
	TPriority increasePriority(TElem elem, TPriority newPriority);

	//destructor
	~PriorityQueue();

};