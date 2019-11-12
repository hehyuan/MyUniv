#include<iostream>
#include<istream>
#include<fstream>
#include"LL.h"
#include"GetWord.h"
#include"CFormat.h"
using namespace std;
int main()
{	
	init();
	ifstream fread;
	string src;
	string dir;
	src = "test1.c";
	dir = "output1.c";
	//prettyCode(src, dir);
	fread.open("test1.c", ios::in);
	program(fread);
	/*while(!fread.eof()){
		getword(fread);
		cout << row << endl;
	}
	fread.close();*/
}

