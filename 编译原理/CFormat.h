#pragma once
#ifndef CFORMAT_H
#define CFORMAT_H
#include"GetWord.h"
#include<istream>
#include<fstream>
#include<iostream>
#include<string>
using namespace std;
const char* margin = "    ";
const char* space = " ";
static int blocks = 0;
static int signal = 0;
string lastWord = " ";
void putLineAndMargin(ostream& fwrite) {
	fwrite << endl;	//putLine
		//putMargin
	int temp = blocks;
	if (signal < 0)
		temp += signal;
	while ((temp--) > 0)// 输出margin,按照嵌套的层数来执行
		fwrite << margin;
	blocks += signal;
	signal = 0;
}
void oneTurn(ifstream& fread, ofstream& fwrite) {
	getword(fread);
	if (word == "{" || word == "}") {
		if (word == "}")signal = -1;
		if (word == "{")signal = 1;
		putLineAndMargin(fwrite);
		fwrite << word;
		putLineAndMargin(fwrite);
	}
	else if (word == ";") {
		fwrite << word;
		putLineAndMargin(fwrite);
	}
	else if (word == "int" || word == "if" || word == "while" || word == "do") {
		fwrite << word << space;
	}
	else {
		fwrite << word << space;
	}
	lastWord = word;
}
void prettyCode(string src,string dir) {
	ifstream fread(src, ios::in);
	ofstream fwrite(dir, ios::out);
	while (!fread.eof()) {
		oneTurn(fread, fwrite);
	}
	fread.close(), fwrite.close();
}
#endif // !CFORMAT_H

