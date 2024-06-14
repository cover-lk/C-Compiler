#pragma once
#include<string>
#include<vector>

using namespace std;

/*
0是数字number
1是变量名id
2是符号op
3是函数名func
4是return
5是类型type
6是段落终结符     "}"
7是函数声明终结符
8是函数使用终结符 ")"
9是句子终结符    ";"
10是运算式终结符
11是参数终结符
*/
struct Keyword 
{
    int type=-1;
    int num_value=0;
    string str_value="";
};

extern vector<Keyword> kw_list;






