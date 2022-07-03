#include <iostream>
using namespace std;

class BSTNode   //二叉检索树树结点类
{
private:
    string cityname;  //城市名称
    int x;  //横纵坐标
    int y;
    BSTNode* lc;  //左右结点
    BSTNode* rc;
public:
    BSTNode(string name,int cx,int cy)
    {
        cityname=name;
        x=cx;
        y=cy;
        lc=NULL;
        rc=NULL;
    }
    ~BSTNode(){}
    string getname(){return cityname;}
    int getx(){return x;}
    int gety(){return y;}
    inline BSTNode* left() const{return lc;}
    inline BSTNode* right() const{return rc;}

    void setname(string name){cityname=name;}
    void setx(int cx){x=cx;}
    void sety(int cy){y=cy;}
    void setleft(BSTNode* b){lc=(BSTNode*)b;}  //设置左右结点
    void setright(BSTNode* b){rc=(BSTNode*)b;}
};

class BST   //二叉检索树
{
private:
    BSTNode* root;  //根节点
    int nodecount;  //结点个数
    void clearhelp(BSTNode* root);
    BSTNode* inserthelp(BSTNode* root,string name,int x,int y);
    BSTNode* findhelp(BSTNode* root,string name);
    BSTNode* getmin(BSTNode* root);
    BSTNode* deletemin(BSTNode* root);
    BSTNode* removehelp(BSTNode* root,string name);
    void printhelp(BSTNode* root);
    void printhelp_1(BSTNode* root,char ch);
    void printhelp_2(BSTNode* root,int x,int y,int dis);
public:
    BSTNode* getroot(){return root;}
    BST(){root=NULL; nodecount=0;}
    ~BST(){clearhelp(root);}
    void clear()
    {
        clearhelp(root);
        root=NULL;
        nodecount=0;
    }
    void insert(string name,int x,int y)   //按城市名称的插入功能
    {
        root=inserthelp(root,name,x,y);
        nodecount++;
    }
    void find(BSTNode* root,string name)   //按城市名称检索
    {
        BSTNode* temp=findhelp(root,name);
        if (temp!=NULL)
            cout<<"find it:("<<temp->getx()<<","<<temp->gety()<<")\n";
        else
            cout<<"not find it!\n";
    }
    void remove(BSTNode* root,string name)  //按城市名称删除
    {
        BSTNode* temp=findhelp(root,name);
        if (temp!=NULL)
        {
            root=removehelp(root,name);
            nodecount--;
        }
    }
    void print_all()    //中序遍历打印二叉检索树
    {
        if (root==NULL)
            cout<<"The BST is empty.\n";
        else
            printhelp(root);
    }
    void print_1etter(char ch)   //打印指定字母打头的所有城市记录
    {
        if (root==NULL)
            cout<<"The BST is empty.\n";
        else
            printhelp_1(root,ch);
    }
    void print_in_dis(int x,int y,int dis)
    {
        if (root==NULL)
            cout<<"The BST is empty.\n";
        else
            printhelp_2(root,x,y,dis);
    }
};

void BST::clearhelp(BSTNode* root)
{
    if (root==NULL)
        return;
    clearhelp(root->left());
    clearhelp(root->right());
    delete root;
}

BSTNode* BST::inserthelp(BSTNode* root,string name,int x,int y)
{
    if (root==NULL)
        return new BSTNode(name,x,y);
    else if (name < root->getname())
        root->setleft(inserthelp(root->left(),name,x,y));
    else
        root->setright(inserthelp(root->right(),name,x,y));
    return root;
}

BSTNode* BST::findhelp(BSTNode* root,string name)
{
    if (root==NULL)
        return NULL;
    else if (name < root->getname())
        return findhelp(root->left(),name);
    else if (name > root->getname())
        return findhelp(root->right(),name);
    else
        return root;
}

BSTNode* BST::getmin(BSTNode* root)  //寻找最小的结点
{
    if (root->left()==NULL)
        return root;
    else
        return getmin(root->left());
}

BSTNode* BST::deletemin(BSTNode* root)  //删除最小的结点
{
    if (root->left()==NULL)
        return root->right();
    else
    {
        root->setleft(deletemin(root->left()));
        return root;
    }
}

BSTNode* BST::removehelp(BSTNode* root,string name)
{
    if (root==NULL)
        return NULL;
    else if (name < root->getname())
        root->setleft(removehelp(root->left(),name));
    else if (name > root->getname())
        root->setright(removehelp(root->right(),name));
    else
    {
        BSTNode* temp=root;
        if (root->left()==NULL)  //至少一个结点为空，即非分支结点
        {
            root=root->right();
            delete temp;
        }
        else if (root->right()==NULL)
        {
            root=root->left();
            delete temp;
        }
        else   //两个子树都不为空，即为分支结点
        {
            BSTNode* temp=getmin(root->right());  //调用getmin()找到右子树的最小值用于代替被删除值的位置
            root->setname(temp->getname());       //并且调用deletemin()删除右子树的最小值
            root->setx(temp->getx());
            root->sety(temp->gety());
            root->setright(deletemin(root->right()));
            delete temp;
        }
    }
    return root;
}

void BST::printhelp(BSTNode* root)
{
    if (root==NULL)
        return;
    printhelp(root->left());
    cout<<root->getname()<<endl;
    printhelp(root->right());
}

void BST::printhelp_1(BSTNode* root,char ch)
{
    if (root==NULL)
        return;
    printhelp_1(root->left(),ch);
    string name=root->getname();
    if (name[0]==ch)
        cout<<root->getname()<<" "<<root->getx()<<" "<<root->gety()<<endl;
    printhelp_1(root->right(),ch);
}

void BST::printhelp_2(BSTNode* root,int x,int y,int dis)
{
    if (root==NULL)
        return;
    printhelp_2(root->left(),x,y,dis);
    int dis1=(root->getx()-x)*(root->getx()-x)+(root->gety()-y)*(root->gety()-y);
    if (dis1 < (dis*dis))
        cout<<root->getname()<<" "<<root->getx()<<" "<<root->gety()<<"\n";
    printhelp_2(root->right(),x,y,dis);
}

int main()
{
    BST b;
    int num;
    cin>>
}
