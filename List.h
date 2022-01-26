#ifndef __List__
#define __List__

//ListNode 模板类
typedef int Rank;
#define ListNodePosi(T) ListNode<T>* 

template <typename T> struct ListNode
{
    T data;
    ListNodePosi(T) pred;//前驱节点的位置
    ListNodePosi(T) succ;//后继节点的位置

    //structure function
    ListNode(){}
    ListNode(T e,ListNodePosi(T) p=nullptr,ListNodePosi(T) s=nullptr)
        :data(e),pred(p),succ(s){}
        ListNodePosi(T) insertAsPred(T const& e);
        ListNodePosi(T) insertAsSucc(T const& e);
};

template <typename T> class List
{
private:
    int size;
    ListNodePosi(T) header;
    ListNodePosi(T) trailer;

protected:
    void init();
    int clear();
    void copyNodes(ListNodePosi(T),int);
    void merge(ListNodePosi&,int,List<T>&,ListNodePosi(T),int);//merge
    void merge(ListNodePosi&,int);
    void selectionSort(ListNodePosi(T),int);
    void insertionSort(ListNodePosi(T),int);

public:
//构造函数
    List( init();)
    List(List<T> const& L);
    List(List<T> const& L,Rank r,int n);
    List(ListNodePosi(T) P,int n);
//析构函数
    ~List();

//只读访问接口
    Rank size() const {return _size;}//报告列表当前规模的总数
    bool empty() const{return _size<=0;}
    T& operator[](Rank r)const;
    ListNodePosi(T) first() const {return header->succ;}
    ListNodePosi(T) last() const {return trailer->pred;}
    bool valid(ListNodePosi(T) P)//injuege ilgl
    {return p && (trailer !=p)&&(header !=p);}
    int disordered() const;
    ListNodePosi(T) find (T const& e) const{
        return find(e,_size,trailer);
    }
    ListNodePosi(T) search (T const& e,int n,ListNodePosi(T) p)const;
    ListNodePosi(T) selectMax(ListNodePosi(T) P,int n);
    ListNodePosi(T) selectMax(){return selectMax(header->succ,_size);}

//可写访问接口
    ListNodePosi(T) insertAsFirst(T const& e);
    ListNodePosi(T) insertAsLast(T const& e);
    ListNodePosi(T) insertA(ListNodePosi(T) p,T const& e);
    ListNodePosi(T) insertB(ListNodePosi(T) p,T const& e);
    T remove(ListNodePosi(T) p);
    void merge(List<T>& L){merge (first(),size,L,L.first(),L._size);}
    void sort(ListNodePosi(T) p,int n);
    void sort(){
        sort(first(),_size);
    }
    int deduplicate();
    void reverse();

//遍历
    void traverse(void(*)(T&));
    template<typename VST>
    void traverse(VST&);
};

//默认构造方法
template <typename T> void List<T>::init(){
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header ->succ=trailer;
    header->pred=NULL;
    trailer->pred=header;
    trailer->succ=NULL;
    _size=0;
}

//模仿向量的循秩访问的方式
//重载下标操作符
template <typename T>
T List<T>::operator[](Rank r)const{//O(r),效率低下不可常用
    Posi(T) P=first();
    while (0<r--)
    {
        p=p->succ;
    }
    return p->data;
}
//循秩访问，call by rank
//从头/尾出发，挨个访问
//循地址访问，call by possion
//直接利用节点之间的互相引用，确定节点
//等效：头，首，末，尾：-1，0，n-1,n

/*
=================================================================
Unsort
=================================================================
*/


/*
=================================================================
insert
=================================================================
*/
template <typename T> inline 
Posi(T) List<T>::insertBefore(Posi(T) p,T const& e)
{
    _size++;
    return p->insertAsPred(e);
}

template <typename T> inline 
Posi(T) List<T>::insertBefore(T const& e){
    Posi(T) x=new ListNode(e,pred,this);
    pred->succ =x;
    pred=x;
    return x;
}
//const number complise

/*
=================================================================
copy
=================================================================
*/
template <typename T> inline 
void List<T>::copyNodes(Posi(T) p,int n){
    init();
    while(n--){
        insertAsLast(p->data);
        p=p->succ;
    }
}

/*
=================================================================
delete
=================================================================
*/
template <typename T> inline 
T List<T>::remove(Posi(T) p){
    T e=p->data;
    p->pred->succ=p->succ;
    p->succ-pred=p->pred;
    delete p;
    _size--;
    return e;
}

template <typename T> inline 
void List<T>::~List(){
    clear();//clear list
    delete header;//clear 哨兵
    delete trailer;
}

template <typename T> inline 
int List<T>::clear(){
    int oldSize=_size;
    while (0<_size)
    {
        remove(header->succ);
    }
    return oldSize;
}

/*
=================================================================
find
=================================================================
*/
template <typename T> inline 
Posi(T) List<T>::find(T const & e,int n,Posi(T) p)const{
    while (0<n--)
    {
    if(e==(p=p->pred)->data) return p;
    }
    return NULL;
}

/*
=================================================================
去重
=================================================================
*/
template <typename T> inline 
int List<T>::deduplicate(){
    if(_size<2)return 0;
    int oldSize=_size;
    Posi(T) p=first();//指向首节点
    Rank r=1;
    while (trailer !=(p=p->succ))//表示依次到末节点
    {
        Posi(T) q=find(p->data,r,p);//在p的r个前驱中，查找与之雷同者
        q ? remove(q):r++;//如果真的存在，就删去，否则，秩递增
    }
    return oldSize - _size;
}


/*
=================================================================
Sorted
=================================================================
*/

/*
=================================================================
unqion
=================================================================
*/
template <typename T> inline 
int  List<T>::uniquify(){
    if(_size<2)return 0;
    int oldSize=_size;
    ListNodePosi(T) p=first();
    ListNodePosi(T) q;
    while (trailer !=(q=p->succ))
    {
        /* code */
        if(p->data != q->data)p=q;
        else remove(q);
    }
    return oldSize-_size;
}

/*
=================================================================
find
=================================================================
*/
template <typename T> inline 
Posi(T) List<T>::search(T const& e,int n,Posi(T) p)const{
    while (0<=n--)
    {
        if(((p=p->pred)->data)<=e)break;
    }
    return p;
}
/*
=================================================================
selectionSort
=================================================================
*/
template <typename T> inline 
void List<T>::selectionSort(Posi(T) p,int n){
    Posi(T) head = p->pred;
    Posi(T) tail=p;
    for(int i=0;i<n;i++)tail=tail->succ;
    while (1<n)
    {
        insertBefore(tail,remove(selectMax(head->succ,n)));//here will low because new and delete
        tail=tail->pred;
        n--;
    }   
}
template <typename T> inline 
Posi(T) List<T>::selectMax(Posi(T) p,int n){//painter's Alg，即最后的颜色由最后一笔决定
    Posi(T) max=p;
    for(Posi(T) cur=p;1<n;n--){
        if(!lt((cur-cur->succ)->data,max->data))max=cur;
    }//对重复元素进行覆盖
    return max;
}

/*
=================================================================
insertSort

insertSort and selectionSort
selectionSort:O(n^2),anytime
insertSort:O(n^2),the worst time,O(n),best time 

in fact,inserSort's average time is O(n^2)
=================================================================
*/
template <typename T> inline 
void List<T>::insertionSort(Posi(T) p,int n){
    for(int r=0;r<n;r++){
        insertAfter(search(p->data,r,p),p->data);
        p=p->succ;
        remove(p->pred);
    }//n次迭代
}

//inversion:逆序对，排序实际上是对逆序对的讨论

#endif