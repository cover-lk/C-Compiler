#include <iostream>
#include"output.h"
#include"scanner.h"
#include"keyword.h"

using namespace std;

extern "C"
{
    //extern int yylex(void);
    extern void set_yyin(FILE* f);
    extern void set_yyout(FILE* f);
    extern int yyparse(void);
}


int main(int , char **argv){
    //FILE *f=fopen("testin.c","r");
    FILE *f=fopen(argv[1],"r");
    //FILE* e=fopen("../testout.txt","w");
    set_yyin(f);
    //set_yyout(e);
    yyparse();
    
    /*for(Keyword k:kw_list)
    {
        if(k.type==6||k.type==7||k.type==9)
            cout<<"\n";
        else 
            cout<<" "<<k.str_value<<" ";
    }*/
    word_analyze();
    /*for(vector<Keyword> x:token)
    {
        for(Keyword k:x)
        {
            cout<<k.type<<"  "<<k.str_value<<"\n";
        }
    
        cout<<"********\n";
    }*/

    
    code_out();
    return 0;
}
