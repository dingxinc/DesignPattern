#include <iostream>
#include <functional>
#include "../src/Observer.h"

struct T {
    int a, b;
    void print(int a, int b) {
        std::cout << a << ", " << b << std::endl;
    }
};

void print(int a, int b) {
    std::cout << a << ", " << b << std::endl;
}

int main() {
    Observer<std::function<void(int, int)>> myobserver;
    auto key = myobserver.Connect(print);       // 以函数的方式注册观察者，这个函数被添加到 map 中了
    std::cout << key << "\n";

    T t;        // 结构体对象
    auto lambdaKey = myobserver.Connect([&t](int a, int b){
        t.a = a; t.b = b;
    });         // 以 lambda 方式注册观察者，也被添加到 map 中了，map中此时有两个元素
    std::cout << lambdaKey << "\n";
    // 以可调用对象包装器方式注册观察者
    std::function<void(int a, int b)> f = std::bind(&T::print, &t, std::placeholders::_1, std::placeholders::_2);  // 在函数调用时，将占位符替换为参数
    auto fkey = myobserver.Connect(f);   // map 中三个元素
    std::cout << fkey << "\n";
    int a = 1, b = 2;
    myobserver.Notify(a, b);     // 广播所有观察者
    myobserver.Disconnect(key);  // 移除观察者
    myobserver.Disconnect(lambdaKey);
    myobserver.Disconnect(fkey);
}