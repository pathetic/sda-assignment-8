#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

/*
Time complexity: O(1)
*/
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {

	current = b.head;
}

/*
Time complexity: O(1)
*/
TComp SortedBagIterator::getCurrent() {

	if (current != nullptr)
	{
		return current->data;
	}
	throw exception();
}

/*
Time complexity: O(1)
*/
bool SortedBagIterator::valid() {
	return current != nullptr;
}

/*
Time complexity: O(1)
*/
void SortedBagIterator::next() {

	if (current != nullptr)
	{
		current = current->next;
	}
	else {
		throw exception();
	}
}

/*
Time complexity: O(1)
*/
void SortedBagIterator::first() {

	current = bag.head;
}

