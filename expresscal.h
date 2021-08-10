#pragma once
#include"Poly.h"
#include<unordered_map>
#include<stack>
#include<string>
#include<iostream>
#include<vector>
#include<any>
using namespace std;
typedef int status;
typedef char ElemType;
void getfmt(string &s) {
	for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] == '+' || s[i] == '-') {
			if (i == 0) {
				s.insert(0, 1, '0');
			}
			else if (s[i - 1] == '(') {
				s.insert(i, 1, '0');
			}
		}
	}
}

int Priority(char c) {
	switch (c)
	{
	case'+':
	case'-':return 1;
	case'*':
	case'/':return 2;
	case'^':return 3;
	default:
		return 0;
	}
}

void getPostfix(vector<string>& postfix, string& infix) {
	string tmp;
	stack<char> opstack;
	for (int i = 0; i < infix.size(); i++) {
		tmp = "";
		switch (infix[i])
		{
		case'+':
		case'-':
		case'*':
		case'/':
		case'^':
			if (opstack.empty() || opstack.top() == '(' || opstack.top() == '[' || opstack.top() == '{') {
				opstack.push(infix[i]);
			}
			else {
				while (!opstack.empty() && (Priority(opstack.top()) >= Priority(infix[i]))) {
					tmp += opstack.top();
					postfix.push_back(tmp);
					opstack.pop();
					tmp = "";
				}
				opstack.push(infix[i]);
			}
			break;
		case'(':
		case'[':
		case'{':
			opstack.push(infix[i]);
			break;
		case')':
			while (!opstack.empty() && opstack.top() != '(') {
				tmp += opstack.top();
				postfix.push_back(tmp);
				tmp = "";
				opstack.pop();
			}
			if (!opstack.empty() && opstack.top() == '(') {
				opstack.pop();							
			}
			break;
		case']':
			while (!opstack.empty() && opstack.top() != '[') {
				tmp += opstack.top();
				postfix.push_back(tmp);
				tmp = "";
				opstack.pop();
			}
			if (!opstack.empty() && opstack.top() == '[') {
				opstack.pop();
			}
			break;
		case'}':
			while (!opstack.empty() && opstack.top() != '{') {
				tmp += opstack.top();
				postfix.push_back(tmp);
				tmp = "";
				opstack.pop();
			}
			if (!opstack.empty() && opstack.top() == '{') {
				opstack.pop();
			}
			break;
		case'x':
			tmp += infix[i];
			postfix.push_back(tmp);
			break;
		default:
			if (infix[i] >= '0' && infix[i] <= '9') {
				tmp += infix[i];
				while (i + 1 < infix.size() && infix[i + 1] >= '0' && infix[i + 1] <= '9' || infix[i + 1] == '.') {
					tmp += infix[i + 1];
					i++;
				}
			}
			if (tmp[tmp.size() - 1] == '.')tmp += '0';
			postfix.push_back(tmp);
			break;
		}
	}
	while (!opstack.empty()) {
		tmp = "";
		tmp += opstack.top();
		postfix.push_back(tmp);
		opstack.pop();
	}
}

Poly getresult(vector<string> postfix) {
	Poly number;
	Poly n1 = 0, n2 = 0;
	Poly res = 0;
	stack<Poly> numstack;
	for (int i = 0; i < postfix.size(); i++) {
		string tmp = postfix[i];
		if (tmp[0] >= '0' && tmp[0] <= '9') {
			number = atof(tmp.c_str());
			numstack.push(number);
		}
		else if (tmp[0] == 'x') {
			number = Poly(1,'x');
			numstack.push(number);
		}
		else if (tmp[0] == '+') {
			n1 = numstack.top();
			numstack.pop();
			n2 = numstack.top();
			numstack.pop();
			numstack.push(n2 + n1);
		}
		else if (tmp[0] == '-') {
			n1 = numstack.top();
			numstack.pop();
			n2 = numstack.top();
			numstack.pop();
			numstack.push(n2 - n1);
		}
		else if (tmp[0] == '*') {
			n1 = numstack.top();
			numstack.pop();
			n2 = numstack.top();
			numstack.pop();
			numstack.push(n2*n1);
		}
/*		else if (tmp[0] == '/') {
			n1 = numstack.top();
			numstack.pop();
			n2 = numstack.top();
			numstack.pop();
			numstack.push(n2/n1);
		}*/
		else if (tmp[0] == '^') {
			n1 = numstack.top();
			numstack.pop();
			n2 = numstack.top();
			numstack.pop();
			numstack.push(n2 ^(n1.int_part()));
		}
	}
	if (!numstack.empty())res = numstack.top();
	return res;
}
void _main_() {
	vector<string> Postfix;
	string Infix;
	Poly res;
	cout << ">>>";
	cin >> Infix;
	getfmt(Infix);
	getPostfix(Postfix, Infix);
	res=getresult(Postfix);
	cout << res;
}

void outofmemory_test(){
	static int i = 1;
	Poly p1(i);
	Poly p2(i);
	p1 - p2;
	i++;
}