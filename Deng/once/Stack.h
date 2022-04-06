#ifndef __STACK__
#define __STACK__

#include "Vector.h"
template <typename T> 
class Stack : public Vector<T>
{
public:
void push(T const & e){
  insert(size(),e);
}
T pop(){return remove(size()-1);}
T & top(){return (*this)[size() -1];}
};

//last in first out 

/*
=================================================================
Binary conversion（进制转换）
=================================================================
*/
void convert(Stack<char> & S,__int64 n,int base){
  static char digit[] =
  {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  while (n>0)
  {
    S.push(digit[n % base]);
    n /= base;//base instand of Binary
  }
}

/*
=================================================================
parenthesis matching  （括号匹配）
括号匹配的问题本可以使用计数器来进行，那么为什么要使用栈呢？
————当括号是多种的时候便也可以方便的进行括号匹配


栈混洗stack permutation
利用一个中转栈来进行中转
禁形：即无法通过栈混洗得到的排列
not involve 321

判别某一个排列是否为栈混洗
=================================================================
*/
bool paren(const char exp[],int lo,int hi){
  Stack<char> S;
  for(int i=lo;i<hi;i++){
    if('('==exp[i])S.push(exp[i]);
    else if(!S.empty())S.pop();
    else return false;
  }
  return S.empty();
}

/*
=================================================================
中缀表达式：
实现优先级处理方法
=================================================================
*/
float evaluate(char* S,char* & RPN){
  Stack<float> opnd;
  Stack<char> optr;
  optr.push('\0');
  while (!optr.empty())
  {
    if(isdigit(*S))readNumber(S,opnd);
    else switch (orderBetween(optr.top(),*S))
    {
      case '<':optr.push(*S);S++;break;
      case '=':optr.pop();S++;break;//脱括号并接收下一个字符
      case '>':{
        char op=optr.pop();
        if('!'==op)opnd.push(calcu(op,open.pop()));
        else{
          float pOpnd2=opnd.pop(),pOpnd1=opnd.pop();
          opnd.push(calcu(pOpnd1,op,pOpnd2));
        }
      break;
      }
    }
  }
  return opnd.pop();//弹出并返回最后的计算结果
}

const char pri[N_OPTR][N_OPTR]={//运算符优先等级[栈顶][当前]//N——OPTR里面填写的是操作符
  //      |----------------------------------|
  //
  /* + */   '>','>','<','<','<','<','<','>','>',
  /* - */   '>','>','<','<','<','<','<','>','>',
  /* * */   '>','>','>','>','<','<','<','>','>',
  /* / */   '>','>','>','>','<','<','<','>','>',
  /* ^ */   '>','>','>','>','>','<','<','>','>',
  /* ! */   '>','>','>','>','>','>',' ','>','>',
  /* ( */   '<','<','<','<','<','<','<','=',' ',
  /* ) */   ' ',' ',' ',' ',' ',' ',' ',' ',' ',
  /* \0 */  '<','<','<','<','<','<','<',' ','=',
}

/*
=================================================================
逆波兰表达式（Reverse Polish Notation）（RPN）
在运算符和操作数组成的表达式中，不使用括号，即可表示带优先级的运算关系
实例：
0!1+23!4-5^-67*-8-9+=2013
=================================================================
*/
float evaluate(char * S,chae * & RPN){
  while (!optr.empty()){
    if(isdigit(*S)){readNumber(S,opnd);append(RPN,opnd.top());}
    else
      switch (orderBetween(optr.top(),*S)){
      case '>':
        char op=optr.pop();
        append(RPN,op);
        break;
      }
  }
}

/*
=================================================================
栈与队列
队列：
只能从队尾插入，从对头删除
first in first out
队列既然属于序列的特列，故亦可直接基于向量或列表派生

Stack and Vector:
常常将vector的首端作为Stack的盲端
=================================================================
*/
template <typename T> class Queue: public List<T>
{
public:
  void enqurue(T const & e){insertAsLast(e);}//in
  T dequeue(){return remove(first());}//out
  T & front(){return first()->data;}//head
};
#endif
