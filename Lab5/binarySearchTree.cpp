#include<iostream>
#include<vector>
using namespace std;
struct node
{
    int key,value;
    node *parent,*left,*right;
    node(){parent=left=right=NULL;}
    node(int key1,int value1){parent=left=right=NULL;key=key1;value=value1;}
};

//以下三个函数用于traversal_函数的遍历：
vector<int> preorder(node* p,vector<int> result);
vector<int> inorder(node* p,vector<int> result);
vector<int> postorder(node* p,vector<int> result);

class binarySearchTree
{
private:
    node* head;
public:
    binarySearchTree(vector<int> arraykey,vector<int> arrayvalue);
    ~binarySearchTree();
    node* search(int key);
    int search_recursion(int key);//得到key值为key的节点的value值(调用了search)
    int minimum();
    int maximum();
    int successor(int key);//调用了successorNode
    node* successorNode(int key);
    int predecessor(int key);//调用了predecessorNode
    node* predecessorNode(int key);
    void insert(int key,int value);//给key和value来insert
    void insertNode(node* newnode);//直接给一个node*来insert
    void deletenode(int key);//根据key来delete
    vector<int> traversal_pre();//先序遍历
    vector<int> traversal_in();//中序遍历
    vector<int> traversal_post();//后序遍历
    void deleteAllNode(node* p);//用于析构函数，递归调用
};
int main()
{
    vector<int> arraykey={15,5,16,3,12,20,10,13,18,23,6,7};
    vector<int> arrayvalue={1,2,3,4,5,6,7,8,9,10,11,12};
    binarySearchTree tree(arraykey,arrayvalue);

    cout<<tree.predecessor(16)<<endl;
    cout<<tree.successor(18)<<endl;
    cout<<"------------"<<endl;


    vector<int> test;
    test=tree.traversal_pre();
    cout<<"------------"<<endl;
    cout<<"traversal_pre:"<<endl;
    for(auto x:test)
    cout<<x<<endl;

    test.clear();
    test=tree.traversal_in();
    cout<<"------------"<<endl;
    cout<<"traversal_in:"<<endl;
    for(auto x:test)
    cout<<x<<endl;

    test.clear();
    test=tree.traversal_post();
    cout<<"------------"<<endl;
    cout<<"traversal_post:"<<endl;
    for(auto x:test)
    cout<<x<<endl;

    tree.deletenode(5);
    cout<<endl<<endl<<"after delete:"<<endl;
    test=tree.traversal_pre();
    cout<<"------------"<<endl;
    cout<<"traversal_pre:"<<endl;
    for(auto x:test)
    cout<<x<<endl;

    test.clear();
    test=tree.traversal_in();
    cout<<"------------"<<endl;
    cout<<"traversal_in:"<<endl;
    for(auto x:test)
    cout<<x<<endl;

    test.clear();
    test=tree.traversal_post();
    cout<<"------------"<<endl;
    cout<<"traversal_post:"<<endl;
    for(auto x:test)
    cout<<x<<endl;

    return 0;
}

