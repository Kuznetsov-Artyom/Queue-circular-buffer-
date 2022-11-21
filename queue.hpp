#ifndef QUEUE_HPP
#define QUEUE_HPP


#include <iostream>
#include <stdexcept>
#include <algorithm>



template<typename T>
class Queue
{
private:
	T* mArr;
	size_t mSize;
	size_t mHead;
	size_t mTail;
	size_t mCount;

public:
	Queue(size_t size) : mSize{ size }, mHead{ 0 }, mTail{ 0 }, mCount{ 0 }
	{
		if (mSize == 0)
		{
			mArr = nullptr;
			return;
		}

		mArr = new T[mSize];
	}
	Queue(const Queue& other) : mArr{nullptr}, mSize{other.mSize},
		mHead{other.mHead}, mTail{other.mTail}, mCount{other.mCount}
	{
		if (mSize == 0) return;

		mArr = new T[mSize];
		std::copy(other.mArr, other.mArr + mSize, mArr);
	}




	~Queue() { delete[] mArr; }




	// Проверяет на пустоту
	bool empty() const noexcept { return mCount == 0; }
	// Проверяет на заполненность
	bool full() const noexcept { return mCount == mSize; }




	// Возвращает количество элементов на данный момент в очереди
	size_t size() const noexcept { return mCount; }
	// Возвращает ёмкость очереди (максимальное количество элементов)
	size_t capacity() const noexcept { return mSize; }
	// Возвращает значение элемента с головы, не вынимая его из очреди
	T head() const 
	{ 
		if (empty())
			throw std::logic_error{ "queue if empty" };

		return mArr[mHead];
	}
	// Возвращает значение элемента с хвоста, не вынимая его из очреди
	T tail() const 
	{
		if (empty())
			throw std::logic_error{ "queue if empty" };

		return mArr[(mTail > 0) ? mTail - 1 : mSize - 1];
	}
	



	// Добавляет элмент в хвост очереди
	void push(T value)
	{
		if (full())
			throw std::out_of_range{ "queue is full" };

		mArr[mTail] = value;
		mTail = (mTail + 1) % mSize;
		++mCount;
	}
	// Забирает элемент с головы очереди
	T pop()
	{
		if (empty())
			throw std::out_of_range{ "queue is empty" };

		T value = mArr[mHead];

		mHead = (mHead + 1) % mSize;
		--mCount;

		return value;
	}




	// Выводит все элементы очереди в консоль
	void showData()
	{
		for (size_t i = mHead, cnt = 0; cnt < mCount ; i = (i + 1) % mSize, ++cnt)
		{
			std::cout << mArr[i] << ' ';
		}
		std::cout << '\n';
	}




	// Перегрузка оператора присваивания
	Queue& operator = (const Queue& other)
	{
		if (this == &other) return *this;

		mHead = other.mHead;
		mTail = other.mTail;
		mCount = other.mCount;

		if (mSize != other.mSize)
		{
			mSize = other.mSize;

			delete[] mArr;
			mArr = new T[mSize];
		}

		std::copy(other.mArr, other.mArr + mSize, mArr);

		return *this;
	}



};



#endif // QUEUE_HPP
