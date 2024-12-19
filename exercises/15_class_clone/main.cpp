#include "../exercise.h"
#include <cstddef>
#include <cstdio>
#include <cstring>
// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


class DynFibonacci {
public:
    int cached;
    int capacity;
    size_t *cache = nullptr;
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity){
        cache = new size_t[capacity];
        memset(cache, 0, sizeof(size_t) * capacity);
        cache[0] = 0;
        cache[1] = 1;
        cached = 2;
        this->capacity=capacity;
    }

    // TODO: 实现复制构造器
    DynFibonacci(DynFibonacci const & fbi){
       this->cache = new size_t[fbi.capacity];
       memset(this->cache, 0, sizeof(size_t) * fbi.capacity);
       memcpy((void *)this->cache, (void *)fbi.cache, fbi.capacity*sizeof(size_t));
       this->capacity=fbi.capacity;
       this->cached = fbi.cached;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci(){
         delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        if (i <= cached)
            return cache[i];

        for (int j = 2; j <= i; ++j) {
            if (cache[j] != 0)
                continue;
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        this->cached = i;
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
    size_t get(int i) const {
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}