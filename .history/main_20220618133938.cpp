/* 基于智能指针实现双向链表 */
#include <cstdio>
#include <memory>
#include <cstring>
// struct Node {
//     // 这两个指针会造成什么问题？请修复
//     std::shared_ptr<Node> next;
//     std::shared_ptr<Node> prev;
//     // 如果能改成 unique_ptr 就更好了!

//     int value;

//     // 这个构造函数有什么可以改进的？
//     Node(int val) {
//         value = val;
//     }

//     void insert(int val) {
//         auto node = std::make_shared<Node>(val);
//         node->next = next;
//         node->prev = prev;
//         if (prev)
//             prev->next = node;
//         if (next)
//             next->prev = node;
//     }

//     void erase() {
//         if (prev)
//             prev->next = next;
//         if (next)
//             next->prev = prev;
//     }

//     ~Node() {
//         printf("~Node()\n");   // 应输出多少次？为什么少了？
//         /*这里的主要问题是说，下面的b = {}和 a= {}，相应的节点应该被回收，但是似乎没有正确回收？*/
//     }
// };

// struct List {
//     std::shared_ptr<Node> head;

//     List() = default;

//     List(List const &other) {
//         printf("List 被拷贝！\n");
//         head = other.head;  // 这是浅拷贝！
//         // 请实现拷贝构造函数为 **深拷贝**
//         // memcpy(head, other.head, sizeof(head));
//     }

//     List &operator=(List const &) = delete;  // 为什么删除拷贝赋值函数也不出错？

//     List(List &&) = default;
//     List &operator=(List &&) = default;

//     Node *front() const {
//         return head.get();
//     }

//     int pop_front() {
//         int ret = head->value;
//         head = head->next;
//         return ret;
//     }

//     void push_front(int value) {
//         auto node = std::make_shared<Node>(value);
//         node->next = head;
//         if (head)
//             head->prev = node;
//         head = node;
//     }

//     Node *at(size_t index) const {
//         auto curr = front();
//         for (size_t i = 0; i < index; i++) {
//             curr = curr->next.get();
//         }
//         return curr;
//     }
// };

// // void print(List lst) {  // 有什么值得改进的？
//     void print(const List& lst) {  // 打印时不应该构造新的对象
//     printf("[");
//     for (auto curr = lst.front(); curr; curr = curr->next.get()) {
//         printf(" %d", curr->value);
//     }
//     printf(" ]\n");
// }

// int main() {
//     // List a;

//     // a.push_front(7);
//     // a.push_front(5);
//     // a.push_front(8);
//     // a.push_front(2);
//     // a.push_front(9);
//     // a.push_front(4);
//     // a.push_front(1);

//     // print(a);   // [ 1 4 9 2 8 5 7 ]

//     // a.at(2)->erase();

//     // print(a);   // [ 1 4 2 8 5 7 ]

//     // List b = a;

//     // a.at(3)->erase();

//     // print(a);   // [ 1 4 2 5 7 ]
//     // print(b);   // [ 1 4 2 8 5 7 ]

//     // b = {};
//     // a = {};

//     // return 0;
// }
#include <iostream>
class X{

};
template <typename T>
void g(T&& t) {
    f(std::forward<T>(t));
}
void f(X&) {
    std::cout << "f for X&" << std::endl;
}
void f(const X&) {
    std::cout << "f for const X&" << std::endl;
}
void f(const X&&) {
    std::cout << "f for const X&&" << std::endl;
}
#include "header.h"
#include <type_traits>
class Person {
    std::string name;
    public:
        Person(const Person& src):name(src.name){
        }
        Person(Person&& src):name(std::move(src.name)) {
        }
        template<typename STR, typename = std::enable_if_t<std::is_convertible<STR, std::string>::value>>
        Person(STR&& str) {
            name = std::forward<STR>(str);
            std::cout << "use forward" << std::endl;
        }
};
/*假设传递一个容器，如何获取容器的元素类型*/
#include <vector>
template <typename T>
class Element;
template <typename T>
class Element<std::vector<T>> {
    public:
    using TYPE = T;
};
template <typename T>
void printele_type(const T& contnainter) {
    std::cout << typeid(typename Element<T>::TYPE).name() << std::endl;
}
/**/
// int main() {
//     // X x_1;
//     // g(x_1);
//     // const X x;
//     // g(x);
//     // g(std::move(x));
//     // g(std::move(x_1));
//     // 	std::cout << std::boolalpha;

// 	// std::cout << "is_const:" << std::endl;
// 	// std::cout << "int: " << std::is_const<int>::value << std::endl;
// 	// std::cout << "const int: " << std::is_const<const int>::value << std::endl;
// 	// std::cout << "const int&: " << std::is_const<const int&>::value << std::endl;
// 	// std::cout << "cont int* " << std::is_const<const int*>::value << std::endl;
// 	// std::cout << "int * const:" << std::is_const<int* const>::value << std::endl;
//     // double d = 3.0;
//     // print_typeof(d);
//     const std::string s("hel");
//     Person p1(s);
//     Person p2("hell");
//     Person p3(p1);
//     return 0;
// }

template<typename T>
void Check(const T&)
{
    // static_assert(std::is_same_v<T,void ()(void)>, "Not func pointer");
}

void Func(){}

/*My tuple*/
template<typename... Args>
class Mytuple;

template<typename Head, typename... Tails>
class Mytuple<Head, Tails...> {
    private:
        Head head_;
        Mytuple<Tails...> Tails_;
    public:
        Head& GetHead() {
            return head_;
        }
};
template<>
class Mytuple<> {

};

// template<unsigned int N>

/*序列求和*/
template<typename T>
struct AccumT;
template<>
struct AccumT<char> {
    using AccT = int;
};
template<>
struct AccumT<int> {
    using AccT = int;
};

struct BigInt {
};

template<typename T>
T accum(T* begin, T* end) {
    T* ptr = begin;
    using AccT = typename AccumT<T>::AccT;
    // T rlt{};
    AccT rlt{};
    while (ptr != end) {
        rlt += *ptr;
        ptr++;
    }
    return rlt;
}

/*序列求和*/
/*My tuple*/
int main() {
    int a[] = {1, 2, 3, 4, 5};
    std::cout << accum(a, a + (sizeof(a) / sizeof(a[0]))) / (sizeof(a) / sizeof(a[0])) << std::endl;
    char st[] = "templates";
    std::cout << accum(st, st + sizeof(st) - 1); // / (sizeof(st) - 1) << std::endl;
    // std::cout << (-49) / 9;
/*My tuple*/
    // Check(Func);
    // Check(Func);//error
    // Check(*Func);//error
    // std::vector<double> vec;
    // printele_type(vec);
}