binarySearchTree::binarySearchTree(vector<int> arraykey,vector<int> arrayvalue)
{
    head=new node(arraykey[0],arrayvalue[0]);
    for(int i=1;i<arraykey.size();i++)
    {
        insert(arraykey[i],arrayvalue[i]);
    }
}
void binarySearchTree::insert(int key,int value)
{
    node* newnode=new node(key,value);
    insertNode(newnode);
}
void binarySearchTree::insertNode(node* newnode)
{
    node *p=head;
    while(p->left||p->right)
    {
        if(newnode->key<p->key)
        {
            if(p->left)
            p=p->left;
            else
            break;
        }
        else
        {
            if(p->right)
            p=p->right;
            else
            break;
        }
    }
    newnode->parent=p;
    if(newnode->key<p->key)
    {
        p->left=newnode;
    }
    else
    {
        p->right=newnode;
    }

}
node* binarySearchTree::search(int key)
{
    node* p=head;
    while(p&&p->key!=key)
    {
        if(key<p->key)
        p=p->left;
        else
        p=p->right;
    }
    return p;
}
int binarySearchTree::search_recursion(int key)
{
    node* p=search(key);
    if(!p)
    {
        return -1;
    }
    return p->value;
}
void binarySearchTree::deletenode(int key)
{
    node* p=search(key);
    if(!p)
    {
        cout<<"can't find!"<<endl;
    }
    else
    {
        if(!p->left&&!p->right)//没有孩子
        {
            if(p->parent)//有父母
            {
                if(p->parent->left==p)
                {
                    p->parent->left=NULL;
                }
                else 
                {
                    p->parent->right=NULL;
                }
            }
        }
        else if(!p->left)//只有右孩子
        {
            if(p->parent)//有父母
            {
                if(p->parent->left==p)
                {
                    p->parent->left=p->right;
                }
                else 
                {
                    p->parent->right=p->right;
                }
            }
            else//无父母，是头结点
            {
                head=p->right;
            }
            p->right->parent=p->parent;
        }
        else if(!p->right)//只有左孩子
        {
            if(p->parent)//有父母
            {
                if(p->parent->left==p)
                {
                    p->parent->left=p->left;
                }
                else 
                {
                    p->parent->right=p->left;
                }
            }
            else//无父母，是头结点
            {
                head=p->left;
            }
            p->left->parent=p->parent;
        }
        else //左右孩子都有
        {
            node* newp=successorNode(key);

            //或者可以直接改变数据域：
            // p->value=newp->value;
            // p->key=newp->key;
            //......

            if(newp==p->right)//newp就是p右孩子
            {
                if(p->parent->left==p)
                {
                    p->parent->left=newp;
                }
                else 
                {
                    p->parent->right=newp;
                }
                newp->left=p->left;
                p->left->parent=newp;
            }
            else
            {
                newp->parent->left=newp->right;
                if(p->parent->left==p)
                {
                    p->parent->left=newp;
                }
                else 
                {
                    p->parent->right=newp;
                }
                newp->left=p->left;
                newp->right=p->right;
                p->left->parent=newp;
                p->right->parent=newp;
            }
        }
        delete p;
    }
}
void binarySearchTree::deleteAllNode(node* p)
{
    if(!p)return;
    node* l=p->left,*r=p->right;
    delete p;
    deleteAllNode(l);;
    deleteAllNode(r);
}
binarySearchTree::~binarySearchTree()
{
    deleteAllNode(head);
}
int binarySearchTree::minimum()
{
    if(head)
    {
        node* min=head;
        while(min->left)
        {
            min=min->left;
        }
        return min->value;
    }
    else
    {
        cout<<"empty!"<<endl;
        return -1;
    }
    
}
int binarySearchTree::maximum()
{
    if(head)
    {
        node* max=head;
        while(max->right)
        {
            max=max->right;
        }
        return max->value;
    }
    else
    {
        cout<<"empty!"<<endl;
        return -1;
    }
}
vector<int> binarySearchTree::traversal_pre()
{
    vector<int> result;
    result=preorder(head,result);
    return result;
}
vector<int> preorder(node* p,vector<int> result)
{
    if(!p)return result;
    result.push_back(p->value);
    result=preorder(p->left,result);
    result=preorder(p->right,result);
    return result;
}
vector<int> binarySearchTree::traversal_in()
{
    vector<int> result;
    result=inorder(head,result);
    return result;
}
vector<int> inorder(node* p,vector<int> result)
{
    if(!p)return result;
    result=inorder(p->left,result);
    result.push_back(p->value);
    result=inorder(p->right,result);
    return result;
}
vector<int> binarySearchTree::traversal_post()
{
    vector<int> result;
    result=postorder(head,result);
    return result;
}
vector<int> postorder(node* p,vector<int> result)
{
    if(!p)return result;
    result=postorder(p->left,result);
    result=postorder(p->right,result);
    result.push_back(p->value);
    return result;
}
node* binarySearchTree::successorNode(int key)
{
    //查找比key值大的最小key值的元素
    node* p =search(key);
    if(p->right)
    {
        p=p->right;
        while(p->left)
        {
            p=p->left;
        }
        return p;
    }
    while(p->parent&&p->parent->key<=key)
        p=p->parent;
    if(p->parent)
        return p->parent;
    return NULL;
}
int binarySearchTree::successor(int key)
{
    node *findNode=successorNode(key);
    if(findNode)
    return findNode->value;
    else
    {
        cout<<"Cannot find a node with a Key smaller than its own key!"<<endl;
        return -1;
    }
    
}
node* binarySearchTree::predecessorNode(int key)
{
     //查找比key值小的最大key值的元素
    node* p =search(key);
    if(p->left)
    {
        p=p->left;
        while(p->right)
        {
            p=p->right;
        }
        return p;

    }
    while(p->parent&&p->parent->key>=key)
        p=p->parent;
    if(p->parent)
        return p->parent;
    return NULL;
}
int binarySearchTree::predecessor(int key)
{
    node *findNode=predecessorNode(key);
    if(findNode)
    return findNode->value;
    else
    {
        cout<<"Cannot find a node with a Key smaller than its own key!"<<endl;
        return -1;
    }
}
