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
    static const AccT zero = 0;
};
template<>
struct AccumT<int> {
    using AccT = int;
    static const AccT zero = 0;
};

#include<iostream>
struct BigInt {
    BigInt(int val) {
        val_ = val;
    }
    int val_;
    inline static const int zero = 0;

    friend std::ostream& operator<<(std::ostream& __cout, const BigInt& ins) {
        __cout << ins.val_ << std::endl;
    }
    BigInt& operator+=(const BigInt& src) {
        val_ += src.val_;
        return *this;
    }
};
template<>
struct AccumT<BigInt> {
    using AccT = BigInt;
    inline static const AccT zero = BigInt(0);
};


template<typename T>
T accum(T* begin, T* end) {
    T* ptr = begin;
    using AccT = typename AccumT<T>::AccT;
    // T rlt{};
    // AccT rlt{};
    AccT rlt = AccumT<T>::zero;
    while (ptr != end) {
        rlt += *ptr;
        ptr++;
    }
    return rlt;
}

/*Stack类相关*/
#include <vector>
#include <cassert>

// template<typename T>
template<typename T, template<typename ElemType> class Cont = std::vector>
class Stack {
  private:
    // std::vector<T> elems;      // elements
    Cont<T> elems;
  public:
    void push(T const& elem);  // push element
    void pop();                // pop element
    T const& top() const;      // return top element
    bool empty() const {       // return whether the stack is empty
        return elems.empty();
    }
    template<typename T2>
    Stack<T>& operator=(const Stack<T2> opstack) {
        Stack<T2> tmp(opstack);
        elems.clear();
        while (!(tmp.empty())) {
            push(tmp.top());
            tmp.pop();
        }
        return *this;
    }
};

/*判断两个类别类型是否相同*/
template<typename T1, typename T2>
struct issametype {
    const static bool value = false;
};
template<typename T>
struct issametype<T, T> {
    const static bool value = true;
};
/*判断两个类别类型是否相同*/
// template<typename T>
template<typename T, template<typename ElemType> class Cont> 
// void Stack<T>::push (T const& elem)
void Stack<T, Cont>::push (T const& elem)
{
    elems.push_back(elem);     // append copy of passed elem
}

// template<typename T>
// void Stack<T>::pop ()
template<typename T, template<typename ElemType> class Cont> 
// void Stack<T>::push (T const& elem)
void Stack<T, Cont>::pop()
{
    assert(!elems.empty());
    elems.pop_back();          // remove last element
}

// template<typename T>
template<typename T, template<typename ElemType> class Cont> 
// T const& Stack<T>::top () const
T const& Stack<T, Cont>::top () const
{
    assert(!elems.empty());
    return elems.back();       // return copy of last element
}
/*Stack类相关end*/
/*序列求和*/
/*My tuple*/

/*测试空类相关*/
class Empty {
};
class Empty1: public Empty {

};
class Empty2: public Empty1 {
};
/*测试空类相关 end*/

/*打印任意容器：函数模板*/
template<typename Container>
std::ostream& printcontainer(const Container ct, std::ostream& _cout = std::cout) {
    auto itr = ct.begin();
    while (itr != ct.end()) {
        _cout << *itr << std::endl;
        itr++;
    }
    return _cout;
}
/*打印任意容器：函数模板end*/

/*迭代器向前移动的不同特化版本*/
#include <iterator>
template<typename Iterator, typename Distance>
void IteratorAdvance(Iterator itr, Distance n) {
    IteratorAdvanceImpl(itr, n, typename std::iterator_traits<Iterator>::iterator_category());
}

template<typename Iterator, typename Distance>
void IteratorAdvanceImpl(Iterator iter, Distance n, std::input_iterator_tag) {
    while (n > 0) {
        iter++;
        n--;
    }
}

template<typename Iterator, typename Distance>
void IteratorAdvanceImpl(Iterator iter, Distance n, std::random_access_iterator_tag) {
    iter += n;
}

// static int a = 100;
// constexpr int addtest(int val) {
//     return a++ + val;
// }

/*输入是类型，输出是*/

/*实现计数器，记录这个类的实例目前现存多少个*/
template<typename T>
class Counter {
    public:
        inline static int count = 0;
    Counter() {
        count++;
    }
    Counter(const Counter&) {
        count++;
    }
    Counter(Counter&&) {
        count++;
    }
    ~Counter() {
        count--;
    }
};
/*提供的测试类*/
class MyTestCls: public Counter<MyTestCls> {

};

/*实现简单的std::function*/
#include <algorithm>
template<typename R, typename... Args>
class FunctorBridge
{
  public:
    virtual ~FunctorBridge() {
    }
    virtual FunctorBridge* clone() const = 0;
    virtual R invoke(Args... args) const = 0;
};

/*FunctorBridge的偏特化*/
template<typename Functor, typename R, typename... Args>
class SpecificFunctorBridge : public FunctorBridge<R, Args...> {
  Functor functor;

 public:
  template<typename FunctorFwd>
  SpecificFunctorBridge(FunctorFwd&& functor)
    : functor(std::forward<FunctorFwd>(functor)) {
  }
  virtual SpecificFunctorBridge* clone() const override {
    return new SpecificFunctorBridge(functor);
  }
  virtual R invoke(Args... args) const override {
    return functor(std::forward<Args>(args)...);
  }
};
/*FunctorBridge的偏特化 end*/

// primary template:
template<typename Signature> 
class FunctionPtr;

