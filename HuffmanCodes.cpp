#include "HuffmanCodes.h"


using namespace std;



HuffmanCodes::HuffmanCodes(string fileName)
{
	data = getFileText(fileName);

	setCharacterFrequencies();
	
}


string HuffmanCodes::getFileText(string fileName)
{
	string file_text = "";
	string line;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		cout << "Reading from file..." << endl;
		while (getline(myfile, line))
		{
			file_text += line + '\n';
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	return file_text;
}



void HuffmanCodes::printMap()  // print out each key/value.
{
	cout << "Printing..." << endl;
	for (auto elem : frequency_map)
	{
		if (elem.first == '\n')
		{
			cout << "\\n" << ": " << elem.second << "\n";
		}
		else
		{
			cout << elem.first << " : " << elem.second << "\n";
		}
	}
}

void HuffmanCodes::setCharacterFrequencies() // Get character freq in data and update "char freq" in map
{
	for (int i = 0; i < data.length(); i++) {
		frequency_map[data[i]]++;
	}
}

void HuffmanCodes::buildHuffmanTree()
{
	
	// The top or 'internal' node, along with it's two child nodes
	MinHeapNode *left, *right, *top;

	// Add each character along with its frequency to the heap. The priority in which the elements are assigned is dictated by the 'compare'
	// function specified in the declaration of the queue. In this case the nodes with lowest frequency are given highest priority at the 'top' of the queue
	for (auto elem : frequency_map)
	{
		minHeap.push(new MinHeapNode(elem.first, elem.second));
	}

	// The heap size is initially the number of unique characters in the frequencies map. Each time around this loop the size
	// decrements as elements are 'popped' off the top of the queue and added to the Huffman Tree via a new 'top' node. When the size of the
	// heap is 2, the last 2 elements are placed into the left and right nodes of the final root node and the while loop finishes
	while (minHeap.size() > 1)
	{
		//The two least frequent nodes are gathered from the queue
		left = minHeap.top();		// Assign the left child node to the top node in the queue
		minHeap.pop();				// Remove the top element from the queue
		right = minHeap.top();		// Assign the right child node to the top node in the queue after removing the previous top
		minHeap.pop();				// Again remove the top element


		// '`' (grave accent) is a special value not used in the text file given to internal 'top' nodes. These are NOT used in encoding/ decoding
		// Create the new 'internal' node with the value of the frequency of left the right nodes summed
		//top = new MinHeapNode('`', left->freq + right->freq);
		top = new MinHeapNode('`', left->freq + right->freq);

		// Set the new top node's children to be those same left and right nodes
		top->left = left;
		top->right = right;

		// Push the top node onto the tree gradually adding all the required nodes to the Huffman Tree. Repeat this for every two least 
		// frequent elements. After the last 2 elements are removed the final 'top' link is pushed to the tree. This is the top level root node.
		minHeap.push(top);
	}
	return;
}

void HuffmanCodes::encodeCharacters()
{
	encodeCharacters(minHeap.top(), "");
}

void HuffmanCodes::encodeCharacters(MinHeapNode* root, string binary_representation)
{
	if (!root)
	{
		return;
	}
	if (root->data != '`')
	{
		encoded_map[root->data] = binary_representation;	// Accumulate and add the combination of 0s and 1s representing the character to the map for each character
	}
	encodeCharacters(root->left, binary_representation + "0");
	encodeCharacters(root->right, binary_representation + "1");
}

void HuffmanCodes::HuffmanCodes::writeEncodedText(const string& file_name)
{
	writeEncodedText(file_name, data);
}

void HuffmanCodes::writeEncodedText(const string& file_name, string text)
{
	ofstream myfile(file_name);
	cout << "Encoding text..";
	char curr_char = ' ';
	if (myfile.is_open())
	{
		for (int i = 0; i < data.length(); i++)
		{
			curr_char = data[i];
			myfile << encoded_map[curr_char];
		}
		
		myfile.close();
	}
	else cout << "Unable to open file";
}
void HuffmanCodes::writeDecodedText(const string& file_name, string text)
{
	ofstream myfile(file_name);
	cout << "Decoded text sending..";
	if (myfile.is_open())
	{
		myfile << text;
		myfile.close();
	}
	else cout << "Unable to open file";
}


void HuffmanCodes::decodeTextToFile(const string& encoded_file, const string& new_file)		// Decode the encoded file and write result to a new file
{
	string encoded_text = getFileText(encoded_file);
	string decoded_text = "";
	cout << "Decoding..";
	MinHeapNode* current = minHeap.top();
	for(int i = 0; i < encoded_text.length(); i++)										// Read in each character in the file
	{
		// Traverse through the Tree based on the encoded 1's and 0's. The unique prefix code property of the HuffMan Tree means
		// that there are no duplicate sequences of 1's and 0's that lead to a character node
		if (encoded_text[i] == '0')
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}

		// When we reach the leaf node (both children nodes are NULL), write the corresponding character to the decoded file
		if (current->isLeaf())
		{
			decoded_text += current->data;
			//Reset the current node to the root and go again
			current = minHeap.top();
		}
	}
	writeDecodedText(new_file, decoded_text);
}