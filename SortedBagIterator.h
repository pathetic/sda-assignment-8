#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	//keep the current position in array
	int position;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