// partial specialization:
template<typename R, typename... Args> 
class FunctionPtr<R(Args...)>
{
 private:
  FunctorBridge<R, Args...>* bridge;
 public:
  // constructors:
    FunctionPtr() : bridge(nullptr) {
    }
    FunctionPtr(const FunctionPtr& other) {
        bridge = other.bridge->clone();
    }
    FunctionPtr(FunctionPtr& other) : FunctionPtr(static_cast<const FunctionPtr&>(other){
    }
    FunctionPtr(const FunctionPtr&& other) {
        bridge = other.bridge;
        other.bridge = nullptr;
    }

    /*拷贝赋值：写的不好，看下面的！！！*/
    FunctionPtr& operator=(FunctionPtr&& other) {
        if (nullptr != bridge) {
            delete bridge;
        }
        bridge = other.bridge;
        other.bridge = nullptr;
        return *this;

    }
    FunctionPtr& operator=(FunctionPtr& other) {
            FunctionPtr tmp(other);
        swap(*this, tmp);
        return *this;
    }
    friend void swap(FunctionPtr& op1, FunctionPtr& op2) {
        std::swap(op1.bridge, op2.bridge);
    }











//   FunctionPtr() : bridge(nullptr) {
//   }
//   FunctionPtr(FunctionPtr const& other);    // see functionptr-cpinv.hpp
//   FunctionPtr(FunctionPtr& other) 
//     : FunctionPtr(static_cast<FunctionPtr const&>(other)) { 
//   }
//   FunctionPtr(FunctionPtr&& other) : bridge(other.bridge) {
//     other.bridge = nullptr;
//   }
//   // construction from arbitrary function objects:
//   // template<typename F> FunctionPtr(F&& f);  // see functionptr-init.hpp
// template<typename F> FunctionPtr(F&& f): bridge(nullptr)  {  // see functionptr-init.hpp
//     using Functor = std::decay_t<F>;
//     using Bridge = SpecificFunctorBridge<Functor, R, Args...>;
//     // bridge = new Bridge(f); // 写的也不对！！
//     // bridge = new SpecificFunctorBridge<F, R, Args...>(f);  // 这么写是不对的，不知道f是否是引用类型的，
// }
//   // assignment operators:
//   FunctionPtr& operator=(FunctionPtr const& other) {
//     FunctionPtr tmp(other);
//     swap(*this, tmp);
//     return *this;
//   }
//   FunctionPtr& operator=(FunctionPtr&& other) {
//     delete bridge;
//     bridge = other.bridge;
//     other.bridge = nullptr;
//     return *this;
//   }
//   // construction and assignment from arbitrary function objects:
//   template<typename F> FunctionPtr& operator=(F&& f) {
//     FunctionPtr tmp(std::forward<F>(f));
//     swap(*this, tmp);
//     return *this;
//   }

//   // destructor:
//   ~FunctionPtr() { 
//     delete bridge; 
//   }

//   friend void swap(FunctionPtr& fp1, FunctionPtr& fp2) {
//     std::swap(fp1.bridge, fp2.bridge);
//   }
//   explicit operator bool() const {
//     return bridge == nullptr;
//   }

//   // invocation:
//   R operator()(Args... args) const;         // see functionptr-cpinv.hpp
};

/*简单的std::function end*/
int main() {
    /*测试accm*/
//     int a[] = {1, 2, 3, 4, 5};
//     std::cout << accum(a, a + (sizeof(a) / sizeof(a[0]))) / (sizeof(a) / sizeof(a[0])) << std::endl;
//     char st[] = "templates";
//     std::cout << accum(st, st + sizeof(st) - 1) << std::endl; // / (sizeof(st) - 1) << std::endl;
//     BigInt arr[] = {BigInt(1), BigInt(2), BigInt(3), BigInt(4), BigInt(5)};
//     std::cout << accum(arr, arr + 5) << std::endl;
//     // std::cout << (-49) / 9;
//     /*测试accm end*/
//     Stack<int>         intStack;       // stack of ints
//     Stack<std::string> stringStack;    // stack of strings
  
//     // manipulate int stack
//     intStack.push(7);
//     std::cout << intStack.top() << '\n';
  
//     // manipulate string stack
//     stringStack.push("hello");
//     std::cout << stringStack.top() << '\n';
//     stringStack.pop();
//     Stack<double> doublestack;
//     doublestack.push(2.5);
//     intStack = doublestack;
//     std::cout << intStack.top() << '\n';
//     // intStack = stringStack;
//     /*测试issametype*/
//     std::cout << issametype<int, int>::value << '\n';
//     /*测试issametype*/
// /*My tuple*/
//     // Check(Func);
//     // Check(Func);//error
//     // Check(*Func);//error
//     // std::vector<double> vec;
//     // printele_type(vec);
    
//     /*测试空类的大小*/
//     std::cout << sizeof(Empty) << std::endl;
//     std::cout << sizeof(Empty1) << std::endl;
//     std::cout << sizeof(Empty2) << std::endl;
//     /*测试空类的大小结束*/

//     /*打印任意的stl*/
//     std::vector<int> vec_int{1, 2, 3};
//     std::cout << "print vec" << std::endl;
//     printcontainer(vec_int);
    /*打印任意的stl结束*/
   
   /*测试，计数器的使用*/
   {
        MyTestCls a;
        MyTestCls b;
        std::cout << MyTestCls::count << std::endl;
   } 
   std::cout << MyTestCls::count << std::endl; 
      /*测试，计数器的使用*/
}

