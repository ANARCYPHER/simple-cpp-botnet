#include <iostream>
#include <fstream>
#include <stdint.h>
#include <cstring>
using namespace std;

#define BLOCK_SIZE 8
unsigned int key[4] = { 0xDEAD, 0xDEAD, 0xDEAD, 0xDEAD };

void encipher(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4]) 
{
	unsigned int i;
	uint32_t v0 = v[0], v1 = v[1], sum = 0, delta = 0x9E3779B9;

	for (i = 0; i < num_rounds; i++) 
	{
		v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
		sum += delta;
		v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
	}
	v[0] = v0; v[1] = v1;
}

void decipher(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4])
{
	unsigned int i;
	uint32_t v0 = v[0], v1 = v[1], delta = 0x9E3779B9, sum = delta * num_rounds;
	for (i = 0; i < num_rounds; i++)
	{
		v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
		sum -= delta;
		v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
	}
	v[0] = v0; v[1] = v1;
}

void xtea(char filePath[], bool boolEncrypt)
{
	
	fstream file(filePath, ios::in | ios::out | ios::binary);
	if (!file)
	{
		cout << "File " << filePath << " cannot be opened" << endl; 
		return;
	}

	file.seekg(0, ios::end);
	unsigned fileSize = file.tellg(); 
	file.seekg(ios::beg);
	file.clear();

	int blockNumber = fileSize / BLOCK_SIZE;
	if (fileSize % BLOCK_SIZE != 0) { ++blockNumber; }

	unsigned char dataArray[BLOCK_SIZE];
	unsigned filePosition = file.tellg();
	for (int i = 0; i < blockNumber; i++)
	{
		file.seekg(filePosition);
		file.read((char*)dataArray, BLOCK_SIZE);
		if (boolEncrypt) { encipher(64, (uint32_t*)dataArray, key); }
		else { decipher(64, (uint32_t*)dataArray, key); }
		file.seekp(filePosition);
		file.write((char*)dataArray, BLOCK_SIZE);

		memset(dataArray, 0, BLOCK_SIZE);
		filePosition += BLOCK_SIZE;
	}
	
	file.close();
	
}

int main(int argc, char *argv[])
{
	if (argc != 3) 
	{
		if ((argc == 2) && (string(argv[1]) == "-h"))
		{
			cout << "usage: xtea.exe path/to/file -e/-d";
		}
		else { cout << endl << argv[0] << " You have entered invalid number of parameters" << endl; }
		return 1;
	}

	bool encrypt = false;
	if ((string(argv[2]) != "-e") && ((string(argv[2]) != "-d"))) { cout << "Invalid parameter " << argv[2] << endl; return 1; }
	if (string(argv[2]) == "-e") { encrypt = true; }
	
	
	xtea(argv[1], encrypt);
	return 0;
}