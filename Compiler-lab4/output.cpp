#include"output.h"

map<string,int> varToInt;
extern map<string,vector<string>> func_in_var; //函数入参
extern map<string,vector<string>> func_var;    //函数局部变量
extern vector<string> function_list;            //函数列表 

string func_now="";  //当前函数域
int seqe=1; //记录跳转结构的序号
//stack<Jump> jump_st;

int find_var(string in)
{
    for(int i=0;i<func_var[func_now].size();i++)
    {
        if(func_var[func_now][i]==in)
            return i+1;
    }
    return -10;
}

int find_in_var(string in)
{
    for(int i=0;i<func_in_var[func_now].size();i++)
    {
        if(func_in_var[func_now][i]==in)
            return i+2;
    }
    return -10;
}

int is_InOrOut(string in)
{
    int i=find_var(in);
    int o=find_in_var(in);
    if(i!=-10)
        return 2;
    else if(o!=-10)
        return 1;
    return 0;
}

Jump findIF(stack<Jump> temp)
{
    //stack<Jump> temp=jump_st;
    while(temp.top().type!=1)
    {
        temp.pop();
    }
    return temp.top();

}

Jump findWhile(stack<Jump> temp)
{
    //stack<Jump> temp=jump_st;
    while(temp.top().type!=0)
    {
        temp.pop();
    }
    return temp.top();
}

Jump removeWhile(stack<Jump> &jump_st)
{
    while(jump_st.top().type!=0)
    {
        jump_st.pop();
    }
    Jump j=jump_st.top();
    jump_st.pop();
    return j;
}


int func_cal(vector<Keyword> in)
{
    vector<vector<Keyword>> varlist;    //函数参数列表
    vector<Keyword> ::iterator key=in.begin();
    string func_name=(*key).str_value; //函数名
    stack<string> func_area;
    while(key!=in.end())
    {
        vector<Keyword> temp;
        
        while(true)
        {
            if((*key).type==3)      //跳过函数名
            {
                func_area.push((*key).str_value);
                if((*key).str_value!=func_name)
                    temp.push_back(*key);
                key++;
            }   
            else if((*key).type==11&&func_area.top()==func_name)
            {
                key++;
                break;
            }
            else if((*key).type==8)
            {
                func_area.pop();
                temp.push_back(*key);
                key++;
            }
            else 
            {
                //cout<<"******"<<func_area.top()<<"*******"<<endl;
                temp.push_back(*key);
                key++;
            }
        }  
        varlist.push_back(temp);  
    }
    vector<vector<Keyword>> ::iterator line ;
    for(line=varlist.end()-1;line>=varlist.begin();line--)
    {
        calculate(*line);
    }
    return varlist.size();
    /*while(key!=in.end())
    {
        if((*key).type==3)            //函数名跳过
        {
            key++;
        }
        else if((*key).type==1&&(*(key+1)).type!=2&&(key+1)!=in.end())  //单一变量
        {
            varlist.push(*key);
            key++;
        }
        else if((*key).type==1&&(*(key+1)).type!=2)                     //普通
        {

        }

    }*/
}

