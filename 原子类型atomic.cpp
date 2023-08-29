//
// Created by Administrator on 2023/7/30.
//
/*
 * C++11提供了atomic<T>模板类(结构体)，用于支持原子类型，模板参数可以是bool,char,int ,long ,long long ,指针类型
 * 不支持浮点类型和自定义数据类型
 * 原子操作由CPU指令提供支持，它的性能比锁和消息传递更高，并且，不需要程序要处理加锁和释放锁的问题，支持修改、读取、交换、比较并交换等操作
 *
 * 构造函数
 * atomic()noexcept=default;    //默认构造函数
 * atomic(T val)noexcept;   //转换函数
 * atomic(const atomic&)=delete;    //禁用拷贝构造函数
 *
 * 赋值函数
 * atomic& operator=(const atomic&)=delete;  //禁用赋值函数
 *
 * 常用函数
 * void store(T val)noexcept;   //把val的值存入原子变量
 * T load()noexcept;    //读取原子变量中的值
 * T fetch_add(T val)noexcept;  //把原子变量的值与val相加，返回原值
 * T fetch_sub(T val)noexcept;  //把原子变量的值减val，返回原值
 * T exchange(T val)noexcept;   //把val的值存入原子变量，返回原值
 * T compare_exchange_strong(T &expect,T val)noexcept;  //比较原子变量的值和预期值expect,
 * 如果当两个值相等，把val存到原子变量中，函数返回true;如果当两个值不想等，用原子变量的值更新锁(返回false)预期值,函数返回false
 * bool is_lock_free()  //查询某原子类型的操作是直接用CPU指令(返回true),还是编译器内部的锁(返回false)
 *
 * 注意
 * 原子类型只支持整数
 * atomic<T>模板类重载了整数操作的各种运算符
 * atomic<T>模板类的模板参数支持指针，但不代表指针所指向的对象是原子类型
 * 原子类型可以用作计数器，布尔型可以用做开关
 * CAS指令是实现无锁队列基础
 */
#include "thread"
#include "iostream"
#include "windows.h"
#include "atomic"

using namespace std;

void test01() {
    atomic<int> a = 3; //转换函数
    cout << "a=" << a.load() << endl;
    a.store(8);
    cout << "a=" << a.load() << endl;

    int old;//存放原值
    old = a.fetch_add(5);
    cout << "old=" << old << ",a=" << a.load() << endl;
    old = a.fetch_sub(2);
    cout << "old=" << old << ",a=" << a.load() << endl;
}

void test02() {
    atomic<int> i = 3;  //原子变量
    int expect = 3;     //期待值
    int val = 5;    //打算存入原子变量的值
    //比较原子变量的值和预期值expect
    //如果当两个值相等，把val存储到原子变量中
    //如果两个值不想等，用原子变量的值更新预期值
    //执行存储操作时返回true,否则返回false
    bool bret = i.compare_exchange_strong(expect, val);
    cout << "bret=" << bret << endl;
    cout << "i=" << i << endl;
    cout << "expect=" << expect << endl;
}

int main() {
    test01();
    test02();
}