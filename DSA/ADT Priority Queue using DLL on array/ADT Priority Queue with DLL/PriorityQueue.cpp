#include <iostream>
#include "PriorityQueue.h"
#include <exception>
#include <vector>

using namespace std;

PriorityQueue::Node::Node()
{
	this->information = NULL_TELEM;
	this->next = -1;
	this->previous = -1;
	this->index = -1;

	// implicit constructor for node
	// overall time complexity -> O(1)
}

PriorityQueue::Node::Node(Element currentElement, int index)
{
	this->information = currentElement;
	this->next = -1;
	this->previous = -1;
	this->index = index;

	// constructor for node with parameters
	// overall time complexity -> O(1)
}

void PriorityQueue::resize()
{
	this->capacity = this->capacity * 2;
	Node* vector = new Node[this->capacity];
	for (int i = 0; i < this->size; i++)
	{
		vector[i] = vectorNode[i];
	}
	delete[] vectorNode;
	this->vectorNode = vector;

	// when the size exceeds the capacity, we resize the dynamically allocated vector
	// overall time complexity->O(n)
	// overall extra space complexity -> O(1)
}

PriorityQueue::PriorityQueue(Relation r) {
	this->head = -1;
	this->tail = -1;
	this->size = 0;
	this->relation = r;
	this->capacity = 1;
	this->vectorNode = new Node[this->capacity];

	// constructor for priority queue with parameters
	// overall time complexity -> O(1)
}

void PriorityQueue::push(TElem e, TPriority p) {
	Element currentElement = Element(e, p);
	Node currentNode = Node(currentElement, this->size);

	if (this->capacity == this->size) // if there is no more space in the vector, we resize it.
		resize();

	vectorNode[this->size] = currentNode; // we add the element to the vector.

	if (head == tail and head == -1) // if there is currently no element in the vector then we update the tail and head to point at 0.
	{
		head = currentNode.index;
		tail = currentNode.index;
	}
	else
	{
		if (this->size == 1) // if the size of the vector is one we only have to check if we place the element before or after the element on position 0.
		{
			Node nextNode = vectorNode[head];
			if (relation(currentNode.information.second, nextNode.information.second) == false) // we place the element on the last position and update the tail.
			{
				vectorNode[nextNode.index].next = currentNode.index;
				vectorNode[currentNode.index].previous = nextNode.index;
				tail = currentNode.index;
			}
			else // we place the element on the first position and update the head.
			{
				vectorNode[nextNode.index].previous = currentNode.index;
				vectorNode[currentNode.index].next = nextNode.index;
				head = currentNode.index;
			}
		}
		else
		{
			Node nextNode = vectorNode[head];
			while (relation(nextNode.information.second, currentNode.information.second) and nextNode.next != -1)
			{
				nextNode = vectorNode[nextNode.next];
			}

			// 'nextNode' will hold the node with the closest priority, but less prioritary than the 'currentNode'.

			if (nextNode.next == -1 and relation(nextNode.information.second, currentNode.information.second) == true)
			{

				// if the current element is less prioritary than the tail, we add it at the end of the queue and update the tail.

				vectorNode[nextNode.index].next = currentNode.index;
				vectorNode[currentNode.index].previous = nextNode.index;
				tail = currentNode.index;
			}
			else
			{
				if (nextNode.previous == -1 and relation(nextNode.information.second, currentNode.information.second) == false)
				{

					// if the current element is more prioritary than the head, we add it at the beginning of the queue and update the head.

					vectorNode[nextNode.index].previous = currentNode.index;
					vectorNode[currentNode.index].next = nextNode.index;
					head = currentNode.index;
				}
				else
				{

					// if we don't place the element at the head or at the tail, we will get it's succesor and it's predecessor and bond them to each other.

					Node previousNode = vectorNode[vectorNode[nextNode.index].previous];
					vectorNode[currentNode.index].next = nextNode.index;
					vectorNode[currentNode.index].previous = previousNode.index;
					vectorNode[previousNode.index].next = currentNode.index;
					vectorNode[nextNode.index].previous = currentNode.index;
				}
			}
		}
	}
	this->size += 1;

	// time complexity -> O(1) if the list is empty, or if it contains one element (best case)
	//                 -> O(n) if the element we have to add has a smaller priority than the last one in the DLLA (worst case)
	// overall time complexity -> O(n)
}

Element PriorityQueue::top() const {
	if (this->size != 0)
		return vectorNode[this->head].information;
	throw exception();

	// time complexity -> O(1)
	// overall time complexity -> O(1)
}

