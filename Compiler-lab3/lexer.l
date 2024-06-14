%{
        #include<math.h>
        #include<stdio.h>
        #include"keyword.h"

        #define YYSTYPE Keyword
        #include "parser.hpp"

        extern "C"
        {
                extern int yywrap(void);
                extern int yylex(void);
                extern void set_yyin(FILE* f);
                extern void set_yyout(FILE* f);
        }
%}

%{


using namespace std;

%}

white [\t\n\r\f\v ]
digit [0-9]
letter [A-Za-z]
id ({letter}|_)({letter}|{digit}|_)*
number [1-9]{digit}*|0


%%


{white}+ {}
{number} {
        yylval.type=0;
        yylval.num_value=atoi(yytext);        
        yylval.str_value=yytext;
        return NUMBER;
}

"void" {
        yylval.type=5;
        yylval.str_value="void";
        yylval.num_value=0;
        return VOID;
}

"int"  {
        
        yylval.type=5;
        yylval.str_value= "int";
        yylval.num_value=0;
        return INT;
}

"main" {
        
        yylval.type=5;
        yylval.str_value="main";
        yylval.num_value=0;
        return MAIN;
}

"return" {
        
        yylval.type=4;
        yylval.str_value="return";
        yylval.num_value=0;
        return RETURN;
}
"println_int" {
        
        yylval.type=3;
        yylval.str_value="println_int";
        yylval.num_value=0;
        return PRINTF_INT;
}
{id} {

        yylval.type=1;
        yylval.str_value=yytext;
        yylval.num_value=0;
        return ID;
}
"{" {
        yylval.type=2;
        yylval.str_value="{";
        return LC;
}
"}" {
        yylval.type=2;
        yylval.str_value="}";
        return RC;
}
"[" {
        yylval.type=2;
        yylval.str_value="[";
        return LB;
}
"]" {
        yylval.type=2;
        yylval.str_value="]";
        return RB;
}
"(" {
        yylval.type=2;
        yylval.str_value="(";
        return LP;
}
")" {
        yylval.type=2;
        yylval.str_value=")";
        return RP;
}

"\*" {
        //printf("%d\n",STAR);
        yylval.type=2;
        yylval.str_value="*";
        return STAR;
}
"/" {
        //printf("%d\n",DIVOP);
        yylval.type=2;
        yylval.str_value="/";
        return DIVOP;
}
"\%" {
        //printf("%d\n",COMOP);
        yylval.type=2;
        yylval.str_value="%";
        return COMOP;
}
"\+" {
        //printf("%d\n",PLUS);
        yylval.type=2;
        yylval.str_value="+";
        return PLUS;
}
"-" {
        //printf("%d\n",MINUS);
        yylval.type=2;
        yylval.str_value="-";
        return MINUS;
}
">=" {
        //printf("%d\n",RELGEQ);
        yylval.type=2;
        yylval.str_value=">=";
        return RELGEQ;
}
"<=" {
        //printf("%d\n",RELLEQ);
        yylval.type=2;
        yylval.str_value="<=";
        return RELLEQ;
}
">" {
        //printf("%d\n", RELG);
        yylval.type=2;
        yylval.str_value=">";
        return RELG;
}
"<" {
        //printf("%d\n",RELL);
        yylval.type=2;
        yylval.str_value="<";
        return RELL;
}

"==" {
        
        //printf("%d\n",EQUOP);
        yylval.type=2;
        yylval.str_value="==";
        return EQUOP;
}
"!=" {
        //printf("%d\n",UEQUOP);
        yylval.type=2;
        yylval.str_value="!=";
        return UEQUOP;
}



"\&\&" {
        //printf("%d\n",AND);
        yylval.type=2;
        yylval.str_value="&&";
        return L_AND;
}

"\&" {
        //printf("%d\n",AND);
        yylval.type=2;
        yylval.str_value="&";
        return AND;
}

"\|\|" {
        //printf("%d\n",OR);
        yylval.type=2;
        yylval.str_value="||";
        return L_OR;
}
"\|" {
        //printf("%d\n",OR);
        yylval.type=2;
        yylval.str_value="|";
        return OR;
}
"\^" {
        //printf("%d\n",POW);
        yylval.type=2;
        yylval.str_value="^";
        return POW;
}

"=" {
        yylval.type=2;
        yylval.str_value="=";
        return EQUAL;
}


"~" {
        //printf("%d\n",FAN);
        yylval.type=2;
        yylval.str_value="~";
        return FAN;
}

"!" {
        //printf("%d\n",FEI);
        yylval.type=2;
        yylval.str_value="!";
        return FEI;
}


"," {
        yylval.type=2;
        yylval.str_value=",";
        return COMMA;
}
";" {
        yylval.type=2;
        yylval.str_value=";";
        return SEMI;
}

%%
/*int main()
{
  memset(map, 0, sizeof(map));
  yyin=fopen("testin.c","r");
  yyout=fopen("testout.txt","w");
  f//printf(yyout,"token name value\n");
  yylex();
  return 0;
}*/
void set_yyin(FILE* f)
{
        yyin=f;
}
void set_yyout(FILE* f)
{
        yyout=f;
}
int yywrap()
{
return 1;
}

