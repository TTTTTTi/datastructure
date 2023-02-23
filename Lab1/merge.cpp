#include<iostream>
//#include<stdlib.h>
using namespace  std;

void MergeSort(int *array,int left,int right);//left,right代表下标
void merge(int *array,int left,int right);

int main()
{
    int n;
    cin>>n;
    if(n>=0)
    {
        int* array=new int[n];
        for(int i=0;i<n;i++)
            cin>>array[i];
        MergeSort(array,0,n-1);
        // cout<<"after mergesort:"<<endl;
        for(int i=0;i<n;i++)
                cout<<array[i]<<' ';
        delete[] array;
    }
    else
    {
        cout<<"number error!"<<endl;
    }   

    return 0;
}

void MergeSort(int *array,int left,int right)//left,right代表下标
{
    if(right>left)
    {
        int mid=left+(right-left)/2;
        MergeSort(array,left,mid);
        MergeSort(array,mid+1,right);
        merge(array,left,right);
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
