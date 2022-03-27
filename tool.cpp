#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>

//array
//在Stack上定义
int array[M][N];
//在heap上定义（动态数组）
int **array=new int* [M];//C++
(int**)malloc(M* sizeof(int*));//C

void func(int **arr,int M,int N){

}

for(int i=0;i<M;i++){
    delete[] array[i];
}
delete[] array;

//智能指针
make_shared函数:
最安全的分配和使用动态内存的方法就是调用一个名为make_shared的标准库函数，此函数在动态内存中分配一个对象并初始化它，返回指向此对象的shared_ptr。头文件和share_ptr相同，在memory中
必须指定想要创建对象的类型
下面时标准化的定义
shared_ptr<int> p3 = make_shared<int>(42);
shared_ptr<string> p4 = make_shared<string>(10,'9');
shared_ptr<int> p5 = make_shared<int>();





//vector
vector<type> a;
a[]
a.size()
a.push_back
a.pop_back
a.erase()//删除

//Hash Table
insert:O(1)
delete:O(1)
find:O(1)
Open Hashing : 拉链法，后面挂着一些链表
Closed Hashing : 开地址法，关键字冲突时有一个检测序列，查找到空位置插进去

JAVA
HashTable: 同步
HashSet: 
HashMap: 不同步，适合处理非线性的

//string
C:
char* strcpy(char* destination,const char* source);
char* strcat(char* destination, const char* source);
int strcmp(const char* st1,const char* st2);
char* strstr(char* str1,const char* str2);
size_t strlen(const char* str);
double atof(const char* str);
int atoi(const char* str);

C++:
String 重载了+<>=,==,复制，比较，附加子串
size_t find(const string& str,size_t pos=0)const;
string substr(size_t pos=0,size_t len=npos)const;
string &erase(size_t pos=0,size_t len=npos)const;
size_t length();