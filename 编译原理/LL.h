#pragma once
#ifndef LL_H
#define LL_H
#include"GetWord.h"
#include<string>
#include<vector>
#include<stack>
using namespace std;

//	用e来代表空字符/epsion

//枚举可能出现的语法错误
enum errorType {
	variableDiscribeError,
	fenhaoError,
	kuohaoError,
	keyWordError,
	assumeError,
	ifError,
	whileError,
	otherError,
	identifiError,
};
string errorString[] = {
	"变量说明错误,应该是int型",
	"缺少;",
	"括号不全!",
	"关键词错误!",
	"不是正确的赋值语句!",
	"缺少else!",
	"缺少do!",
	"多加了;!",//otherError
	"未定义的标识符"
};
vector<identsheetTemplate> idSheet;
bool canDefineId = false;
bool hasError = false;
long long int addnow = 0x0000;
long long int countId = 0;
void error() {	
	hasError = true;
	cout << "Error!" << endl;
	cout << nowline << "^" << word << "\t At row: " << row << endl;
}
void error(string e) {
	hasError = true;
	cout << "Error:" << e << endl;
	cout << nowline << "^" << word << "\t At row: " << row << endl;
}
stack<string>rgister;
string to_register(int i) {
	return string("r") + to_string(i);
}
//初始化寄存器所在的栈
void rgisterInit() {
	for (int i = 35; i>=0; --i) {
		rgister.push(to_register(i));
	}
}
// 从栈中获得一个寄存器
//如果此时的栈已经空,则返回“\0”
string getRgister() {
	string res = "\0";
	if (!rgister.empty()) {//如果栈不空
		res = rgister.top();
		rgister.pop();
	}
	return res;
}

//将用完的寄存器送回栈中
void giveBackRgister(string str) {
	rgister.push(str);
}

//定义一个用于存放表达式所需用到的结构体
struct expressBean {
	string code;//存放代码
	string place;//存放地址,有可能是寄存器,也有可能是存储地址
};

//从标识符的表中找到标识符的地址
unsigned int getAddress(string id) {
	int indx = -1;
	for (int i = 0; i < idSheet.size(); ++i) {
		if (id == idSheet[i].name) {
			indx = idSheet[i].adress;
			break;
		}
	}
	return indx;
}

//定义开始

// <程序> ::= main(){<主函数>}
string program(ifstream& fread);
// <主函数> ::=<变量说明部分> ; <语句部分>
string mainFunction(ifstream& fread);
// <变量说明部分> ::= <变量说明> <标识符表>
void variableDiscribePart(ifstream& fread);
// <变量说明> ::= int
void variableDiscribe(ifstream& fread);
// <标识符表> ::= <标识符><标识符表1>
void identSheet(ifstream& fread);
//<标识符表1> ::= , <标识符><标识符表1> | e
void identSheet1(ifstream& fread);
//<标识符> 通过getword来判断
string identity(ifstream& fread);
//<语句部分> ::= <语句><语句部分1>
string sentencePart(ifstream& fread);
//<语句部分1> ::= ;<语句><语句部分1> | e 
string sentencePart1(ifstream& fread);
//<语句> ::=<赋值语句> | <条件语句> | <循环语句>
string sentence(ifstream& fread);
//<赋值语句> ::=<标识符> = <表达式>
string assumeSentence(ifstream& fread);
//<条件> ::= <表达式><关系运算符><表达式>
string condition(ifstream& fread); //TODO
//<关系运算符> 通过getword来得到
string relationOp(ifstream &fread);
// <表达式> ::=<项><表达式1>
expressBean expression(ifstream& fread);
//<表达式1> ::= <加法运算符><项><表达式1> | e
expressBean expression1(ifstream& fread, string &place);
//<加法运算符> 由getword得到
void plusOp(ifstream& fread);
//<项> ::= <因子><项1>
expressBean term(ifstream& fread);
//<项1> ::=<乘法运算符><因子><项1> | e
expressBean term1(ifstream& fread, string &place);
//<乘法运算符> 由getword得到
void multiOp(ifstream& fread);
// <因子> ::= <标识符>|<常量>|(<表达式>)
expressBean factor(ifstream& fread);
//<常量> 由getword得到
string constVal(ifstream& fread);
// <复合语句> ::= {<语句部分>}
string complexSentence(ifstream& fread);
// <语句1> ::= <语句>|<复合语句>
string sentence1(ifstream& fread);
// <条件语句> ::= if(<条件>) <语句1> else <语句1>
string conditionSentence(ifstream& fread);
// <循环语句> ::= while(<条件>)do<语句1>
string loopSentence(ifstream& fread);

