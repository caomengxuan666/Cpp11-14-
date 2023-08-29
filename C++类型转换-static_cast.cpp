//
// Created by Administrator on 2023/7/14.
//
/*
 * C++认为C风格类型转换不安全推出了四个新的关键字来实现类型转换
 * static_cast  1.用于内置数据类型之间的转换 2.用于指针之间的转换
 * const_cast   1.static_cast不能丢掉指针(引用)的const和volatile属性,
 * reinterpret_cast 1.reinterpret_cast可以解决static_cast不能转换不同类型的指针(引用)的问题，它的意思是重新解释，能够将一种对象类型转换为另一种，不管它们是否有关系
 * dynamic_cast 1.运行时类型识别机制，，可以从一个虚的基类强制到一个派生类，可以获取运行时类型的信息
 *
 *  注意:C++的类型转换只是语法上的解释，本质上与C风格的类型转换没有什么不同
 *
 *  static_cast转换指针的应用场景：1.其它类型指针->void*指针->其它类型指针
 *
 *  const_cast的应用场景:1.丢掉指针(引用)的const和volatile属性
 *
 *  reinterpret_cast的应用场景：1.改变指针(引用)的类型
 *                            2.将指针(引用）转换成整形变量，整形与指针占用的字节数必须一致，否则转换可能损失精度
 *                            3.将一个整形变量转换成指针(引用)
 *
 *
 *  语法:
 *  static_cast<目标类型>(表达式);
 *  reinterpret_cast<目标类型>(表达式）;
 *  要求:<目标类型>和(表达式)中必须有一个是指针（引用）类型，reinterpret_cast不能丢掉（表达式）的const或volatile属性
 */
#include "iostream"

using namespace std;

void func(void *ptr) {    //转换指针
    //double *p = static_cast<double *>(ptr);
    long long ii = reinterpret_cast<long long>(ptr);
}

void test01() {
    int i = 3;
    long l = i;   //安全的隐式转换，无警告

    double d = 1.23;
    long l1 = d;  //可以隐式转换，但是会出现可能丢失数据的警告

    long l2 = (long) d;    //C风格的显示转换，不会出现警告
    long l3 = static_cast<long>(d);   //C++风格的显示转换，不会出现警告

    int ii = 10;
    //double *pd1=&ii;    //错误，不能隐式转换
    double *pd2 = (double *) &ii;   //C风格的强制转换
    //double*pd3=static_cast<double>(&ii);    //错误，static_cast不支持不同类型指针的转换，需要先转换为void*类型

    void *pv = &ii;     //任何类型的指针都可以隐式转化成void*
    double *pd4 = static_cast<double *>(pv);    //static_cast可以把void*转换成其它类型的指针
    func(&ii);
}

void test02() {
    long long ii = 10;

    double *pd1 = reinterpret_cast<double *>(&ii);  //reinterpret_cast可以直接转换指针类型


    func(reinterpret_cast<void *>(ii));
}

void test03() {
    const void *aa;
    int *bb = (int *) aa;   //C风格强制转换，丢掉const限定符
    void *cc = const_cast<void *>(aa);   //C++风格，强制转换，丢掉const限定符

    func(const_cast<void*>(aa));
}

int main() {
    test01();
    test02();
    test03();
}