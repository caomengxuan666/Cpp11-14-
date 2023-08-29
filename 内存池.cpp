//
// Created by Administrator on 2023/7/11.
//
#include "iostream"
#include "string.h"

using namespace std;

class Person {
public:
    Person(int Index = 0, string Name = "cmx") : index(Index), name(Name) { cout << "构造函数调用" << endl; }

    ~Person() { cout << "析构函数调用" << endl; }

    static bool initPool() {
        m_Pool = (char *) malloc(82);   //申请内存空间
        if (m_Pool == 0)return false;           //申请失败情况
        memset(m_Pool, 0, 82);      //将内存池清空
        cout << "内存池起始地址为:" << (void *) m_Pool << endl;
        return true;
    }

    static void freePool() {
        if (m_Pool == 0)return;
        free(m_Pool);
        cout << "内存池已释放" << endl;
    }

    void *operator new(size_t size) {
        if (m_Pool[0] == 0) {
            cout << "分配了第一块内存" << (void *) (m_Pool + 1) << endl;
            m_Pool[0] = 1;    //把第一个位置标记成已经分配
            return m_Pool + 1;    //返回第一个用于存放对象的值
        }
        if (m_Pool[41] == 0) {
            cout << "分配了第二块内存" << (void *) (m_Pool + 42) << endl;
            m_Pool[41] = 1;
            return m_Pool + 42;
        }
        //如果内存池都满了，那么就直接向系统申请内存
        void *ptr = malloc(size);
        cout << "申请到的内存地址是" << ptr << endl;
        return ptr;
    }

    void operator delete(void *ptr) {
        if (ptr == 0) {
            cout << "空指针释放" << endl;
        }
        if (ptr == m_Pool + 1) {
            cout << "释放了第一块内存" << endl;
            m_Pool[0] = 0;    //第一块位置标记为空
            return;
        }
        if (ptr == m_Pool + 42) {
            cout << "释放了第二块内存" << endl;
            m_Pool[41] = 0;
            return;
        }
        //不属于内存池就直接归还系统了
        free(ptr);
    }

    int index;
    string name;
    static char *m_Pool;
};

char *Person::m_Pool = 0;  //初始化内存池指针

void testSize() {
    Person a;
    cout << sizeof(a);
}

int main() {
    //testSize();
    //初始化内存池
    if (Person::initPool() == false) {
        cout << "初始化内存池失败" << endl;
        return -1;
    }
    Person *p1 = new Person(0, "cmx");
    cout << "p的地址是" << p1 << "编号" << p1->index << "姓名" << p1->name << endl;

    Person *p2 = new Person(1, "lwb");
    cout << "p的地址是" << p2 << "编号" << p2->index << "姓名" << p2->name << endl;

    Person *p3 = new Person(2, "hhw");
    cout << "p的地址是" << p3 << "编号" << p3->index << "姓名" << p3->name << endl;

    delete p1;

    Person *p4 = new Person(3, "cyz");
    cout << "p的地址是" << p4 << "编号" << p4->index << "姓名" << p4->name << endl;

    delete p2;

    delete p3;

    delete p4;

    Person::freePool();
}