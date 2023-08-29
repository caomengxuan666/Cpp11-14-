//
// Created by Administrator on 2023/7/28.
//
/*
 * 可变参数模板是C++11新增的最强大的特性之一，它对参数进行了泛化，能支持任意个数、任意数据类型的参数
 */
#include "iostream"
#include "thread"

using namespace std;

void print() {//需要定义一个非模板函数，这个函数没有参数，表示参数包中已经没有参数了
    cout << "递归终止" << endl;
}

//展开参数包的递归函数模板
template<typename T, typename ...Args>
void print(T arg, Args...args) {
    cout << "参数" << arg << endl;  //显示本次展开的参数
    cout<<"还有"<<sizeof...(args)<<"个参数没有被展开"<<endl;
    print(args...);  //继续展开参数
}

int main() {
    print("cmx", "C++", 666);
    print("lwb", "JAVA","mysql",666);
}