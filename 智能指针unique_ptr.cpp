//
// Created by Administrator on 2023/7/16.
//
/*
 * 智能指针的设计思路
 * 智能指针是类模板，在栈上创建智能指针对象
 * 把普通指针交给智能指针对象
 * 智能指针对象过期时，调用析构函数释放普通指针的内存
 *
 * 智能指针的类型
 * auto_ptr是C++98标准，C++17已经弃用
 * unique_ptr,shared_ptr,weak_ptr是C++11标准
 *
 * 智能指针unique_ptr
 * unique_ptr独享它指向的对象，也就是说，同时只有一个unique_ptr指向同一个对象，当这个unique_ptr被销毁时，指向的对象也随即被销毁
 *
 * 基本用法
 * 1.初始化
 * 方法一
 * unique_ptr<A>p0(new A("cmx"));  //分配内存并且初始化
 *
 * 方法二
 * unique_ptr<A>p0=make_unique<A>("cmx") //C++14标准
 *
 * 方法三（有些不安全）
 * A*p=new A("cmx");
 * unique_ptr<A>p0(p)   //用已经存在的地址初始化
 *
 * 使用方法
 * 1.智能指针重载了*和->操作符，可以像使用指针一样使用unique_ptr
 * 2.不支持普通的拷贝和赋值，已经用explict来禁用了这两个函数
 * 3.不要用同一个裸指针初始化多个unique_ptr
 * get()方法返回裸指针
 * 不要用unique_ptr管理不是new分配的内存
 *
 * 用于函数的参数
 * 传引用（不可以传值，因为unique_ptr没有拷贝构造函数）或者传裸指针（不推荐）
 *
 * unique_ptr不支持指针的运算如+ - ++ --
 *
 * 更多技巧
 *
 * 1.将一个unique_ptr赋给另一个时，如果源unique_ptr是一个临时右值，编译器允许这样做，如果源unique_ptr将存在一段时间，编译器将禁止这样做，一般用于函数的返回值
 *  unique_ptr<A>p0;
 *  p0=unique_ptr<A>(new A("cmx"));
 *
 *  2.用nullptr给unique_ptr赋值将释放对象，空的unique_ptr==nullptr
 *
 *  3.release()释放对指针的控制权，将unique_ptr置为空，返回裸指针(可以把unique_ptr传递给子函数，并且在子函数中释放对象)
 *
 *  4.std::move()可以转移对指针的控制权(可以把unique_ptr传递给子函数，并且在子函数中释放对象)
 *
 *  5.reset()释放对象
 *  p.reset();  //释放p对象指向的资源对象
 *  p.reset(nullptr);    //释放p对象指向的资源对象
 *  p.reset(new AA("bbb"));     //释放p指向的资源对象，同时指向新的对象
 *
 *  6.swap()交换两个unique_ptr的控制权
 *  void swap(unique<ptr<T>&_Right)
 *
 *  7.unique_ptr也可以像普通指针那样，当指向一个类继承体系的基类对象时，也具有多态性质，如同使用裸指针管理基类对象和派生类对象那样
 *
 *  8.unique_ptr不是绝对安全，如果程序中调用exit()退出，，全局的unique_ptr可以释放，但是局部的unique_ptr无法释放
 *
 *  9.unique_ptr提供了支持数组的具体化版本
 *  数组版本的unique_ptr重载了操作符[]，操作符[]返回的是引用，可以作为左值使用
 *  unique_ptr<int[]>parr1(new int[3]); //不指定初始值
 *  unique_ptr<int[]>parr1(new int[3]{33,22,11};    //指定初始值
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

class Hero {
public:
    int hp;
    int attack;

    virtual void skillQ() { cout << "英雄释放了Q技能" << endl; }

    virtual void skillW() { cout << "英雄释放了W技能" << endl; }

    virtual void skillE() { cout << "英雄释放了E技能" << endl; }

    virtual void skillR() { cout << "英雄释放了R技能" << endl; }
};

class Shen : public Hero {
    void skillQ() { cout << "慎释放了Q技能" << endl; }

    void skillW() { cout << "慎释放了W技能" << endl; }

    void skillE() { cout << "慎释放了E技能" << endl; }

    void skillR() { cout << "慎释放了R技能" << endl; }
};

class ZhaoXin : public Hero {
    void skillQ() { cout << "赵信释放了Q技能" << endl; }

    void skillW() { cout << "赵信释放了W技能" << endl; }

    void skillE() { cout << "赵信释放了E技能" << endl; }

    void skillR() { cout << "赵信释放了R技能" << endl; }
};

class Zed : public Hero {
    void skillQ() { cout << "劫释放了Q技能" << endl; }

    void skillW() { cout << "劫释放了W技能" << endl; }

    void skillE() { cout << "劫释放了E技能" << endl; }

    void skillR() { cout << "劫释放了R技能" << endl; }
};

unique_ptr<A> func() {
    unique_ptr<A> p(new A("lwb"));
    return p;
}

//函数func1()需要一个指针，但是不对这个指针负责
void func1(const A *a) {
    cout << a->m_Name << endl;
}

//函数func2()需要一个指针，并且会对这个指针负责
void func2(A *a) {
    cout << a->m_Name << endl;
    delete a;
}

//函数func3()需要一个unique_ptr,不会对这个unique_ptr负责
void func3(const unique_ptr<A> &a) {
    cout << a->m_Name << endl;
}

//函数func4()需要一个unique_ptr,对这个unique_ptr负责
void func4(unique_ptr<A> a) {
    cout << a->m_Name << endl;
}

void test01() {
    A *p = new A("cmx");
    unique_ptr<A> ptr1(p);
    cout << "m_Name=" << ptr1->m_Name << endl;
}

void test02() {//这种做法是错误的
    A *p = new A("cmx");
    unique_ptr<A> ptr1(p);
    unique_ptr<A> ptr2(p);
    unique_ptr<A> ptr3(p);
}

void test03() {
    unique_ptr<A> p1(new A("cmx"));
    unique_ptr<A> p2;
    //p2=pu1;   这是一个错误的写法
    p2 = unique_ptr<A>(new A("cyz")); //用匿名对象赋值
    cout << "调用func（）之前" << endl;
    p2 = func();
    cout << "调用func()之后" << endl;
}

void test04() {  //把nullptr赋值给智能指针会导致对象被释放
    unique_ptr<A> p(new A("cmx"));
    cout << "赋值之前" << endl;
    if (p != nullptr)cout << "p不为空" << endl;
    p = nullptr;
    cout << "赋值之后" << endl;
    if (p == nullptr)cout << "p为空" << endl;
}

void test05() {
    unique_ptr<A> p(new A("cmx"));
    cout << "函数调用开始" << endl;
    //func1(p.get());   //通过get返回一下原始指针，不会变为空指针
    //func2(p.release());//把原始指针交给了func2,失去了控制权之后自己就成了空指针
    //func3(p);     //最常见，传递一个引用，不会变为空指针
    //func4(move(p));   //传值而不是传引用，用move函数把对原始指针的控制权交给func4函数的形参，p变为空指针
    cout << "函数调用完成\n";
    if (p == nullptr)cout << "p是空指针" << endl;
}

void test06() {
    int id = 0;
    cout << "请选用英雄" << endl;
    cin >> id;

    //创建基类指针指向派生类对象,用基类指针调用派生类的
    unique_ptr<Hero> ptr;
    if (id == 1) {
        ptr = unique_ptr<Hero>(new Shen);
    } else if (id == 2) {
        ptr = unique_ptr<Hero>(new ZhaoXin);
    } else if (id == 3) {
        ptr = unique_ptr<Hero>(new Zed);
    }
    if (ptr != nullptr) {
        ptr->skillQ();
        ptr->skillW();
        ptr->skillE();
        ptr->skillR();
    }
}

void test07() {
    unique_ptr<A[]> pa(new A[2]);    //unique_ptr数组
    pa[0].m_Name = "cmx";
    cout << pa[0].m_Name << endl;
    pa[1].m_Name = "lwb";
    cout << pa[1].m_Name << endl;
}

int main() {
    //test01();
    //test02();
    //test03();
    //test04();
    //test05();
    //test06();
    test07();
}