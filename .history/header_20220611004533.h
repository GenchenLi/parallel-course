#include <iostream>
#include <typeinfo>
template <typename T>
void print_typeof(const T& t) {
    std::cout << typeid(t).name << std::endl;
}