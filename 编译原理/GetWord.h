#pragma once
#include <iostream>
#include<iomanip>
#include<algorithm>
#include<fstream>
#include<string>
#include<vector>
#define words_num 6
using namespace std;
enum symType {
	number,//数字
	ident,//标识符
	beginsym,//开始保留字:main
	Intsym,//int保留字
	Ifsym,//if
	elsesym,//else
	whilesym,//while
	dosym,//do
	comma,// ,
	semicolon,// ;
	lbrace,// {
	rbrace,// }
	lpar,// (
	rpar,// )
	neq,// !=
	becomes,// =
	leq,// <=
	lt,//<
	geq,// >=
	gt,//>
	eq,// ==
	pls,// +
	mins,// -
	times,// *
	divide,// /
};
//用C或C++语言编写一个简单的词法分析程序，扫描C语言小子集的源程序，
//根据给定的词法规则，识别单词，填写相应的表。如果产生词法错误，
//则显示错误信息、位置，并试图从错误中恢复。
//简单的恢复方法是忽略该字符（或单词）重新开始扫描。
string words[words_num];//保留字表,由于该C语言小子集的保留字只有6个，故而线性查找比二分查找更快,不需要按照字典序排列
symType wsym[words_num];//保留字的种别,用于说明保留字的类型

//标识符表的类
struct identsheetTemplate {
public:
	string name;
	int number;
	string type;
	int adress;
	
};
identsheetTemplate identsheet[100];//标识符的表，用于存放标识符的编号,类型和地址
int row;//全局变量,存储当前读取字符所在的行
symType sym;//全局变量,用于说明当前读取的单词的类型
int addressnow = 0x80;//预定的初始标识符所在的地址
int numbernow = 1;//预定的初始标识符的编号
char ch;//用于单个字符读取的变量
int Num_of_idents;//当前读取的标识符的数量
string word;//单个字符汇集成的单词
void output() {
	int value = -1;
	//当前的单词为标识符
	if (sym == ident) {
		for (int i = 0; i < Num_of_idents; i++) {
			if (word == identsheet[i].name)
				value = identsheet[i].adress;
		}
	}
	//当前的单词为数字
	if (sym == number) {
		value = stoi(word);
	}
	//如果当前的单词为标识符或是数字
	if (value > 0) {
		cout << right << "[ '" << word << "', " << value << "]" << endl;
		//cout << right << "[ " << sym << ", " << value << "]" << endl;
	}
	else {
		cout << right << "[ '" << word << "', " << '-' << "]" << endl;
		//cout << right << "[ " << sym << ", " << '-' << "]" << endl;
	}
}
//判断这个字符是否是分界符:空格,换行,逗号,分号,大括号,小括号
bool Is_IsolateSym(char ch) {
	if (ch == ' ' || ch == '\n' || ch == ',' || ch == '(' || ch == ')' || ch == ';' || ch == '{' || ch == '}')
		return true;
	return false;
}

//判断这个字符是否为小写字母
bool Is_lowerLetter(char ch) {
	if (ch >= 'a' && ch <= 'z')
		return true;
	return false;
}

//判断这个字符是否为数字
bool Is_Number(char ch) {
	if (ch >= '0' && ch <= '9')
		return true;
	return false;
}

