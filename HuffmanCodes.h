#ifndef HUFMANCODES_H
#define HUFMANCODES_H
#include "MinHeapNode.h"
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <queue>
#include <bitset>

#pragma once
class HuffmanCodes
{
private:
	string data;
	string encodedData;
	map<char, int> frequency_map;
	map<char, string> encoded_map;
	// Create a min heap & inserts all characters of data[] 
	void setCharacterFrequencies();
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
	void encodeCharacters(MinHeapNode* root, string binary_representation);
	string getFileText(string fileName);
	void writeEncodedText(const string& file_name, string text);
	void writeDecodedText(const string& file_name, string text);
public:
	HuffmanCodes(string fileName);
	~HuffmanCodes() { delete minHeap.top(); };
	void printMap();
	
	void buildHuffmanTree();
	void encodeCharacters();
	void writeEncodedText(const string& file_name);
	void decodeTextToFile(const string& encoded_file, const string& new_file);
	
	
};

#endif
