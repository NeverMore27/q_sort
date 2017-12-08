#include <future>
#include <lomuto_partition.hpp>
#include <thread_safe_stack.hpp>
#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <ctime> 
#include <memory>
#include <vector>
#include <iterator>
#include <algorithm>

template <typename T>
class stack
{
public:
	stack() /*noexcept*/ noexcept;
	~stack()  /*noexcept*/ noexcept;
	stack(const stack<T>&) /*strong*/;
	stack<T>& operator =(const stack<T>&) noexcept;
	void push(T const &) /*strong*/;
	template <typename U>
	void emp(U && value);
	auto pop()->std::shared_ptr<T>;
	size_t size() const /*noexcept*/ noexcept;
	bool empty() const /*noexcept*/ noexcept;
private:
	mutable std::mutex mutex_;
	T * array_;
	size_t array_size_;
	size_t count_;
	void swap(stack<T>&) /*noexcept*/ noexcept;
};

template <typename T>
void stack<T>::swap(stack<T>& object) noexcept
{
	std::lock(mutex_, object.mutex_);
	std::swap(object.array_size_, array_size_);
	std::swap(count_, object.count_);
	std::swap(object.array_, array_);
	mutex_.unlock();
	object.mutex_.unlock();
}

template <typename T>
stack<T>::stack() noexcept: count_{ 0 }, array_size_{ 0 }, array_{ nullptr }
{
}

template <typename T>
stack<T>::~stack() noexcept
{
	delete[] array_;
}

template <typename T>
stack<T>::stack(const stack& object)
{
	std::lock_guard<std::mutex> lock(object.mutex_);
	array_size_ = object.array_size_;
	count_ = object.count_;
	array_ = new T[count_];
	try
	{
		std::copy(object.array_, object.array_ + count_, array_);
	}
	catch (...)
	{
		delete[] array_;
		throw;
	}
}

template <typename T>
stack<T>& stack<T>:: operator =(const stack<T>&object) noexcept
{
	if (this != &object)
	{
		stack{ object }.swap(*this);
	}
	return *this;
}

template <typename T>
void stack<T>::push(T const &value)
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (array_size_ == count_)
	{
		size_t array_size = array_size_ == 0 ? 1 : array_size_ * 2;
		T *ptr = new T[array_size];
		try
		{
			std::copy(array_, array_ + count_, ptr);
		}
		catch (...)
		{
			delete[] ptr;
			throw;
		}

		array_size_ = array_size;
		delete[] array_;
		array_ = ptr;
	}

	array_[count_] = value;
	++count_;
}

template <typename T>
template <typename U>
void stack<T>::emp(U &&value)
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (array_size_ == count_)
	{
		size_t array_size = array_size_ == 0 ? 1 : array_size_ * 2;
		T *ptr = new T[array_size];
		try
		{
			std::copy(array_, array_ + count_, ptr);
		}
		catch (...)
		{
			delete[] ptr;
			throw;
		}

		array_size_ = array_size;
		delete[] array_;
		array_ = ptr;
	}

	array_[count_] = std::move(value);
	++count_;
}
template <typename T>
auto stack<T>::pop() -> std::shared_ptr<T>
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (count_ == 0) return nullptr;
	auto ar = std::make_shared<T>(array_[count_ - 1]);
	--count_;
	return ar;
}

template <typename T>
size_t stack<T>::size() const noexcept
{
	std::lock_guard<std::mutex> lock(mutex_);

	return count_;
}

template <typename T>
bool stack<T>::empty() const noexcept
{
	std::lock_guard<std::mutex> lock(mutex_);
	return count_ == 0;
}