//定义结束
//
//
//
inline string program(ifstream& fread) {
	string code;
	rgisterInit();
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
					code = mainFunction(fread);  //程序的目标代码就等于主函数的目标代码
					//在主函数中返回的时候已经取得了下一个单词了
					if (word == "}") {
						cout << "规约到<程序>" << endl;
						getword(fread);
						return code;
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
	return "生成目标代码失败";
}

inline string mainFunction(ifstream& fread) {
	string code;
	cout << "开始规约<主函数>" << endl;
	canDefineId = true;
	variableDiscribePart(fread); //主函数的第一部分,变量声明(在目标代码中不体现)
	canDefineId = false;
	if (word == ";") {
		getword(fread);
		code = sentencePart(fread);//主函数的目标代码就相当于语句部分的目标代码
		cout << "归约到<主函数>" << endl;
		return code;
	}
	else {
		error(errorString[fenhaoError]);
		return "Error:主函数目标代码生成失败\n";
	}
}

inline void variableDiscribePart(ifstream& fread) {
	cout << "开始规约<变量说明部分>" << endl;
	variableDiscribe(fread);
	if (hasError != true) {
		identSheet(fread);
	}
	else {//尝试从错误中恢复，舍弃掉其他部分
		while (word != ";" && word != "}" && !fread.eof()) {
			getword(fread);
		}
		hasError = false;//最后记得把标志恢复，便于后续的查错
	}
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
	string id =identity(fread);
	identSheet1(fread);
	cout << "归约到<标识符表>" << endl;
}

inline void identSheet1(ifstream& fread) {
	cout << "开始规约<标识符表1>" << endl;
	if (word == ",") {
		getword(fread);
		string id =identity(fread);
		identSheet1(fread);
		cout << "规约到<标识符表1>" << endl;
	}
	else cout << "规约到<标识符表1>" << endl;
}

inline string identity(ifstream& fread) {//返回标识符的id,用于赋值、计算等
	string id = "";
	cout << "开始规约<标识符>" << endl;
	//当前读取的单词的类型为标识符
	if (sym == ident) {
		id = word;
		if (canDefineId == true) {//可以定义标识符
			identsheetTemplate temp(word,countId++, addnow+=2);
			idSheet.push_back(temp);
		}
		else {//此时不能定义标识符
			bool flag = 0;
			for (int i = 0; i < idSheet.size(); i++) {
				if (idSheet[i].name == word)
					flag = 1;
			}
			if(flag!=1)
				error(errorString[identifiError]);
		}
		getword(fread);
		cout << "归约到<标识符>" << endl;
		return id;
	}
	else error();
}

inline string sentencePart(ifstream& fread)
{
	string code;
	cout << "开始规约<语句部分>" << endl;
	code += sentence(fread);//<语句部分>的第一部分<语句>
	code += sentencePart1(fread);//<语句部分>的第二部分<语句部分1>
	cout << "归约到<语句部分>" << endl;
	return code;
}

inline string sentencePart1(ifstream& fread)
{
	string code = "";
	cout << "开始规约<语句部分1>" << endl;
	if (word == ";") {
		getword(fread);
		code += sentence(fread); //<语句部分1>的第一部分<语句>
		code += sentencePart1(fread);//<语句部分1>的第二部分<语句部分1>
		cout << "归约到<语句部分1>" << endl;
	}
	else if (word != "}") {
		error(errorString[fenhaoError]);
	}
	else cout << "归约到<语句部分1>" << endl;
	return code;
}

inline string sentence(ifstream& fread)
{
	string code = "";
	cout << "开始归约<语句>" << endl;
	//FIRST(赋值语句)={<标识符>}	FIRST(条件语句)={'if'}	FIRST(循环语句)={'while'}
	if (sym==ident) {
		code += assumeSentence(fread);//<语句>为<赋值语句>
		cout << "归约到<语句>" << endl;
	}
	else if (word == "if") {
		code += conditionSentence(fread);//<语句>为<条件语句>
		cout << "归约到<语句>" << endl;
	}
	else if (word == "while") {
		code += loopSentence(fread);//<语句>为<循环语句>
		cout << "归约到<语句>" << endl;
	}
	else error();
	if (hasError == true) {
		while (word != ";" && word != "}" && !fread.eof()) {//尝试排查错误，直到遇见分号，赋值语句结束或者遇到右括号
			getword(fread);
		}
		hasError = false;
	}
	return code;
}

inline string assumeSentence(ifstream& fread)
{
	string code = "";
	expressBean bean;
	cout << "开始归约<赋值语句>" << endl;
	string id  = identity(fread);
	if (word == "=") {
		getword(fread);
		bean = expression(fread); 
		code += bean.code;//首先将表达式的代码赋值给code
		unsigned int address = getAddress(id);//获得标识符的地址
		code += "\tsw "+id+","+bean.place+"\n";//将表达式的地址中的值赋给标识符
		cout << "归约到<赋值语句>" << endl;
		giveBackRgister(bean.place); // 释放寄存器
	}
	else { 
		error(errorString[assumeError]); 
	}
	return code;
}

inline string condition(ifstream& fread)
{
	expressBean bean, bean1;
	string op;
	string code;
	cout << "开始规约<条件>" << endl;
	bean = expression(fread);
	op = relationOp(fread);
	bean1 = expression(fread);
	code += bean.code;
	code += bean1.code;
	code += "\tJ" + op + "," + bean.place + "," + bean1.place + "\n";
	cout << "归约到<条件>" << endl;
	return code;
}

inline string relationOp(ifstream &fread)
{
	string op;
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
		op = word;
		getword(fread);
		cout << "归约到<关系运算符>" << endl;
	}
	else error();
	return op;
}

