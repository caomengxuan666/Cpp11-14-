//
// Created by Administrator on 2023/7/29.
//
/*
 *  C++11提供了命名空间this_thread来表示当前线程，该命名空间中有四个函数:get_id()，sleep_for(),sleep_unit(),yield()
 *
 *  1.get_id()
 *  该函数用于获取线程id，thread类也有同名的成员函数
 *
 *  2.sleep_for()
 *  该函数让线程休眠一段时间
 *
 *  3.sleep_until()
 *  该函数让线程休眠至指定时间点(可定时任务)
 *
 *  4.yield()
 *  该函数让线程主动让出自己已经抢到的CPU时间片
 *
 *  5.thread类其他的成员函数
 *  void swap(std::thread&other)    //交换两个线程对象
 *  static unsigned hardware_concurrency()noexcept; //返回硬件线程上下文的数量
 */
#include "iostream"
#include "windows.h"
#include "thread"

using namespace std;

//普通函数
void func(int num, const string &str) {
    cout<<"子线程："<<this_thread::get_id()<<endl;
    for(int i=0;i<10;i++) {
        cout << "第" << i << "次" << num << "号" << str << endl;
        //Sleep(1000);
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void test01() {
    thread t1(func,6,"cmx");
    thread t2(func,4,"cmx");
    cout<<"主线程："<<this_thread::get_id()<<endl;
    cout<<"线程t12:"<<t2.get_id()<<endl;
    t1.swap(t2);

    thread t3=move(t2);
    t1.join();
    //t2.join();
    t3.join();
}

int main() {
    test01();
}