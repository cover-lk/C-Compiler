#pragma once
#include"keyword.h"
#include<map>
#include <algorithm>

extern vector<vector<Keyword>> token;

extern map<string,vector<string>> func_in_var;
extern map<string,vector<string>> func_var;
extern vector<string> function_list;



extern int flag;

void word_analyze();

void func_var_num();


