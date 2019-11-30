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
	dir = "output1.txt";
	cout << "输入目标代码文件" << endl;
	cin >> src;
	fread.open(src, ios::in);
	if (fread.good()) {
		string code;
		cout << endl << "开始翻译源代码:\n\n\n" << (code = program(fread));
		fread.close();
		if (hasError == false) {
			ofstream fwrite("output.txt", ios::out);
			fwrite << code;
			fwrite.close();
		}
		if (totalError == 0) {
			cout << "是否需要美化源代码?\n1:yes\n0:No" << endl;
			int a = 0;
			cin >> a;
			if (a != 0) {
				cout << "\n\n\n开始美化原代码" << endl;
				prettyCode(src, dir);
				cout << "\n\nLoading……" << endl;
				cout << "\n\n\n美化完成,源代码位于当前目录下的output1.txt中!" << endl;
			}
		}
	}
	else {
		cout << "文件不存在" << endl;
	}
	cout << "按任意键退出程序" << endl;
	char a = 0;
	cin >> a;
}

