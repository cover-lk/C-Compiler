#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <cstring>
#include <stack>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

string keywords[]={"int","return"};
string symbol[] = {"(",")","*","/","%","+","-","=","++","--","+=","-=","*=","/=",","};

/*关键字：1
  数字  ：2
  变量  ：3
  符号  ：4
*/
struct Key{
    int type;
    int num_value;
    string char_value="";
} ;

struct Variable{
    string name;
    int num;
};

//字符串分割
std::vector<std::string> stringSplit(const std::string& str, char delim) {
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        if (!item.empty()) {
            elems.push_back(item);
        }
    }
    return elems;
}

//字符串替换
char *strpl(char *str, char *o, char *n)
{
	char *p = NULL;
	int len = 0;
	char newstr[64] = {0};

	p = strstr(str,o);
	len =  p - str;
	strncpy(newstr, str, len);
	strcat(newstr, n);
	strcat(newstr,p+strlen(o));
	strcpy(str,newstr);

	return str;
}


//判断数字
bool isDigital(string s)
{
    for (char c : s) 
    {
        if (!isdigit(c)) 
            return false;
    }
    return true;
}

//字符串转数字
int strToInt(string s)
{
    return stoi(s);
}

//判断符号
bool isSymbol(string s,string& ret)
{
    for(string i:symbol)
    {
        if(i.compare(s)==0)
        {
            ret=i;
            return true;
        }
    }
    return false;
}

//符号转汇编
string which_symbol(string s)
{
    if(s=="+")
        return "add";
    else if(s=="-")
        return "sub";
    else if(s=="*")
        return "imul";
    else if(s=="/")
        return "idiv";
}

//判断关键字
bool isKeywords(string s,string& ret)
{
    for(string i:keywords)
    {
        if(i.compare(s)==0)
        {
            ret=i;
            return true;
        }
    }
    return false;
}

//判断表达式
bool isExpress(vector<Key> in)
{
    string ret="=";
    for(Key k: in)
    {
        if(isSymbol(k.char_value,ret)&&(ret!="="))
            return true;
    }
    return false;
}

//判断变量次序
int findvar(vector<Variable> in,string s)
{
    for(Variable v: in)
    {
        if(s==v.name)
            return v.num;
    }
    return -1;
}

//符号优先级
int getPriority(string op) 
{
    if(op=="+"||op=="-")
        return 1;
    else if(op=="*"||op=="/"||op=="%")
        return 2;
    else if(op=="++"||op=="--")
        return 3;
    else
        return 0;
}

