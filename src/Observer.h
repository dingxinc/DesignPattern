#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <utility>
#include <map>

class NonCopyable {
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;                // 删除拷贝构造
    NonCopyable& operator = (const NonCopyable&) = delete;   // 删除拷贝赋值
};

template <typename Func>
class Observer : NonCopyable {
private:
    // 保存观察者，并分配观察者编号
    template <typename F>
    int Assgin(F&& f) {
        int k = m_observerId++;
        m_observers.emplace(k, std::forward<F>(f));
        return k;
    }

    int m_observerId = 0;                  // 观察者编号
    std::map<int, Func> m_observers;       // 观察者列表

public:
    // 添加观察者，支持右值引用
    int Connect(Func&& f) {
        return Assgin(f);
    }

    // 添加观察者
    int Connect(const Func& f) {
        return Assgin(f);
    }

    // 移除观察者
    void Disconnect(int key) {
        m_observers.erase(key);
    }

    // 通知所有观察者
    template <typename... Args>
    void Notify(Args&&... args) {           // 万能引用
        for (auto& it : m_observers) {
            it.second(std::forward<Args>(args)...);  // 完美转发，参数解包
        }
    }
};

#endif /* __OBSERVER_H__ */