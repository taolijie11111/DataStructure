/*
=================================================================
BST (二叉搜索树)
=================================================================
*/

template <typename K,typename V> struct Entry //词条模板类
{
  K key;
  V value;
  Entry(K k=K(),V v=V()):key(k),value(v){};
  Entry(Entry<K,V> const& e):key(e.key),value(e.value){}//clone
  //
  bool operator< (Entry<k,v> const& e){return key < e.key;}
  bool operator> (Entry<k,v> const& e){return key > e.key;}
  bool operator== (Entry<k,v> const& e){return key == e.key;}
  bool operator!= (Entry<k,v> const& e){return key != e.key;}

};

#include "BinTree.h"
template <typename T>class BST:public BinTree<T>{
  public:
  virtual BinNodePosi(T)& search(const T&);//search
  virtual BinNodePosi(T) insert(const T&);//insert
  virtual bool remove(const T&);//remove
  protected:
  BinNodePosi(T) _hot;
  BinNodePosi(T) connect34(
    BinNodePosi(T),BinNodePosi(T),BinNodePosi(T),
    BinNodePosi(T),BinNodePosi(T),BinNodePosi(T),BinNodePosi(T)
  );
  BinNodePosi(T) rotateAt(BinNodePosi(T));
};

/*
=================================================================
search
=================================================================
*/
template<typename T> BinNodePosi(T)& BST<T>::search(const T& e)
{
  return searchIn(_root,e,_hot=NULL);//缺省值
}
//失败时指向最后一次试图转向的NULL
static BinNodePosi(T)& searchIn(
  BinNodePosi(T)& v,
  const T& e,
  BinNodePosi(T)& hot
){
  if(!v||(e==v->data))return v;
  hot=v;
  return searchIn(((e<v->data)?v->rChild),e,hot);
}

/*
=================================================================
insert
先查找，失败了，将该数值接入正确的位置
=================================================================
*/
template <typename T>BinNodePosi(T) BST<T>::insert(const T & e){
  BinNodePosi(T)& x=search(e);
  if(!x){
    x=new BInNode<T>(e,_hot);//在x处创建新节点，以——hot为父亲
    _size++;
    updateHeightAbove(x);
  }
  return x;
}//该算法插入边界情况依旧适用

/*
=================================================================
remove
=================================================================
*/
template <typename T> bool BST<T>::remove(const T& e){
  BinNodePosi(T)& x=search(e);
  if(!x)return false;
  removeAt(x,_hot);
  _size--;
  updateHeightAbove(_hot);//更新_hot及其历代祖先高度
  return true;
}

//condition 1
template<typename T>static BinNodePosi(T)
removeAt(BinNodePosi(T)& x,BinNodePosi(T)& hot){
  BinNodePosi(T) w=x;
  BinNodePosi(T) succ=NULL;
  if(!HasLChild(*x))succ=x->rChild;
  else if(!HasLChild(*x))succ=x->rChild;
  else{
    hot=w->parent;
    if(succ)succ->parent=hot;
    release(w->data);
    release(w);
    return succ;
  }
}

//condition 2
template<typename T>static BinNodePosi(T)
removeAt(BinNodePosi(T)& x,BinNodePosi(T)& hot){
  BinNodePosi(T) w=x;
  BinNodePosi(T) succ=NULL;
  if(!HasLChild(*x))succ=x->rChild;
  else if(!HasLChild(*x))succ=x->rChild;
  else{//all left and right are exist 
    w=w->succ();
    swap(x->data,w->data);
    BinNodePosi(T) u=w->parent;//原问题即转化为，摘除非二度的节点
    (u==x?u->rChild:u->lChild)=succ=w->rChild;
  }
}

/*
=================================================================
AVL
在一个AVL中插入一个元素可能会引起若干祖先失衡 
=================================================================
*/
#define Balanced(x) \
(stature((x).lChild)==stature((x).rChild))
#define BalFac(x) \
(stature((x).lChild)-stature((x).rChild))
#define AvlBalanced(x) \
((-2 < BalFac(x)) && （BalFac(x) < 2))
template <typename T> class AVL::pubilc BST<T>{
  public:
  BinNodePosi(T) insert(const T&);
  bool remove(const T&);//删除重写
}
 
//调整历代祖先
template <typename T>BinNodePosi(T) AVL<T>::insert(const T& e){
  BinNodePosi(T)& x=search(e);
  if(x)return x;
  x=new BinNode<T>(e,_hot);
  _size++;
  BinNodePosi(T) xx=x;
  for(BinNodePosi(T) g=x->parent;g;g=g->parent)
    if(!AvlBalanced（*g)){
      FromParentIn(*g)=rotateAt(tallerChild(tallerChild(g)));
      break;
    }else
      updateHeight(g);
    return xx;
}

//remove node
template <typename T> bool AVL<T>::remove(const T& e){
  BinNodePosi(T)& x=search(e);
  id(!x)return false;
  removeAt(x,_hot);
  _size--;
  for(BinNodePosi(T) g=_hot;g;g=g->parent){
    if(!AvlBalanced(*g))
      g=FromParentTo(*g)=rotateAt(tallerchild(tallerChild(g)));
    updateHeight(g);
  }
  return true;
}

/*
=================================================================
3+4重构
=================================================================
*/
template<typename T >BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T)v){
  BinNodePosi(T) p=v->parent,g=p->parent
  if(IsChild(*p))//zig
    if(IsChild(*v)){//zig-zig
      p->parent=g->parent;
      return connect34(v,p,g,v->lChild,v->rChild,p->rChild,g->rChild);
    }else{//zig-zag
    v->parent=g->parent;
    return connect34(p,v,g,p->lChild,v->rChild,g->rChild);
    }
    else{/* zag-zig & zag-zag */}
}