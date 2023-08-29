//
// Created by Administrator on 2023/7/28.
//
/*
 * 在C++11之前，C++没有对线程提供语言级别的支持，各种操作系统和编译器实现线程的方法不一样
 * C++11增加了线程以及线程相关的类，统一编程风格、简单易用、跨平台
 *
 * thread()noexcept;
 * 默认构造函数，构造一个线程对象，不执行任何任务(不会创建/启动子进程)
 *
 * template<class Function,class...Args>
 * explicit thread(Function&&fx,Args&&...args);
 * 创建线程对象，在线程中执行任务函数fx中的代码，args是要传递给任务函数fx的参数
 * 任务函数fx可以是普通函数、类的非静态成员函数、类的静态成员函数、匿名函数、仿函数
 *
 * thread(const thread&)=delete;
 * 删除拷贝构造函数，不允许线程对象之间的拷贝
 *
 * thread(thread&&other)noexcept;
 * 移动构造函数，将线程other的资源所有权转移给新创建的线程对象
 *
 * 赋值函数
 * thread&operator=(thread&&other)noexcept;
 * thread&operator=(const other&)=delete;
 * 线程中的资源不能被复制，如果other是右值，会进行资源所有权的转移，如果other是左值，禁止拷贝
 *
 * 注意
 * 先创建的子线程不一定跑得最快
 * 线程的任务函数返回后，子线程将终止
 * 如果主程序（主线程）退出，不论是正常退出还是意外终止，所有的子线程将会被强行终止
 */
#include "thread"
#include "iostream"
#include "windows.h"

using namespace std;

//普通函数
void func(int num, const string &str) {
    for (int i = 1; i <= 10; i++) {
        cout << i << ":" << num << "号" << str << endl;
        Sleep(1000);//休眠1s
    }
}

//仿函数
class myThread1 {
public:
    void operator()(int num, const string &str) {
        {
            for (int i = 1; i <= 10; i++) {
                cout << i << ":" << num << "号" << str << endl;
                Sleep(1000);//休眠1s
            }
        }
    }
};

//类中静态成员函数
class myThread2 {
public:
    static void func(int num, const string &str) {
        for (int i = 1; i <= 10; i++) {
            cout << i << ":" << num << "号" << str << endl;
            Sleep(1000);//休眠1s
        }
    }
};

//类中普通成员函数
class myThread3 {
public:
    void func(int num, const string &str) {
        for (int i = 1; i <= 10; i++) {
            cout << i << ":" << num << "号" << str << endl;
            ::Sleep(1000);//休眠1s
        }
    }
};

int main() {
    //用普通函数创建线程
    thread t1(func, 3, "cmx");
    thread t2(func, 8, "cmx");

    //用lambda函数创建线程
    auto f = [](int num, const string &str) {
        for (int i = 1; i <= 10; i++) {
            cout << i << ":" << num << "号" << str << endl;
            Sleep(1000);//休眠1s
        }
    };
    thread t3(f, 6, "cmx");

    //用仿函数创建线程
    thread t4(myThread1(), 4, "cmx");

    //用类的静态成员函数创建线程
    thread t5(myThread2::func, 9, "cmx");

    //用类的普通成员函数创建线程
    myThread3 myth; //必须要先创建类的对象，必须保证对象的生命周期比子线程要长
    thread t6(&myThread3::func, &myth, 3, "cmx");//第一个参数填成员函数的地址，第二个参数必须填对象的地址，也就是this指针

    cout << "任务开始\n";
    for (int i = 0; i < 10; i++) {
        cout << "执行任务中\n";
        Sleep(1000);
    }
    cout << "任务完成\n";
    t1.join();  //回收线程t1的资源
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
}
