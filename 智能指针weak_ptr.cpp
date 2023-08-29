//
// Created by Administrator on 2023/7/23.
//
/*
 *  shared_ptr存在的问题
 *  shared_ptr内部维护了一个共享的引用计数器，多个shared_ptr可以指向同一个资源
 *  如果出现了循环引用的情况，引用计数永远无法归0，资源部会被释放
 *
 *  weak_ptr是为了配合shared_ptr而引入的，它指向一个由shared_ptr管理的资源但是不影响资源的生命周期
 *  也就是说将一个weak_ptr绑定到shared_ptr不会改变shared_ptr的引用计数
 *
 *  不论是否有weak_ptr指向，如果最后一个指向资源的shared_ptr被销毁，资源就会被释放
 *
 *  weak_ptr更像是shared_ptr的助手而不是智能指针
 *
 *  使用方法
 *  weak_ptr没有重载->和*，不能直接访问资源
 *  1.operator=()   //把shared_ptr或者是weak_ptr赋值给weak_ptr
 *  2.expired() //判断它指的资源是否已经过期或者被销毁
 *  3.lock()    //返回shared_ptr,如果资源已经过期，返回空的shared_ptr
 *  4.reset()   //将当前weak_ptr指针置为空
 *  5.swap()    //交换
 *
 *  weak_ptr不会控制对象的生命周期，但是，它知道对象是否还活着
 *
 *  用lock()函数把它可以提升为shared_ptr,如果对象还活着，返回有效的shared_ptr,如果对象已经死了，提升会失败，返回一个空的shared_ptr
 *
 *  提升的行为lock()是线程安全的
 */
#include "iostream"
#include "memory"

using namespace std;

class B;

class A {
public:
    string m_Name;

    A() { cout << "构造函数调用A" << endl; }

    A(const string &name) : m_Name(name) { cout << "构造函数调用A" << m_Name << endl; }

    ~A() { cout << "析构函数调用A" << m_Name << endl; }

    //shared_ptr<B>m_p;
    weak_ptr<B> m_p;
};

class B {
public:
    string m_Name;

    B() { cout << "构造函数调用B" << endl; }

    B(const string &name) : m_Name(name) { cout << "构造函数调用B" << m_Name << endl; }

    ~B() { cout << "析构函数调用B" << m_Name << endl; }

    //shared_ptr<A>m_p;
    weak_ptr<A> m_p;
};

void test01() {//如果对方不能析构，则自身也无法析构，析构函数无法被调用,所以采用weak_ptr
    shared_ptr<A> pa = make_shared<A>(" cmxA");
    shared_ptr<B> pb = make_shared<B>(" cmxB");

    cout << "pa.use_count=" << pa.use_count() << endl;
    cout << "pb.use_count=" << pb.use_count() << endl;
    pa->m_p = pb;
    pb->m_p = pa;
    cout << "pa.use_count=" << pa.use_count() << endl;
    cout << "pb.use_count=" << pb.use_count() << endl;
}

void test02() {
    shared_ptr<A> pa = make_shared<A>(" cmxA");
    shared_ptr<B> pb = make_shared<B>(" cmxB");
    pa->m_p = pb;
    pb->m_p = pa;

    shared_ptr<B>p=pa->m_p.lock();  //把weak_ptr提升为shared_ptr，是线程安全的
    if(pa->m_p.expired()==true)cout<<"语句块内部pa->m_p已过期"<<endl;
    else cout<<"语句块内部:pa->m_p.lock()->m_name"<<pa->m_p.lock()->m_Name<<endl;

    if(pa->m_p.expired()==true)cout<<"语句块外部:pa->m_p已过期"<<endl;
    else cout<<"语句块外部:pa->m_p.lock()->m_name"<<pa->m_p.lock()->m_Name<<endl;
}

int main() {
    //est01();
    test02();
}