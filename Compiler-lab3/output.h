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


int find_var(string s);//查找局部变量
int find_in_var(string s);//查找入参
void calculate(vector<Keyword>);
int func_cal(vector<Keyword>);
int is_InOrOut(string in); //1是函数入参，2是函数局部变量

int findvar(vector<Variable> in,string s);
int getPriority(string op);
void code_out();
int postfix_out(vector<Keyword>& in,vector<Variable>& V);
void infixToPostfix(vector<Keyword>& in,vector<Keyword>& out);
