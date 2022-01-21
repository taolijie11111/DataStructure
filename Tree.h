#ifndef __TREE__
#define __TREE__

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
template <typename T,typename VST>
static void visitAlongLeftBranch(
  BinNodePosi(T) x,
  VST& visit,
  //Stack <BinNodePosi(T)>& S)
  {
  while (x)
  {
    visit(x->data);
    S.push(x->rChild);
    x=x->lChild;
  }
  }
template<typename T,typename VST>
void travPre I2(BinNodePosi(T) x,VST& visit){
  Stack <BinNodePosi(T)》 S；
  while (true)
  {
    visitAlongLeftBranch(x,visit,S);//访问子树x的左侧链，右子树入栈缓冲
    if(S.empty())break;//栈空即退出
    x=S.pop();//弹出下一子树的根
  }
  
}

#endif