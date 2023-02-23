#include<iostream>
using namespace std;

int CAPACITY;//堆的容量
//其实也可以把n设为全局变量，减少了函数的传参（n 代表堆中目前元素个数）

//能构造一个 d-ary max-heap
void HEAPIFY(int* array,int n,int d);
// HEAPIFY中用到的函数
void build(int* array,int n,int d,int i);
void swap(int* array,int i,int j);
// EXTRACT_MAX()：返回 heap 中最大值，并将该元素从 heap 中删除
int EXTRACT_MAX(int* array,int n,int d);
// INSERT(x)：在 heap 中加入一个值为 x 的元素
void INSERT(int* array,int n,int d,int x);
// INCREASE_KEY(A,i,k)：先将 A[i]赋值成 max(A[i], k)，再更新 A 这个 d-ary max-heap。
void INCREASE_KEY(int* array,int n,int d,int i,int k);
//测试输出
void test(int* array,int n,int d);

int main()
{
    int d;
    cin>>CAPACITY>>d;
    int n=CAPACITY;
    int* array=new int[CAPACITY];
    for(int i=0;i<CAPACITY;i++)
    {
        cin>>array[i];
    }
    test(array,n,d);//测试输出结果
    delete[] array;
    return 0;
}


void test(int* array,int n,int d)
{
    
    HEAPIFY(array,n,d);
    for(int i=0;i<n;i++)
    {
        cout<<array[i]<<' ';
    }
    cout<<endl;


    EXTRACT_MAX(array,n,d);
    n--;
    for(int i=0;i<n;i++)
    {
        cout<<array[i]<<' ';
    }
    cout<<endl;


    INSERT(array,n,d,81);//自定义了一些数据
    n++;
    for(int i=0;i<n;i++)
    {
        cout<<array[i]<<' ';
    }
    cout<<endl;


    INCREASE_KEY(array,n,d,8,797);//自定义了一些数据
    for(int i=0;i<n;i++)
    {
        cout<<array[i]<<' ';
    }
    cout<<endl;
}

void swap(int* array,int i,int j)
{
    if(i==j)return;
    int t=array[i];
    array[i]=array[j];
    array[j]=t;
}

void HEAPIFY(int* array,int n,int d)
{
    //array[i]结点的双亲为array[(i-1)/d]
    //index从最后一个非叶子结点开始遍历
    for(int index=(n-1-1)/d;index>=0;index--)
    {
        build(array,n,d,index);
    }
}

void build(int* array,int n,int d,int i)
{
    // array[i]结点的最左边的孩子为array[i*d+1]，最右边的孩子为array[i*d+d]
    int j,maxindex=i;
    for(j=i*d+1;j<n&&j<=i*d+d;j++)
    {
        if(array[maxindex]<array[j])
        maxindex=j;
    }
    if(maxindex!=i)
    { 
        swap(array,i,maxindex);
        build(array,n,d,maxindex);
    }
}

//返回 heap 中最大值，并将该元素从 heap 中删除
int EXTRACT_MAX(int* array,int n,int d)
{
    if(n>0)
    {
        int max=array[0];
        swap(array,0,--n);
        //HEAPIFY(array,--n,d);//错误用不到把所有节点都重构
        //只要让新的头结点不断和子节点比较以及下移就可以了:
                    build(array,n,d,0);
        return max;
    }
    else
    {
        cout<<"empty heap!"<<endl;
        return -1;
    }
}

// 不能够扩充容量INSERT的版本：
void INSERT(int* array,int n,int d,int x)
{
    if(n<CAPACITY)
    { 
        //array[n]=x;
        // //HEAPIFY(array,++n,d);//用不到全构建一遍：
        //法一：
        //              array[n]=x;
        //             int i=n;
        //             while(i>0)
        //             {
        //                 if(array[i]>array[(i-1)/d])
        //                 {
        //                     swap(array,i,(i-1)/d);
        //                     i=(i-1)/d;
        //                 }
        //             }
        //法二：
                    array[n]=1<<31;
                    n++;
                    INCREASE_KEY(array,n,d,n-1,x);
    }
    else
    {
        cout<<"lack of space!"<<endl;
    }
}

