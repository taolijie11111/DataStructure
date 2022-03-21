# 一些标准库主要结构的应用场景

vector的使用场景：比如软件历史操作记录的存储，我们经常要查看历史纪录，比如上一次的记录，上上次的记录。
deque的使用场景：比如排队购票系统，对排队者的存储可以采用deque，支持头端的快速移除，尾端的快速添加。如果采用的是vector，则头端删除时，会移动大量的数据，速度慢。
vector与deque的比较：

1. vector.at()比deque.at()效率高，因为vecto是一段连续的存储空间，而deque是分段连续的存储空间，中间用一个map的数据结构对其进行连接，所以其查询速度是没有vector快的。

2. 如果要大量释放容器中元素的话，vector花费的时间更少，原因还是由于两者的存储结构不同。

list的使用场景：比如公交车乘客的存储，随时可能有乘客下v很，支持频繁的不确实位置原始的删除和插入。

set/multiset的使用场景：比如对手机游戏的个人得分记录的存储，存储要求从高分到低分地顺序排列。

map/multimap的使用场景：比如ID号存储十万个用户，想要快速通过ID查找对应的用户。二叉树的查找效率，

这事就体现出来了。如果是vector容器，最坏的情况下可能要遍历完整个容器才能找到该用户。

原文链接：https://blog.csdn.net/Attention_0/article/details/86564147


# set和map两者之间的区别
关于，set是只能排列一个数据吗？
如果是用指针来排列，那和map有什么区别呢？
map为什么还需要加一个data呢？


https://docs.microsoft.com/en-us/cpp/cpp/welcome-back-to-cpp-modern-cpp?redirectedfrom=MSDN&view=msvc-170

