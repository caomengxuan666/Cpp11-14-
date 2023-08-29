//
// Created by Administrator on 2023/7/30.
//
/*
 *  线程同步：多个线程协同工作，协商如何使用共享资源
 *
 *  互斥锁(互斥量)
 *  加锁和解锁，确保同一时间只有一个线程访问共享资源
 *  访问共享资源之前加锁，访问完成后释放锁
 *  如果某线程持有锁，其他的线程形成等待队列
 *  C++11提供了四种互斥锁
 *  mutex:互斥锁
 *  timed_mutex:带超时机制的互斥锁
 *  recursive_mutex:递归互斥锁
 *  recursive_time_mutex:带超时机制的递归互斥锁
 *  包含头文件<mutex>
 *
 *  mutex类
 *  1.加锁lock()
 *  互斥锁有锁定和未锁定两种状态
 *  如果互斥锁是未锁定状态，调用lock()成员函数的线程会得到互斥锁的所有权，并将其上锁
 *  如果互斥锁是锁定状态，调用lock()成员函数的线程就会阻塞等待，直到互斥锁变成未锁定状态
 *  2.解锁unlock()
 *  只有持有锁的线程才能解锁
 *  3.尝试加锁trylock()
 *  如果互斥锁是未锁定状态，则加锁成功，函数返回true;
 *  如果互斥锁是锁定状态，则加锁失败，函数立即返回false(线程不会阻塞等待)
 *
 *  time_mutex类
 *  增加了两个成员函数
 *  bool try_lock_for(时间长度)
 *  bool try_lock_until(时间点)
 *
 *  recursive_mutex类
 *  递归互斥锁允许同意线程多次获得互斥锁，可以解决同一线程多次加锁造成的死锁问题
 *
 *  lock_guard类
 *  lock_guard是模板类，可以简化互斥锁的使用，也更安全
 *  lock_guard的定义如下
 *
 *  template<class Mutex>
 *  class lock_guard{
 *  explict lock_guard(Mutex&mtx);
 *  };
 *
 *  lock_guard在构造函数中加锁，在析构函数中解锁
 *  lock_guard采用了RAII思想(在类构造函数中分配内存，在析构函数中释放内存，保证资源在离开作用域时自动释放)
 *
 *  条件变量
 *
 *  生产/消费者模型
 */
#include "iostream"
#include "thread"
#include "mutex"

using namespace std;

mutex mtx;  //创建互斥锁，保护共享资源cout对象
mutex mtx1; //创建互斥锁，保护共享资源a

int a = 0;

class A {
public:
    recursive_mutex m_mutex;

    void func1() {
        m_mutex.lock();
        cout << "调用了func1()\n";
        m_mutex.unlock();
    }

    void func2() {
        m_mutex.lock();
        cout << "调用了func2()\n";
        func1();
        m_mutex.unlock();
    }
};

void func(int num, const string &str) {
    for (int i = 1; i < 10; i++) {
        mtx.lock();//申请加锁
        cout << "第" << i << "次装逼,帅气的" << num << "号," << str << endl;
        mtx.unlock();//解锁
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void func1() {
    for (int i = 1; i <= 10000000; i++) {
        cout << "线程" << this_thread::get_id() << "申请加锁...\n";
        mtx1.lock();
        cout << "线程" << this_thread::get_id() << "加锁成功...\n";
        a++;
        this_thread::sleep_for(chrono::seconds(5));
        mtx1.unlock();
        cout << "线程" << this_thread::get_id() << "释放了锁...\n";
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void func2() {
    for (int i = 1; i <= 10000000; i++) {
        lock_guard<mutex> mlock(mtx);
        a++;
    }
}

void test01() {
    thread t1(func, 1, "cmx");
    thread t2(func, 2, "cmx");
    thread t3(func, 3, "cmx");
    thread t4(func, 4, "cmx");
    thread t5(func, 5, "cmx");

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}

void test02() {
    thread t1(func1);
    thread t2(func1);

    t1.join();
    t2.join();
    cout << "a=" << a << endl;
}

void test03() {
    A a;
    //a.func1();
    a.func2();
}

void test04() {
    thread t1(func2);
    thread t2(func2);

    t1.join();
    t2.join();
    cout << "a=" << a << endl;
}

int main() {
    //test01();
    //test02();
    //test03();
    test04();
}