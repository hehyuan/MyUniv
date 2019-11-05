#pragma once
#include"GetWord.h"
#include<string>
using namespace std;
/*
	用e来代表空字符/epsion
*/


// <程序> ::= main(){<主函数>}
void program() {

}

// <主函数> ::=<变量说明部分> ; <语句部分>
void mainFunction() {

}

// <变量说明部分> ::= <变量说明> <标识符表>
void variableDiscribePart() {

}

// <变量说明> ::= int
void variableDiscribe() {

}

// <标识符表> ::= <标识符><标识符表1>
void identSheet() {

}

//<标识符表1> ::= , <标识符><标识符表1> | e
void identSheet1() {

}

//<语句部分> ::= <语句><语句部分1>
void sentencePart() {

}

//<语句部分1> ::= ;<语句><语句部分1> | e 
void sentencePart1() {

}

//<语句> ::=<赋值语句> | <条件语句> | <循环语句>
void sentence() {

}

//<赋值语句> ::=<标识符> = <表达式>
void assumeSentence() {

}

//<条件> ::= <表达式><关系运算符><表达式>
void condition() {

}

// <表达式> ::=<项><表达式1>
void expression() {

}

//<表达式1> ::= <加法运算符><项><表达式1> | e
void expression1() {

}

//<项> ::= <因子><项1>
void term() {

}

//<项1> ::=<乘法运算符><因子><项1> | e
void term1() {

}

// <因子> ::= <标识符>|<常量>|(<表达式>)
void factor() {

}

// <复合语句> ::= {<语句部分>}
void complexSentence() {

}

// <语句1> ::= <语句>|<复合语句>
void sentence1() {

}

// <条件语句> ::= if(<条件>) <语句1> else <语句1>
void conditionSentence() {

}

// <循环语句> ::= while(<条件>)do<语句1>
void loopSentence() {

}