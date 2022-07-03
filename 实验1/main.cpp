#include <iostream>
using namespace std;

template <typename E> class Node  //双链表结点类
{
private:
    static Node<E>* freelist;  //可利用空间表
public:
    E c;    //系数
    E e;    //指数
    Node* next;   //后继结点
    Node* prev;   //前驱结点

    //构造函数
    Node(const E& c1,const E& e1,Node* prevp,Node* nextp)   //创建普通结点
    {
        c=c1;
        e=e1;
        prev=prevp;
        next=nextp;
    }
    Node(Node* prevp=NULL,Node* nextp=NULL)  //创建头尾结点
    {
        prev=prevp;
        next=nextp;
    }

    //重载
    void* operator new(size_t)
    {
        if (freelist==NULL)
            return ::new Node;   //可利用空间表空间不足，调用标准new
        Node<E>* temp=freelist;
        freelist=freelist->next;
        return temp;
    }

    void operator delete(void* ptr)
    {
       ((Node<E>*)ptr)->next=freelist;
        freelist=(Node<E>*)ptr;
    }
};
template <typename E>
Node<E>* Node<E>::freelist=NULL;  //初始置为空


template <typename E> class LList  //双链表类
{
private:
    Node<E>* head;  //头结点
    Node<E>* tail;  //尾结点
    Node<E>* curr;  //当前结点
    int cnt;  //长度
    void init()
    {
        curr=head=new Node<E>;
        tail=new Node<E>;
        head->next=tail;
        tail->prev=head;
        cnt=0;
    }
    void removeall()
    {
        while(head!=NULL)
        {
            curr=head;
            head=head->next;
            delete curr;
        }
    }
public:
    LList(){init();}
    ~LList(){removeall();}
    void clear(){removeall();init();}  //清空
    void append(const E& c,const E& e)  //添加一个结点
    {
        tail->prev=tail->prev->next=new Node<E>(c,e,tail->prev,tail);
        cnt++;
    }
    void remove()  //删除一个结点
    {
        if (curr==tail)
            return;
        Node<E>* temp=curr;
        curr->prev->next=curr->next;
        curr->next->prev=curr->prev;
        delete temp;
        cnt--;
    }
    void insert(const E& c,const E& e)
    {
        curr->prev=curr->prev->next=new Node<E>(c,e,curr->prev,curr);
        cnt++;
    }
    void prev()
    {
        if (curr!=head)
            curr=curr->prev;
    }
    void next()
    {
        if (curr!=tail)
            curr=curr->next;
    }
    void get_begin()
    {
        curr=head->next;
    }
    int currPos() const
    {
        Node<E>* temp=head;
        int i;
        for (i=0;temp!=curr;i++)
            temp=temp->next;
        return i;
    }
    int length() const {return cnt;}

    const E& get_C() const {return curr->c;}  //获得系数
    const E& get_E() const {return curr->e;}  //获得指数

    void change_C(E n) { curr->c +=n;} //修改系数
    void change_E(E n) { curr->e +=n;} //修改指数
};

LList<int>l1,l2;

void read()   //读取两个多项式
{
    int m,n;
    cin>>m>>n;
    int c,e;
    for (int i=0;i<m;i++)
    {
        cin>>c>>e;
        l1.append(c,e);
    }

    for (int j=0;j<n;j++)
    {
        cin>>c>>e;
        l2.append(c,e);
    }
}

void print(LList<int>l)  //按照要求打印
{
    l.next();
    cout<<l.length()<<endl;
    for (int i=0;i<l.length();i++)
    {
        cout<<l.get_C()<<" "<<l.get_E()<<" ";
        l.next();
    }
}

LList<int> add(LList<int>& l1,LList<int>& l2) //多项式相加
{
    LList<int>l3;
    l1.get_begin();
    l2.get_begin();
    while (true)
    {
        if (l1.get_E() >l2.get_E())  //多项式1的指数大于2的指数
        {
            l3.append(l1.get_C(),l1.get_E());
            l1.next();
        }
        else if (l1.get_E() <l2.get_E())
        {
            l3.append(l2.get_C(),l2.get_E());
            l2.next();
        }
        else
        {
            if (l1.get_C()+l2.get_C() != 0)
                l3.append(l1.get_C()+l2.get_C(),l1.get_E());
            l1.next();
            l2.next();
        }
        if (l1.currPos()>l1.length() || l2.currPos()>l2.length())  //其中一个链表遍历完,结束循环
            break;
    }

    //将另一个没有遍历完的链表合并
    if (l1.currPos()>l1.length() && l2.currPos()>l2.length())
    {}
    else if (l1.currPos()>l1.length())
    {
        while (true)
        {
            l3.append(l2.get_C(),l2.get_E());
            l2.next();
            if (l2.currPos()>l2.length())
                break;
        }
    }
    else
    {
        while (true)
        {
            l3.append(l1.get_C(),l1.get_E());
            l1.next();
            if (l1.currPos()>l1.length())
                break;
        }
    }
    return l3;
}

LList<int> mult(LList<int>& C,LList<int>& D)  //多项式相乘
{
    LList<int> l;
    int i=0;
    C.get_begin();
    while (C.currPos()<=C.length())
    {
        D.get_begin();
        i+=1;
        while (D.currPos()<=D.length())
        {
            l.get_begin();  //每次放入新运算的一项就从头开始
            int coef=C.get_C()*D.get_C();  //系数相乘
            int exp=C.get_E()+D.get_E();  //指数相加
            if (i>1)  //不是第一次运算就将其放在l3合适的位置,找到即跳出
            {
                for (int j=0;j<l.length();j++)
                {
                    if (exp<l.get_E() && j!=l.length()-1)
                        l.next();
                    else if (exp<l.get_E() && j==l.length()-1)
                    {
                        l.append(coef,exp);
                        break;
                    }
                    else if (exp==l.get_E())
                    {
                        if (coef+l.get_C()!=0)
                            l.change_C(coef);
                        else
                            l.remove();
                        break;
                    }
                    else
                    {
                        l.insert(coef,exp);
                        break;
                    }
                }
            }
            else   //第一次运算结果直接添加进去
                l.append(coef,exp);
            D.next();
        }
       C.next();
    }
    return l;
}

int main()
{
    read();
    print(add(l1,l2));  //相加
    cout<<endl;
    print(mult(l1,l2)); //相乘
    return 0;
}