inline expressBean expression(ifstream& fread)
{
	expressBean bean,bean1, ans; // bean 接受来自<项>的返回值 ,bean1 接受来自<表达式1>的返回值
	cout << "开始归约<表达式>" << endl;
	bean = term(fread);
	bean1 = expression1(fread,bean.place);
	ans.code += bean.code;
	ans.code += bean1.code;
	ans.place = bean.place;	//令返回的地址为<项>的地址
	cout << "归约到<表达式>" << endl;
	return ans;
}

inline expressBean expression1(ifstream& fread, string &place)
{
	expressBean bean, bean1, ans;
	cout << "开始规约<表达式1>" << endl;
	if (sym == pls || sym == mins) {
		int sym1 = sym;
		plusOp(fread);
		bean = term(fread);
		ans.code += bean.code;
		if (sym1 == pls)
			ans.code += "\taddw " + place + "," + bean.place + "," + place + "\n";
		else if (sym1 == mins)
			ans.code += "\tminw " + place + "," + bean.place + "," + place + "\n";
		bean1 = expression1(fread,place);
		ans.code += bean1.code;
		ans.place = place;
	}
	cout << "规约到<表达式1>" << endl;
	return ans;
}

inline void plusOp(ifstream& fread)
{
	if (sym == pls || sym == mins) {
		getword(fread);
	}
	else error();
}

inline expressBean term(ifstream& fread)
{
	expressBean bean, bean1, ans;
	cout << "开始规约<项>" << endl;
	bean = factor(fread);
	bean1 = term1(fread, bean.place);
	ans.code += bean.code;
	ans.code += bean1.code;
	ans.place = bean.place;
	cout << "规约到<项>" << endl;
	return ans;
}

