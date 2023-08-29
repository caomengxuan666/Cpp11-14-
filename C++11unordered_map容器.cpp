//
// Created by Administrator on 2023/7/15.
//
/*
 * 构造函数
 * unordered_map(); //创建一个空的容器
 * unordered_map(size_t bucket);    //创建一个空容器并且指定桶的个数
 * unordered_map(initializer_list<pair<K,V>>il); //使用统一初始化列表
 * unordered_map(initializer_list<pair<K,V>il,size_t bucket);   //使用统一初始化列表
 * unordered_map(iterator first,iterator last); //用迭代器创建容器
 * unordered_map(const unordered_map<K,V>&m);   //拷贝构造函数
 * unordered_map(unordered_map<K,V>&&m);    //移动构造函数(C++11标准)
 *
 * 特性操作
 * 1.size_t size()const   //返回容器中元素的个数
 * 2.bool empty()const    //判断容器是否为空
 * 3.void clear();    //清空容器
 * 4.size_t max_bucket_count()    //返回容器底层最多使用多少桶
 * 5.size_t bucket_count()    //返回容器桶的数量，空容器中有8个桶
 * 6.size_t bucket_size(size_t n) //返回第n个桶中元素的个数,load_factor()=size()/bucket_count()
 * 7.size_t bucket(K &key)    //返回值为key的元素的对应的桶的编号
 * 8.float load_factor()  //返回容器当前的最大装填因子，达到该值后，容器将扩容，缺省为1
 * 9.void max_load_factor(float z)  //设置容器的最大装填因子
 * 10.iterator begin(size_t n); //返回第n个桶中的第一个元素的迭代器
 * 11.iterator end(size_t n);   //返回第n个桶中最后一个元素尾后的迭代器
 * 12.void reserve(size_t n);   //将容器设置为至少n个桶，创建容器后设置
 * 13.void rehash(size_t n);    //将桶的数量调整为>=n，如果n大于当前容器的桶数，将会自动扩容桶的数量
 *
 * 元素操作
 * V &operator[](K key); //用给定的key访问元素
 * const V &operator[](K key)const   //用给定的key访问元素，只读
 * V &at(K key);    //用给定的key访问元素
 * const V &at(K key)const  //用给定的key访问元素，只读
 *
 * 注意
 * 1.[]运算符：如果指定键不存在，会向容器中添加新的键值对，如果指定键不存在，则读取或者修改容器中指定键的值
 * 2.at成员函数如果指定件不存在是不会添加新的键值对的，会抛出out_of_range
 *
 * 赋值操作
 * 给已经存在的容器赋值，将覆盖容器中的原有内容
 * unordered_map<K,V> &operator(const unordered_map<K,V>&m);    //把容器m赋值给当前容器
 * unordered_mmap<K,V> &operator=(initializer_list<pair<K,V>>il);   //用统一初始化列表给容器赋值
 *
 * 交换操作
 * void swap(unordered_map<K,V>&m); //把当前容器与m交换
 * 交换的是树的根节点
 *
 * 比较操作
 * bool operator==const(unordered_map<K,V>&m)const;
 * bool operator!=(const unordered_map<K,V>m)const;
 *
 * 查找操作
 * 1.查找键值为key的键值对
 * 在map容器中查找键值为key的键值对，如果成功找到，则返回指向该键值对的迭代器，失败返回end():
 * iterator find(const K&key)
 * const_iterator find(const K&key)const //只读
 * 2.统计键值对的个数
 * 统计map容器中键值为Key的键值对的个数
 * size_t count(const K&key)const;
 *
 * 插入和删除
 * 1.void insert(initializer_list<pair<K,V>il)    //用统一初始化列表在容器内插入多个元素
 * 2.pair<iterator,bool> insert(const pair<K,V>&value)    //在容器中插入一个元素,返回值pair
 * 3.void insert(iterator first,iterator last)    //用迭代器插入一个区间的元素
 * 4.pair<iterator,bool> emplace(...) //将创建新键值对所需的数据作为参数直接传入，map容器将直接构造元素，返回值pair,first是已经插入元素的迭代器,second是插入结果
 * 5.iterator emplace_hint(const _iterator pos,...) //功能与第四个函数相同，第一个参数提示插入位置，，该参数只有参考意义
 * 6.size_t erase(const K&key)  //从容器中删除指定key的元素，返回已删除的元素个数
 * 7.iterator erase(iterator pos)   //用迭代器删除元素，返回下一个有效的迭代器
 * 8.iterator erase(iterator first,iterator last)    //用迭代器删除一个区间的元素，返回下一个有效的迭代器
 *
 */
#include "iostream"
#include "unordered_map"

using namespace std;

template<class K, class V>
using umap = std::unordered_map<K, V>; //相当于简化名字了

void test01() {
    //1.空容器
    umap<int, string> m1;

    //2.使用统一的初始化列表
    umap<int, string> m2({{8, "cmx"},
                          {2, "lwb"},
                          {4, "hhw"}});
    for (auto &val: m2) {
        cout << val.first << " " << val.second << " ";
    }
    cout << endl;

    //3.拷贝构造函数
    umap<int, string> m3 = m2;
    for (auto &val: m3) {
        cout << val.first << " " << val.second << " ";
    }
    cout << endl;

    //4.用迭代器创建map容器
    auto first = m3.begin();
    first++;
    auto last = m3.end();
    //last--;
    umap<int, string> m4(first, last);
    for (auto &val: m4) {
        cout << val.first << "," << val.second << " ";
    }
    cout << endl;

    //5.移动构造函数(C++11标准)

}

void test02() {
    umap<int, string> m;
    cout << m.bucket_count() << endl;   //空容器有8个桶
    size_t itmp = m.bucket_count();
    for (int i = 0; i < 200000; i++) {  //插入容器中插入若干记录
        char name[50];
        sprintf_s(name, "西施%d", i);
        m.emplace(i, name);//在指定位置之前添加一个新的元素
        if (itmp != m.bucket_count()) {//如果桶自动扩展，显示日志
            cout << m.bucket_count() << endl;
            itmp = m.bucket_count();
        }
    }
}

void test03(){
    umap<int, string> m;

    cout<<"最大装填因子"<<m.max_load_factor()<<endl;
    m.insert({{1,"cmx"},{2,"cyz"},{3,"hhw"},{4,"lwb"}});
    cout<<"当前桶数"<<m.bucket_count()<<endl;
    cout<<"当前装填因子"<<m.load_factor()<<endl;

    m.insert({{5,"cjj"},{6,"cr"},{7,"cyz"},{8,"cx"}});
    cout<<"当前桶数"<<m.bucket_count()<<endl;
    cout<<"当前装填因子"<<m.load_factor()<<endl;

    m.emplace(9,"chy");
    cout<<"当前桶数"<<m.bucket_count()<<endl;
    cout<<"当前装填因子"<<m.load_factor()<<endl;

}
int main() {
    //test01();
    //test02();
    test03();
}