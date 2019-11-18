#include<iostream>
#include<istream>
#include<fstream>
#include"LL.h"
#include"GetWord.h"
#include"CFormat.h"
#include"asemble.h"
using namespace std;
int main()
{	
	init();
	ifstream fread;
	string src;
	string dir;
	src = "mycode.c";
	dir = "output1.txt";
	prettyCode(src, dir);
	/*fread.open("mycode.c", ios::in);
	program(fread);*/
	//下面测试汇编指令情况
	/*cout << "Test Assemblely code" << endl;
	cout << "----------------------" << endl;
	cout << asm_assume("a",100) << endl;*/
	/*while(!fread.eof()){
		getword(fread);
	}*/
	fread.close();

}

