#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

/*
Time complexity: O(1)
*/
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {

	position = -1;

	//find first
	for (int i = 0; i < bag.arraySize; i++)
	{
		if (b.data[i] != NULL_TCOMP) {

			position = i;
			break;
		}
	}
}

/*
Time complexity: O(1)
*/
TComp SortedBagIterator::getCurrent() {

	if (position != -1)
	{
		return bag.data[position];
	}
	throw exception();
}

/*
Time complexity: O(1)
*/
bool SortedBagIterator::valid() {
	return position != -1;
}

/*
Time complexity: O(1)
*/
void SortedBagIterator::next() {

	if (position == -1)
	{
		throw exception();
	}

	//next position
	for (int i = position + 1; i < bag.arraySize; i++)
	{
		if (bag.data[i] != NULL_TCOMP) {

			position = i;
			return;
		}
	}

	position = -1;	
}

/*
Time complexity: O(1)
*/
void SortedBagIterator::first() {

	position = -1;

	//find first
	for (int i = 0; i < bag.arraySize; i++)
	{
		if (bag.data[i] != NULL_TCOMP) {

			position = i;
			break;
		}
	}
}

