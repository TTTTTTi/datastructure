#include<iostream>
#include<stdlib.h>
#include <chrono>
#include <fstream>
#include<string.h>
#define CNT 100//测试次数，当n很大时，可以适量减小CNT，当n不是很大时为了准确性也可以适量增大CNT

using namespace std;

void ImprovedSort(int *array,int left,int right,int k);//left,right代表下标
void merge(int *array,int left,int right);//left,right代表下标
void InsertSort(int *array,int len);
int selectK(int *array,int n);
int getTime(int *array,int n ,int k);//得到每次运行的时间，并且是算了CNT次求平均的值

int main()
{
    int n,k;
    cin>>n>>k;
    //ifstream in;
    // in.open("testdata100000.txt",ios::out);//个人测试时使用了自己生成的数据集，每次使用一样的数据减小误差
    // if(in)
    // {
        if(n>1&&k>1&&k<=n)
        {
            int* array=new int[n];
            for(int i=0;i<n;i++)
                cin>>array[i];//in>>array[i];//个人测试时是从文件中取数据的
            //cout<<"k:"<<selectK(array,n);//要在排序之前完成K的选取，要不然array已经是排好序的了
            ImprovedSort(array,0,n-1,k);
            // cout<<"after improvedsort:"<<endl;
            for(int i=0;i<n;i++)
                cout<<array[i]<<' ';
            delete[] array;
        }
        else
        {
            cout<<"number error!"<<endl;
        }
    //}
    return 0;
}

void ImprovedSort(int *array,int left,int right,int k)//left,right代表下标
{
    if(right-left+1>=k)
    {
        int mid=left+(right-left)/2;
        ImprovedSort(array,left,mid,k);
        ImprovedSort(array,mid+1,right,k);
        merge(array,left,right);
    }
    else//区间元素少于k个就用插入排序
    {
        InsertSort(array+left,right-left+1);
    }
}

void merge(int *array,int left,int right)
{
    int mid=left+(right-left)/2;
    int *temp=new int[right-left+1];
    int i=0,leftp=left,rightp=mid+1;
    for(;leftp<=mid&&rightp<=right;i++)
    {
        if(array[leftp]<=array[rightp])
        {
            temp[i]=array[leftp];
            leftp++;
        }
        else
        {
            temp[i]=array[rightp];
            rightp++;
        }
    }
    while(leftp<=mid)
    {
        temp[i++]=array[leftp++];
    }
    while(rightp<=right)
    {
        temp[i++]=array[rightp++];
    }
    for(int i=left,j=0;i<=right;i++,j++)
    {
        array[i]=temp[j];
    }
    delete[] temp;
}

void InsertSort(int *array,int len)
{
    for(int i=1;i<len;i++)
    {
        for(int j=i;j>0;j--)
        {
            if(array[j]<array[j-1])
            {
                int t=array[j];
                array[j]=array[j-1];
                array[j-1]=t;
            }
            else
            break;
        }
    }
}

int selectK(int *array,int n)
{
    unsigned long long int mintime=~0;
    int bestk=n;
    int k=2*n;//k=n的情况也要测试，而getTime的参数用的是k/2，所以要初始化为2n；
    while(k>=4&&k%2==0)//因为k不可以等于1，若k为3则，k/2是1，所以k要>=4
    {
        int time=getTime(array,n,k/2);//getTime的参数用的是k/2而不是n是因为：
        //k为奇数时，才考虑k/2和k/2+1的情况,用k/2就可以在第一次循环时判断k是不是奇数就可以了
        if(time<mintime)
        {
            bestk=k/2;
            mintime= time  ;     
        }
        k/=2;
    }
    while(k>=4)//出现了奇数后，每次都要多考虑一种加一的情况
    {
        int time1=getTime(array,n,k/2),time2=getTime(array,n,k/2+1);
        if(time1<mintime)
        {
            bestk=k/2;
            mintime= time1  ;     
        }
        if(time2<mintime)
        {
            bestk=k/2+1;
            mintime= time2  ;     
        }
        k/=2;
    }
    if(k==3)//也要把k=2考虑进去
    {
        int time=getTime(array,n,2);
        if(time<mintime)
        {
            bestk=2;   
        }
    }
    return bestk;
}

int getTime(int *array,int n ,int k)
{
    int* newarray=new int[n];
    unsigned long long int time=0;
    for(int count=0;count<CNT;count++)//多次求时间取平均，减小误差
    {
        for(int i=0;i<n;i++)
            newarray[i]=array[i];
        auto start = std::chrono::steady_clock::now();
        ImprovedSort(newarray,0,n-1,k);
        auto end = std::chrono::steady_clock::now();
        //cout<<std::chrono::duration_cast<std::chrono::microseconds >(end - start).count()<<endl;
        // getchar();
        time+=std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
    //getchar();
    delete[] newarray;
    //cout<<k<<' '<<time<<endl;
    return time/CNT;
}