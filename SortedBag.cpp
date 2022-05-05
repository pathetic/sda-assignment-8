#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	//initialize the class attributes
	relation = r;
	head = nullptr;
	numElements = 0;
}

/*
Time complexity: O(N) because the method iterate the list to find the position to insert data
Best time O(1) where the data is put as head of linked list
Worst time O(N) where the data is put as tail of linked list
*/
void SortedBag::add(TComp e) {

	//create new node
	Node* newNode = new Node();
	newNode->data = e;
	newNode->next = nullptr;

	numElements++;

	//if empty, head points to new node
	if (head == nullptr)
	{
		head = newNode;
	}
	else {

		//find the position to insert data
		Node* prev = nullptr;
		Node* curr = head;

		//iterate list and find the position to insert new node
		while (curr != nullptr && relation(curr->data, e))
		{
			prev = curr;

			//move to next node
			curr = curr->next;
		}

		if (prev == nullptr) //insert as head
		{
			newNode->next = head;
			head = newNode;
		}
		else {//insert between prev and curr. Note: the curr maybe null if the node node is inserted as tail node
			prev->next = newNode;
			newNode->next = curr;
		}
	}
}

/*
Time complexity: O(N) because the method iterate the list to find the position to delete
Best time O(1) where the deleted node is head of linked list
Worst time O(N) where the deleted node is tail of linked list
*/
bool SortedBag::remove(TComp e) {

	//declare previous and current node to iterate the linked list
	Node* prev = nullptr;
	Node* curr = head;

	//iterate list and find the position to insert new node
	while (curr != nullptr && relation(curr->data, e))
	{
		//for example: relation is <= then relation function returns true,
		//need to check equal to break the while
		if (curr->data == e)
		{
			break;
		}

		//move to next node
		prev = curr;
		curr = curr->next;
	}

	//not found
	//when the while moves to the tail or break due to relation function
	//need to compare data with e
	if (curr == nullptr || curr->data != e)
	{
		return false;
	}

	if (prev == nullptr) //delete head
	{
		head = head->next;
	}
	else {//delete current
		prev->next = curr->next;
	}

	numElements--;

	//delete node
	delete curr;

	return true;
}

/*
Time complexity: O(N) because the method iterate the list to find the element
Best time O(1) where the found node is head of linked list
Worst time O(N) where the found node is tail of linked list
*/
bool SortedBag::search(TComp elem) const {

	Node* curr = head; //pointer to iterate the linked list

	//iterate list and find the position to insert new node
	while (curr != nullptr && relation(curr->data, elem))
	{
		if (curr->data == elem)
		{
			break;
		}

		//move to next node
		curr = curr->next;
	}

	//if current node is not null and data in current is element
	return (curr != nullptr && curr->data == elem);
}

/*
Time complexity: O(N) because the method iterate the list to find the element
Best time O(1) where the relation function (with head node) return false
Worst time O(N) where the loop move to tail of linked list
*/
int SortedBag::nrOccurrences(TComp elem) const {

	int count = 0; //number of occurrences

	Node* curr = head;

	//iterate list and count
	while (curr != nullptr && relation(curr->data, elem))
	{
		if (curr->data == elem)
		{
			count++;
		}

		//move to next node
		curr = curr->next;
	}

	return count;
}


/*
Time complexity: O(1)
*/
int SortedBag::size() const {
	return numElements;
}

/*
Time complexity: O(1)
*/
bool SortedBag::isEmpty() const {
	return numElements == 0;
}

/*
Time complexity: O(1)
*/
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

/*
Time complexity: O(N) because the method iterate the list and delete
*/
SortedBag::~SortedBag() {

	//pointers to iterate the linked list
	Node* prev = nullptr;
	Node* curr = head;

	//iterate list and find the position to insert new node
	while (curr != nullptr)
	{
		prev = curr;

		//move to next node
		curr = curr->next;

		//delete node
		delete prev;

	}
}
