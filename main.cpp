#include "HuffmanCodes.h"

int main()
{
	HuffmanCodes* huff = new HuffmanCodes("test.txt");
	huff->buildHuffmanTree();
	huff->printMap();
	huff->encodeCharacters();
	huff->writeEncodedText("encodedFile.txt");
	huff->decodeTextToFile("encodedFile.txt", "encodedFile.txt");
	system("pause");
	return 0;
}