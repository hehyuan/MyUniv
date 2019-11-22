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
	src = "mycode.c";
	dir = "output1.txt";
	//prettyCode(src, dir);
	fread.open("mycode.c", ios::in);
	cout<<program(fread);
	/*while(!fread.eof()){
		getword(fread);
	}*/
	fread.close();

}