//未修改：
// 能够扩充容量INSERT的版本：
// int* INSERT(int* array,int n,int d,int x)
// {
// //若想扩展堆的容量也可以重新分配空间（多一个元），把原数组依次赋值给新数组，
// //再在数组最末端加上新的元素然后再HEAPIFY，
// //最后delete掉原数组，让函数返回新的数组的地址并赋值给主函数的array
//     if(n==CAPACITY)
//     {
//         int *temp=array;
//         array=new int[CAPACITY+1]
//         for(int i=0;i<n;i++)
//         array[i]=temp[i];
//         delete temp;
//     }
//     array[n]=x;
//     HEAPIFY(array,++n,d);
//         return array;
// }

void INCREASE_KEY(int* array,int n,int d,int i,int k)
{
    if(i<n&&i>=0&&array[i]<k)
    {
        array[i]=k;
        //HEAPIFY(array,n,d);//用不到全构建一遍：
                    while(i>0)
                    {
                        if(array[i]>array[(i-1)/d])
                        {
                            swap(array,i,(i-1)/d);
                            i=(i-1)/d;
                        }
                    }
    }
}

//----------------还写了vector版本，为了更方便地扩充heap的容量：----------------
// #include<iostream>
// #include<vector>
// using namespace std;
// //对任意的 n 和 d 以及初始数据（可以读入或随机生成），能构造一个 d-ary max-heap
// void heapify(vector<int> *array,int d);
// void build(vector<int> *array,int d,int i);
// void swap(vector<int> *array,int i,int j);
// // EXTRACT_MAX()：返回 heap 中最大值，并将该元素从 heap 中删除
// int EXTRACT_MAX(vector<int> *array,int d);
// // INSERT(x)：在 heap 中加入一个值为 x 的元素
// void INSERT(vector<int> *array,int d,int x);
// // INCREASE_KEY(A,i,k)：先将 A[i]赋值成 max(A[i], k)，再更新 A 这个 d-ary max-heap。
// void INCREASE_KEY(vector<int> *array,int d,int i,int k);
// int main()
// {
//     int d,n;
//     cin>>n>>d;
//     vector<int> array;
//     for(int i=0;i<array.size();i++)
//     {
//         int t;
//         cin>>t;
//         array.push_back(t);
//     }
//     for(int i=0;i<array.size();i++)
//     {
//         cout<<array[i]<<' ';
//     }
//     cout<<endl;
//     heapify(&array,d);
//     for(int i=0;i<array.size();i++)
//     {
//         cout<<array[i]<<' ';
//     }
//     cout<<endl;
//     EXTRACT_MAX(&array,d);
//     for(int i=0;i<array.size();i++)
//     {
//         cout<<array[i]<<' ';
//     }
//     cout<<endl;
//     INSERT(&array,d,81);
//     for(int i=0;i<array.size();i++)
//     {
//         cout<<array[i]<<' ';
//     }
//     cout<<endl;
//     INCREASE_KEY(&array,d,8,797);
//     for(int i=0;i<array.size();i++)
//     {
//         cout<<array[i]<<' ';
//     }
//     cout<<endl;
//     return 0;
// }
// void swap(vector<int> *array,int i,int j)
// {
//     if(i==j)return;
//     int t=(*array)[i];
//     (*array)[i]=(*array)[j];
//     (*array)[j]=t;
// }
// void heapify(vector<int> *array,int d)
// {
//     int n=(*array).size();
//     for(int index=n-1;index>=0;index--)
//     {
//         build(array,d,index);
        
//     }

// }
// void build(vector<int> *array,int d,int i)
// {
//     int n=(*array).size();
//     if(i*d+1>n-1)return;
//     int j,maxindex=i;
//     for(j=i*d+1;j<n&&j<=i*d+d;j++)
//     {
//         if((*array)[maxindex]<(*array)[j])
//         maxindex=j;
//     }
//     if(maxindex!=i)
//    { swap(array,i,maxindex);
//     build(array,d,maxindex);}
// }
// //返回 heap 中最大值，并将该元素从 heap 中删除
// int EXTRACT_MAX(vector<int> *array,int d)
// {
//     if(!(*array).empty())
//     {
//         int max=(*array)[0];
//         swap(array,0,(*array).size()-1);
//         (*array).pop_back();
//         heapify(array,d);
//         return max;
//     }
//     else
//     {
//         cout<<"empty heap!"<<endl;
//         return -1;
//     }
// }

// void INSERT(vector<int> *array,int d,int x)
// {
//     (*array).push_back(x);
//     heapify(array,d);
// }

// void INCREASE_KEY(vector<int> *array,int d,int i,int k)
// {
//     if(i<(*array).size()&&i>=0&&(*array)[i]<k)
//     {
//         (*array)[i]=k;
//         heapify(array,d);
//     }
// }