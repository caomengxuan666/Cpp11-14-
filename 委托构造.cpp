//
// Created by Administrator on 2023/7/26.
//
/*
 * 在实际的开发当中，一个类可能会重载多个构造函数。多个构造函数之间可能会有重复的代码
 * 例如变量初始化，如果在每个构造函数中都写一遍，这样代码会显得很臃肿
 * 委托构造就是在一个构造函数的初始化列表中红调用另一个构造函数
 *
 * 注意
 * 不要生成环状的构造过程
 * 一旦使用委托构造，就不能在初始化列表中初始化其他的成员变量
 *
 * 继承构造
 * 在C++11之前，派生类如果要使用基类的构造函数，可以在派生类构造函数的初始化列表中指定。
 * C++11推出了继承构造，在派生类中使用using来声明继承基类的构造函数
 */
#include "iostream"

using namespace std;

class A {
public:
    int m_a;
    int m_b;
    double m_c;

    //有一个参数的构造函数，初始化m_c
    A(double c) {
        m_c = c + 3;    //初始化m_c
        cout << "A(double c)" << endl;
    }

    //有两个参数的构造函数，初始化m_a和m_b
    A(int a, int b) {
        m_a = a + 1;    //初始化m_a
        m_b = b + 2;    //初始化m_b
        cout << "A(int a,int b)" << endl;
    }

    A(int a, int b, const string &str) : A(a, b) { //委托构造初始化m_a和m_b
        cout << "m_a=" << m_a << ",m_b=" << m_b << ",str=" << str << endl;
    }

    //委托A(double c)初始化m_c
    A(double c, const string &str) : A(c) {
        cout << "m_c=" << m_c << ",str" << str << endl;
    }
};

class B : public A {
public:
    double m_c;
    using A::A;//使用基类的构造函数
    //有三个参数的构造函数，调用A(a,b)初始化m_a和m_b,同时初始化m_c
    B(int a, int b, double c) : A(a, b), m_c(c) {
        cout << "B(int a,int b,double c)" << endl;
    }

    void show() { cout << "m_a=" << m_a << ",m_b=" << m_b << ",m_c" << m_c << endl; }
};

void test01() {
    A a1(10, 20, "cmx");
    A a2(3.1, "cmx");
}

void test02() {
    //将使用基类有一个参数的构造函数初始化m_a
    B b1(10);
    b1.show();

    //将使用基类有两个参数的构造函数，初始化m_a和m_b
    B b2(10, 20);
    b2.show();

    //将使用派生类有三个参数的构造函数，调用A(a,b)初始化m_a和m_b，同时初始化m_c
    B b3(10, 20, 3.14);
    b3.show();
}

int main() {
    //test01();
    test02();
}