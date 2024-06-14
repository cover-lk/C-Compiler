#pragma once
#include<string>
#include<vector>

using namespace std;

struct Keyword
{
    int type=-1;
    int num_value=0;
    string str_value="";
};
extern vector<Keyword> kw_list;






