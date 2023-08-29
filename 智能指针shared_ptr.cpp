//
// Created by Administrator on 2023/7/22.
//
/*
 * shared_ptr共享它指向的对象，多个shared_ptr可以指向(关联)相同的对象，在内部采用计数机制来实现
 * 当新的shared_ptr与对象关联时，引用计数增加1
 * 当shared_ptr超出作用域时，引用计数-1，当引用计数变为0时，则表示没有任何shared_ptr与对象关联，则释放该对象
 *
 * 基本用法
 * shared_ptr的构造函数也是explicit，但是没有删除拷贝构造函数和赋值函数
 * 初始化
 * 方法一
 * shared_ptr<A>p0(new A("cmx"));   //分配内存并初始化
 * 方法二
 * shared_ptr<A>p0=make)shared<A>("cmx")    //C++11标准，效率更高
 * 方法三
 * A*p=new A("cmx");
 * shared_ptr<A>po(p);  //用已经存在的地址初始化
 * 方法四
 * shared_ptr<A>p0(new A("cmx"));
 * shared_ptr<A>p1(p0); //用已经存在的shared_ptr初始化，计数+1
 * shared_ptr<A>p1=p0;  //用已经存在的shared_ptr初始化，计数+1
 *
 * 使用方法
 * 智能指针重载了*和->操作符，可以像使用指针一样使用shared_ptr
 * use_count()方法返回引用计数器的值
 * unique()方法，如果use_count()为1，返回true,否则返回false
 * 支持普通的拷贝和赋值，左值的shared_ptr计数器将减1，右值shared_ptr的计算器将加1
 * get()方法返回裸指针
 * 不要使用同一个裸指针初始化多个shared_ptr
 * 不要用shared_ptr管理不是new分配的内存
 *
 * 用于函数的参数
 * 与unique_ptr原理相同
 *
 * 不支持指针运算+,-,++,--
 *
 * 更多细节
 * 1.用nullptr给shared_ptr赋值把计数减1，如果计数为0，将释放对象，空的shared_ptr==nullptr
 *
 * 2.shared_ptr没有release,因为多个指针共享一个对象，不能由某一个决定是否释放
 *
 * 3.move可以转移对原始指针的控制权，还可以将unique_ptr转移成shared_ptr，但是反过来并不行
 *
 * 4.reset()改变与资源的关联关系
 * p.reset()    //解除与资源的关系，资源的引用计数减1
 * p.reset(new A("b")); //解除与资源的关系，资源的引用计数减1，关联新资源
 *
 * 5.swap()交换两个shared_ptr的控制权
 * void swap(shared_ptr<T>&_Right)
 *
 * 6.shared_ptr可以像普通指针那样，当指向一个类继承体系的基类对象时，也具有多态性质，如同使用裸指针管理基类对象和派生类对象那样
 *
 * 7.shared_ptr不是绝对安全，如果程序中调用exit()退出，全局的shared_ptr可以自动释放，但是局部的shared_ptr无法释放
 *
 * 8.shared_ptr提供了支持数组的具体化版本，
 * 数组版本的shared_ptr，重载了操作符[],操作符[]返回的是引用，可以作为左值使用
 *
 * 9.shared_ptr的线程安全性
 * shared_ptr的引用计数本身是线程安全(引用计数是原子操作)
 * 多个线程同时读一个shared_ptr对象是线程安全的
 * 如果是多个线程对一个shared_ptr对象进行读和写，则需要加锁
 * 多线程读写shared_ptr所指向的对象，不管是相同的shared_ptr对象，还是不同的shared_ptr对象，也需要加锁保护
 */
#include "iostream"
#include "memory"

using namespace std;

class A {
public:
    string m_Name;

    A() { cout << "构造函数调用" << endl; }

    A(const string &name) : m_Name(name) { cout << "构造函数调用" << m_Name << endl; }

    ~A() { cout << "析构函数调用" << m_Name << endl; }
};

void test01() {
    A *p = new A("cmx");
    shared_ptr<A> p0(p); //用已经存在的地址初始化
    shared_ptr<A> p1 = p0; //用已经存在的shared_ptr拷贝构造，计数+1
    cout << "po.use_count()=" << p0.use_count() << endl;  //显示p0引用计数的值
    cout << "m_name: " << p0->m_Name << endl;
    cout << "p1.use_count()=" << p1.use_count() << endl;  //显示p1引用计数的值
    cout << "m_name: " << p1->m_Name << endl;
}

void test03() {
    shared_ptr<A> p0(new A("cmx"));
    shared_ptr<A> p1 = p0; //用已经存在的shared_ptr拷贝构造，计数加1
    shared_ptr<A> p2 = p0; //用已经存在的shared_ptr拷贝构造，计数加1
    cout << "p0.use_count()=" << p0.use_count() << endl;  //值为3

    shared_ptr<A> p3(new A("cmx1"));
    shared_ptr<A> p4 = p3;
    cout << "p3.use_count()=" << p3.use_count() << endl;//值为2

    p4 = p1;    //左值减1，右值加1
    p3 = p1;    //倘若这么写，导致没有指针指向cmx1，这样的话会指向cmx的同时释放cmx1，指向的就是一个对象了
    cout << "p0.use_count()=" << p0.use_count() << endl;    //值为4
    cout << "p3.use_count()=" << p3.use_count() << endl;    //值为1
}

int main() {
    //test01();
    test03();
}