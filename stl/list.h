template <class T>
struct __list_node
{
    /* data */
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};

template<class T,class Alloc=alloc>
class list

#include <list>
