#ifndef __VISITOR_H__
#define __VISITOR_H__

template <typename... Types>
struct Visitor;

template <typename T, typename... Types>
struct Visitor<T, Types...> : Visitor<Types...> {
    // 通过 using 避免隐藏基类的 Visit 同名方法
    using Visitor<Types...>::Visit;
    virtual void Visit(const T&) = 0;
};

template <typename T>
struct Visitor<T> {
    virtual void Visit(const T&) = 0;
};

#endif /* __VISITOR_H_ */