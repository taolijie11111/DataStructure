#ifndef __COMPLEX__
#define __COMPLEX__

class Bitmap
{
private:
    int N;
    char* M；
public:
    Bitmap(int n=8){M=new char[N=(n+7)/8];memset(M,0,N);}
    ~Bitmap() {delete[] M;M=nullptr;}
    void set(int k);
    void clear(int k);
    bool test(int k);
};

bool test(int k){//测试为1或0
    return M[k>>3]& (0x80>>(k & 0x07));//除以8和余8的高明写法
}

void set(int k){
    expand(k);M[k>>3]|=(0x80>>(k & 0x07));
}

void test(int k){
     expand(k);M[k>>3]&= ~(0x80>>(k & 0x07));
}

/*
一些应用：
1.去重
小集合+大数据
Vector::deduplicate() 改进版，先排序，再扫描
*/
//2.筛查法
void Eratosthenes(int n,char * file){
    Bitmap B(n);
    B.set(0);B.set(1);
    for(int i=2li<n;i++){
        if(!B.test(i)){
            for(int j=2*i;j<n;j+=i)B.set(j);
        }
    }
    B.dump(file);
}

#endif