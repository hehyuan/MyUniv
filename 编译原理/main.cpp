#include<iostream>
#include<istream>
#include<fstream>
#include"GetWord.h"
using namespace std;
int main()
{	
	init();
	ifstream fread;
	fread.open("mycode.c", ios::in);
	while(!fread.eof()){
		getword(fread);
		output();
	}
	fread.close();
}

