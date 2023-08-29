//
// Created by Administrator on 2023/7/28.
//
/*
 * 完美转发
 * 在函数模板中，可以将自己的参数完美地转发给其他函数，所谓完美即不仅能够准确地转发参数的值，还能保证被转发的参数的左右值属性不变
 * C++11标准引入了右值引用和移动语义，所以，能否实现完美转发，决定了该参数在传递过程中使用的是拷贝语义还是移动语义
 *
 * 为了支持完美转发，C++11提供了以下方案
 * 如果函数模板的参数类型为T&&，那么，函数既可以接受左值引用，又可以接受右值引用
 *
 * 提供了模板函数std::forward<T>(参数),用于转发参数，如果参数是一个右值，转发之后仍然是右值引用，如果参数是左值，转发之后仍然是左值引用
 */
#include "iostream"

using namespace std;

void func1(int &i) {//如果参数是左值，调用此函数
    cout << "参数是左值=" << i << endl;
}

void func1(int &&i) {//如果参数是右值，调用此函数
    cout << "参数是右值=" << i << endl;
}

template<typename T>
void func(T &&i) {
    func1(forward<T>(i));
}

int main() {
    int i = 3;
    func(i);   //将调用左值函数
    func(8);   //将调用右值函数
}