#include <iostream>
#include <string>
#include "../src/Singleton.cc"

struct A {
	A(const std::string&) { std::cout << "lvalue" << std::endl; }
	A(std::string&&) { std::cout << "rvalue" << std::endl; }
};

struct B {
	B(const std::string&) { std::cout << "lvalue" << std::endl; }
	B(std::string&&) { std::cout << "rvalue" << std::endl; }
};

struct C {
	C(int x, double y) {}
	void test() { std::cout << "test" << std::endl; }
};

int main() {
	std::string str = "bb";
	// 创建 A 类型的单例
	Singleton<A>::Instance(str);
	// 创建 B 类型的单例，临时变量 str 被 move 后变为右值，根据移动语义避免拷贝
	Singleton<B>::Instance(std::move(str));
	// 创建 C 类型的单例，含有两个参数
	Singleton<C>::Instance(1, 2.1);
	// 通过单例对象调用成员函数
	Singleton<C>::GetInstance()->test();

	// 销毁单例对象
	Singleton<A>::DestroyInstance();
	Singleton<B>::DestroyInstance();
	Singleton<C>::DestroyInstance();
}