void calculate(vector<Keyword> in)
{
    stack<Keyword> st;
    vector<vector<Keyword>> vk;
    vector<Keyword> ::iterator key=in.begin();

    while(key!=in.end())
    {
        if((*key).type==0)  //数字直接进栈
        {
            cout<<"mov eax, "<<(*key).num_value<<endl;
            cout<<"push eax"<<endl;
            //st.push(*key);
            key++;
        }
        else if((*key).type==1) //变量直接进栈
        {
            int flag=is_InOrOut((*key).str_value);
            if(flag==1)
                cout<<"mov eax, DWORD PTR [ebp+"<<4*find_in_var((*key).str_value)<<"]"<<endl;
            else 
                cout<<"mov eax, DWORD PTR [ebp-"<<4*find_var((*key).str_value)<<"]"<<endl;
            cout<<"push eax"<<endl;
            st.push(*key);
            key++;
        }
        else if((*key).type==3)  //函数先计算结果
        {
            string func_name=(*key).str_value;
            vector<Keyword> func;
            while(key!=in.end())
            {
                if((*key).type==8&&(*key).str_value==func_name)
                {
                    key++;
                    break;
                }
                func.push_back(*key);
                key++;
            }
            func_cal(func);

            cout<<"call "<<func_name<<endl; //调用函数

            if(func_in_var[func_name].size()!=0&&func_now=="main")
                cout<<"add esp , "<<4*func_in_var[func_name].size()<<endl;
            else if(func_now!="main")
            {
                cout<<"add esp , "<<4*(func_in_var[func_name].size())<<endl;
            }

            cout<<"push eax"<<endl;     //取得函数值
        }
        else if((*key).type==2)     //符号
        {
            if((*key).str_value=="FU")  //负号
            {
                cout<<"pop eax"<<endl;
                cout<<"neg eax "<<endl;
                cout<<"push eax"<<endl;
            }
            else if((*key).str_value=="~") //求反
            {
                cout<<"pop eax"<<endl;
                cout<<"not eax"<<endl;
                cout<<"push eax"<<endl;
            }
            else if((*key).str_value=="!") //求逻辑非
            {
                cout<<"mov ebx,0"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"cmp eax , ebx"<<endl;
                cout<<"sete al"<<endl;
                cout<<"movzx eax ,al"<<endl;
                cout<<"push eax"<<endl;
            }
            else if((*key).str_value=="+") //加法
            {
                cout<<"pop ebx"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"add eax, ebx"<<endl;
                cout<<"push eax"<<endl;
            }
            else if((*key).str_value=="-") //减法
            {
                cout<<"pop ebx"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"sub eax, ebx"<<endl;
                cout<<"push eax"<<endl;
            }
            else if((*key).str_value=="*") //乘法
            {
                cout<<"pop ebx"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"imul eax, ebx"<<endl;
                cout<<"push eax"<<endl;
            }
            else if((*key).str_value=="/") //除法
            {
                cout<<"pop ebx"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"cdq"<<endl;
                cout<<"idiv ebx"<<endl;
                cout<<"push eax"<<endl;
            }
            else if((*key).str_value=="%") //求余
            {
                cout<<"pop ebx"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"cdq"<<endl;
                cout<<"idiv ebx"<<endl;
                cout<<"push edx"<<endl;
            }
            else if((*key).str_value=="|") //按位或
            {
                cout<<"pop ebx"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"or eax, ebx"<<endl;
                cout<<"push eax"<<endl;
            }
            else if((*key).str_value=="||") //逻辑或
            {
                /*cout<<"mov ebx , 0"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"cmp eax , ebx"<<endl;
                cout<<"setne al"<<endl;
                cout<<"xor eax, eax"<<endl;
                cout<<"movzx eax ,al"<<endl;

                cout<<"mov ecx , 0"<<endl;
                cout<<"pop ebx"<<endl;
                cout<<"cmp ebx , ecx"<<endl;
                cout<<"setne al"<<endl;
                cout<<"xor ecx, ecx"<<endl;
                cout<<"movzx ecx ,al"<<endl;
                
                cout<<"or eax ,ebx"<<endl;
                cout<<"push eax"<<endl;*/

                cout<<"mov ebx , 0"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"cmp eax , ebx"<<endl;
                cout<<"setne al"<<endl;
                
                

                cout<<"mov ecx , 0"<<endl;
                cout<<"pop ebx"<<endl;
                cout<<"cmp ebx , ecx"<<endl;
                cout<<"setne bl"<<endl;

                cout<<"or al ,bl"<<endl;
                cout<<"movzx eax ,al"<<endl;
                
            
                cout<<"push eax"<<endl;



                /*cout<<"pop ebx"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"or eax, ebx"<<endl;
                cout<<"push eax"<<endl;*/
            }
            else if((*key).str_value=="^") //按位异或
            {
                cout<<"pop ebx"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"xor eax, ebx"<<endl;
                cout<<"push eax"<<endl;
            }
            else if((*key).str_value=="&") //按位与
            {
                cout<<"pop ebx"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"and eax, ebx"<<endl;
                cout<<"push eax"<<endl;
            }
            else if((*key).str_value=="&&") //逻辑与
            {
                /*cout<<"mov ebx , 0"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"cmp eax , ebx"<<endl;
                cout<<"setne al"<<endl;
                cout<<"xor eax, eax"<<endl;
                cout<<"movzx eax ,al"<<endl;

                cout<<"mov ebx , 0"<<endl;
                cout<<"pop edx"<<endl;
                cout<<"cmp edx , ebx"<<endl;
                cout<<"setne bl"<<endl;
                cout<<"xor edx, edx"<<endl;
                cout<<"movzx edx ,al"<<endl;
                
                cout<<"and eax ,edx"<<endl;
                cout<<"push eax"<<endl;*/
                cout<<"mov ebx , 0"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"cmp eax , ebx"<<endl;
                cout<<"setne al"<<endl;
              
                cout<<"movzx eax ,al"<<endl;

                cout<<"mov ebx , 0"<<endl;
                cout<<"pop edx"<<endl;
                cout<<"cmp edx , ebx"<<endl;
                cout<<"setne bl"<<endl;
                
                cout<<"and al ,bl"<<endl;
                cout<<"movzx eax ,al"<<endl;
                
                cout<<"push eax"<<endl;
                
                /*cout<<"pop ebx"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"and eax, ebx"<<endl;
                cout<<"push eax"<<endl;*/
            }
            else if((*key).str_value==">") //大于
            {
                cout<<"pop ebx"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"cmp eax , ebx"<<endl;
                cout<<"setg al"<<endl;
                cout<<"movzx eax ,al"<<endl;
                cout<<"push eax"<<endl;
            }
            else if((*key).str_value==">=") //大于等于
            {
                cout<<"pop ebx"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"cmp eax , ebx"<<endl;
                cout<<"setge al"<<endl;
                cout<<"movzx eax ,al"<<endl;
                cout<<"push eax"<<endl;
            }
            else if((*key).str_value=="<") //小于
            {
                cout<<"pop ebx"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"cmp eax , ebx"<<endl;
                cout<<"setl al"<<endl;
                cout<<"movzx eax ,al"<<endl;
                cout<<"push eax"<<endl;
            }
            else if((*key).str_value=="<=") //小于等于
            {
                cout<<"pop ebx"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"cmp eax , ebx"<<endl;
                cout<<"setle al"<<endl;
                cout<<"movzx eax ,al"<<endl;
                cout<<"push eax"<<endl;
            }
            else if((*key).str_value=="==") //等于
            {
                cout<<"pop ebx"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"cmp eax , ebx"<<endl;
                cout<<"sete al"<<endl;
                cout<<"movzx eax ,al"<<endl;
                cout<<"push eax"<<endl;
            }
            else if((*key).str_value=="!=") //不等于
            {
                cout<<"pop ebx"<<endl;
                cout<<"pop eax"<<endl;
                cout<<"cmp eax ,ebx"<<endl;
                cout<<"setne al"<<endl;
                cout<<"movzx eax ,al"<<endl;
                cout<<"push eax"<<endl;
            }
            key++;
        }
        else if((*key).type==11||(*key).type==10||(*key).type==9||(*key).type==8||(*key).type==7||(*key).type==6)
        {
            key++;
        }
        else 
        {
            key++;
        }
    }
}



