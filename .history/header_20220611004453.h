#include <iostream>
#include <typeinfo>
template <typename T>
void print_typeof(const T&) {
    std::cout << typeid(T).name << std::endl;
}