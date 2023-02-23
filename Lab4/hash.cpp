#include<iostream>
#include<fstream>
#include<string.h>
#include<vector>
#include<math.h>
using namespace std;
#define CAPACITY 51
enum Nodestatus{Exist=0,Delete=1};
struct hashNode
{
    unsigned  long long number;
    string name;
    string major;
    string sex;
    bool isgirl;
    Nodestatus status;
    hashNode(unsigned long long number1,string name1,string major1,string sex1):number(number1),name(name1),major(major1),sex(sex1){};
};

class myHash
{ 
    int num;
    int capacity;//ʵ�ʲ��ܴ���������Ѱ��һ�������ڵ�ֵʱ��Զ�޷�����ѭ��
    int counter;
    vector<hashNode*> hash;
public:  
    myHash():num(0),capacity(CAPACITY),hash(capacity,NULL){}
    ~myHash(){for(auto x:hash){if(x)delete x;}}
    friend double  Evaluate(myHash studentHash);
    void initMyHash(ifstream& students);
    hashNode* HASH_SEARCH(string name);
    bool HASH_INSERT(hashNode* student);
    bool HASH_DELETE(string name);
};

double  Evaluate(myHash studentHash)
{
    ifstream students;
    unsigned sum=0;
    unsigned num=0;
    students.open("Lab41.txt",ios::in);
    if(students)
    {
        string name;
        unsigned long long number;
        string major;
        string sex;
        string age;
        while(students>>number>>name>>major>>sex)
        {
            num++;
            studentHash.HASH_SEARCH(name);
            // cout<<studentHash.counter<<endl;
            sum+=studentHash.counter;
        }
        // cout<<num<<" "<<sum<<endl;

    }
    return (double)sum/num;
}

int main()
{
    int i=0;
    ifstream students;
    students.open("Lab41.txt",ios::in);
    if(students)
    {
        myHash studentHash;
        studentHash.initMyHash(students);
        hashNode* findStudent=studentHash.HASH_SEARCH("������");
        if(findStudent)
        {
            cout<<findStudent->number<<' '<<findStudent->name<<' '<<findStudent->major<<' '<<findStudent->sex<<endl;
        }
        else
        {
            cout<<"did not find!"<<endl;
        }

        hashNode *newstudent=new hashNode(12345678889,"��һ","ABC","Ů");
        if(studentHash.HASH_INSERT(newstudent))cout<<"successful insert!\n";
        else cout<<"no space for insertion!"<<endl;
        hashNode *newstudent2=new hashNode(12345678239,"����","ABC","Ů");
        if(studentHash.HASH_INSERT(newstudent2))cout<<"successful insert!\n";
        else cout<<"no space for insertion!"<<endl;
        hashNode *newstudent3=new hashNode(12323456789,"����","ABC","��");
        if(studentHash.HASH_INSERT(newstudent3))cout<<"successful insert!\n";
        else cout<<"no space for insertion!"<<endl;
        hashNode *newstudent34=new hashNode(143223456789,"����","ABC","Ů");
        if(studentHash.HASH_INSERT(newstudent34))cout<<"successful insert!\n";
        else cout<<"no space for insertion!"<<endl;
        hashNode *newstudent345=new hashNode(123463456789,"����","ABC","Ů");
        if(studentHash.HASH_INSERT(newstudent345))cout<<"successful insert!\n";
        else cout<<"no space for insertion!"<<endl;
        if(!studentHash.HASH_DELETE("����")) cout<<"did not find!"<<endl;
        if(!studentHash.HASH_DELETE("����")) cout<<"did not find!"<<endl;


        hashNode* findStudent1=studentHash.HASH_SEARCH("Mike");
        if(findStudent1)
        {
            cout<<findStudent1->number<<' '<<findStudent1->name<<' '<<findStudent1->major<<' '<<findStudent1->sex<<endl;
        }
        else
        {
            cout<<"did not find!"<<endl;
        }


        cout<<"average time:"<<Evaluate(studentHash)<<"��"<<endl;
    }
    else
    {
        cout<<"can't find document!"<<endl;
    }
    students.close();
    
    return 0;
}

void myHash::initMyHash(ifstream& students)
{
    if(students)
    {
        string name1;
        unsigned long long number1;
        string major1;
        string sex1;
        while(students>>number1>>name1>>major1>>sex1)
        {
            hashNode* newstudent=new hashNode(number1,name1,major1,sex1);
            HASH_INSERT(newstudent);
        }
    }
}
hashNode* myHash::HASH_SEARCH(string name)
{
    counter=0;
    int key=0,i=0,hashkey;
    for(int i=0;i<name.size();i++)
    {
        key+=name[i];
    }
    key=int(fabs(key))%capacity;
    hashkey=(key+i*i)%capacity;
    counter++;
    while(hash[hashkey])
    {
        if(hash[hashkey]->name==name&&hash[hashkey]->status==Exist)
        {
            return hash[hashkey];
        }
        i++;
        hashkey=(hashkey+i*i)%capacity;//֮ǰ�õ�(key+i*i)%capacity������������ʱ��ѭ���޷��ҵ���λ
        counter++;
    }
    return nullptr;
}
bool myHash::HASH_INSERT(hashNode* student)
{
    if(num<capacity-1)
    {
        int key=0,i=0,hashkey;
        for(int i=0;i<student->name.size();i++)
        {
            key+=student->name[i];
        }
        key=int(fabs(key))%capacity;
        hashkey=(key+i*i)%capacity;
        while(hash[hashkey]&&hash[hashkey]->status==Exist)//��DeleteҲ���Բ���
        {
            i++;
            hashkey=(hashkey+i*i)%capacity;
        }
        if(hash[hashkey])//��Delete�����Ҫ��delete����ط��������¸�ֵ�����������ڴ�����
        {
            delete hash[hashkey];
        }
        hash[hashkey]=student;
        student->status=Exist;
        num++;
        return true;
    }
    else
    {
        return false;
    }
}
bool myHash::HASH_DELETE(string name)
{
    if(HASH_SEARCH(name)&&HASH_SEARCH(name)->status==Exist)
    {
        HASH_SEARCH(name)->status=Delete;
        return true;
    }
    else
    return false;
}