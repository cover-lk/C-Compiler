#pragma once
#include"scanner.h"
#include<iostream>
#include <stack>
#include<map>

struct Variable
{
    string name;
    int num;
    int value;
};

int findvar(vector<Variable> in,string s);
int getPriority(string op);
void code_out();
int postfix_out(vector<Keyword>& in,vector<Variable>& V);
void infixToPostfix(vector<Keyword>& in,vector<Keyword>& out);
