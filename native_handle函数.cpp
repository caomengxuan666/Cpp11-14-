//
// Created by Administrator on 2023/7/29.
//
/*
 * C++11定义了线程标准，不同的平台和编译器在实现的时候，本质上都是对操作系统的线程库进行封装，会损失一部分功能
 * 为了弥补C++11线程库的不足，thread类提供了native_handle()成员函数，用于获得与操作系统相关的原生线程句柄，操作系统原生的线程库就可以用原生线程句柄操作系统
 *
 */
#include "iostream"
#include "thread"
#include "pthread.h"

using namespace std;

void func() {//线程任务函数
    for (int i = 0; i < 10; i++) {
        cout << "i=" << i << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void test01() {
    thread t1(func);
    this_thread::sleep_for(chrono::seconds(5));
    pthread_t thid = t1.native_handle();  //获取Linux操作系统原生的操作句柄
    pthread_cancel(thid);   //取消线程
    t1.join();  //等待线程退出
}

int main() {
    test01();
}