#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r){
	//initialize the class attributes
	relation = r;
	arraySize = initialArraySize;
	data = new TComp[initialArraySize];
	
	numElements = 0;

	for (int i = 0; i < initialArraySize; i++)
	{
		data[i] = NULL_TCOMP;
	}
}

/*
Time complexity: O(N) because the method iterate the array to find the position to insert data
Best time O(1) where the data is put as head of array
Worst time O(N) where the data is put as tail of array
*/
void SortedBag::add(TComp e) {

	if (numElements == arraySize)
	{
		arraySize *= 2;

		TComp* newData = new TComp[arraySize];

		//copy old data
		for (int i = 0; i < numElements; i++)
		{
			newData[i] = data[i];
		}

		//other locations are empty
		for (int i = numElements; i < arraySize; i++)
		{
			newData[i] = NULL_TCOMP;
		}

		delete[] data;
		data = newData;
	}

	int before = -1;

	//find before location to insert
	for (int i = 0; i < arraySize; i++)
	{
		//find element before the new one
		if (data[i] != NULL_TCOMP)
		{
			if (relation(data[i], e))
			{
				before = i;
			}
			else {
				break;
			}
		}
	}

	int after = -1;

	//find after location to insert
	for (int i = 0; i < arraySize; i++)
	{
		//find element before the new one
		if (data[i] != NULL_TCOMP)
		{
			if (!relation(data[i], e))
			{
				after = i;
				break;
			}
		}
	}

	if (before == -1 && after == -1) //empty
	{
		data[0] = e;
	}
	else if (before == -1 && after != -1)
	{
		if (after != 0) //not the first location
		{
			data[after - 1] = e;
		}
		else {
			//find first empty position after 'after'
			int emptyPos = after + 1;
			while (data[emptyPos] != NULL_TCOMP)
			{
				emptyPos++;
			}

			//shift right to create a hold to insert e
			for (int i = emptyPos; i > after; i--)
			{
				data[i] = data[i - 1];
			}
			data[after] = e;
		}
	}
	else if (before != -1 && after == -1)
	{
		if (before != arraySize - 1) //not the last location
		{
			data[before + 1] = e;
		}
		else {
			//find first empty position before 'before'
			int emptyPos = before - 1;
			while (data[emptyPos] != NULL_TCOMP)
			{
				emptyPos--;
			}

			//shift left to create a hold to insert e
			for (int i = emptyPos; i < before; i++)
			{
				data[i] = data[i + 1];
			}
			data[before] = e;
		}
	}
	else { //(before != -1 && after != -1)

		bool done = false;

		//insert between 'before' and 'after'
		for (int i = before + 1; i < after - 1; i++)
		{
			if (data[i] != NULL_TCOMP)
			{
				data[i] = e;
				done = true;
				break;
			}
		}

		if (!done)//try to shift right
		{
			//find first empty position after 'after'
			int emptyPos = after + 1;
			while (emptyPos < arraySize && data[emptyPos] != NULL_TCOMP)
			{
				emptyPos++;
			}

			if (emptyPos < arraySize)
			{
				//shift right to create a hold to insert e
				for (int i = emptyPos; i > after; i--)
				{
					data[i] = data[i - 1];
				}
				data[after] = e;
				done = true;
			}			
		}

		if (!done)//try to shift left
		{
			//find first empty position before 'before'
			int emptyPos = before - 1;
			while (data[emptyPos] != NULL_TCOMP)
			{
				emptyPos--;
			}

			//shift left to create a hold to insert e
			for (int i = emptyPos; i < before; i++)
			{
				data[i] = data[i + 1];
			}
			data[before] = e;
		}
	}

	numElements += 1;
}

/*
Time complexity: O(N) because the method iterate the array to find the position to delete
Best time O(1) where the deleted element is head of array
Worst time O(N) where the deleted element is tail of array
*/
bool SortedBag::remove(TComp e) {

	//find empty location to remove
	for (int i = 0; i < arraySize; i++)
	{
		if (data[i] == e) {
			data[i] = NULL_TCOMP;

			numElements--;

			return true;
		}

		//exit the for if the relation is violated
		if (data[i] != NULL_TCOMP && !relation(data[i], e))
		{
			break;
		}
	}

	return false; //not found
}

/*
Time complexity: O(N) because the method iterate the array to find the element
Best time O(1) where the found element is head of array
Worst time O(N) where the found element is tail of array
*/
bool SortedBag::search(TComp elem) const {

	//find element
	for (int i = 0; i < arraySize; i++)
	{
		if (data[i] == elem) {

			return true;
		}

		//exit the for if the relation is violated
		if (data[i] != NULL_TCOMP && !relation(data[i], elem))
		{
			break;
		}
	}

	return false; //not found
}

/*
Time complexity: O(N) because the method iterate the array to find the element
Best time O(1) where the relation function (at position 0) return false
Worst time O(N) where the loop move to tail ofarray
*/
int SortedBag::nrOccurrences(TComp elem) const {

	int count = 0; //number of occurrences

	//find element
	for (int i = 0; i < arraySize; i++)
	{
		if (data[i] == elem) {

			count += 1;
		}
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
Time complexity: O(1) 
*/
SortedBag::~SortedBag() {

	delete[] data;
}
