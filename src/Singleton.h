#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <utility>
#include <stdexcept>

template <typename T>
class Singleton {
private:
	static T* m_pInstance;

private:
	Singleton(void) = default;
	virtual ~Singleton();
	Singleton(const Singleton&);
	Singleton& operator = (const Singleton&);

public:
	template <typename... Args>
	static T* Instance(Args... arg) {
		if (m_pInstance == nullptr) {
			m_pInstance = new T(std::forward<Args>(arg)...);
		}
		return m_pInstance;
	}

	// 获取单例
	static T* GetInstance() {
		if (m_pInstance == nullptr) {
			throw std::logic_error("the instance is not init, please initialize the instance first");
		}
        // 饿汉模式，访问单例模式的时候，单例已经被创建出来了
		return m_pInstance;
	}

	// 销毁单例
	static void DestroyInstance() {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
};

template <class T> T* Singleton<T>::m_pInstance = nullptr;

#endif /* __SINGLETON_H__ */