#include <iostream>
#include "../src/Visitor.h"

struct A;
struct B;

struct Base {
    // 定义通用的访问者类型，它可以访问 A 和 B
    typedef Visitor<A, B> MyVisitor;
    virtual void Accept(MyVisitor&) = 0;
};

struct A : Base {
    double val;
    void Accept(Base::MyVisitor& v) {
        v.Visit(*this);
    }
};

struct B : Base {
    int val;
    void Accept(Base::MyVisitor& v) {
        v.Visit(*this);
    }
};

struct PrintVisitor : Base::MyVisitor {
    void Visit(const A& a) {
        std::cout << "from A : " << a.val << std::endl;
    }
    void Visit(const B& b) {
        std::cout << "from B : " << b.val << std::endl;
    }
};

void TestVisitor() {
    PrintVisitor vis;
    A a;
    a.val = 8.79;
    B b;
    b.val = 8;
    Base* base = &a;
    base->Accept(vis);
    base = &b;
    base->Accept(vis);
}

int main() {
    TestVisitor();
    return 0;
}