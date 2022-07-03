#include <iostream>
#include <vector>
using namespace std;

template <typename E> class Stack
{
private:
    void operator=(const Stack&){}
    Stack(const Stack&){}
public:
    Stack(){}
    virtual ~Stack(){}
    virtual void clear()=0;
    virtual void push(const E& it)=0;
    virtual void pop()=0;
    virtual const E& topValue()=0;
    virtual int length()=0;

};

template <typename E> class AQueue    //顺序队列类
{
private:
    int maxSize;    //最大容量
    int front;
    int rear;
    E* listArray;    //数组
public:
    AQueue(int size)
    {
        maxSize=size+1;
        rear=0;
        front=1;
        listArray=new E[maxSize];
    }
    ~AQueue(){delete [] listArray;}
    void clear(){rear=0; front=1;}
    void enqueue(const E& it)   //入队
    {
        rear=(rear+1) % maxSize;
        listArray[rear]=it;
    }
    void dequeue()   //出队
    {
        front=(front+1) % maxSize;
    }
    const E& frontValue(){return listArray[front];}
    const E& rearValue(){return listArray[rear];}
    bool empty()
    {
        if (front==rear+1)
            return true;
        else
            return false;
    }
    int length() const {return ((rear+maxSize)-front+1) % maxSize;}
};

template <typename E>
class QStack:Stack<E>{   //双队列实现栈
private:
    int maxSize;   //栈的容量
    AQueue<E> QA;   //基于数组实现的队列
    AQueue<E> QB;
   public:
     QStack(int size): QA(size), QB(size) //初始化队列
     {
        maxSize=size;
     }
     ~QStack(){}
     void clear() //清空栈
     {
         QA.clear();
         QB.clear();
     }
     void push(const E& it) //压栈
     {
         if (!QA.empty())
             QA.enqueue(it);
         else
             QB.enqueue(it);
     }
     void pop() //弹栈
     {
         if (!QA.empty())
         {
             int num=QA.length();
             while (num>1)
             {
                 QB.enqueue(QA.frontValue());
                 QA.dequeue();
                 num--;
             }
             QA.dequeue();
         }
         else
         {
             int num=QB.length();
             while (num>1)
             {
                 QA.enqueue(QB.frontValue());
                 QB.dequeue();
                 num--;
             }
             QB.dequeue();
         }
     }
     const E& topValue()  //栈顶元素
     {
         if (!QA.empty())
             return QA.rearValue();
         else
             return QB.rearValue();
     }
     int length()
     {
         if (!QA.empty())
            return QA.length();
         else
             return QB.length();
     }
};

bool ispopOrder(vector<int>& v1,int N,int K)    //判断是否为正确的出栈顺序
{
    QStack<int> q(K);
    int pos=0;
    for (int i=1;i<=N;i++)
    {
        if (q.length()==K)
            return false;
        q.push(i);
        while (q.topValue()==v1[pos])
        {
            q.pop();
            pos++;
        }
    }
    if (pos==5)
        return true;
    else
        return false;
}

int main()
{
    int N,K,m;
    cin>>N>>K>>m;
    vector<int>v1;   //待判断的出栈顺序
    for (int i=0;i<m;i++)
    {
        for (int j=0;j<N;j++)
        {
            int num;
            cin>>num;
            v1.push_back(num);
        }
        if (ispopOrder(v1,N,K))
            cout<<"T"<<endl;
        else
            cout<<"F"<<endl;
        v1.clear();
    }
    return 0;
}
