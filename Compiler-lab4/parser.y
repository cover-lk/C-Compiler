%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string>
    #include <iostream>
    #include "keyword.h"
    
    struct Keyword ;
    #define YYSTYPE Keyword
    extern "C"
    {
        extern int yylex(void);
        extern int yyparse(void);
    }
    void yyerror(char*);
  
    using namespace std;

%}

%token VOID  MAIN  INT  RETURN  PRINTF_INT IF ELSE WHILE BREAK CONTINUE
%token LC RC  
%token LB RB 
%token LP RP  
%token COMMA SEMI ID NUMBER EQUAL

%left L_OR
%left L_AND
%left OR 
%left POW  
%left AND 
%left EQUOP 
%left UEQUOP 
%left RELLEQ RELGEQ RELL RELG  
%left PLUS MINUS  
%left STAR DIVOP COMOP
%right FAN  
%right FEI  
%right FU

%start unit
%%
/*整体代码unit*/
unit
    : function_unit                 
    | unit function_unit            
    ;

/*函数块function_unit*/
function_unit
    : func_defy LC sentence RC     {Keyword k;k.type=6;kw_list.push_back(k);}
    ;

func_defy
    : func_declar LP varlist RP   {Keyword k;k.type=7;kw_list.push_back(k);}
    | func_declar LP RP           {Keyword k;k.type=7;kw_list.push_back(k);}
    ;

func_declar
    : type ID     {Keyword k;k.type=3;k.str_value=$2.str_value;kw_list.push_back(k);}
    | type MAIN   {Keyword k;k.type=3;k.str_value=$2.str_value;kw_list.push_back(k);}
    ;

/*类型type*/
type
    : VOID        {Keyword k;k.type=5;k.str_value=$1.str_value;kw_list.push_back(k);}
    | INT         {Keyword k;k.type=5;k.str_value=$1.str_value;kw_list.push_back(k);}
    ;

/*参数列表varlist*/
varlist
    : type ID     {Keyword k;k.type=1;k.str_value=$2.str_value;kw_list.push_back(k);}
    | varlist COMMA type ID {Keyword k;k.type=1;k.str_value=$4.str_value;kw_list.push_back(k);}
    ;

/*代码语句sentence*/
sentence
    : declar_sent
    | calculate_sent
    | func_sent
    | return_sent
    | break_sent
    | continue_sent
    | if_sent
    | while_sent
    | SEMI
    | sentence declar_sent
    | sentence calculate_sent
    | sentence func_sent
    | sentence return_sent
    | sentence break_sent
    | sentence continue_sent
    | sentence if_sent
    | sentence while_sent
    ;

/*声明语句declar_sent*/
declar_sent
    : type declar_list SEMI  {Keyword k;k.type=9;kw_list.push_back(k);}
    ;

    //声明变量列表
declar_list
    : ID                  {Keyword k;k.type=1;k.str_value=$1.str_value;kw_list.push_back(k);Keyword w;w.type=10;w.str_value=$1.str_value;kw_list.push_back(w);}
    | declar_head cal_list      {Keyword k;k.type=10;k.str_value=$1.str_value;kw_list.push_back(k);}
    | declar_list COMMA ID      {Keyword k;k.type=1;k.str_value=$3.str_value;kw_list.push_back(k);Keyword w;w.type=10;w.str_value=$3.str_value;kw_list.push_back(w);}
    | declar_list COMMA declar_head cal_list    {Keyword k;k.type=10;k.str_value=$3.str_value;kw_list.push_back(k);}
    ;

declar_head
    : ID EQUAL              {
                                $$.str_value=$1.str_value;
                                Keyword k;k.type=1;k.str_value=$1.str_value;kw_list.push_back(k);
                                Keyword w;w.type=2;w.str_value=$2.str_value;kw_list.push_back(w);
                            }
    ;



/*运算语句calculate_sent*/
calculate_sent
    : declar_head cal_list SEMI  {Keyword k;k.type=9;kw_list.push_back(k);}
    ;

    //所有计算符号情况，括号以及函数
