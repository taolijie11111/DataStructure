/*
* @Author: taolijie
* @Date: 2022-01-02 18:29:57
 * @Last Modified by: taolijie
 * @Last Modified time: 2022-01-04 12:00:50
*/
//这是一个向量大类
//Vector模板类
#ifndef __VECTOR__
#define __VECTOR__

typedef int Rank; //秩
#define DEFAUT_CAPACITY 3
//默认的初始容量

template <typename T>
class Vector //向量模板类
{
private:
    Rank _size;
    int _capacity;
    T *_elem; //定义数据类型和数据结构，表示规模，容量和数据区
protected:
    void copyFrom(T const *A, Rank lo, Rank hi); //复制数组
    void expand();                               //扩展数组
    void shrink();                               //装填因子过小的时候压缩
    bool bubble(Rank lo, Rank hi);               //扫描交换
    void bubbleSort(Rank lo, Rank hi);           //气泡排序
    Rank max(Rank lo, Rank hi);                  //选取最大元素
    void electionSort(Rank lo, Rank hi);         //选择排序算法
    void merge(Rank lo, Rank mi, Rank hi);       //归并算法
    void mergeSort(Rank lo, Rank hi);            //归并排序算法
    Rank partition(Rank lo, Rank hi);            //轴点构造算法
    void quickSort(Rank lo, Rank hi);            //快速排序算法
    void heapSort(Rank lo, Rank hi);             //堆排序

public:
    //构造函数
    Vector(int c = DEFAUT_CAPACITY, int s = 0, T v = 0)
    { //容量为c，规模为s，元素初始化为0
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v)
            ;
    }
    Vector(T const *A, Rank n) { copyFrom(A, 0, n); }                           //数组整体赋值
    Vector(T const *A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }               //区间
    Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V._size); }               //向量整体复制
    Vector(Vector<T> const &V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //区间
                                                                                //析构函数
    ~Vector() { delete[] _elem; }

    Rank size() const { return _size; }                       //规模
    bool empty() const { return !_size; }                     //判空
    int discordered() const;                                  //判断向量是否已排序
    Rank find(T const &e) const { return find(e, 0, _size); } //无序向量整体查找
    Rank find(T const &e, Rank lo, Rank hi) const;            //无序向量区间查找
    Rank search(T const &e) const
    {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const &e, Rank lo, Rank hi) const; //有序向量区间查找

    //可写访问接口
    T &operator[](Rank r) const;                         //重载下标操作符，可以类似于数组形式引用各元素
    Vector<T> &operator=(Vector<T> const &V);            //重载赋值操作符，以便直接克隆向量
    T remove(Rank r);                                    //删除秩为r的元素
    int remove(Rank lo, Rank hi);                        //删除秩在区间之内的元素
    Rank insert(Rank r, T const &e);                     //插入元素
    Rank insert(T const &e) { return insert(_size, e); } //默认作为末元素插入
    void sort(Rank lo, Rank hi);                         //排序
    void sort() { sort(0, _size); }                      //整体排序
    void unsort(Rank lo, Rank hi);                       //对区间置乱
    void unsort() { unsort(0, _size); }                  //整体置乱
    int deduplicate();                                   //无序去重
    int uniquify();                                      //有序去重
                                                         //遍历
    void traverse(void (*)(T &));                        //使用函数指针遍历
    template <template VST>
    void traverse(VST &); //遍历（使用函数对象，可以全局修改）
};
//vector

//copyFrom :
template <typename T>
inline Vector<T>::copyFrom(T const *A, Rank lo, Rank hi)
{
    //For the line I added by myself, delete the existing vector first
    if (_elem)
        delete[] _elem;
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi)
    {
        _elem[_size++] = A[lo++]; //将A的内容复制到_elem
    }
}

//vector assignment by =

template <typename T>
inline //here need write the template
    Vector<T> &
    Vector<T>::operator=(Vector<T> const &V)
{ //“Vecotr<T>” indicates that it returns a class type
    if (this == &V)
    {
        return *this;
    }
    if (_elem)
        delete[] _elem; //release original content
    copyFrom(V._elem, 0, V._size);
    return *this;
}