//词法分析
void word_analyze(const vector<string>& in,vector<vector<Key> >& out)
{
    //循环读取每行
    for(string line:in)
    {
        vector<Key> t;
        vector<string> word;
        istringstream i(line);
        string token;
        while (getline(i, token, ' ')) {
            if(!token.empty()){
                //cout << "Token: " << token << endl;
                word.push_back(token);
            }
        }
        for(int i=0;i<word.size();i++)
        {
            if(word[i]=="int")
            {
                Key k={1,0,"int"};
                t.push_back(k);
            }
            else if(word[i]=="return")
            {
                Key k={1,0,"return"};
                t.push_back(k);
            }
            else if(isDigital(word[i]))
            {
                Key k={2,strToInt(word[i]),""};
                t.push_back(k);
            }
            else if(isSymbol(word[i],word[i]))
            {
                Key k={4,0,word[i]};
                t.push_back(k);
            }
            else 
            {
                Key k={3,0,word[i]};
                t.push_back(k);
            }
        }
        out.push_back(t);
        /*if(word[0]=="int")
        {
            Key k={1,0,"int"};
            Key l={3,0,word[1]};
            t.push_back(k);
            t.push_back(l);
        }
        else if(word[0]=="return")
        {
            Key k={1,0,"return"};
            Key l={3,0,word[1]};
            t.push_back(k);
            t.push_back(l);
        }
        else if(word.size() == 3 && word[1] == "=")
        {
            if(isDigital(word[2]))
            {
                Key k={2,strToInt(word[2]),""};
                Key l={4,0,"="};
                Key m={3,0,word[0]};
                t.push_back(m);
                t.push_back(l);
                t.push_back(k);
            }
            else
            {
                Key k={3,0,word[0]};
                Key m={4,0,"="};
                Key l={3,0,word[2]};
                t.push_back(k);
                t.push_back(m);
                t.push_back(l);
            }
        }
        else
        {
            Key k={4,0,word[0]};
            t.push_back(k);
        }
        out.push_back(t);
        /*if(line.compare("")==0||line.compare("\n")==0)
            continue;
        //按空格分割字符串
        int flag=0;
        for(char c: line)
        {
            if(c!=' '&&c!='\n'&&c!=';')
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
            continue;*/

        /*vector<Key> t;
        vector<string> word;*/

        /*char *data;
        int len = line.length();
        data = (char *)malloc((len+1)*sizeof(char));
        //line.copy(data,len,0);
        strcpy(data,line.c_str());
        string l=strpl(data,";",(char*)"");
        //l=l.substr(0,len);
        word=stringSplit(l,' ');*/

        /*for(string w:word)
        {
            //std::cout<<w<<"**";
            string ret;
            if(isKeywords(w,ret))  //是否为关键字
            {
                Key k={1,0,ret};
                t.push_back(k);
            }
            else if(isSymbol(w,ret))//是否为符号
            {
                Key k={4,0,ret};
                t.push_back(k);
            }
            else if(isDigital(w)) //是否为数字
            {
                Key k={2,strToInt(w),""};
                t.push_back(k);
            }
            else                   //是否为计算式或者变量名
            {
                /*char *c;
                int len = w.length();
                c = (char *)malloc((len+1)*sizeof(char));
                w.copy(c,len,0);

                if(strstr(c,"=")==NULL)//不含等号
                {
                    Key k={3,0,w};
                    t.push_back(k);
                }
                else
                {
                    string::iterator sit = w.begin();
                    while (sit != w.end())
                    {
                        //cout << *sit << " ";
                        string sx;
                        string sy="";
                        string ret1,ret2;
                        sx=*sit;
                        if((sit+1)!=w.end())
                            sy=*(sit+1);
                        if((*sit<='Z'&&*sit>='A')||(*sit<='z'&&*sit>='a'))
                        {
                            //Key k={3,0,si};
                            //t.push_back(k);
                            //sit++;

                            string str="";
                            while(sit!=w.end())
                            {
                                string x,y;
                                x=*sit;
                                if(isSymbol(x,y))
                                    //sit++;
                                    break;
                                
                                str=str+*sit;
                                sit++;
                            }
                            Key k={3,0,str};
                            t.push_back(k);
                        }
                        else if(isSymbol(sx,ret1))
                        {
                            if(isSymbol(sy,ret2))
                            {      
                                string x="";
                                string op="";
                                x=ret1+ret2;
                                if(isSymbol(x,op))
                                { 
                                    Key k={4,0,op};
                                    t.push_back(k);
                                    sit++;
                                }
                            }
                            else if((*(sit+1)<='Z'&&*(sit+1)>='A')||(*(sit+1)<='z'&&*(sit+1)>='a'))
                            {
                                string x="";
                                x=sx+sy;
                                Key k={3,0,x};
                                t.push_back(k);
                                sit++;
                            }
                             
                        }
                        else if(*sit>='0'&&*sit<='9')
                        {
                            string num="";
                            while(*sit>='0'&&*sit<='9'&&sit!=w.end())
                            {
                                num=num+*sit;
                                sit++;
                            }
                            int n=strToInt(num);
                            Key k={2,n,""};
                            t.push_back(k);
                        }
                        /*else
                        {
                            sit++;
                        }
                            
                    }
                //}
            }
        }*/
       
        
    }
}

