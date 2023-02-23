#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <string>
using namespace std;

map<char,int> sign; //使用map是为代码方便添加其他的操作数
void initialization();
string infixToProfix(string infix);

int main()
{
    initialization();
    string infix;
    cin>>infix;
    cout<<infixToProfix(infix);
    return 0;
}

string infixToProfix(string infix)
{  
stack<char> process;
string profix;
for(int i=0;i<infix.size();i++)
{
    if(infix[i]<='9'&&infix[i]>='0')
    {
        profix+=infix[i];
    }
    else
    {
        if(process.empty()||infix[i]=='(')
            {
                process.push(infix[i]);
                //cout<<infix[i]<<endl;
            }
        else if(infix[i]==')')
        {
            while(!process.empty())     
            {
                if(process.top()=='(')
                {   //cout<<"pop"<<process.top()<<endl;
                    process.pop();break;
                }
                else
                {
                    profix+=process.top();
                    //cout<<"pop"<<process.top()<<endl;
                    process.pop();
                }
            }     
        }
        else
        {
            while(!process.empty()&&process.top()!='('&&sign[process.top()]>=sign[infix[i]])
            {
                profix+=process.top();
                //cout<<"pop"<<process.top()<<endl;
                process.pop();
                
            }
            process.push(infix[i]);
            //cout<<"push"<<infix[i]<<endl;
        }
    }
}
while(!process.empty())                                                                                                                                                                                                                                                                                        
{
    profix+=process.top();
    //cout<<"pop"<<process.top()<<endl;
    process.pop();
}
return profix;                                                                                                                                                                               
}

void initialization()
{
    sign.insert(pair<char,int>('+',1));
    sign.insert(pair<char,int>('-',1));
    sign.insert(pair<char,int>('*',2));
    sign.insert(pair<char,int>('/',2));
    sign.insert(pair<char,int>('m',2));  
}