//expend
template <typename T>
Vector<T>::expand()
{
    if (_size < _capactiy)
        return;
    if (_capacity < DEFAUT_CAPACITY)
        _capacity = DEFAUT_CAPACITY; //not lower than minimum size
    T *oldElem = _elem;
    _elem = new T[_capacity <<= 1]; //means *2
    for (int i = 0; i < _size; i++)
    { //copy the old one
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}

//shrink()
template <typename T>
Vector<T>::shrink()
{
    if (_capacity < DEFAUT_CAPACITY << 1)
        return; //bit operation
    if (_size << 2 > _capacity)
        return;
    T *oldElem = elem;
    _elem = new T[_capacity >>= 1]; //halve capacity
    for (int i = 0; i < size; i++)
        _elem[i] = oldElem[i];
    delete[] oldElem; //release original content
}

// reference
template <typename T>
T &Vector<T>::operator[](Rank r) const //"T&" indicates that it returns a T type by reference
{
    return _elem[r]; //assert: 0<=r<_size
}
//permute
template <typename T>
permute(Vector<T> &V)
{
    for (int i = V.size(); i > 0; i++)
    {
        swap(V[i - 1], V[rand() % i]); //random exchange
    }
}
//when it in the range
template <typename T>
Vector<T>::unsort(Rank lo, Rank hi)
{
    T *V = _elem + lo; //start from lo
    for (Rank i = hi - lo; i > 0; i--)
    {
        swap(V[i - 1], V[rand() % i]);
    }
}
//insert
template <typename T>
Rank V<T>::insert(Rank r, T const &e)
{
    expand();
    for (int i = _size; i > r; i--)
    {
        _elem[i] = _elem[i - 1];
    }
    _elem[r] = e;
    _size++;
    return r;
}
//delete interval
template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
    if (lo == hi)
        return 0;
    while (hi < _size)
    {
        _elem[lo++] = _elem[hi++];
    }
    _size = lo;
    shrink();
    return hi - lo;
}
//delete single interval
template <typename T>
T Vector<T>::remove(Rank r)
{
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}
//find
template <typename T>
Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const
{
    while ((lo < hi--) && (e != _elem[hi]));
    return hi;
}
//union
//insure elements different from each other in range between 0 and i
template <typename T> //delete duplicate elements,return numbers of them
int Vector<T>::deduplicate()
{
    int oldSize = _size;
    Rank i = 1;
    while (i < size)
    {
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
    }
    return oldSize - _size;
}

//visite
/*
-----------------------------------------------------------
use function object to visite
a new and effective operation
-----------------------------------------------------------
*/
//an example
template <typename T>
struct Increase //actual operation
{
    virtual void operator()(T &e) { e++; }
};
template <typename T>
increase(Vector<T> &V)
{ //start visite
    V.traverse(Increase<T>());
}

template <typename T>
Vector<T>::traverse(void (*visit)(T &))
{
    for (int i = 0; i < _size; i++)
    {
        visit(_elem[i]);
    }
}

/*
-----------------------------------------------------------
ordered vector
-----------------------------------------------------------
*/
template <typename T>
int Vector<T>::discordered() const
{
    int n = 0;
    for (int i = 1; i < _size; i++)
        n += (_elem[i - 1] > _elem[i]);
    return n; //return the number of discordered
}

//uniquify
//
//this is a ineffcient algorithm!!!!!!!!
//the time depends on "while",everythme it will use remove()
template <typename T>
int Vector<T>::uniquify()
{
    int oldSize = _size;
    int i = 0;
    while (i < _size - 1))
        {
            (_elem[i] == _elem[i + 1]) ? remove(i + 1) : i++;
        }
    return oldSize - _size;
}

//effcient one
template <typename T>
int Vector<T>::uniquify()
{
    Rank i = 0, j = 0;
    while (++j < _size))
        {
            if (_elem[i] != _elem[j])  //i,j mutual independence!!nice job!!
                _elem[++i] = _elem[j]; //find the different elements and instead it
        }
    _size = ++i;
    shrink(); //this time the superfluous elements in the low
    return j - i;
}
/*
in those code,change is point to the orginal data,mybe we need keep the orginal one? 
if like what i think,when it become different,copy it to another array?? maybe a nice mothod.
*/

//========================================================
//search
//========================================================
//binary search versions A
template <typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi)
{
    while (lo < hi)
    {
        Rank mi = (lo + hi) >> 1; //means /2
        if (e < A[mi])
            hi = mi; //use "<" is more fit for ordered vector because the defult ordered is form smaller to bigger
        else if (A[mi] < e)
            lo = mi + 1;
        else
            return mi;
    }
    return -1;
}
//versions B
//improvement:original:left:+1.right:+2. now:left=right:+1
//adventages:more stabilize
template <typename T> static Rank binSearch(T* A,T const& e,Rank lo,Rank hi){
    while ( 1<hi-lo)
    {
        Rank mi=(lo+hi)>>1;
        (e<A[mi])?hi=mi:lo=mi;
    }
    return(e==A[lo])?lo:-1;
}
//versions C
//more concise and effective
//不变性和单调性
//该算法在功能上语义上性能上都比较完美
template <typename T> static Rank binSearch(T* A,T const& e,Rank lo,Rank hi){
    while (lo<hi)
    {
        Rank mi=(lo+hi)>>1;
        (e<A[mi])?hi=mi:lo=mi+1;//change
    }
    return --lo;
}

