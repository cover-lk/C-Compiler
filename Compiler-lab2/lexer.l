%{
        #include<math.h>
        #include<string>
        #include<stdio.h>
        #include"keyword.h"

        extern "C"
        {
                extern int yywrap(void);
                extern int yylex(void);
                extern void set_yyin(FILE* f);
                extern void set_yyout(FILE* f);
        }
%}

%{
#define VOID 1
#define MAIN 2
#define INT  3

#define RETURN 4
#define PRINTF_INT 5

#define LC 6 //{
#define RC 7 //}

#define LB 8 //[
#define RB 9 //]

#define LP 10 //(
#define RP 11 //)

#define INPLUS 12//++
#define INMINUS 13//--

#define STAR 14//*
#define DIVOP 15// /
#define COMOP 16// %
#define PLUS  17//+
#define MINUS 18//-

#define RELG 19//>
#define RELGEQ 20//>=
#define RELL 21//<
#define RELLEQ 22//<=
#define EQUOP 23//==
#define UEQUOP 24//!=

#define AND 25//&
#define OR 26// |
#define POW 27 // ^

#define EQUAL 28// =
#define ASSIGNDIV 29// /=
#define ASSIGNSTAR 30 //*=
#define ASSIGNCOM 31 //%=
#define ASSIGNPLUS 32 //+=
#define ASSIGNMINUS 33 //-=

#define COMMA 34 //,
#define SEMI 35//;

#define ID 36 //identifyer
#define NUMBER 37 //number

using namespace std;




%}

white [\t\n\r\f\v ]
digit [0-9]
letter [A-Za-z]
id ({letter}|_)({letter}|{digit}|_)*
number [1-9]{digit}*|0
commentbegin "/*"
commentelement .|\n
commentend "*/"
%x COMMENT

%%

{commentbegin} {BEGIN COMMENT; fprintf(yyout,"Begin a comment:\n");}
<COMMENT>{commentelement} {fprintf(yyout,"%s",yytext);}
<COMMENT>{commentend} {BEGIN INITIAL; fprintf(yyout,"\nthis comment End!\n");}
{white}+ ;
{number} {
        //fprintf(yyout,"NUMBER %d %s\n",NUMBER,yytext);
        Keyword k;
        k.type=NUMBER;
        k.num_value=atoi(yytext);
        kw_list.push_back(k);
}

