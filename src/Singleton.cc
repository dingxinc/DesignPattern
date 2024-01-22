#include <utility>
#include <stdexcept>

template <typename T>
class Singleton {
private:
	static T* m_pInstance;

private:
	Singleton(void);
	virtual ~Singleton();
	Singleton(const Singleton&);
	Singleton& operator = (const Singleton&);

public:
	template <typename... Arg>
	static T* Instance(Arg... arg) {
		if (m_pInstance == nullptr) {
			m_pInstance = new T(std::forward<Arg>(arg)...);
		}
		return m_pInstance;
	}

	// 获取单例
	static T* GetInstance() {
		if (m_pInstance == nullptr) {
			throw std::logic_error("the instance is not init, please initialize the instance first");
		}
		return m_pInstance;
	}

	// 销毁单例
	static void DestroyInstance() {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
};

template <class T> T* Singleton<T>::m_pInstance = nullptr;