//fibonacci
//improvment:change mi’s location
template <typename T>
static Rank fibSearch(T *A, T const &e, Rank lo, Rank hi)
{
    Fib fib(hi - lo);
    while (lo < hi)
    {
        while (hi - lo < fib.get())
        {
            fib.prev();
        }
        Rank mi = lo + fib.get() - 1; //according to golden ratio
        if (e < A[mi])
            hi = mi;
        else if (A[mi] < e)
            lo = mi + 1;
        else
            return mi;
    }
    return -1;//failure
}

//interpolation search 
//those search mothers need to kown the elements,
//but in mathmatics there need use search mothods to calculate the elements
//二分查找基本上复杂度量级为log(n)
/*
========================================================
Optional search method in gengeral case:
1.large-scale  interpolation search  O(loglogn)
2.minddle-scale 折半查找 
3.small-scale   顺序查找
========================================================
*/

//========================================================
//sort algorithm
//========================================================

//ADT about sorts
template <typename T>
void Vector<T>::msort(Rank lo,Rank hi){
    switch (rand()%5)
    {
    case 1:bubbleSort(lo,hi);break;
    case 2:selectionSort(lo,hi);break;
    case 3:mergeSort(lo,hi);break;
    case 4:heapSort(lo,hi);break;
    default:quickSort(lo,hi);break;
    }
}


//versions 1
template <typename T>
void Vector<T>::bubbleSort(Rank lo,Rank hi){
    while (!bubble(lo,hi--));//扫描交换，每次遇到一个逆序的元素便进行交换
}

//改进方法：在每趟扫描交换中，是否曾经出现过逆序的元素
//to release 扫描 number

//versions 2
//O（n^1.5）
template <typename T>
bool Vector<T>::bubbleSort(Rank lo,Rank hi){
    bool sorted=true;
    while (++lo<hi)
    {
        if(_elem[lo-1]>_elem[lo]){
            sorted=false;
            swap(_elem[lo-1],_elem[lo]);
        }
    }
    return sorted;
}

//versions 3
//complexity is O(n)
//let them become closer and closer
template <typename T>
Rank Vector<T>::bubbleSort(Rank lo,Rank hi)
{
    Rank last=lo;
    while (++lo<hi)
    {
        if(_elem[lo-1]>_elem[lo]){
            last=lo;
            swap(_elem[lo-1],_elem[lo]);
        }
    }
    return last;
}

//mergeSort
template <typename>
void Vector<T>::mergeSort(Rank lo,Rank hi){
    if(hi-lo<2)return ;
    int mi=(lo+hi)>>1;//bounded by the midpoint
    //important location
    mergeSort(lo,mi);
    mergeSort(mi,hi);
    merge(lo,mi,hi);//meger
}
//思想：
//将数据分为两列，之后两列对应元素进行比较，小的就排上去
//two load mergeSort
//O(n)
template<typename T>void Vector<T>::merge(Rank lo,Rank mi,Rank hi){
    T* A=_elem+lo;//这里的mi是自定义的，并不一定是除以2
    int lb=mi-lo;
    T* B=new T[lb];
    for(Rank i=0;i<lb;B[i]=A[i++]);
    int lc=hi-mi;
    T* C=_elem+mi;
    //冗余版
    // for(Rank i=0,j=0,k=0;(j<lb)||(k<lc);){//同时越界才会退出
    //     if((j<lb)&&(lc<=k||(B[j]<=C[k])))A[i++]=B[j++];//使用哨兵
    //     if((k<lc)&&(lb<=j||(C[k]<B[j])))A[i++]=C[k++];
    // }
    //后面并不需要将数据进行转移
    //？？但是很奇怪的是，这个程序中貌似并没有说归并？？？？
    for(Rank i=0,j=0,k=0;j<lb;){
        if((j<lb)&&(B[j]<=C[k]))A[i++]=B[j++];//使用哨兵
        if(lb<=j||(C[k]<B[j]))A[i++]=C[k++];
    }
    delete []B;//release space
}

#endif