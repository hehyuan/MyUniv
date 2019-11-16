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
	src = "test1.c";
	dir = "output1.c";
	//prettyCode(src, dir);
	fread.open("mycode.c", ios::in);
	program(fread);
	//下面测试汇编指令情况
	cout << "Test Assemblely code" << endl;
	cout << "----------------------" << endl;
	cout << asm_add("a", "b", "y") << asm_sub("a", "b", "y") << asm_add(10, "a", "b")
		<<asm_div("a","b","y")<< endl;
	/*while(!fread.eof()){
		getword(fread);
	}*/
	fread.close();

}

