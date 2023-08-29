//
// Created by Administrator on 2023/7/27.
//
/*
 * 移动语义
 * 如果一个对象中有堆区资源，需要编写拷贝构造函数和赋值函数，实现深拷贝
 * 深拷贝把对象中的堆区资源复制了一份，如果源对象（被拷贝的对象）是临时对象，拷贝完就没什么用了，这样会造成没有意义的资源申请和释放操作。
 * 如果能够直接使用源对象拥有的资源，可以节省资源申请和释放的时间，C++11新增加的移动语义就能做到这一点
 * 实现移动语义要增加两个函数:移动构造函数和移动赋值函数
 *
 * 移动构造函数的语法
 * 类名（类名&&源对象)(...)
 *
 * 移动赋值函数的语法
 * 类名&operator(类名&&源对象)(...)
 *
 * 注意
 * 对于一个左值，会调用拷贝构造函数，但是有些左值是局部变量，生命周期也很短，C++为了使其也能移动而不是拷贝，
 * 提供了std::move方法来将左值转义为右值，从而方便使用移动语义。它其实就是告诉编译器，虽然是一个左值，但是
 * 不要对其使用拷贝构造函数，而是使用移动构造函数。左值对象被转移资源之后，不会立即析构，只有在离开自己的作用域
 * 的时候才会析构，如果继续使用左值中的资源，可能出现意想不到的错误
 *
 * 如果没有提供移动构造或者是赋值函数，只提供了拷贝构造或者是赋值函数，编译器找不到移动构造或者是赋值函数就会去找拷贝构造和赋值函数
 *
 * C++11中的所有容器都实现了移动语义，避免对含有资源的对象发生无意义的拷贝
 *
 * 移动语义对于拥有资源（如内存、文件句柄）对象有效，如果是基本类型，使用移动语义没有意义
 */
#include "iostream"
#include "string.h"

using namespace std;

class A {
public:
    int *m_data = nullptr;//数据成员
    A() = default;    //启用默认构造函数
    void alloc() {   //给m_data分配内存
        m_data = new int; //分配内存
        memset(m_data, 0, sizeof(int));//初始化已经分配的内存
    }

    A(const A &a) {
        cout << "调用了拷贝构造函数" << endl;    //显示自己被调用的日志
        if (m_data == nullptr)alloc();    //如果没有分配内存就分配
        memcpy(m_data, a.m_data, sizeof(int));    //把数据从源对象中拷贝过来
    }

    A(A &&a) {
        cout << "调用了移动构造函数" << endl;  // 添加移动构造函数的日志
        if (m_data != nullptr) delete m_data;  // 如果已经分配内存，先释放掉
        m_data = a.m_data;    // 把资源从源对象中转移过来
        a.m_data = nullptr;   // 把源对象中的指针置空
    }


    A &operator=(const A &a) {
        cout << "调用了赋值函数\n";
        if (this == &a)return *this;   //避免自我赋值
        if (m_data == nullptr)alloc();    //如果没有分配内存就分配
        memcpy(m_data, a.m_data, sizeof(int));
        return *this;
    }

    A &operator=(A &&a) {
        cout << "调用了移动赋值函数\n";
        if (this == &a)return *this;   //避免自我赋值
        if (m_data!= nullptr)delete m_data;  //如果已经分配内存，先释放掉
        m_data=a.m_data;
        a.m_data=nullptr;
        return *this;
    }

    ~A() {//析构函数
        if (m_data != nullptr) {
            delete m_data;
            m_data = nullptr;
        }
    }
};

void test01() {
    A a1;
    a1.alloc(); //分配堆区资源
    *a1.m_data = 3;   //给堆区内存赋值
    cout << "a1.m_data=" << *a1.m_data << endl;

    A a2 = a1;  //如果加上move会调用移动构造函数
    cout << "a2.m_data=" << *a2.m_data << endl;

    A a3;
    a3 = a1;    //如果在这里给a1加上一个move，会调用移动赋值函数
    cout << "a3.m_data=" << *a3.m_data << endl;

    auto f=[](){//返回A类对象的lambda函数
        A a;a.alloc();*a.m_data=8;return move(a);
    };
    A a4=f();   //lambda函数返回临时对象，是右值，将调用移动构造函数
    cout<<"a4.m_data="<<*a4.m_data<<endl;

    A a5;
    a5=f();
    cout<<"a6.m_data="<<*a3.m_data<<endl;
}

int main() {
    test01();
}