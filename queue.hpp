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



	bool empty() const noexcept { return mCount == 0; }
	bool full() const noexcept { return mCount == mSize; }

	size_t size() const noexcept { return mCount; }
	size_t capacity() const noexcept { return mSize; }
	T head() const 
	{ 
		if (empty())
			throw std::logic_error{ "queue if empty" };

		return mArr[mHead];
	}
	T tail() const 
	{
		if (empty())
			throw std::logic_error{ "queue if empty" };

		return mArr[(mTail > 0) ? mTail - 1 : mSize - 1];
	}
	



	void push(T value)
	{
		if (full())
			throw std::out_of_range{ "queue is full" };

		mArr[mTail] = value;
		mTail = (mTail + 1) % mSize;
		++mCount;
	}
	T pop()
	{
		if (empty())
			throw std::out_of_range{ "queue is empty" };

		T value = mArr[mHead];

		mHead = (mHead + 1) % mSize;
		--mCount;

		return value;
	}

	void showData()
	{
		for (size_t i = mHead, cnt = 0; cnt < mCount ; i = (i + 1) % mSize, ++cnt)
		{
			std::cout << mArr[i] << ' ';
		}
		std::cout << '\n';
	}


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
