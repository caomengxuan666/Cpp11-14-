//
// Created by Administrator on 2023/7/28.
//
/*
 * C++11提供了chrono模板库，实现了一系列时间相关的操作(时间长度、系统时间和计时器)
 *
 * 时间长度
 * duration模板类用表示一段时间(时间长度、时钟周期)
 * duration定义如下
 * template<class Rep,class Period=std::ratio<1,1>>
 * class duration{
 * ...
 * };
 * 为了方便使用，定义了一些常用的时间长度，比如:时，分，秒，毫秒，微秒，纳秒
 * 定义如下
 * using hours=duration<Rep,std::ratio<3600>>   //小时
 * using minutes=duration<Rep,std::ratio<60>>   //分钟
 * using seconds=duration<Rep>  //秒
 * using milliseconds=duration<Rep,std:milli>   //毫秒
 * using microseconds=duration<Rep,std:micro>   //微秒
 * using nanoseconds=duration<Rep,std::nano>    //纳秒
 * 注意
 * duration模板类重载了各种算术运算符，用于操作duration对象
 * duration模板类提供了count()方法，获取duration对象的值
 *
 * 系统时间
 * system_lock类支持了队系统时钟的访问，提供了三个静态成员函数
 * //返回当前时间的时间点
 * static std::chrono::time_point<std::chrono::system_lock>now()noexcept;
 * //将时间点time_point类型转换为std::time_t类型
 * static std::time_t to_time_t(const time_point&t)noexcept;
 * //将std::time_t类型转换为时间点time_point类型
 * static std::chrono::system_clock::time_point from_time_t(std::time_t t)noexcept;
 *
 * 计时器
 * steady_clock类相当于秒表，操作系统只要启动就会进行时间的累加，常用于耗时的统计(精确到纳秒)
 */
#include "iostream"
#include "chrono"
#include "iomanip"
#include "sstream"

using namespace std;

void test01() {
    using namespace std::chrono;
    hours t1(1);    //1小时
    minutes t2(60); //60分钟
    seconds t3(60 * 60);  //60*60秒
    milliseconds t4(60 * 60 * 1000);    //60*60*1000毫秒
    if (t1 == t2)cout << "t1==t2\n";
    if (t1 == t3)cout << "t1==t3\n";
    if (t1 == t4)cout << "t1==t4\n";

    //获取时钟周期的值，返回的是int整数
    cout << "t1=" << t1.count() << endl;
    cout << "t2=" << t2.count() << endl;
    cout << "t3=" << t3.count() << endl;
    cout << "t4=" << t4.count() << endl;
}

void test02() {
    using namespace chrono;
    //1.静态成员函数chrono::system_clock::now()用于获取系统时间（C++时间）
    auto now = system_clock::now();

    //2.静态成员函数chrono::system_clock::to_time_t()把系统时间转换成time_t(UTC时间)
    auto t_now = system_clock::to_time_t(now);

    //可以使用时间偏移
    //t_now=t_now+24*60*60  //把当前时间加1天

    //3.std::localtime()函数把time_t转换成本地时间(北京时间)
    //localtime()不是线程安全的，VS用localtime_s代替，Linux用localtime_r代替
    auto tm_now = std::localtime(&t_now);

    //4.格式化输出本地时间
    cout << put_time(tm_now, "%Y-%m-%d %H:%M:%S") << endl;
    cout << put_time(tm_now, "%Y-%m-%d") << endl;
    cout << put_time(tm_now, "%H:%M:%S") << endl;
    cout << put_time(tm_now, "%Y%m%d%H%M%S") << endl;

    stringstream ss;    //创建stringstream对象ss
    ss << put_time(tm_now, "%Y-%m-%d %H:%M:%S");   //把时间输出到对象ss中
    string timestr = ss.str();
    cout << timestr << endl;
}

void test03() {
    //静态成员函数chrono::steady_clock::now()获取开始的时间点
    using namespace chrono;
    auto start = steady_clock::now();

    //执行代码段
    cout << "计时开始\n";
    for (int i = 0; i < 1000000; i++) {
    }
    cout << "计时完成\n";

    //静态成员函数chrono::steady_clock()::now()获取结束的时间点
    auto end = steady_clock::now();

    //计算消耗的时间
    auto dt=end-start;
    cout<<"耗时:"<<dt.count()<<"纳秒（"<<(double)dt.count()/(1000*1000*1000)<<"秒)";
}

int main() {
    //test01();
    //test02();
    test03();
}