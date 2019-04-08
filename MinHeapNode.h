#ifndef MINHEAPNODE_H
#define MINHEAPNODE_H
#include <iostream>
#include <string>


using namespace std;
#pragma once

class MinHeapNode
{
	friend class HuffmanCodes;
	friend struct compare;
private:
	char data;
	int freq;
	string code;
	MinHeapNode *left, *right;
public:
	MinHeapNode(char d, int f);
	void setCode();
	bool isLeaf();
	//friend ostream& operator<<(ostream&, const MinHeapNode&);
	friend bool operator<(const MinHeapNode& lhs, const MinHeapNode& rhs);

};

// Struct to provide the Priority Queue with a custom ordering, in this case the nodes
// with lowest frequency are given highest priority at the 'top' of the queue
struct compare {

	bool operator()(MinHeapNode* left, MinHeapNode* right)		//Return true if the left node is more frequent than the right. 
	{
		return (left->freq > right->freq);
	}
};

#endif