//从待编译的程序中获得一个单词
void getword(ifstream& fread) {
	word.clear();//先清空当前的单词
	//如果ch还没赋值,则取一个字符
	if (!ch) {
		ch = fread.get();
	}
	//去掉空格
	while (ch == ' ') {
		ch = fread.get();
	}
	//读到一个换行符,row增加
	if (ch == '\n') {
		row++;
		ch = fread.get();//再读一个字符
	}
	//读取的是一个小写字母
	if (Is_lowerLetter(ch)) {
		while (true) {
			//读取的还是小写字母或是数字
			if (Is_lowerLetter(ch) || Is_Number(ch)) {
				word.push_back(ch);//加入word中
			}
			//读取其他字符,单词结束
			else {
				sym = ident;//word的类型为标识符或是保留字
				//在保留字中线性查找
				for (int i = 0; i < words_num; i++) {
					if (word == words[i]) {
						sym = wsym[i];
						break;
					}
				}
				//标识符
				if (sym == ident) {
					int flag = 1;
					//判断当前标识符是否已经在表中
					for (int i = 0; i <= Num_of_idents; i++) {
						if (word == identsheet[i].name)
							flag = 0;
					}
					if (flag) {
						identsheet[Num_of_idents].name = word;//标识符的名字
						identsheet[Num_of_idents].adress = addressnow++;//标识符的地址
						identsheet[Num_of_idents].number = numbernow++;//标识符的编码
						identsheet[Num_of_idents].type = number;//标识符的类型，这里的类型只有int
						Num_of_idents++;
					}
				}
				return;
			}
			ch = fread.get();
		}
	}
	//读取到数字
	if (Is_Number(ch)) {
		while (true) {
			//仍是数字
			if (Is_Number(ch)) {
				word.push_back(ch);
			}
			//读入分界符
			else if (Is_IsolateSym(ch)) {
				sym = number;
				return;
			}
			//非法
			else {
				cout << '\a' << "unsupport identifier at row:" << row << endl;
				cout << "ignore: " << ch << endl;
				ch = fread.get();
			}
			ch = fread.get();
		}
	}
	//读到分界符(不包括空格和换行)
	if (Is_IsolateSym(ch)) {
		word.push_back(ch);
		//逗号
		if (ch == ',') {
			sym = comma;
		}
		//分号
		if (ch == ';') {
			sym = semicolon;
		}
		//左大括号
		if (ch == '{') {
			sym = lbrace;
		}
		//右大括号
		if (ch == '}') {
			sym = rbrace;
		}
		//左小括号
		if (ch == '(') {
			sym = lpar;
		}
		//右小括号
		if (ch == ')') {
			sym = rpar;
		}
		ch = fread.get();
		return;
	}
	//读到=
	if (ch == '=') {
		word.push_back(ch);
		sym = becomes;
		ch = fread.get();
		//又读到一个=号,变为等于判断
		if (ch == '=') {
			word.push_back(ch);
			sym = eq;
			ch = fread.get();
			return;
		}
		else return;
	}
	//读到!
	if (ch == '!') {
		word.push_back(ch);
		ch = fread.get();
		//又读到=，变为不等于判断
		if (ch == '=') {
			word.push_back(ch);
			sym = neq;
			ch = fread.get();
			return;
		}
		//读入除了=以外的字符都无法得到有效的程序语句
		else {
			cout << '\a' << "Error !\n unidentify symbol  at row " << row << endl;
		}
	}
	//读到>
	if (ch == '>') {
		word.push_back(ch);
		sym = gt;
		ch = fread.get();
		//读到=，变为大于等于
		if (ch == '=') {
			word.push_back(ch);
			sym = geq;
			ch = fread.get();
			return;
		}
		else return;
	}
	//读到<
	if (ch == '<') {
		word.push_back(ch);
		sym = lt;
		ch = fread.get();
		//读到=，变为小于等于
		if (ch == '=') {
			word.push_back(ch);
			ch = fread.get();
			sym = leq;
			return;
		}
		else return;
	}
	//读到+
	if (ch == '+') {
		word.push_back(ch);
		ch = fread.get();
		sym = pls;
		return;
	}
	//读到-
	if (ch == '-') {
		word.push_back(ch);
		ch = fread.get();
		sym = mins;
		return;
	}
	//读到*
	if (ch == '*') {
		word.push_back(ch);
		ch = fread.get();
		sym = times;
		return;
	}
	//读到/
	if (ch == '/') {
		word.push_back(ch);
		ch = fread.get();
		sym = divide;
		return;
	}
}
void init() {
	words[0] = "main";	wsym[0] = beginsym;
	words[1] = "int";		wsym[1] = Intsym;
	words[2] = "if";		wsym[2] = Ifsym;
	words[3] = "else";	wsym[3] = elsesym;
	words[4] = "while";	wsym[4] = whilesym;
	words[5] = "do";		wsym[5] = dosym;
	row = 1;
}