//中缀转后缀
void infixToPostfix(vector<Key>& in,vector<Key>& out)
{
    stack<Key> sk;
    vector<Key>::iterator in_p=in.begin();
    //vector<Key>::iterator out_p=out.begin();

    while((*in_p).char_value!="="&&(*in_p).char_value!="+="&&(*in_p).char_value!="-="&&(*in_p).char_value!="*="&&(*in_p).char_value!="/=")
    {
        in_p++;
    }
    in_p++;

    while(in_p!=in.end())
    {
        if((*in_p).type==2||(*in_p).type==3)
        {
            out.push_back(*in_p);
            in_p++;
        }
        else if((*in_p).char_value=="++"||(*in_p).char_value=="--")
        {
            out.push_back(*in_p);
            in_p++;
        }
        else if((*in_p).type==4)
        {
            string x=(*in_p).char_value;
            if(x==")")
            {
                while(!sk.empty()&&sk.top().char_value!="(")
                {
                    Key k=sk.top();
                    sk.pop();
                    out.push_back(k);
                }
                if(!sk.empty()&&sk.top().char_value=="(")
                {
                    sk.pop();
                }
                in_p++;
            }
            else if(x=="(")
            {
                sk.push(*in_p);
                in_p++;
            }
            else
            {
                int priority=getPriority(x);
                while(!sk.empty()&&sk.top().type==4&&getPriority(sk.top().char_value)>=priority)
                {
                    Key k=sk.top();
                    sk.pop();
                    out.push_back(k);
                }
                sk.push(*in_p);
                in_p++;
            }
            
        }
        else
            in_p++;

    }

    while(!sk.empty())
    {
        Key k=sk.top();
        sk.pop();
        out.push_back(k);
    }

   
}

//后缀输出
void postfix_out(vector<Key>& in,vector<Variable>& V)
{
    stack<Key> sk;
    vector<Key>::iterator in_p=in.begin();

    while(in_p!=in.end())
    {
        if((*in_p).type==2)
        {
            std::cout<<"mov eax, "<<(*in_p).num_value<<"\n";
            std::cout<<"push eax\n";

            sk.push(*in_p);
            in_p++;
        }
        else if((*in_p).type==3)
        {
            std::cout<<"mov eax, DWORD PTR [ebp-"<<4*findvar(V,(*in_p).char_value)<<"]\n";
            std::cout<<"push eax\n";

            sk.push(*in_p);
            in_p++;
        }
        else if((*in_p).type==4)
        {
            if((*in_p).char_value=="++")
            {
                std::cout<<"pop eax\n";
                std::cout<<"add eax, 1\n";
                std::cout<<"push eax\n";
            }
            else if((*in_p).char_value=="--")
            {
                std::cout<<"pop eax\n";
                std::cout<<"sub eax, 1\n";
                std::cout<<"push eax\n";
            }
            else
            {
                std::cout<<"pop ebx\n";
                std::cout<<"pop eax\n";
                if((*in_p).char_value=="/")
                {   
                    std::cout<<"cdq\n";
                    std::cout<<"idiv ebx\n";
                    std::cout<<"push eax\n";
                }
                else if((*in_p).char_value=="%")
                {
                    std::cout<<"cdq\n";
                    std::cout<<"idiv ebx\n";
                    std::cout<<"push edx\n";
                }
                else 
                { 
                    std::cout<<which_symbol((*in_p).char_value)<<" eax, ebx\n";
                    std::cout<<"push eax\n";
                }
                
            }
            

            /*Key a=sk.top();
            sk.pop();
            Key b=sk.top();
            sk.pop();

            Key c=a+b;
            sk.push(c);*/
            in_p++;
        }
    }
}

