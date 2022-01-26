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

//BFS
template <typename Tv,typename Te>
void Graph<Tv,Te>::BFS(int v,int & clock){
  Queue<int> Q;status(v)=DISCOVERED;
  Q.enqueue(v);
  while (!Q.empty())
  {
    int v=Q.dequeue();
    dTime(v)=++clock;
    for(int u=firstNbr(v);-1<u;u=nextNbr(v,u))
      if(UNDISCOVERED==status(u)){
        status(u)=DISCOVERED;
        Q.enqueue(u);
        status(v,u)=TREE;
        parent(u)=v;
      }else
        status(v,u)=CROSS;
    status(v)=VISITED;
  }
}


#endif