//
// Created by Administrator on 2023/7/29.
//
/*
 *  线程资源的回收
 *  虽然同一个进程的多个线程共享进程的栈空间，但是，每个子线程在这个栈中拥有自己私有的栈空间，所以，线程结束时需要回收资源
 *
 *  回收自线程资源的两种办法
 *  1.在主程序中，调用join()成员函数等待子线程退出，回收它的资源。如果子线程已经退出，join()函数立即返回，否则会产生阻塞，直到子线程退出
 *  2.在子线程中，调用detach()成员函数分离子线程，子线程退出时，系统自动回收资源。分离后的子线程不可join()
 *
 *  joinable()成员函数可以判断子线程的分离状态，函数返回bool类型
 */
#include "iostream"
#include "thread"
#include "windows.h"

using namespace std;

void func(int num, const string &str) {
    for (int i = 0; i < 10; i++) {
        cout << "第" << i << "次" << num << "号" << str << endl;
        Sleep(1000);
    }
}

void test01() {
    thread t1(func, 5, "cmx");
    t1.detach();    //分离子线程

    cout << "任务开始" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "执行任务中\n";
        Sleep(1000);    //假设执行任务所需时间
    }
    cout << "任务结束\n";

    //t1.join();
    Sleep(10000);
}

void test02() {

}

int main() {
    test01();
}