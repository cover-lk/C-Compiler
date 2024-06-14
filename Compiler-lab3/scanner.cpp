#include "scanner.h"
#include<iostream>
vector<vector<Keyword>> token;
map<string,vector<string>> func_in_var;
map<string,vector<string>> func_var;
vector<string> function_list;


void word_analyze()
{
    vector<Keyword>::iterator key=kw_list.begin();
    while(key!=kw_list.end())
    {
        vector<Keyword> x;
        while(true)
        {
            Keyword* t; 
            if((*key).type==6||(*key).type==7||(*key).type==9)
            {
                Keyword k;
                k.type=(*key).type;
                k.str_value=(*key).str_value;
                x.push_back(k);
                key++;
                break;
            }   
            else
            {
                Keyword k;
                k.type=(*key).type;
                k.num_value=(*key).num_value;
                k.str_value=(*key).str_value;
                x.push_back(k);
                key++;
            }  
        }
        token.push_back(x);
    }

    func_var_num();
}


void func_var_num()
{
    int func_id=0;
    vector<vector<Keyword>>::iterator line=token.begin();
    while(line!=token.end())
    {
        
        if((*line)[0].type==5&&(*line)[1].type==3)
        {
            int flag=0;
            Keyword x=(*line)[1];
            function_list.push_back(x.str_value);
            for(Keyword key:(*line))
            {
                if(key.type==1)
                {
                    //cout<<x.str_value<<"  in_var "<<key.str_value<<endl;
                    func_in_var[x.str_value].push_back(key.str_value);
                }
            }
            line++;
            while(line!=token.end())
            {
                if((*line)[0].type==6)
                {
                    line++;
                    break;
                }
                if((*line)[0].type!=5)
                {
                    line++;
                    continue;
                }
                for(Keyword key:(*line))
                {
                    if(key.type==1&&std::count(func_var[x.str_value].begin(),func_var[x.str_value].end(),key.str_value)==0&&std::count(func_in_var[x.str_value].begin(),func_in_var[x.str_value].end(),key.str_value)==0)
                    {
                        //cout<<x.str_value<<"  var "<<key.str_value<<endl;
                        func_var[x.str_value].push_back(key.str_value);
                    }

                    if(key.type==6)
                    {
                        flag=1;
                        break;
                    }
                }
                line++;
                if(flag==1)
                    break;
            }
        }
    }

    /*map<string, vector<string>>::iterator it;
    for (it = func_var.begin(); it != func_var.end(); it++) {
        std::cout<<(*it).first<<(*it).second.size()<<endl;
    }
    std::cout<<"*******"<<endl;
    for (it = func_in_var.begin(); it != func_in_var.end(); it++) {
        std::cout<<(*it).first<<(*it).second.size()<<endl;
    }*/
}