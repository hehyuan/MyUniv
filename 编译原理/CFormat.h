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
static int blocks = 0; //用于设置margin
static int signal = 0; // 用于考虑缩进的信号
string lastWord = " ";
void initCFormat(ifstream &fread) {
	getword(fread);
	lastWord = word;
}
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
	if (lastWord == "{" || lastWord == "}") {
		if (lastWord == "}")signal = -1;
		if (lastWord == "{")signal = 1;
		putLineAndMargin(fwrite);
		fwrite << lastWord;
		if (!(lastWord == "}" && word == "}")) {
			if (!(lastWord == "}" && word == ";"))
				putLineAndMargin(fwrite);
		}
		else {
			blocks += signal;
			signal = 0;
		}
	}
	else if (lastWord == ";") {
		fwrite << lastWord;
		if (!(word == "}")) {
			putLineAndMargin(fwrite);
		}
		else {
			blocks += signal;
			signal = 0;
		}
	}
	else if (lastWord == "int" || lastWord == "if" || lastWord == "while" || lastWord == "do") {
		fwrite << lastWord << space;
	}
	else {
		fwrite << lastWord << space;
	}
	lastWord = word;
}
void prettyCode(string src,string dir) {
	ifstream fread(src, ios::in);
	fread.seekg(0, ios::beg);
	ofstream fwrite(dir, ios::out);
	initCFormat(fread);
	while (!fread.eof()) {
		oneTurn(fread, fwrite);
	}
	oneTurn(fread, fwrite);
	fread.close(), fwrite.close();
}
#endif // !CFORMAT_H

