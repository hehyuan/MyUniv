#pragma once
#ifndef LL_H
#define LL_H
#include"GetWord.h"
#include<string>
using namespace std;
/*
	用e来代表空字符/epsion
*/

//枚举可能出现的语法错误
enum errorType {
	variableDiscribeError,
	fenhaoError,
	kuohaoError,
	keyWordError,
	assumeError,
	ifError,
	whileError,
};
string errorString[] = {
	"变量说明错误,应该是int型",
	"缺少;",
	"括号不全!",
	"关键词错误!",
	"不是正确的赋值语句!",
	"缺少else!",
	"缺少do!",
};
void error() {	
	cout << "Error!" << endl;
	cout << nowline << "^" << word << "\t At row: " << row << endl;
}
void error(string e) {
	cout << "Error:" << e << endl;
	cout << nowline << "^" << word << "\t At row: " << row << endl;
}
//定义开始

// <程序> ::= main(){<主函数>}
void program(ifstream& fread);
// <主函数> ::=<变量说明部分> ; <语句部分>
void mainFunction(ifstream& fread);
// <变量说明部分> ::= <变量说明> <标识符表>
void variableDiscribePart(ifstream& fread);
// <变量说明> ::= int
void variableDiscribe(ifstream& fread);
// <标识符表> ::= <标识符><标识符表1>
void identSheet(ifstream& fread);
//<标识符表1> ::= , <标识符><标识符表1> | e
void identSheet1(ifstream& fread);
//<标识符> 通过getword来判断
void identity(ifstream& fread);
//<语句部分> ::= <语句><语句部分1>
void sentencePart(ifstream& fread);
//<语句部分1> ::= ;<语句><语句部分1> | e 
void sentencePart1(ifstream& fread);
//<语句> ::=<赋值语句> | <条件语句> | <循环语句>
void sentence(ifstream& fread);
//<赋值语句> ::=<标识符> = <表达式>
void assumeSentence(ifstream& fread);
//<条件> ::= <表达式><关系运算符><表达式>
void condition(ifstream& fread);
//<关系运算符> 通过getword来得到
void relationOp(ifstream &fread);
// <表达式> ::=<项><表达式1>
void expression(ifstream& fread);
//<表达式1> ::= <加法运算符><项><表达式1> | e
void expression1(ifstream& fread);
//<加法运算符> 由getword得到
void plusOp(ifstream& fread);
//<项> ::= <因子><项1>
void term(ifstream& fread);
//<项1> ::=<乘法运算符><因子><项1> | e
void term1(ifstream& fread);
//<乘法运算符> 由getword得到
void multiOp(ifstream& fread);
// <因子> ::= <标识符>|<常量>|(<表达式>)
void factor(ifstream& fread);
//<常量> 由getword得到
void constVal(ifstream& fread);
// <复合语句> ::= {<语句部分>}
void complexSentence(ifstream& fread);
// <语句1> ::= <语句>|<复合语句>
void sentence1(ifstream& fread);
// <条件语句> ::= if(<条件>) <语句1> else <语句1>
void conditionSentence(ifstream& fread);
// <循环语句> ::= while(<条件>)do<语句1>
void loopSentence(ifstream& fread);