void code_head()
{
    cout<<".intel_syntax noprefix"<<endl;

    cout<<".global main"<<endl;
    vector<string> ::iterator it= function_list.begin();
    while(it!=function_list.end())
    {
        if((*it)!="main")
            cout<<".global "<<(*it)<<endl;
        it++;
    }
    
    cout<<".data"<<endl;
    cout<<"format_str:"<<endl;
    cout<<"  .asciz \"%d\\n\"\n";
    cout<<".extern printf"<<endl;
    cout<<".text"<<endl;
    cout<<endl;
}


void code_out()
{
    stack<Jump> jump_st;
    code_head();
    for(vector<Keyword> line:token)
    {
        if(line[0].type==5&&line[1].type==3)    //函数定义
        {
            func_now=line[1].str_value;
            cout<<line[1].str_value<<":"<<endl;
            cout<<" push ebp "<<endl;
            cout<<" mov ebp, esp "<<endl;
            if(func_var[line[1].str_value].size()!=0&&line[1].str_value=="main")
                cout<<" sub esp, "<<4*func_var[line[1].str_value].size()<<endl;
            else if(line[1].str_value!="main")
                cout<<" sub esp, "<<4*(func_var[line[1].str_value].size()+1)<<endl;
        }
        else if(line[0].type==5&&line[1].type==1)  //声明变量
        {
            vector<Keyword>::iterator key= line.begin();
            key++;
            while(key!=line.end())
            {
                if((*key).type==1&&(*(key+1)).type==10&&(key+1)!=line.end())     // 普通声明
                {
                    cout<<"mov DWORD PTR [ebp-"<<4*find_var((*key).str_value)<<"], 0"<<endl;
                    key++;
                }
                else if((*key).type==1&&(*(key+1)).str_value=="="&&(key+1)!=line.end()) //赋值声明式
                {
                    cout<<"mov DWORD PTR [ebp-"<<4*find_var((*key).str_value)<<"], 0"<<endl;
                    string var_name=(*key).str_value;
                    key+=2;
                    vector<Keyword> cal;
                    while(key!=line.end())
                    {
                        cal.push_back(*key);
                        key++;
                        if((*key).type==10)
                        {
                            break;
                        }
                    }

                    calculate(cal);
                    cout<<"pop eax"<<endl;
                    cout<<"mov DWORD PTR [ebp-"<<4*find_var(var_name)<<"], eax"<<endl;
                }
                else if((*key).type==11||(*key).type==10||(*key).type==9||(*key).type==8||(*key).type==7||(*key).type==6)
                {
                    key++;
                }
            }
        }
        else if(line[0].type==1&&line[1].str_value=="=")  //计算式
        {
            vector<Keyword>::iterator key= line.begin();
            string var_name=(*key).str_value;
            key+=2;
            vector<Keyword> cal;
            while(key!=line.end())
            {
                cal.push_back(*key);
                key++;
            }
            calculate(cal);
            cout<<"pop eax"<<endl;

            int flag=is_InOrOut(var_name);
            if(flag==1)
                cout<<"mov DWORD PTR [ebp+"<<4*find_in_var(var_name)<<"] , eax"<<endl;
            else 
                cout<<"mov DWORD PTR [ebp-"<<4*find_var(var_name)<<"] , eax"<<endl;
           
        }
        else if(line[0].type==3)   //函数使用
        {
            vector<Keyword>::iterator key= line.begin();
            string func_name=(*key).str_value;
            vector<Keyword> func;
            while(key!=line.end())
            {
                if((*key).type==8&&(*key).str_value==func_name)
                {
                    key++;
                    break;
                }
                func.push_back(*key);
                key++;
            }
            int num=func_cal(func);
            if(func_name=="println_int")
            {    
                cout<<"push offset format_str"<<endl;
                cout<<"call printf "<<endl;
                if(func_now=="main")
                    cout<<"add esp , "<<4*num<<endl;
                else if(func_now!="main")
                    cout<<"add esp , "<<4*(num)<<endl;
            }
            else
            {
                cout<<"call "<<func_name<<endl; //调用函数
                if(func_in_var[func_name].size()!=0&&func_now=="main")
                    cout<<"add esp , "<<4*func_in_var[func_name].size()<<endl;
                else if(func_now!="main")
                {
                    cout<<"add esp , "<<4*(func_in_var[func_name].size())<<endl;
                }
            }
            
        }
        else if(line[0].type==4)    //return
        {
            vector<Keyword>::iterator key= line.begin();
            key++;
            vector<Keyword> cal;
            while(key!=line.end())
            {
                cal.push_back(*key);
                key++;
            }
            calculate(cal);
            cout<<"pop eax"<<endl;

        }
        else if(line[0].type==6)    //退出
        {
            cout<<"leave"<<endl;
            cout<<"ret"<<endl;
            cout<<endl;
        }
        else if((line[0].type==0||line[0].type==1||line[0].type==3)&&line[1].str_value!="=")
        {
            vector<Keyword>::iterator key= line.begin();
            vector<Keyword> cal;
            while(key!=line.end())
            {
                cal.push_back(*key);
                key++;
            }
            calculate(cal);
            cout<<"pop eax"<<endl;
            cout<<"cmp eax,0"<<endl;
        }
        else if(line[0].type==18)    //if
        {
            Jump j;
            j.seq=seqe++;
            j.type=1;
            jump_st.push(j);
            cout<<"je .L_"<<j.seq<<"_if_false"<<endl;
        }
        else if(line[0].type==12&&line[1].type==19) //else
        {
            Jump j=findIF(jump_st);

            cout<<"jmp .L_"<<j.seq<<"_if_end"<<endl;
            cout<<".L_"<<j.seq<<"_if_false:"<<endl;
        }
        else if((line[0].type==12||line[0].type==21)&&line[1].type==13)//if_else结束
        {
            if(line[0].type==12)
            {
                Jump j=findIF(jump_st);
                jump_st.pop();
                cout<<".L_"<<j.seq<<"_if_false:"<<endl;
            }
            else 
            {
                Jump j=findIF(jump_st);
                jump_st.pop();
                cout<<".L_"<<j.seq<<"_if_end:"<<endl;
            }
        }
        else if(line[0].type==20) //while条件
        {
            Jump j;
            j.seq=seqe++;
            j.type=0;
            jump_st.push(j);
            cout<<".L_"<<j.seq<<"_while_condition:"<<endl;
        }
        else if(line[0].type==14)   //while判断中止
        {
            Jump j=findWhile(jump_st);

            cout<<"je .L_"<<j.seq<<"_while_end"<<endl;
        }
        else if(line[0].type==15)   //结束循环
        {
            Jump j=removeWhile(jump_st);
            cout<<"jmp .L_"<<j.seq<<"_while_condition"<<endl;
            cout<<".L_"<<j.seq<<"_while_end:"<<endl;
        }
        else if(line[0].type==16)   //break
        {
            Jump j=findWhile(jump_st);
            cout<<"jmp .L_"<<j.seq<<"_while_end"<<endl;
        }
        else if(line[0].type==17)   //continue
        {
            Jump j=findWhile(jump_st);
            cout<<"jmp .L_"<<j.seq<<"_while_condition"<<endl;
        }
        else
        {
            cout<<endl;
        }
    }
}


