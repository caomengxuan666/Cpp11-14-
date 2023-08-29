//
// Created by Administrator on 2023/7/23.
//
/*
 * 在默认情况下，智能指针过期的时候，用delete原始指针，释放它管理的资源
 * 程序员可以自定义删除器，，改变智能指针释放资源的行为
 * 删除器可以是全局函数，仿函数和lambda表达式，形参为原始指针
 */
#include "iostream"
#include "memory"

using namespace std;

class A {
public:
    string m_Name;

    A() { cout << "构造函数调用" << endl; }

    A(const string &name) : m_Name(name) { cout << "构造函数调用" << m_Name << endl; }

    ~A() { cout << "析构函数调用" << m_Name << endl; }
};

void deleteFunc(A *a) {
    cout << "全局函数的自定义删除器\n";
    delete a;
}

struct deleteClass {
    void operator()(A *a) {
        cout << "仿函数的自定义删除器\n";
        delete a;
    }
};

auto deleterLamb = [](A *a) {
    cout << "lambda的自定义删除器\n";
    delete a;
};

void test01() {
    shared_ptr<A> p1(new A("cmx"));  //用缺省的删除器
    shared_ptr<A> p2(new A("cmx"), deleteFunc);
    shared_ptr<A> p3(new A("cmx"), deleteClass());
    shared_ptr<A> p4(new A("cmx"), deleterLamb);

    unique_ptr<A, decltype(deleteFunc)*> p5(new A("cmx"), deleteFunc);
    unique_ptr<A,void(*)(A*)> p6(new A("cmx"), deleteFunc);//函数指针
    unique_ptr<A,deleteClass>p7(new A("cmx"),deleteClass());
    unique_ptr<A, decltype(deleterLamb)>p8(new A("cmx"),deleterLamb);

}

int main() {
    test01();
}