"void" {
        //fprintf(yyout,"VOID %d %s\n",VOID,yytext);
        Keyword k;
        k.type=VOID;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"int"  {
        //fprintf(yyout,"INT %d %s\n",INT,yytext);
        Keyword k;
        k.type=INT;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"main" {
        //fprintf(yyout,"MAIN %d %s\n",MAIN,yytext);
        Keyword k;
        k.type=MAIN;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"return" {
        //fprintf(yyout,"RETURN %d %s\n",RETURN,yytext);
        Keyword k;
        k.type=RETURN;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"println_int" {
        //fprintf(yyout,"PRINTF_INT %d %s\n",PRINTF_INT,yytext);
        Keyword k;
        k.type=PRINTF_INT;
        k.str_value=yytext;
        kw_list.push_back(k);
}
{id} {
        Keyword k;
        k.type=ID;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"{" {
        Keyword k;
        k.type=LC;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"}" {
        Keyword k;
        k.type=RC;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"[" {
        //fprintf(yyout,"LB %d %s\n",LB,yytext);
        Keyword k;
        k.type=LB;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"]" {
        //fprintf(yyout,"RB %d %s\n",RB,yytext);
        Keyword k;
        k.type=RB;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"(" {
        //fprintf(yyout,"LP %d %s\n",LP,yytext);
        Keyword k;
        k.type=LP;
        k.str_value=yytext;
        kw_list.push_back(k);
}
")" {
        //fprintf(yyout,"RP %d %s\n",RP,yytext);
        Keyword k;
        k.type=RP;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"\+\+" {
        //fprintf(yyout,"INPLUS %d %s\n",INPLUS,yytext);
        Keyword k;
        k.type=INPLUS;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"--" {
        //fprintf(yyout,"INMINUS %d %s\n",INMINUS,yytext);
        Keyword k;
        k.type=INMINUS;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"\*" {
        //fprintf(yyout,"STAR %d %s\n",STAR,yytext);
        Keyword k;
        k.type=STAR;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"/" {
        //fprintf(yyout,"DIVOP %d %s\n",DIVOP,yytext);
        Keyword k;
        k.type=DIVOP;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"\%" {
        //fprintf(yyout,"COMOP %d %s\n",COMOP,yytext);
        Keyword k;
        k.type=COMOP;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"\+" {
        //fprintf(yyout,"PLUS %d %s\n",PLUS,yytext);
        Keyword k;
        k.type=PLUS;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"-" {
        //fprintf(yyout,"MINUS %d %s\n",MINUS,yytext);
        Keyword k;
        k.type=MINUS;
        k.str_value=yytext;
        kw_list.push_back(k);
}
">" {
        //fprintf(yyout,"RELG %d %s\n",RELG,yytext);
        Keyword k;
        k.type=RELG;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"<" {
        //fprintf(yyout,"RELL %d %s\n",RELL,yytext);
        Keyword k;
        k.type=RELL;
        k.str_value=yytext;
        kw_list.push_back(k);
}
">=" {
        //fprintf(yyout,"RELGEQ %d %s\n",RELGEQ,yytext);
        Keyword k;
        k.type=RELGEQ;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"<=" {
        //fprintf(yyout,"RELLEQ %d %s\n",RELLEQ,yytext);
        Keyword k;
        k.type=RELLEQ;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"==" {
        //fprintf(yyout,"EQUOP %d %s\n",EQUOP,yytext);
        Keyword k;
        k.type=EQUOP;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"!=" {
        //fprintf(yyout,"UEQUOP %d %s\n",UEQUOP,yytext);
        Keyword k;
        k.type=UEQUOP;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"\&\&" {
        //fprintf(yyout,"AND %d %s\n",AND,yytext);
        Keyword k;
        k.type=AND;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"\&" {
        //fprintf(yyout,"AND %d %s\n",AND,yytext);
        Keyword k;
        k.type=AND;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"\|\|" {
        //fprintf(yyout,"OR %d %s\n",OR,yytext);
        Keyword k;
        k.type=OR;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"\|" {
        //fprintf(yyout,"OR %d %s\n",OR,yytext);
        Keyword k;
        k.type=OR;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"\^" {
        //fprintf(yyout,"POW %d %s\n",POW,yytext);
        Keyword k;
        k.type=POW;
        k.str_value=yytext;
        kw_list.push_back(k);
}

"=" {
        //fprintf(yyout,"EQUAL %d %s\n",EQUAL,yytext);
        Keyword k;
        k.type=EQUAL;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"/=" {
        //fprintf(yyout,"ASSIGNDIV %d %s\n",ASSIGNDIV,yytext);
        Keyword k;
        k.type=ASSIGNDIV;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"*=" {
        //fprintf(yyout,"ASSIGNSTAR %d %s\n",ASSIGNSTAR,yytext);
        Keyword k;
        k.type=ASSIGNSTAR;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"\%=" {
        //fprintf(yyout,"ASSIGNCOM %d %s\n",ASSIGNCOM,yytext);
        Keyword k;
        k.type=ASSIGNCOM;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"\+=" {
        //fprintf(yyout,"ASSIGNPLUS %d %s\n",ASSIGNPLUS,yytext);
        Keyword k;
        k.type=ASSIGNPLUS;
        k.str_value=yytext;
        kw_list.push_back(k);
}
"-=" {
        //fprintf(yyout,"ASSIGNMINUS %d %s\n",ASSIGNMINUS,yytext);
        Keyword k;
        k.type=ASSIGNMINUS;
        k.str_value=yytext;
        kw_list.push_back(k);
}

"," {
        //printf(yyout,"COMMA %d %s\n",COMMA,yytext);
        Keyword k;
        k.type=COMMA;
        k.str_value=yytext;
        kw_list.push_back(k);
}
";" {
        //fprintf(yyout,"SEMI %d %s\n",SEMI,yytext);
        Keyword k;
        k.type=SEMI;
        k.str_value=yytext;
        kw_list.push_back(k);
}

%%
/*int main()
{
  memset(map, 0, sizeof(map));
  yyin=fopen("testin.c","r");
  yyout=fopen("testout.txt","w");
  fprintf(yyout,"token name value\n");
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

