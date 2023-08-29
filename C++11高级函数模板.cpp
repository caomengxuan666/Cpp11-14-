//
// Created by Administrator on 2023/7/14.
//
/*
 * 语法:decltype(expression)var;
 * decltype推导规则(按步骤)
 * 1.如果expression是一个没有用括号括起来的标识符，则var的类型与该标识符的类型相同，包括const等限定符
 * 2.如果expression是一个函数调用，则var的类型与函数的返回值类型相同(函数不能返回void,但是可以返回void*)
 * 3.如果expression是一个左值（能取地址，且要排除第一种情况），或者用括号括起来的标识符，那么var的类型是expression的引用
 * 4.如果上面的条件都不满足，则var的类型与expression的类型相同
 * 注意:如果需要多次使用decltype，可以结合typedef和using
 * 注意:C++14标准中函数的返回值可以auto,不用写尾随类型
 */
#include "iostream"

using namespace std;

template<typename T1, typename T2>
auto func(T1 x, T2 y)-> decltype(x+y) {
    decltype(x+y) temp = x + y;
    cout << "temp=" << temp << endl;
}

int function() {
    cout << "func被调用" << endl;
    return 3;
}

void test01() {
    short a = 5;
    short &ra = a;
    short b = 10;
    decltype(a) da0;
    decltype(ra) da1 = b;  //必须初始化引用

    decltype(function) *da2 = function; //da2这里是函数指针
    //只填写函数名，得到的是函数的类型，而不是函数返回值的类型
    da2();
    decltype(a) da3 = b;
    decltype((a)) da4 = b; //没有用括号和用了括号是不一样的，用了括号就是引用
    decltype(function) da5;  //这里是函数类型
    decltype((function)) da6 = function;   //这里是函数的引用
    da6();
}

int main() {
    test01();
}