//-------------------------------以下是优化版本(支持多位数字，功能包括conversion和evaluation)-------------------------------:
/*
#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <string>
using namespace std;

map<string,int> sign; 
vector<string> infixToVector(string x);
vector<string> profixToVector(string x,int choose);
int stringToNumber(string x);
string infixToProfix(string x,int choose);
void initialization();
int getValue(string x,int choose);

int main()
{
    initialization();
    string infix,profix;
    cin>>infix;
    int choose;
    cout<<"请选择profix格式\n用空格分隔数字按1,用()分隔数字按2:";
    while(!(cin>>choose))
    {
        fflush(stdin);
        cin.clear();
    }
    profix=infixToProfix(infix,choose);
    cout<<profix<<endl;
    cout<<getValue(profix,choose)<<endl;
    return 0;
}

void initialization()
{
    sign.insert(pair<string,int>("+",1));
    sign.insert(pair<string,int>("-",1));
    sign.insert(pair<string,int>("*",2));
    sign.insert(pair<string,int>("/",2));
    sign.insert(pair<string,int>("m",2)); 
    //sign.insert(pair<string,int>("",2)); 
}

vector<string> infixToVector(string x)
{
    vector<string> infix;
    for(int i=0,j=0;i<x.size();i++)
    {
        if(x[i]<'0'||x[i]>'9')
        {
            string t;
            t+=x[i];
            infix.push_back(t);
            j=i+1;
        }
        else
        {
            if(i==x.size()-1||x[i+1]<'0'||x[i+1]>'9')
            {
                infix.push_back(x.substr(j,i-j+1));
            }
        }
    }
    // for(auto x:infix)
    // cout<<x<<endl;
    return infix;
}

vector<string> profixToVector(string x,int choose)
{
    vector<string> profix;
    if(choose==1)
    {
        //方法一：空格型
        for(int i=0,j=0;i<x.size();i++)
        {
            if(x[i]<'0'||x[i]>'9')
            {
                string t;
                t+=x[i];
                profix.push_back(t);
                j=i+1;
            }
            else if(x[i+1]==' ')
            {
                profix.push_back(x.substr(j,i-j+1));
                j=i+2;
                i++;
            }
        }
    }
    else
    {
        //方法二：()型
        for(int i=0,j=0;i<x.size();i++)
        {
            if(x[i]=='(')
            {
                j=i+1;
            }
            else if(x[i]==')')
            profix.push_back(x.substr(j,i-j));
            else if(x[i]<'0'||x[i]>'9')
            {
                string t;
                t+=x[i];
                profix.push_back(t);
            }
        }
    }
    //for(auto x:profix)
  //cout<<x<<endl;
    return profix;
}

int stringToNumber(string x)
{
    int result=0;
    if(x[0]=='-')
    {
        for(int i=1;i<x.size();i++)
        {
            result*=10;
            result+=x[i]-'0';
        }
        return -1*result;
    }
    else
    {
        for(int i=0;i<x.size();i++)
        {
            result*=10;
            result+=x[i]-'0';
        }
        return result;
    }
}

string infixToProfix(string x,int choose)
{ 
vector<string> infix=infixToVector(x);
stack<string> process;
string profix;
for(int i=0;i<infix.size();i++)
{
    if(infix[i][0]<='9'&&infix[i][0]>='0')//是数字
    {
        if(choose==1)
            //方法一：
            profix+=infix[i]+' ';//每个数字后面都有一个空格，方便区分数字与数字
        else
            //方法二：
            profix+='('+infix[i]+')';//用()把数字都包裹起来
    }
    else
    {
        if(process.empty()||infix[i]=="(")
            {
                process.push(infix[i]);
                //cout<<"push"<<infix[i]<<endl;
            }
        else if(infix[i]==")")
        {
            while(!process.empty())     
            {
                if(process.top()=="(")
                {  //cout<<"pop"<<process.top()<<endl;
                    process.pop();break;
                }
                else
                {
                    profix+=process.top();
                    //cout<<"pop"<<process.top()<<endl;
                    process.pop();
                }
            }     
        }
        else
        {
            while(!process.empty()&&process.top()!="("&&sign[process.top()]>=sign[infix[i]])
            {
                //cout<<process.top()<<">"<<infix[i]<<endl;
                profix+=process.top();
                //cout<<"pop"<<process.top()<<endl;
                process.pop();
            }
            process.push(infix[i]);
            //cout<<"push"<<infix[i]<<endl;
        }
    }
}
while(!process.empty())                                                                                                                                                                                                                                                                                        
{
    profix+=process.top();
    //cout<<"pop"<<process.top()<<endl;
    process.pop();
}
return profix;                                                                                                                                                                               
}

int getValue(string x,int choose)
{
    stack<int> process;
    vector<string> profix=profixToVector(x,choose);
    while(!process.empty())                                                                                                                                                                                                                                                                                      
        process.pop();
        for(int i=0;i<profix.size();i++)
        {
            if(profix[i][0]>='0'&&profix[i][0]<='9')
            {
                process.push(stringToNumber(profix[i]));
              //cout<<"push"<<stringToNumber(profix[i])<<endl;
            }
            else
            {
                if(process.empty()||profix[i]=="(")
                {
                    //cout<<profix[i];
                  //cout<<"profix error!"<<endl;
                    return -1;
                }
                else 
                {
                    int x1=process.top();
                    process.pop();
                    int x2=process.top();
                    process.pop();
                    int x3;
                    if(profix[i]=="+")
                    x3=x2+x1;
                    else if(profix[i]=="-")
                    x3=x2-x1;
                    else if(profix[i]=="*")
                    x3=x2*x1;
                    else if(profix[i]=="/")
                    x3=x2/x1;
                    else if(profix[i]=="m")
                    x3=x2%x1;
                    else 
                    {cout<<"sign error!"<<endl;return -1;}
                    process.push(x3);
                  //cout<<"push"<<x3<<endl;
				}
            }
        }
        return process.top();

}
*/