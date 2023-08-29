//
// Created by Administrator on 2023/7/29.
//
/*
 *  在多线程环境中，某些函数只能被调用一次，例如:初始化某个对象，而这个对象只能被初始化一次
 *  在线程的任务函数中，可以用std::call_once()来保证某个函数只被调用一次
 *  头文件#include<mutex>
 *  template<class callable,class...Args>
 *  void call_once(std::once_flag&flag,Function&&fx,Args&&...args)
 *  第一个参数是std::once_flag,用于标记函数fx是否已经被执行过
 *  第二个参数是需要执行的函数
 */
#include "iostream"
#include "mutex"
#include "windows.h"
#include "thread"

using namespace std;

once_flag onceflag; //once_flag全局变量,本质是取值为0和1的锁

void once_func(const int num, const string &str){
    for (int i = 0; i < 10; i++) {
        cout << "第" << i << "次" << num << "号" << str << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}
//普通函数
void func(int num, const string &str) {
    call_once(onceflag,once_func,0,"全体目光向我看齐");
}

void test01() {
    thread t1(func,2,"cmx");
    thread t2(func,3,"cmx");
    t1.join();
    t2.join();
}

int main() {
    test01();
}