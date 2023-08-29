//
// Created by Administrator on 2023/7/26.
//
/*
 * lambda函数是C++11标准新增的语法糖，也称为lambda函数或者匿名函数
 * lambda函数的特点是:距离近，简洁，高效和功能强大
 * 实例[](const int&no)->void{cout<<"亲爱的"<<no<<"号:我是cmx\n;);
 * 语法:[捕获列表](参数列表) 函数选项 ->返回类型 {函数体}
 *
 * 参数列表
 * 参数列表是可选的，类似于普通函数的参数列表，如果没有参数列表()可以省略不写
 * 与普通函数的不同
 * lambda函数不能有默认参数
 * 所有参数必须有参数名
 * 不支持可变参数
 *
 * 返回类型
 * 用后置的方法书写返回类型，类似于普通函数的返回类型，如果不写返回类型，lambda会根据函数体中的代码推断出来
 * 如果有返回类型，建议显示地指定，自动推断可能与预期不一致
 *
 * 函数体
 * 类似于普通函数的函数体
 *
 * 捕获列表
 * 通过捕获列表，lambda函数可以访问父作用域中的非静态局部变量（静态局部变量可以直接访问）
 * 捕获列表书写在[]中，与函数参数的传递类似，捕获方式也可以是值或者引用
 *
 * 不同的捕获方式
 * []空捕获列表，lambda不能使用所在函数中的变量
 * [names]names是一个逗号分隔的名字列表，这些名字都是lambda所在函数的局部变量，默认情况下是值捕获，前面加&指明是引用捕获
 * [=]隐式捕获列表，采用值捕获方式，lambda体将拷贝所使用的来自所在函数的实体的值
 * [&]隐式捕获列表，采用引用捕获方式，lambda体中所使用的的来自所在函数体的实体都采用引用方法使用
 * [&,identifier_list]identifier_list是一个逗号分隔的列表，包含0个或多个来自所在函数的变量。这些变量采用值捕获方式，而任何的隐式捕获的变量都采用引用捕获，identifier_list中的名字前面不能使用&
 * [=,identifier_list]identifier_list的变量都采用引用方式捕获，而任何隐式捕获都采用值捕获。identifier_list中的名字不能包括this,且这些名字之前必须使用&
 *
 *
 * 修改值捕获的值
 * 在lambda函数中，如果以传值方式捕获变量，则函数体中不能修改该变量，否则会引发编译错误
 * 在lambda函数中，如果希望修改值捕获变量的值，可以加mutable选项，但是在lambda函数的外部，变量的值不会被修改
 * lambda函数的本质
 * 当我们编写了lambda函数之后，编译器将其翻译成一个类，该类中有一个重载了()的函数
 * 1.采用值捕获
 * 采用值捕获时,lambda函数生成的类用捕获变量的值初始化自己的成员变量
 * 默认情况下，由lambda函数生成的类是const成员函数，所以变量的值不能修改。如果加上mutable,相当于去掉const
 * 2.采用引用捕获
 * 如果lambda函数采用引用捕获的方式，编译器直接引用就行了
 * 唯一需要注意的是，lambda函数执行时，程序必须保证引用的对象有效
 */
#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;

void zsShow(const int &no) {
    cout << "亲爱的" << no << "号:我是cmx\n";
}

class czs {
public:
    void operator()(const int &no) {
        cout << "亲爱的" << no << "号:我是cmx\n";
    }
};

void test01() {
    vector<int> w = {2, 5, 0};

    for_each(w.begin(), w.end(), zsShow);

    for_each(w.begin(), w.end(), czs());

    auto f = [](const int &no) -> int {
        cout<<"亲爱的"<<no<<"号:我是cmx\n";
        return 0;
    };
    for_each(w.begin(), w.end(), f);
}

void test02() {
    int i=3;
    double d=3.14;
    auto f = [i,&d](const int &no) -> int {
        cout<<"i="<<i<<endl;        //值捕获无法修改值
        cout<<"d="<<d++<<endl;      //引用捕获可以修改值
       cout<<"亲爱的"<<no<<"号:我是cmx\n";
        return 0;
    };
    auto f1 = [=](const int &no) -> int {
        cout<<"i="<<i<<endl;
        cout<<"d="<<d<<endl;
        cout<<"亲爱的"<<no<<"号:我是cmx\n";
        return 0;
    };
    auto f2 = [&](const int &no) -> int {
        cout<<"i="<<i++<<endl;
        cout<<"d="<<d++<<endl;
        cout<<"亲爱的"<<no<<"号:我是cmx\n";
        return 0;
    };
    auto f3 = [=,&d](const int &no) -> int {
        cout<<"i="<<i<<endl;
        cout<<"d="<<d++<<endl;
        cout<<"亲爱的"<<no<<"号:我是cmx\n";
        return 0;
    };
    auto f4 = [&,d](const int &no) -> int {
        cout<<"i="<<i++<<endl;
        cout<<"d="<<d<<endl;
        cout<<"亲爱的"<<no<<"号:我是cmx\n";
        return 0;
    };
    f(8);   //像使用普通函数一样使用lambda函数
}

int main() {
    //test01();
    test02();
}