cal_list
    : cal_list OR cal_list      {Keyword k;k.type=2;k.str_value=$2.str_value;kw_list.push_back(k);}
    | cal_list POW cal_list     {Keyword k;k.type=2;k.str_value=$2.str_value;kw_list.push_back(k);}
    | cal_list AND cal_list     {Keyword k;k.type=2;k.str_value=$2.str_value;kw_list.push_back(k);}
    | cal_list L_AND cal_list     {Keyword k;k.type=2;k.str_value=$2.str_value;kw_list.push_back(k);}
    | cal_list L_OR cal_list     {Keyword k;k.type=2;k.str_value=$2.str_value;kw_list.push_back(k);}
    | cal_list EQUOP cal_list     {Keyword k;k.type=2;k.str_value=$2.str_value;kw_list.push_back(k);}
    | cal_list UEQUOP cal_list    {Keyword k;k.type=2;k.str_value=$2.str_value;kw_list.push_back(k);}
    | cal_list RELLEQ cal_list    {Keyword k;k.type=2;k.str_value=$2.str_value;kw_list.push_back(k);}
    | cal_list RELGEQ cal_list    {Keyword k;k.type=2;k.str_value=$2.str_value;kw_list.push_back(k);}
    | cal_list RELL cal_list     {Keyword k;k.type=2;k.str_value=$2.str_value;kw_list.push_back(k);}
    | cal_list RELG cal_list     {Keyword k;k.type=2;k.str_value=$2.str_value;kw_list.push_back(k);}
    | cal_list PLUS cal_list     {Keyword k;k.type=2;k.str_value=$2.str_value;kw_list.push_back(k);}
    | cal_list MINUS cal_list     {Keyword k;k.type=2;k.str_value=$2.str_value;kw_list.push_back(k);}
    | cal_list STAR cal_list     {Keyword k;k.type=2;k.str_value=$2.str_value;kw_list.push_back(k);}
    | cal_list DIVOP cal_list     {Keyword k;k.type=2;k.str_value=$2.str_value;kw_list.push_back(k);}
    | cal_list COMOP cal_list     {Keyword k;k.type=2;k.str_value=$2.str_value;kw_list.push_back(k);}
    | FAN cal_list              {Keyword k;k.type=2;k.str_value="~";kw_list.push_back(k);}
    | FEI cal_list              {Keyword k;k.type=2;k.str_value="!";kw_list.push_back(k);}
    | MINUS cal_list %prec FU     {Keyword k;k.type=2;k.str_value="FU";kw_list.push_back(k);}
    | LP cal_list RP              {}
    | NUMBER                    {Keyword k;k.type=0;k.str_value=$1.str_value;k.num_value=$1.num_value;kw_list.push_back(k);}
    | ID                        {Keyword k;k.type=1;k.str_value=$1.str_value;kw_list.push_back(k);}
    | func                      {}
    ;

/*函数语句func_sent*/
func_sent
    : func SEMI                         {Keyword k;k.type=9;kw_list.push_back(k);}
    ;

    //函数调用func
func
    : func_name LP para_list RP         {Keyword k;k.type=8;k.str_value=$1.str_value;kw_list.push_back(k);}
    ;

func_name
    : ID                                {$$.str_value=$1.str_value;Keyword k;k.type=3;k.str_value=$1.str_value;kw_list.push_back(k);}
    | PRINTF_INT                        {$$.str_value=$1.str_value;Keyword k;k.type=3;k.str_value=$1.str_value;kw_list.push_back(k);}

    //函数调用参数列表para_list
para_list
    : cal_list                                {Keyword k;k.type=10;kw_list.push_back(k);Keyword w;w.type=11;kw_list.push_back(w);}
    | para_list COMMA cal_list                {Keyword k;k.type=10;kw_list.push_back(k);Keyword w;w.type=11;kw_list.push_back(w);}
    |
    ;

/*返回语句*/
return_sent
    : ret_head ret_list SEMI              {Keyword k;k.type=9;kw_list.push_back(k);}
    ;

ret_head
    :RETURN                               {Keyword k;k.type=4;k.str_value=$1.str_value;kw_list.push_back(k);}
    ;

    //返回类型列表ret_list
ret_list
    : cal_list                            {Keyword k;k.type=10;kw_list.push_back(k);}
    ;

/*break语句*/
break_sent
    : BREAK SEMI                          {Keyword k;k.type=16;k.str_value=$1.str_value;kw_list.push_back(k);Keyword l;l.type=9;kw_list.push_back(l);}
    ;

/*continue语句*/
continue_sent
    : CONTINUE SEMI                       {Keyword k;k.type=17;k.str_value=$1.str_value;kw_list.push_back(k);Keyword l;l.type=9;kw_list.push_back(l);}
    ;

/*if语句*/
if_sent
    : IF_UNIT ELSE_UNIT                   {Keyword k;k.type=13;kw_list.push_back(k);}
    | IF_UNIT                             {Keyword k;k.type=13;kw_list.push_back(k);}
    ;

IF_UNIT
    : if_head LC sentence RC              {Keyword k;k.type=12;kw_list.push_back(k);}
    ;

if_head
    : IF LP condition RP                   {Keyword k;k.type=18;k.str_value=$1.str_value;kw_list.push_back(k);}
    ;

ELSE_UNIT
    : else_head LC sentence RC            {Keyword k;k.type=21;kw_list.push_back(k);}
    ;

else_head
    : ELSE                                {Keyword k;k.type=19;k.str_value=$1.str_value;kw_list.push_back(k);}
    ;

/*while语句*/
while_sent
    : while_condition LC sentence RC      {Keyword k;k.type=15;kw_list.push_back(k);}
    ;

while_condition
    : while_head LP condition RP          {Keyword k;k.type=14;kw_list.push_back(k);}
    ;

while_head
    : WHILE                               {Keyword k;k.type=20;k.str_value=$1.str_value;kw_list.push_back(k);}
    ;

condition
    : cal_list                            {Keyword k;k.type=22;kw_list.push_back(k);}
    ;




%%
/*main(int argc,char **argv){
        yyparse();
}*/
void yyerror(char *s)
{
    fprintf(stderr,"error: %s\n",s);
}
