#ifndef __BINTREE__
#define __BINTREE__
#include "Stack.h"
/*
=================================================================
BinNode(二叉树)
=================================================================
*/
#define BinNodePosi(T) BinNode<T>*
template <typename T> struct BinNode
{
  BinNodePosi(T) parent,lChild,rChild;
  T data;
  int height;
  int size();
  BinNodePosi(T) insertAsLC(T const &);//作为左孩子插入新节点
  BinNodePosi(T) insertAsRC(T const &);//作为右孩子插入新节点
  BinNodePosi(T) succ();//中序遍历下，当前节点的直接后继
  template <typename VST> void travLevel(VST &); //子树层次遍历
  template <typename VST> void travPre(VST &); //先序遍历
  template <typename VST> void travIn(VST &); //中序
  template <typename VST> void travPost(VST &); //后序
};

template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const & e)
  {return lChild=new BinNode(e,this);}
template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const & e)
  {return rChild=new BinNode(e,this);}

template <typename T> int BinNode<T>::size(){//子树规模
  int s=1;
  if(lChild) s+=lChild->size();//递归计入左子树
  if(rChild) S+=rChild->size();//递归计入右子树
  return s;
}

template <typename T> class BinTree
{
private:
  int _size;
  BinNodePosi(T) _root;
  virtual int updateHeight(BinNodePosi(T) x);//更新节点x的高度
  void updateHeightAbove(BinNodePosi(T) x);//更新x及祖先的高度
public:
  int size() const {return _size;}//规模
  bool empty() const {return !_root;}//判空
  BinNodePosi(T) root() const{return _root;}//树根
  BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x,T const& e);
  BinTree(/* args */);
  ~BinTree();
};

//update height
#define stature(p)((p)?(p)->height: -1)
template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x){
  return x->height=1+max(stature(x->lChild),stature(x->rChild));
}
template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x){
  while (x)
  {
    updateHeight(x);
    x=x->parent;
  }
}

//insert 结点
template <typename T> 
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x,T const& e){
  _size++;x->insertAsRC(e);
  updateHeightAbove(x);//更新高度
  return x->rChild;
}

/*
=================================================================
先序遍历
=================================================================
*/
template <typename T,typename VST>
void traverse(BinNodePosi(T) x,VST& visit){
  if(!x)return ;
  visit(x->data);
  traverse(x->lchild, visit);//tail recursion
  traverse(x->rChild，visit);
}

//改进
//遍历都是先根-先右后左
template <typename T,typename VST>
void travPre_I1(BinNodePosi(T) x,VST& visit){
  Stack <BinNodePosi(T)> S;
  if(x) S.push(x);
  while (!S.empty())
  {
    x=S.pop();
    visit(x->data);
    if(HasRChild(*x))S.push(x->rChild);//右孩子先入后出
    if(HasLChild(*x))S.push(x->lChild);//左孩子后入先出
  }
}

//改进 version 2
//每当运算到一个节点，它便会先将节点的右节点推送到栈中，然后遍历左节点
template <typename T,typename VST>
static void visitAlongLeftBranch(BinNodePosi(T) x,VST& visit,
Stack <BinNodePosi(T)>& S)
{
while (x)
{
  visit(x->data);
  S.push(x->rChild);
  x=x->lChild;
}
}

template<typename T,typename VST>
void travPre_I2(BinNodePosi(T) x,VST& visit){
  Stack <BinNodePosi(T)> S；
  while (true)
  {
    visitAlongLeftBranch(x,visit,S);//访问子树x的左侧链，右子树入栈缓冲
    if(S.empty())break;//栈空即退出
    x=S.pop();//弹出下一子树的根
  }
}

/*
=================================================================
中序遍历
=================================================================
*/
template <typename T,typename VST>
void traverse(BinNodePosi(T) x,VST& visit){
  if(!x)return ;
  traverse(x->lChild,visit);
  visit(x->data);//访问根节点
  traverse(x->rChild,visit);
}

//iteration version
/*
everytime meet left subtree ,右边开始进栈，直到没有右节点，开始出栈
*/
template<typename T>
static void goAlongLeftBranch(BinNodePosi(T) x,Stack <BinNodePosi(T)& >S){
  while (x)
  {
    S.push(x);
    x=x->lChild;
  }
}
template<typename T,typename V>
void travIn_I1(BinNodePosi(T) x,V& visit){
  Stack <BinNodePosi(T)> S;
  while (ture)
  {
    goAlongLeftBranch(x,S);
    if(S.empty())break;
    x=S.pop();
    visit(x->data);
    x=x->rChild;//accsee the right subtree
  }
}

/*
=================================================================
后序遍历
先遍历子结点遍历根节点
尽可能沿左出发，实在不得已才沿右边

如今将递归转化为迭代形式更多的是根据空间复杂度的考量，但是幸运的是
时间复杂度上也还可以

使用分摊分析工具

RPN与后序遍历有较强的相关性
=================================================================
*/
template <typename T,typename VST>
void traverse(BinNodePosi(T) x,VST& visit){
  if(!x)return ;
  traverse(x->lChild,visit);
  traverse(x->rChild,visit);
  visit(x->data);//访问根节点
}

template<typename T>
static void gotoLeftmostLeaf(Stack <BinNodePosi(T)>& S){
  while (BinNodePosi<T> x=S.top()))
  {
    if(HasLChild(*x)){
      if(HasRChild(*x))S.push(x->rc);
      S.push(x->lc);
    }else
      S.push(x->rc);
  }
  S.pop();
}
template<typename T,typename VST>
void travPost_I(BinNodePosi<T> x,VST& visit){
  Stack<BinNodePosi<T>> S;
  if(x) S.push(x);
  while (!S.empty())
  {
    if(S.top()!=x->parent)gotoLeftmostLeaf(S);
    x=S.pop();
    visit(x->data);
  }
  
}

/*
=================================================================
层次遍历
左先右后
=================================================================
*/
template<typename T,typename VST>
void BinNode<T>::travLevel(VST& visit){
  Queue<BinNodePosi(T)> Q;
  Q.enqueue(this);
  while (!Q.empty())
  {
    BinNodePosi(T) x=Q.dequeue();
    visit(x->data);
    if(HasLChild(*x))Q.enqueue(x->lChild);
    if(HasRChild(*x))Q.enqueue(x->rChild);
  }
  
}

/*
=================================================================
Huffman树
一种编码应用方式
=================================================================
*/



#endif