Element PriorityQueue::pop() {
	if (isEmpty() == true)
		throw exception();
	Node currentNode = vectorNode[head]; // 'currentNode' is a copy of the most prioritary element.

	// if we only have one element in the vector, we delete it and return it's information.

	if (size == 1)
	{
		vectorNode[0] = Node();
		size -= 1;
		return currentNode.information;
	}

	vectorNode[vectorNode[head].next].previous = -1;
	vectorNode[head] = Node(); // we delete the head of the queue.
	for (int i = head; i < size; i++)
		vectorNode[i] = vectorNode[i + 1];

	// ok = 0 if the 2nd prioritary's element index is less than the most prioritary element index.
	// ok = 1 if the 2nd prioritary's element index is greater than the most prioritary element index.

	int ok = 0;
	if (head < currentNode.next)
		ok = 1;

	// after we delete the head, all the elements placed after it in the vector will have their real indices, but increased with 1.
	// we have to subtract 1 from the field 'index' of those nodes.
	// we also have to subtract one from the fields 'next' and 'previous' if they are greater than the 'head', as they were moved one position to left.

	for (int i = 0; i < size; i++)
	{
		if (vectorNode[i].index > head)
			vectorNode[i].index -= 1; 

		if (vectorNode[i].next > head)
			vectorNode[i].next -= 1;

		if (vectorNode[i].previous > head)
			vectorNode[i].previous -= 1;
	}
	
	// -> if ok = 0, then the position of the 2nd prioritary element was not modified (for example we have [1] [2] [3] [4] [5]. 
	//    let [3] be the most prioritary element and [3].next = 1. We remove [3], the positions of [4] and [5] are modified in the new vector
	//    ([1] [2] [4] [5]; [3].next = 1 => [2] which is correct; the position of [2], the 2nd prioritary element remains the same so we do not need to update it).
	// -> if ok = 1, then the position of the 2nd prioritary element was modified (for example we have [1] [2] [3] [4] [5].
	//    let [3] be the most prioritary element and [3].next = 3. We remove [3], the positions of [4] and [5] are modified in the new vector
	//    ([1] [2] [4] [5], [3].index = 3 => [5] which is incorrect; should have been [4]; we will need to subtract one from the [3].next field in order
	//    to get the real index of 2nd prioritary element).
		
	if (ok == 0)
		head = vectorNode[currentNode.next].index;
	else
	{
		if (size == 2) // -> if the size is equal to 1 after popping the 1st element, then we have one element left in the 
		{	           //vector and 'tail' will be equal to 'head' and will be equal to 0 (the index of that element).
			head = 0;
		}
		else
		{
			if (currentNode.next == size)
				head = vectorNode[currentNode.next - 1].index; // -> if the 2nd prioritary element is the last in the list, we have to go to it's index field - 1,
				                                                   //    because the index has been previously reduced in the for loop.
			else
				head = currentNode.next - 1; // -> the 2nd prioritary element's 'index' was greater than the most prioritary 'index', so we have to subtract
			                                 //    one from it's index field in order to get the real index.
		}
	}
	if (head == -1) // if the 'head' is equal to -1, there are no elements in the list and we will also set the 'tail' to -1
		tail -= 1;
	
	size -= 1;
	return currentNode.information;

	// time complexity -> O(1) if there is only 1 element in the list (best case)
	//                 -> O(n^2) if we remove the last but one element (worst case) -> we have to update the vector
	//                 -> O(n) average complexity
	// overall time complexity -> O(n)
}

bool PriorityQueue::isEmpty() const {
	if (this->size == 0)
		return true;
	return false;

	// time complexity -> O(1)
	// overall time complexity -> O(1)
}

TPriority PriorityQueue::increasePriority(TElem elem, TPriority newPriority)
{

	int currentNode = head;
	while (currentNode != tail)
	{
		if (elem != vectorNode[currentNode].information.first)
			currentNode = vectorNode[currentNode].next;
		else
		{
			TElem element = vectorNode[currentNode].information.first;
			TPriority old_priority = vectorNode[currentNode].information.second;

			if (relation(old_priority, newPriority) == true)
				throw exception();

			for (int i = currentNode; i < size - 1; i++)
				vectorNode[i] = vectorNode[i + 1];

			size--;

			for (int i = 0; i < size; i++)
			{
				if (vectorNode[i].index > currentNode)
					vectorNode[i].index -= 1;

				if (vectorNode[i].next > currentNode)
					vectorNode[i].next -= 1;

				if (vectorNode[i].previous > currentNode)
					vectorNode[i].previous -= 1;
			}
			this->push(element, newPriority);
			return old_priority;
			
		}
	}
	return -1;

}

PriorityQueue::~PriorityQueue()
{
	delete[] this->vectorNode;

	// destructor of the priority queue
	// overall time complexity -> O(1)
}

