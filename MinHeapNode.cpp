#include "MinHeapNode.h"




MinHeapNode::MinHeapNode(char d, int f) : data(d), freq(f)
{
	left = right = nullptr;
}


void MinHeapNode::setCode()
{
}

bool MinHeapNode::isLeaf()
{
	if (!left && !right) {
		return true;
	}
	return false;
}


bool operator<(const MinHeapNode & lhs, const MinHeapNode & rhs)
{
	return lhs.freq < rhs.freq;
}
