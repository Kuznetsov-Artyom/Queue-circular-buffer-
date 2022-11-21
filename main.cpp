#include <iostream>
#include "queue.hpp"



int main()
{
	int size = 3;
	Queue<int> queueOne(size);
	
	int i{};

	for (i = 1; i <= size; ++i)
	{
		queueOne.push(i);
		std::cout << queueOne.tail() << '\n';
	}
	std::cout << '\n';

	queueOne.showData();

	queueOne.pop();
	queueOne.showData();
	std::cout << queueOne.tail() << '\n';

	queueOne.push(i);
	queueOne.showData();
	std::cout << queueOne.tail() << '\n';

	queueOne.pop();
	queueOne.showData();
	std::cout << queueOne.tail() << '\n';



	return 0;
}