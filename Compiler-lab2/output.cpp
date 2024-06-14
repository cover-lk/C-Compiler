#include"output.h"

map<string,int> varToInt;
int count=0;
int findvar(vector<Variable> in,string s)
{
    for(Variable v: in)
    {
        if(s==v.name)
            return v.num;
    }
    return -10;
}

//+ - * / % < <= > >= == != & | ^
int getPriority(string op)
{
    if(op=="+"||op=="-")
        return 7;
    else if(op=="*"||op=="/"||op=="%")
        return 8;
    else if(op=="<"||op==">"||op==">="||op=="<=")
        return 6;
    else if(op=="=="||op=="!=")
        return 5;
    else if(op=="&&"||op=="&")
        return 4;
    else if(op=="||"||op=="|")
        return 3;
    else if(op=="^")
        return 2;
    else
        return 0;
}

//中缀转后缀
void infixToPostfix(vector<Keyword>& in,vector<Keyword>& out)
{
    stack<Keyword> sk;
    vector<Keyword>::iterator in_p=in.begin();
    while((*in_p).str_value!="="&&(*in_p).str_value!="+="&&(*in_p).str_value!="-="&&(*in_p).str_value!="*="&&(*in_p).str_value!="/=")
    {
        in_p++;
    }
    in_p++;
    while(in_p!=in.end())
    {
        if((*in_p).type==36||(*in_p).type==37)
        {
            out.push_back(*in_p);
            in_p++;
        }
        else if((*in_p).type>5&&(*in_p).type<36)
        {
            string x=(*in_p).str_value;
            if(x==")")
            {
                while(!sk.empty()&&sk.top().str_value!="(")
                {
                    Keyword k=sk.top();
                    sk.pop();
                    out.push_back(k);
                }
                if(!sk.empty()&&sk.top().str_value=="(")
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
                while(!sk.empty()&&((*in_p).type>5&&(*in_p).type<36)&&getPriority(sk.top().str_value)>=priority)
                {
                    Keyword k=sk.top();
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
        Keyword k=sk.top();
        sk.pop();
        out.push_back(k);
    }
}

int postfix_out(vector<Keyword>& in,vector<Variable>& V)
{
    stack<Keyword> sk;
    vector<Keyword>::iterator in_p=in.begin();
    while(in_p!=in.end())
    {
        if((*in_p).type==37)
        {
            std::cout<<"  mov eax, "<<(*in_p).num_value<<"\n";
            std::cout<<"  push eax\n";

            sk.push(*in_p);
            in_p++;
        }
        else if((*in_p).type==36)
        {
            if((*in_p).str_value!="argc"||(*in_p).str_value!="argv")
                std::cout<<"  mov eax, DWORD PTR [ebp-"<<4*findvar(V,(*in_p).str_value)<<"]\n";
            else
                std::cout<<"  mov eax, DWORD PTR [ebp+"<<findvar(V,(*in_p).str_value)<<"]\n";
            //std::cout<<"  mov eax, DWORD PTR [ebp-"<<4*findvar(V,(*in_p).str_value)<<"]\n";
            std::cout<<"  push eax\n";

            sk.push(*in_p);
            in_p++;
        }
        else if((*in_p).type>5&&(*in_p).type<36)
        {
            std::cout<<"  pop ebx\n";
            std::cout<<"  pop eax\n";

            Keyword b=sk.top();
            sk.pop();
            if(b.type==36)
                b.num_value=varToInt[b.str_value];

            Keyword a=sk.top();
            sk.pop();
            if(a.type==36)
                a.num_value=varToInt[a.str_value];
           

            if((*in_p).str_value=="+")
            {
                std::cout<<"  add eax, ebx\n";
                std::cout<<"  push eax\n";

                Keyword end;
                end={37,a.num_value+b.num_value,""};
                sk.push(end);
                in_p++;
            }
            else if((*in_p).str_value=="-")
            {
                std::cout<<"  sub eax, ebx\n";
                std::cout<<"  push eax\n";

                Keyword end;
                end={37,a.num_value-b.num_value,""};
                sk.push(end);
                in_p++;
            }
            else if((*in_p).str_value=="*")
            {
                std::cout<<"  mov ecx, 0\n";
                std::cout<<"  imul eax, ebx\n";
                std::cout<<"  push eax\n";

                Keyword end;
                end={37,a.num_value*b.num_value,""};
                sk.push(end);
                in_p++;
            }
            else if((*in_p).str_value=="/")
            {
                std::cout<<"  cdq\n";
                std::cout<<"  idiv ebx\n";
                std::cout<<"  push eax\n";

                Keyword end;
                end={37,a.num_value/b.num_value,""};
                sk.push(end);
                in_p++;
            }
            else if((*in_p).str_value=="%")
            {
                std::cout<<"  cdq\n";
                std::cout<<"  idiv ebx\n";
                std::cout<<"  push edx\n";

                Keyword end;
                end={37,a.num_value%b.num_value,""};
                sk.push(end);
                in_p++;
            }
            else if((*in_p).str_value=="&&"||(*in_p).str_value=="&")
            {
                std::cout<<"  and eax, ebx\n";
                std::cout<<"  push eax\n";
                
                Keyword end;
                end={37,a.num_value&b.num_value,""};
                sk.push(end);

                int x=a.num_value&b.num_value;
                std::cout<<"  mov eax, "<<x<<"\n";
                std::cout<<"  push eax\n";

                in_p++;
            }
            else if((*in_p).str_value=="||"||(*in_p).str_value=="|")
            {
                std::cout<<"  or eax, ebx\n";
                std::cout<<"  push eax\n";

                Keyword end;
                end={37,a.num_value|b.num_value,""};
                sk.push(end);

                int x=a.num_value|b.num_value;
                std::cout<<"  mov eax, "<<x<<"\n";
                std::cout<<"  push eax\n";

                in_p++;
            }
            else if((*in_p).str_value=="^")
            {
                //std::cout<<"  xor eax, ebx\n";
                //std::cout<<"  push eax\n";

                Keyword end;
                end={37,a.num_value^b.num_value,""};
                sk.push(end);
                
                int x=a.num_value^b.num_value;
                std::cout<<"  mov eax, "<<x<<"\n";
                std::cout<<"  push eax\n";

                in_p++;
            }
            else if((*in_p).str_value==">")
            {
                //std::cout<<"xor eax, ebx\n";
                //std::cout<<"push eax\n";

                /*std::cout<<"cmp eax, ebx\n";   
                std::cout<<"jg greater_than_"<<count<<"\n";
                std::cout<<"mov eax, 0";       
                std::cout<<"push eax\n"; 
                std::cout<<"jmp end_compare_"<<count<<"\n";   
                std::cout<<"\n";
                std::cout<<"greater_than_"<<count<<":\n";
                std::cout<<"mov eax, 1\n"; 
                std::cout<<"push eax\n";  
                std::cout<<"\n";
                std::cout<<"end_compare_"<<count<<":\n";
                count++;*/

                Keyword end;
                if(a.num_value>b.num_value)
                {
                    end={37,1,""};
                    std::cout<<"  mov eax, 1\n";
                    std::cout<<"  push eax\n";
                }
                else 
                {
                    end={37,0,""};
                    std::cout<<"  mov eax, 0\n";
                    std::cout<<"  push eax\n";
                }
                sk.push(end);
                in_p++;
            }
            else if((*in_p).str_value==">=")
            {
                //std::cout<<"xor eax, ebx\n";
                //std::cout<<"push eax\n";


                /*std::cout<<"cmp eax, ebx\n";   
                std::cout<<"jge greater_or_equal_"<<count<<"\n";  
                std::cout<<"mov eax, 0";       
                std::cout<<"push eax\n"; 
                std::cout<<"jmp end_compare_"<<count<<"\n";  
                std::cout<<"\n";
                std::cout<<"greater_or_equal_"<<count<<":\n";
                std::cout<<"mov eax, 1\n"; 
                std::cout<<"push eax\n";  
                std::cout<<"\n";
                std::cout<<"end_compare_"<<count<<":\n";
                count++;*/

                Keyword end;
                if(a.num_value>=b.num_value)
                {
                    end={37,1,""};
                    std::cout<<"  mov eax, 1\n";
                    std::cout<<"  push eax\n";
                }
                else 
                {
                    end={37,0,""};
                    std::cout<<"  mov eax, 0\n";
                    std::cout<<"  push eax\n";
                }
                sk.push(end);
                in_p++;
            }
            else if((*in_p).str_value=="<")
            {
                //std::cout<<"xor eax, ebx\n";
                //std::cout<<"push eax\n";

                
                /*std::cout<<"cmp eax, ebx\n";   
                std::cout<<"jl less_than_"<<count<<"\n";  
                std::cout<<"mov eax, 0";       
                std::cout<<"push eax\n"; 
                std::cout<<"jmp end_compare_"<<count<<"\n";    
                std::cout<<"\n";
                std::cout<<"less_than_"<<count<<":\n";
                std::cout<<"mov eax, 1\n"; 
                std::cout<<"push eax\n";  
                std::cout<<"\n";
                std::cout<<"end_compare_"<<count<<":\n";
                count++;*/

                Keyword end;
                if(a.num_value<b.num_value)
                {
                    end={37,1,""};
                    std::cout<<"  mov eax, 1\n";
                    std::cout<<"  push eax\n";
                }
                else 
                {
                    end={37,0,""};
                    std::cout<<"  mov eax, 0\n";
                    std::cout<<"  push eax\n";
                }
                sk.push(end);
                in_p++;
            }
            else if((*in_p).str_value=="<=")
            {
                //std::cout<<"xor eax, ebx\n";
                //std::cout<<"push eax\n";

                /*std::cout<<"cmp eax, ebx\n";   
                std::cout<<"jle less_or_equal_"<<count<<"\n"; 
                std::cout<<"mov eax, 0";       
                std::cout<<"push eax\n"; 
                std::cout<<"jmp end_compare_"<<count<<"\n";   
                std::cout<<"\n";
                std::cout<<"less_or_equal_"<<count<<":\n";
                std::cout<<"mov eax, 1\n"; 
                std::cout<<"push eax\n";  
                std::cout<<"\n";
                std::cout<<"end_compare_"<<count<<":\n";
                count++;*/


                Keyword end;
                if(a.num_value<=b.num_value)
                {
                    end={37,1,""};
                    std::cout<<"  mov eax, 1\n";
                    std::cout<<"  push eax\n";
                }
                else 
                {
                    end={37,0,""};
                    std::cout<<"  mov eax, 0\n";
                    std::cout<<"  push eax\n";
                }
                sk.push(end);
                in_p++;
            }
            else if((*in_p).str_value=="!=")
            {
                //std::cout<<"xor eax, ebx\n";
                //std::cout<<"push eax\n";

                /*std::cout<<"cmp eax, ebx\n";   
                std::cout<<"jne not_equal_"<<count<<"\n"; 
                std::cout<<"mov eax, 0";       
                std::cout<<"push eax\n"; 
                std::cout<<"jmp end_compare_"<<count<<"\n";  
                std::cout<<"\n";
                std::cout<<"not_equal_"<<count<<":\n";
                std::cout<<"mov eax, 1\n"; 
                std::cout<<"push eax\n";  
                std::cout<<"\n";
                std::cout<<"end_compare_"<<count<<":\n";
                count++;*/

                Keyword end;
                if(a.num_value!=b.num_value)
                {
                    end={37,1,""};
                    std::cout<<"  mov eax, 1\n";
                    std::cout<<"  push eax\n";
                }
                else 
                {
                    end={37,0,""};
                    std::cout<<"  mov eax, 0\n";
                    std::cout<<"  push eax\n";
                }
                sk.push(end);
                in_p++;
            }
            else if((*in_p).str_value=="==")
            {
                //std::cout<<"xor eax, ebx\n";
                //std::cout<<"push eax\n";

                /*std::cout<<"cmp eax, ebx\n";   
                std::cout<<"je equal_"<<count<<"\n"; 
                std::cout<<"mov eax, 0";       
                std::cout<<"push eax\n"; 
                std::cout<<"jmp end_compare_"<<count<<"\n";  
                std::cout<<"\n";
                std::cout<<"equal_"<<count<<":\n";
                std::cout<<"mov eax, 1\n"; 
                std::cout<<"push eax\n";  
                std::cout<<"\n";
                std::cout<<"end_compare_"<<count<<":\n";
                count++;*/

                Keyword end;
                if(a.num_value==b.num_value)
                {
                    end={37,1,""};
                    std::cout<<"  mov eax, 1\n";
                    std::cout<<"  push eax\n";
                }
                else 
                {
                    end={37,0,""};
                    std::cout<<"  mov eax, 0\n";
                    std::cout<<"  push eax\n";
                }
                sk.push(end);
                in_p++;
            }
        }
    }
    int x=sk.top().num_value;
    return x;
}

void code_out()
{
    int num=0;
    vector<Variable> V; 
    for(vector<Keyword> line: token)
    {
        if(line[0].type==3)
        {
            if(line[1].type==2)//int main(int argc, int argv){}
            {
                if(line.size()<=5)
                {
                    /*.intel_syntax noprefix # 使用 Intel 语法
                    .global main # 声明 main 函数为全局符号，这使得链接器能够识别程序
                    的入口点。
                    .extern printf # 声明外部函数 printf，表示该函数在其他地方定义，通
                    常是 C 标准库中。
                    .data # 开始数据段，用于定义程序中的初始化数据。
                    format_str:
                    .asciz "%d\n" # 定义一个用于 printf 的格式字符串，输出整数并换行。
                    .text # 开始代码段，包含程序的实际指令。
                    main:
                    push ebp # 将基指针寄存器 ebp 的当前值压入堆栈，保存上一个函
                    数栈帧的基指针
                    mov ebp, esp # 将栈指针 esp 的值复制到基指针 ebp ，设置新的栈帧
                    基指针
                    sub esp, 0x100 
                    */
                    std::cout<<".intel_syntax noprefix\n";
                    std::cout<<".global main\n";
                    if(flag==1)
                        std::cout<<".extern printf\n";
                    std::cout<<"\n";

                    std::cout<<".data\n";
                    if(flag==1)
                    {
                        std::cout<<"format_str:\n";
                        std::cout<<"  .asciz \"%d\\n\"\n";
                    }
                    std::cout<<"\n";
                    
                    std::cout<<".text\n";
                    std::cout<<"main:\n";
                    std::cout<<"  push ebp\n";
                    std::cout<<"  mov ebp, esp\n";
                    std::cout<<"  sub esp, 0x400\n";
                }
                else
                {
                    std::cout<<".intel_syntax noprefix\n";
                    std::cout<<".global main\n";
                    if(flag==1)
                        std::cout<<".extern printf\n";
                    std::cout<<"\n";

                    std::cout<<".data\n";
                    if(flag==1)
                    {
                        std::cout<<"format_str:\n";
                        std::cout<<"  .asciz \"%d\\n\"\n";
                    }
                    std::cout<<"\n";

                    std::cout<<".text\n";
                    std::cout<<"main:\n";
                    std::cout<<"  push ebp\n";
                    std::cout<<"  mov ebp, esp\n";
                    std::cout<<"  sub esp, 0x400\n";
                    /*	movl	%ecx, 16(%rbp)
	                    movq	%rdx, 24(%rbp)*/
                    /*popl    %ecx        # argc
                    vnext:
                    popl    %ecx        # argv
                    test    %ecx, %ecx  # 空指针表明结束
                    jz  exit*/
                    //std::cout<<"  pop ecx\n";
                    //std::cout<<"  vnext:\n";
                    //std::cout<<"  pop ecx\n";
                    /*std::cout<<"  test ecx, ecx\n";
                    std::cout<<"  jz exit\n";
                    std::cout<<"  exit:\n";
                    std::cout<<"  mov eax, 1\n";
                    std::cout<<"  xor ebx, ebx\n";
                    std::cout<<"  int 0x80\n";
                    std::cout<<"  ret\n";*/
                    Variable v;
                    v={"argc",8,1};
                    V.push_back(v);
                    varToInt["argc"]=1;
                    std::cout<<"  mov ecx, DWORD PTR [ebp+"<<findvar(V,"argc")<<"]\n";
                    Variable y;
                    y={"argv",12,0};
                    V.push_back(y);
                    varToInt["argc"]=0;
                    std::cout<<"  mov edx, DWORD PTR [ebp+"<<findvar(V,"argv")<<"]\n";
                    std::cout<<"\n";
                }
            }
            else if(line[1].type==36)//int x;
            {
                if(findvar(V,line[1].str_value)<0)
                {
                    Variable v={line[1].str_value,++num};
                    V.push_back(v);
                }
                //vector<Keyword>::iterator it=line.end()-1;
                std::cout<<"  mov DWORD PTR [ebp-"<<4*findvar(V,line[1].str_value)<<"],  0\n";
            }
        }
        else if(line[0].type==4)//return 
        {
            if(line[1].type==36)
            {
                std::cout<<"  mov eax, DWORD PTR [ebp-"<<4*findvar(V,line[1].str_value)<<"]\n";
                std::cout<<"  leave\n";
                std::cout<<"  ret\n";
            }
            else if(line[1].type==37)
            {
                std::cout<<"  mov eax, 0\n";
                std::cout<<"  leave\n";
                std::cout<<"  ret\n";
            }
        }
        else if(line[0].type==5)//println_int
        {
            /*  push DWORD PTR [ebp-4] # 准备 printf 的参数
                push offset format_str 
                call printf # 调用 printf 函数
                add esp, 8
            */
           if(line[2].type==36)
            {
                std::cout<<"  push DWORD PTR [ebp-"<<4*findvar(V,line[2].str_value)<<"]\n";
            }
            else if(line[2].type==37)
            {
                std::cout<<"  mov eax,"<<line[2].num_value<<"\n";
                std::cout<<"  push eax\n";
            }

            std::cout<<"  push offset format_str\n";
            std::cout<<"  call printf\n";
            std::cout<<"  add esp, 8\n";
        }
        else if(line[0].type==36)//表达式
        {
            if(line.size()==3)
            {
                if(line[2].type==37)
                {
                    std::cout<<"  mov DWORD PTR [ebp-"<<4*findvar(V,line[0].str_value)<<"], "<<line[2].num_value<<"\n";
                    varToInt.insert(make_pair(line[0].str_value, line[2].num_value));
                }
                else if(line[2].type==36)
                {
                    if(line[2].str_value!="argc"||line[2].str_value!="argv")
                        std::cout<<"  mov eax, DWORD PTR [ebp-"<<4*findvar(V,line[2].str_value)<<"]\n";
                    else
                        std::cout<<"  mov eax, DWORD PTR [ebp+"<<findvar(V,line[2].str_value)<<"]\n";

                    std::cout<<"  mov DWORD PTR [ebp-"<<4*findvar(V,line[0].str_value)<<"], eax\n";
                    varToInt.insert(make_pair(line[0].str_value, varToInt[line[2].str_value]));
                }
                
            }
            else
            {
                Keyword first=line[0];
                vector<Keyword> infix=line;
                vector<Keyword> postfix;
                infixToPostfix(infix,postfix);

                /*for(Keyword k:postfix)
                    std::cout<<k.type<<"  "<<k.str_value<<"  "<<k.num_value<<"\n";
                std::cout<<"******\n";*/
                int x;
                x=postfix_out(postfix,V);

                //line[0].num_value=x;
                varToInt[line[0].str_value]=x;
                

                std::cout<<"  pop eax\n";
                std::cout<<"  mov DWORD PTR [ebp-"<<4*findvar(V,first.str_value)<<"], eax\n";
            }
        }
    }
}