//定义结束
//
//
//
inline void program(ifstream& fread) {
	cout << "开始规约<程序>" << endl;
	getword(fread);
	if (word == "main") {
		getword(fread);
		if (word == "(") {
			getword(fread);
			if (word == ")") {
				getword(fread);
				if (word == "{") {
					getword(fread);//在进入主函数部分之前先取得一个单词
					mainFunction(fread);
					//在主函数中返回的时候已经取得了下一个单词了
					if (word == "}") {
						cout << "规约到<程序>" << endl;
						getword(fread);
						return;
					}
					else error(errorString[kuohaoError]);
				}
				else error(errorString[kuohaoError]);
			}
			else error(errorString[kuohaoError]);
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[keyWordError]);
}

inline void mainFunction(ifstream& fread) {
	cout << "开始规约<主函数>" << endl;
	variableDiscribePart(fread);
	if (word == ";") {
		getword(fread);
		sentencePart(fread);
		cout << "归约到<主函数>" << endl;
	}
	else {
		error(errorString[fenhaoError]);
	}
}

inline void variableDiscribePart(ifstream& fread) {
	cout << "开始规约<变量说明部分>" << endl;
	variableDiscribe(fread);
	identSheet(fread);
	cout << "规约到<变量说明部分>" << endl;
}

inline void variableDiscribe(ifstream& fread) {
	cout << "开始规约<变量说明>" << endl;
	if (word == "int") {
		getword(fread);
		cout << "归约到<变量说明>" << endl;
	}
	else error(errorString[variableDiscribeError]);
}

inline void identSheet(ifstream& fread) {
	cout << "开始规约<标识符表>" << endl;
	identity(fread);
	identSheet1(fread);
	cout << "归约到<标识符表>" << endl;
}

inline void identSheet1(ifstream& fread) {
	cout << "开始规约<标识符表1>" << endl;
	if (word == ",") {
		getword(fread);
		identity(fread);
		identSheet1(fread);
		cout << "规约到<标识符表1>" << endl;
	}
	else cout << "规约到<标识符表1>" << endl;
}

inline void identity(ifstream& fread) {
	cout << "开始规约<标识符>" << endl;
	//当前读取的单词的类型为标识符
	if (sym == ident) {
		getword(fread);
		cout << "归约到<标识符>" << endl;
		return;
	}
	else error();
}

inline void sentencePart(ifstream& fread)
{
	cout << "开始规约<语句部分>" << endl;
	sentence(fread);
	sentencePart1(fread);
	cout << "归约到<语句部分>" << endl;
}

inline void sentencePart1(ifstream& fread)
{
	cout << "开始规约<语句部分1>" << endl;
	if (word == ";") {
		getword(fread);
		sentence(fread);
		sentencePart1(fread);
		cout << "归约到<语句部分1>" << endl;
	}
	else if (word != "}") {
		error(errorString[fenhaoError]);
	}
	else cout << "归约到<语句部分1>" << endl;
}

inline void sentence(ifstream& fread)
{
	cout << "开始归约<语句>" << endl;
	//FIRST(赋值语句)={<标识符>}	FIRST(条件语句)={'if'}	FIRST(循环语句)={'while'}
	if (sym==ident) {
		assumeSentence(fread);
		cout << "归约到<语句>" << endl;
	}
	else if (word == "if") {
		conditionSentence(fread);
		cout << "归约到<语句>" << endl;
	}
	else if (word == "while") {
		loopSentence(fread);
		cout << "归约到<语句>" << endl;
	}
	else error();
}

inline void assumeSentence(ifstream& fread)
{
	cout << "开始归约<赋值语句>" << endl;
	identity(fread);
	if (word == "=") {
		getword(fread);
		expression(fread);
		cout << "归约到<赋值语句>" << endl;
	}
	else error(errorString[assumeError]);
}

inline void condition(ifstream& fread)
{
	cout << "开始规约<条件>" << endl;
	expression(fread);
	relationOp(fread);
	expression(fread);
	cout << "归约到<条件>" << endl;
}

inline void relationOp(ifstream &fread)
{
	cout << "开始规约<关系运算符>" << endl;
	/*
	neq,// !=
	eq,// ==
	leq,// <=
	lt,//<
	geq,// >=
	gt,//>
	*/
	if (sym >= neq && sym <= gt) {
		getword(fread);
		cout << "归约到<关系运算符>" << endl;
	}
	else error();
}

inline void expression(ifstream& fread)
{
	cout << "开始归约<表达式>" << endl;
	term(fread);
	expression1(fread);
	cout << "归约到<表达式>" << endl;
}

inline void expression1(ifstream& fread)
{
	cout << "开始规约<表达式1>" << endl;
	if (sym == pls || sym == mins) {
		plusOp(fread);
		term(fread);
		expression1(fread);
	}
	cout << "规约到<表达式1>" << endl;
}

inline void plusOp(ifstream& fread)
{
	if (sym == pls || sym == mins) {
		getword(fread);
	}
	else error();
}

inline void term(ifstream& fread)
{
	cout << "开始规约<项>" << endl;
	factor(fread);
	term1(fread);
	cout << "规约到<项>" << endl;
}

inline void term1(ifstream& fread)
{
	cout << "开始规约<项1>" << endl;
	if (sym == times || sym == divide) {
		multiOp(fread);
		factor(fread);
		term1(fread);
	}
	cout << "规约到<项1>" << endl;
}

inline void multiOp(ifstream& fread)
{
	if (sym == times || sym == divide) {
		getword(fread);
	}
	else error();
}

inline void factor(ifstream& fread)
{
	cout << "开始规约<因子>" << endl;
	if (sym == ident) {
		identity(fread);
		cout << "规约到<因子>" << endl;
	}
	else if (sym == number) {
		constVal(fread);
	}
	else if (word == "(") {
		getword(fread);
		expression(fread);
		if (word == ")") {
			getword(fread);
			cout << "归约到<因子>" << endl;
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[kuohaoError]);
}

inline void constVal(ifstream& fread)
{
	if (sym == number) {
		getword(fread);
		cout << "归约到<常量>" << endl;
	}
	else error();
}

inline void complexSentence(ifstream& fread)
{
	if (word == "{") {
		getword(fread);
		sentencePart(fread);
		if (word == "}") {
			getword(fread);
			cout << "归约到<复合语句>" << endl;
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[kuohaoError]);
}

inline void sentence1(ifstream& fread)
{
	if (word == "{") {
		complexSentence(fread);
	}
	else {
		sentence(fread);
	}
	cout << "规约到 <语句1>" << endl;
}

inline void conditionSentence(ifstream& fread)
{
	if (word == "if") {
		getword(fread);
		if (word == "(") {
			getword(fread);
			condition(fread);
			if (word == ")") {
				getword(fread);
				sentence1(fread);
				if (word == "else") {
					getword(fread);
					sentence1(fread);
					cout << "归约到<条件语句>" << endl;
				}
				else error(errorString[ifError]);
			}
			else error(errorString[kuohaoError]);
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[keyWordError]);
}

inline void loopSentence(ifstream& fread)
{
	if (word == "while") {
		getword(fread);
		if (word == "(") {
			getword(fread);
			condition(fread);
			if (word == ")") {
				getword(fread);
				if (word == "do") {
					getword(fread);
					sentence1(fread);
					cout << "归约到<循环语句>" << endl;
				}
				else error(errorString[whileError]);
			}
			else error(errorString[kuohaoError]);
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[keyWordError]);
}


#endif