//代码生成
void code_out(vector<vector<Key> >& in)
{
    int num=0;
    vector<Variable> V; 
    for(vector<Key> line: in)
    {
        if(line[0].type==1)
        {
            if(line[0].char_value=="int")
            {
                if(findvar(V,line[1].char_value)<0)
                {
                    Variable v={line[1].char_value,++num};
                    V.push_back(v);
                }
                vector<Key>::iterator it=line.end()-1;
                std::cout<<"mov DWORD PTR [ebp-"<<4*findvar(V,line[1].char_value)<<"], "<<(*it).num_value<<"\n";
            }
            else if(line[0].char_value=="return")
            {
                std::cout<<"mov eax, DWORD PTR [ebp-"<<4*findvar(V,line[1].char_value)<<"]\n";
            }
        }
        else if(line[0].type==3&&isExpress(line)==false)
        {
            vector<Key>::iterator it=line.end()-1;
            if((*it).type==2)
                std::cout<<"mov DWORD PTR [ebp-"<<4*findvar(V,line[0].char_value)<<"], "<<(*it).num_value<<"\n";
            else if((*it).type==3)
            {
                std::cout<<"mov eax, DWORD PTR [ebp-"<<4*findvar(V,(*it).char_value)<<"]\n";
                std::cout<<"mov DWORD PTR [ebp-"<<4*findvar(V,line[0].char_value)<<"], eax\n";
            }
            else if((*it).type==4&&((*it).char_value=="++"))
            {
                std::cout<<"mov eax, DWORD PTR [ebp-"<<4*findvar(V,line[0].char_value)<<"]\n";
                std::cout<<"add eax, 1\n";
                std::cout<<"mov DWORD PTR [ebp-"<<4*findvar(V,line[0].char_value)<<"], eax\n";
            }  
            else if(line[0].type==4&&(line[0].char_value=="++"))
            {
                std::cout<<"mov eax, DWORD PTR [ebp-"<<4*findvar(V,(*it).char_value)<<"]\n";
                std::cout<<"add eax, 1\n";
                std::cout<<"mov DWORD PTR [ebp-"<<4*findvar(V,(*it).char_value)<<"], eax\n";
            }
            else if((*it).type==4&&((*it).char_value=="--"))
            {
                std::cout<<"mov eax, DWORD PTR [ebp-"<<4*findvar(V,line[0].char_value)<<"]\n";
                std::cout<<"sub eax, 1\n";
                std::cout<<"mov DWORD PTR [ebp-"<<4*findvar(V,line[0].char_value)<<"], eax\n";
            }
            else if(line[0].type==4&&(line[0].char_value=="--"))
            {
                std::cout<<"mov eax, DWORD PTR [ebp-"<<4*findvar(V,(*it).char_value)<<"]\n";
                std::cout<<"sub eax, 1\n";
                std::cout<<"mov DWORD PTR [ebp-"<<4*findvar(V,(*it).char_value)<<"], eax\n";
            }
        }
        else 
        {
            Key first=line[0];
            vector<Key> infix=line;
            vector<Key> postfix;
            infixToPostfix(infix,postfix);
            /*for(Key k:postfix)
                std::cout<<k.type<<"  "<<k.char_value<<"  "<<k.num_value<<"\n";
            std::cout<<"******";*/
            postfix_out(postfix,V);
            if(line[1].char_value=="=")
            { 
                std::cout<<"pop eax\n";
                std::cout<<"mov DWORD PTR [ebp-"<<4*findvar(V,first.char_value)<<"], eax\n";
            }
            else if(line[1].char_value=="+=")
            {
                std::cout<<"pop eax\n";
                std::cout<<"add DWORD PTR [ebp-"<<4*findvar(V,first.char_value)<<"], eax\n";
            }
            else if(line[1].char_value=="-=")
            {
                std::cout<<"pop eax\n";
                std::cout<<"sub DWORD PTR [ebp-"<<4*findvar(V,first.char_value)<<"], eax\n";
            }
            else if(line[1].char_value=="*=")
            {
                std::cout<<"pop eax\n";
                std::cout<<"imul DWORD PTR [ebp-"<<4*findvar(V,first.char_value)<<"], eax\n";
            }
            else if(line[1].char_value=="/=")
            {
                std::cout<<"pop ebx\n";
                std::cout<<"mov eax, DWORD PTR [ebp-"<<4*findvar(V,first.char_value)<<"]\n";
                std::cout<<"cdq";
                std::cout<<"idiv ebx\n";
                std::cout<<"mov DWORD PTR [ebp-"<<4*findvar(V,first.char_value)<<"], eax\n";
            }
        }
    }
}

int main(int argc, char *argv[])
{
    //读入文件，生成字符串数组
    string path1;
    string line;
    vector<string>File;
    vector<vector<Key> >Token;

    path1=argv[1];
    //std::cin>>path1;
    ifstream read_file(path1);

    string content((std::istreambuf_iterator<char>(read_file)),
                        std::istreambuf_iterator<char>());
    content.erase(remove(content.begin(), content.end(), '\n'), content.end());
    content.erase(remove(content.begin(), content.end(), '\r'), content.end());

    istringstream iss(content);
    
    while (getline(iss, line, ';')) {
        File.push_back(line);
    }
    /*while(getline(fs,line))
    {
        File.push_back(line);
    }
	fs.close();*/
    //std::cout<<File[2];

    //生成字节流
    word_analyze(File,Token);

    /*for(vector<Key> E:Token)
    {   
        for(Key k:E)
            std::cout<<k.type<<"  "<<k.char_value<<"  "<<k.num_value<<"\n";
        std::cout<<"*****\n";
    }*/

    code_out(Token);
  
    return 0;
}