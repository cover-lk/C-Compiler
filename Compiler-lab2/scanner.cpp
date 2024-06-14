#include "scanner.h"

vector<vector<Keyword>> token;
int flag;
void word_analyze()
{
    flag=0;
    vector<Keyword>::iterator key=kw_list.begin();
    while(key!=kw_list.end())
    {
        vector<Keyword> x;
        while(true)
        {
            if((*key).type==6||(*key).type==7)// { }
            {
                Keyword k;
                k.type=(*key).type;
                k.str_value=(*key).str_value;
                x.push_back(k);
                key++;
                break;
            }
            else if((*key).type==35)// ;
            {
                key++;
                break;
            }
            else if((*key).type==37)// number
            {
                Keyword k;
                k.type=(*key).type;
                k.num_value=(*key).num_value;
                x.push_back(k);
                key++;
            }
            else if((*key).type==5) //println_int
            {
                flag=1;
                Keyword k;
                k.type=(*key).type;
                k.str_value=(*key).str_value;
                x.push_back(k);
                key++;
            }
            else if((*key).type>0&&(*key).type<37)// 变量
            {
                Keyword k;
                k.type=(*key).type;
                k.str_value=(*key).str_value;
                x.push_back(k);
                key++;
            }
            
        }
        token.push_back(x);
    }
}
