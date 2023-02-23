#include<iostream>
using namespace  std;

void InsertSort(int *array,int left,int right);

int main()
{
    int n;
    cin>>n;
    if(n>=0)
    {
        int* array=new int[n];
        for(int i=0;i<n;i++)
             cin>>array[i];
        InsertSort(array,0,n-1);
        // cout<<"after insertsort:"<<endl;
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

void InsertSort(int *array,int left,int right)
{
    for(int i=left+1;i<=right;i++)
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