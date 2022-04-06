#ifndef __GRAPH__
#define __GRAPH__

typedef enum{UNDISCOVERED,DISCOVERED,VISITED} VStatus;
typedef enum{UNDISCOVERED,TREE,CROSS,FORWARD,BACKWARD} EType;


template <typename Tv,typename Te> //顶点类型，边类型
class Graph{//图Graph模板类
private:
  void reset(){//所有顶点，边的辅助信息复位
    for(int i=0;i<n;i++){//所有顶点的
      status(i)=UNDISCOVERED;//状态，时间标签
      dTime(i)=fTime(i)=-1;
      parent(i)=-1;//遍历树中的父节点，优先级数
      priority(i)=INT_MAX;
      for(int j=0;j<n;j++)//所有边
        if(exists(i,j))status(i,j)=UNDETERMINED;//类型
    }
  }
  void BFS(int,int&);
  void DFS(int, int&);
  void BCC(int,int&,Stack<int>&);
  bool TSort(int,int&,Stack<Tv>*);
  template<typename PU>void PFS(int,Pu);//(连通域)优先级搜索框架
public：
//注意语义的同一性
int n;//顶点总数
virtual int insert(Tv const&)=0;//插入顶点，返回编号
virtual Tv remove(int)=0;//删除顶点及其关联边，返回该顶点信息
virtual Tv& vertex(int)=0;
virtual int inDegree(int)=0;
virtual int outDegree(int)=0;
virtual int firstNbr(int)=0;
virtual int nextNbr(int,int)=0;
virtual VStatus& status(int)=0;
virtual int& dTime(int)=0;
virtual int& fTime(int)=0;
virtual int& parent(int)=0;
virtual int& priority(int)=0;
//边：这里约定，无向边均统一转化为方向互逆的一对有想向边，从而将无向图视为有向图的特例
int e;
virtual bool exisis(int,int)=0;
virtual void insert(Te const&,int,int,int)=0;
virtual Te remove(int,int)=0;
virtual EType& type(int,int)=0;
virtual Te& edge(int,int)=0;
virtual int& weight(int,int)=0;
//算法
void bfs(int);//
void dfs(int);
void bcc(int);
Stack<Tv>* tSort(int);
void prim(int);
void dijkstra(int);//最短路径算法
template <typename PU> void pfs(int,PU);//优先级搜索框架
};

//BFS 包含一个连通域
template <typename Tv,typename Te>
void Graph<Tv,Te>::BFS(int v,int & clock){
  Queue<int> Q;status(v)=DISCOVERED;
  Q.enqueue(v);
  while (!Q.empty())//O(nxn)
  {
    int v=Q.dequeue();//取出顶点
    dTime(v)=++clock;
    for(int u=firstNbr(v);-1<u;u=nextNbr(v,u))//O(e):只有有限个边才能进去 
      if(UNDISCOVERED==status(u)){
        status(u)=DISCOVERED;
        Q.enqueue(u);//发现该顶点
        status(v,u)=TREE;
        parent(u)=v;
      }else
        status(v,u)=CROSS;
    status(v)=VISITED;
  }
}

//bfs 当含有多个连通域时，需要进行一些改进
template <typename Tv,typename Te>
void Graph<Tv ,Te>::bfs(int s){
  reset();int clock=0;int v=s;
  do{
    if(UNDISCOVERED==status(v))BFS(v,clock);
  }while (s!=(v=(++v%n)));//只有当前的顶点只有通过if判断之后才会启动
}

//Depth first search 
//有可达域，即从一个点可以达到的所有的点的区域
//除此之外，还有一些该点达不到的地方，需要重新确定节点进行搜索
template <typename Tv,typename Te>
void Graph<Tv,Te>::DFS(int v,int& clock){
  dTime(v)=++clock;
  status(v)=DISCOVERED;
  for(int u=firstNbr(v);-1<u;u=nextNbr(v,u))
    switch (status(u))
    {
    case UNDISCOVERED://un discoverd 
      status(v,u)=TREE;
      parent(u)=v;
      DFS(u,clock);
      break;
    case DISCOVERED://discoverd
      status(v,u)BACKWARD;
      break;
    default:
      status(v,u)=dTime(v)<dTime(u)?FORWARD:CROSS;break;
    }
  status(v)=VISITED;
  fTime(v)=++clock;
}

//拓扑排序
//将所有顶点拍成一个线性序列，使其次序与原图相容
//这里面不能有环
//必须要找到一个零入度的顶点：指没有的箭头指向他的哪个点
//Begin with the end in mind

//DFS外面要包一层，将点都找到
//不一定要全部都弄，随便找一个点都可以在意料之中
//率性

//DFS
#define hca(x) (fTime(x))//利用此处闲置的fTime
template <typename Tv,typename Te>
void Graph(Tv,Te)::BCC(int v,int & clock,Stack<int>& S){
  hca(v)=dTime(v)=++clock;
  status(v)=DISCOVERED;
  S.push(v);
  for(int i=firstNbr(v);-1<u;u=nextNbr(v,u))
    switch (status(u))
    {
      //everytime meet hca we can judge it weather ansoter or not
    case DISCOVERED:
      type(v,u)=BACKWARD;
      if(u!=parent(v))hca(v)=min(hca(v),dTime(u));
      break;
    case UNDISCOVERED;
      parent(u)=v;
      type(v,u)=TREE;//拓展树边
      BCC(u,clock,S);
      if(hca(u)<dTime(v))hca(v)=min(hca(v),hca(u));
      else while (u!=S.pop());
      break; 
    default://VISITED(digraphs only)
      type(v,u)=dTime(v)<dTime(u)?FORWARD:CROSS;
      break;
    }
    status(v)=VISITED;
}

#undef hca


//优先级搜索


//Dijkstra算法
g->pfs(0,DijktraPU<char,int>());
template<typename Tv,typename Te>struct DijkPU
{
  virtual void operator()(Graph<Tv,Te>* g,int uk,int v){
    if(UNDISCOVERED != g->status(v))return;
    if(g->priority(v) > g->priority(uk)+g->weight(uk,v)){
      g->priority(v)  = g->priority(uk)+g->weight(uk,v);
      g->parent(v)    = uk;
    }
  }
};

//最小生成树MST
 //同Dijkstra算法


#endif