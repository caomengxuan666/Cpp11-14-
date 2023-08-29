//
// Created by Administrator on 2023/7/30.
//
/*
 *  条件变量是一种线程同步机制，当条件不满足时，相关线程被一直阻塞，直到某种条件出现，这些线程才会被唤醒
 *  为了保护共享资源，条件变量需要和互斥锁结合一起使用
 *  生产/消费者模型(高速缓存队列)
 *  C++11的条件变量提供了两个类
 *
 *  condition_variable 只支持与普通mutex搭配，效率更高
 *  condition_variable_any 是一种通用的条件变量，可以与任意mutex搭配(包括用户自定义的锁类型)
 *
 *  condition_variable类
 *  主要成员函数
 *  condition_variable()    默认构造函数
 *  condition_variable(const condition_variable &)=delete 禁止拷贝
 *  condition_variable& condition_variable::operator=(const condition_variable &)=delete 禁止赋值
 *  notify_one()    通知一个等待的线程
 *  notify_all()    通知全部等待的线程
 *  wait(unique_lock<mutex>lock)    阻塞当前线程，直到通知到达
 *  wait(unique_lock<mutex>lock,Pred,pred)  循环地阻塞当前线程，直到通知到达并且谓词满足
 *  wait_for(unique_lock<mutex>lock,时间长度)
 *  wait_for(unique_lock<mutex>lock,时间长度,Pred,pred)
 *
 *  条件变量的wait(mutex)函数
 *  把互斥锁解锁
 *  阻塞，等待被唤醒
 *  给互斥锁加锁
 *  注意： wait函数返回前会加锁，所以wait函数如果返回则一定申请到了锁
 *
 *  unique_lock类
 *  template<class Mutex>class unique_lock是模板类，模板参数为互斥锁类型
 *  unique_lock和lock_guard都是管理锁的辅助类，都是RAII风格，在构造时获得锁，在析构时释放锁
 *  他们的区别在于，为了配合condition_variable,unique_lock还有lock()和unlock()成员函数
 */
#include "iostream"
#include "thread"
#include "mutex"
#include "string"
#include "deque"
#include "queue"
#include "condition_variable"

using namespace std;

class A {
    mutex m_mutex;  //互斥锁
    condition_variable m_cond;//条件变量
    queue<string, deque<string>> m_q; //缓存队列，底层容器用的deque
public:
    void incache(int num)//生产数据,num指定数据的个数
    {
        lock_guard<mutex> lock(m_mutex); //申请加锁
        for (int i = 0; i < num; i++) {
            static int order = 1; //编号
            string message = to_string(order++) + "号选手";    //拼接出一个数据
            m_q.push(message);  //把生产出来的数据入队
        }
        //如果生产的数据只有一个，用notify_one()比较合适，反之有多个，用notify_all()更合适

        //m_cond.notify_one();    //唤醒一个被当前条件变量阻塞的线程
        m_cond.notify_all();    //唤醒全部线程，多线程操作效率更高
    }

    void outcache() {//消费者线程任务函数
        while (1) {
            //把互斥锁换成unique_lock<mutex>,并申请加锁
            cout << "线程" << this_thread::get_id() << ",申请加锁\n";
            unique_lock<mutex> lock(m_mutex);
            cout << "线程" << this_thread::get_id() << ",加锁成功\n";
            //条件变量虚假唤醒：消费者线程被唤醒后，缓存队列中没有数据

            //while (m_q.empty()) //如果队列非空，不进入循环，直接处理数据。必须用循环，不能用if
               // m_cond.wait(lock);//等待生产者的唤醒信号
               m_cond.wait(lock, [this] { return !m_q.empty(); });//与上面的while循环是一样的
            //数据元素出队
            string message = m_q.front();
            m_q.pop();
            cout << "线程:" << this_thread::get_id() << "," << message << endl;
            lock.unlock();
            //锁的使用时间越短越好，处理数据需要消耗时间，也可以使用作用域机制，让锁超出作用域自动释放

            //处理出队的数据(把数据消费掉)
            this_thread::sleep_for(chrono::milliseconds(1));    //假设处理数据需要1ms
        }
    }
};

void test01() {
    A a;
    thread t1(&A::outcache, &a);
    thread t2(&A::outcache, &a);
    thread t3(&A::outcache, &a);

    this_thread::sleep_for(chrono::seconds(2));
    a.incache(2);

    this_thread::sleep_for(chrono::seconds(3));
    a.incache(5);

    t1.join();
    t2.join();
    t3.join();
}

int main() {
    test01();
}