inline expressBean term1(ifstream& fread, string &place)
{
	expressBean bean, bean1, ans;
	cout << "开始规约<项1>" << endl;
	if (sym == times || sym == divide) {
		int sym1 = sym;
		multiOp(fread);
		bean = factor(fread);
		ans.code += bean.code;
		if (sym1 == times)
			ans.code += "\tmul " + place + "," + bean.place + "," + place + "\n";
		else if (sym1 == divide) 
			ans.code += "\tdiv " + place + "," + bean.place + "," + place + "\n";
		bean1 = term1(fread, place);
		ans.code += bean1.code;
		ans.place = place;
	}
	cout << "规约到<项1>" << endl;
	return ans;
}

inline void multiOp(ifstream& fread)
{
	if (sym == times || sym == divide) {
		getword(fread);
	}
	else error();
}

inline expressBean factor(ifstream& fread)
{
	expressBean bean, ans;
	cout << "开始规约<因子>" << endl;
	if (sym == ident) {
		string id = identity(fread);
		string rigster = getRgister();
		ans.code += "\tlw " +id + "," + rigster + "\n";
		ans.place = rigster;
		cout << "规约到<因子>" << endl;
	}
	else if (sym == number) {
		string val = constVal(fread);
		string rigster = getRgister();
		ans.code += "\taddi " + val + ",$zero," + rigster + "\n";
		ans.place = rigster;
	}
	else if (word == "(") {
		getword(fread);
		bean = expression(fread);
		if (word == ")") {
			ans.code = bean.code;
			ans.place = bean.place;
			getword(fread);
			cout << "归约到<因子>" << endl;
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[assumeError]);
	return ans;
}

inline string constVal(ifstream& fread)
{
	string val;
	if (sym == number) {
		val = word;
		getword(fread);
		cout << "归约到<常量>" << endl;
	}
	else error();
	return val;
}

inline string complexSentence(ifstream& fread)
{
	string code;
	if (word == "{") {
		getword(fread);
		code = sentencePart(fread);
		if (word == "}") {
			getword(fread);
			cout << "归约到<复合语句>" << endl;
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[kuohaoError]);
	return code;
}

inline string sentence1(ifstream& fread)
{
	string code;
	if (word == "{") {
		code = complexSentence(fread);
	}
	else {
		code = sentence(fread);
	}
	cout << "规约到 <语句1>" << endl;
	return code;
}

inline string conditionSentence(ifstream& fread)
{
	string code;
	string con;
	string sen, sen1;
	if (word == "if") {
		getword(fread);
		if (word == "(") {
			getword(fread);
			con = condition(fread);
			if (word == ")") {
				getword(fread);
				sen = sentence1(fread);
				if (word == "else") {
					getword(fread);
					sen1 = sentence1(fread);
					code += con;
					code += "\tJNZ A" + to_string(row) + "\n";
					code += sen1;
					code += "\tJMP QUIT" + to_string(row) + "\n";
					code += "A" + to_string(row) + " :\n" + sen;
					code += "QUIT" + to_string(row) + ":\n";
					cout << "归约到<条件语句>" << endl;
				}
				else if (word == ";") { 
					error(errorString[otherError]);
				}
				else error(errorString[ifError]);
			}
			else error(errorString[kuohaoError]);
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[keyWordError]);
	return code;
}

inline string loopSentence(ifstream& fread)
{
	string code, con, sen;
	if (word == "while") {
		getword(fread);
		if (word == "(") {
			getword(fread);
			con = condition(fread);
			if (word == ")") {
				getword(fread);
				if (word == "do") {
					getword(fread);
					sen = sentence1(fread);
					code += "IN" + to_string(row) + ":\n";
					code += con;
					code += "\tJNZ QUIT" + to_string(row) + "\n";
					code += sen;
					code += "\tJMP IN" + to_string(row) + "\n";
					code += "QUIT" + to_string(row) + ":\n";
					cout << "归约到<循环语句>" << endl;
				}
				else error(errorString[whileError]);
			}
			else error(errorString[kuohaoError]);
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[keyWordError]);
	return code;
}


#endif