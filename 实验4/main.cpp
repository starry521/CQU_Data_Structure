#include <iostream>
using namespace std;

int gcd(int a,int b)   //寻找最小公因数
{return b==0 ? a : gcd(b,a%b);}

class Rational   //有理数类
{
    friend bool operator<(const Rational& r1, const Rational& r2)
    {
        int a=r1.N*r2.D;
        int b=r2.N*r1.D;
       if (a<b)
           return true;
       else
           return false;
    }

    friend bool operator<=(const Rational& r1, const Rational& r2)
    {
        int a=r1.N*r2.D;
        int b=r2.N*r1.D;
       if (a<=b)
           return true;
       else
           return false;
    }

    friend bool operator>(const Rational& r1, const Rational& r2)
    {
        int a=r1.N*r2.D;
        int b=r2.N*r1.D;
       if (a>b)
           return true;
       else
           return false;
    }

    friend bool operator>=(const Rational& r1, const Rational& r2)
    {
        int a=r1.N*r2.D;
        int b=r2.N*r1.D;
       if (a>=b)
           return true;
       else
           return false;
    }

    friend bool operator==(const Rational& r1, const Rational& r2)
    {
        int a=r1.N*r2.D;
        int b=r2.N*r1.D;
        if (a==b)
            return true;
        else
            return false;
    }

    friend bool operator!=(const Rational& r1, const Rational& r2)
    {
        int a=r1.N*r2.D;
        int b=r2.N*r1.D;
        if (a!=b)
            return true;
        else
            return false;
    }
public:
   int N; //分子
   int D; //分母(大于0)

   Rational(){}  //构造函数
   Rational(int n){N=n; D=1;} //构造函数-整数
   Rational(int n,int d) {N=n; D=d;} //构造函数-分数
   Rational(const Rational& r){N=r.N; D=r.D;} //复制构造函数
   ~Rational() {}  //析构函数
   Rational& operator=(const Rational& r)  //赋值运算符重载
   {
       this->N=r.N;
       this->D=r.D;
       return *this;
   }
   void print()
   {
       if (N==0)
       {
           cout<<0<<" ";
           return;
       }
       int num=gcd(N,D);
       N=N/num;
       D=D/num;
       if (D==1)
       {
           cout<<N<<" ";
           return;
       }
       else
           cout<<N<<"/"<<D<<" ";
   }
};



template<typename E>
class minheap    //最小堆类
{
private:
   E* Heap;    //基于数组
   int maxsize;  //堆可容纳的最大元素数目
   int n;   //堆元素的数目

   void siftdown(int pos)   //下沉操作
   {
       while (!isleaf(pos))
       {
           int j=leftchild(pos);
           int rc=rightchild(pos);
           if ((rc<n) && Heap[rc]<Heap[j])
               j=rc;
           if (Heap[pos]<Heap[j])
               return;
           E temp=Heap[pos];
           Heap[pos]=Heap[j];
           Heap[j]=temp;
           pos=j;
       }
   }

   void siftup(int pos)  //上浮操作
   {
       while ((pos!=0) && (Heap[pos]<Heap[parent(pos)]))
       {
           E temp=Heap[pos];
           Heap[pos]=Heap[parent(pos)];
           Heap[parent(pos)]=temp;
           pos=parent(pos);
       }
   }
public:
   minheap(E* h,int num,int max)   //构造函数
   {Heap=h; n=num; maxsize=max; buildHeap();}
   ~minheap(){delete[] Heap;}
   int size() const   //返回堆中元素个数
   {return n;}
   bool isleaf(int pos) const  //判断下标为pos的结点是否为叶
   {return (pos>=n/2) && (pos<n);}
   int leftchild(int pos) const  //返回左孩子下标
   {return 2*pos+1;}
   int rightchild(int pos) const   //返回右孩子下标
   {return 2*pos+2;}
   int parent(int pos) const  //返回父母下标
   {return (pos-1)/2;}

   void buildHeap()  //建堆
   {
       for (int i=n/2-1;i>=0;i--)
           siftdown(i);
   }

   void insert(const E it)
   {
       Heap[n]=it;
       siftup(n);
       n++;
   }

   E removefirst()
   {
       n--;
       E temp=Heap[0];  //将末尾元素与第一个交换
       Heap[0]=Heap[n];
       Heap[n]=temp;
       if (n!=0) siftdown(0);  //将新的堆顶元素下沉
       return Heap[n];  //第一个元素
   }

   void print_heap()  //打印堆序列
   {
       for (int i=0;i<n;i++)
        Heap[i].print();
   }
};

template<typename E>
void heapsort(minheap<E>h,int T)  //堆排序并按要求输出
{
    E it;
    for (int i=0;i<T;i++)
    {
        it=h.removefirst();
        it.print();
    }
}

int main()
{
    int T;
    cin>>T;
    Rational* heap=new Rational[100];   //new数组
    minheap<Rational>h(heap,T,100);  //实例化
    for (int i=0;i<T;i++)
    {
        int n,d;
        cin>>n>>d;
        Rational r(n,d);
        heap[i]=r;
    }
    h.buildHeap();
    h.print_heap();
    cout<<endl;
    heapsort<Rational>(h,h.size());
    return 0;
}
