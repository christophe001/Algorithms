#include "container_test.h"
#include <iostream>

namespace algo {
	void StackTest() {
		Stack<int> st;
		st.push(0);
		for (int i = 0; i < 10; i++)
			st.push(i * 2 + 1);
		std::cout << "top element: " << st.top() << std::endl;
		st.pop();
		std::cout << "after pop 1: " << st.top() << std::endl;
		st.pop();
		std::cout << "after pop 2: " << st.top() << std::endl;
		for (auto it = st.begin(); it != st.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << st.toString();
		Stack<int> st2(st);
		std::cout << st2.toString();
	}

	void QueueTest() {
		Queue<int> qu;
		qu.enqueue(0);
		for (int i = 0; i < 10; i++)
			qu.enqueue(i * 2 + 1);
		std::cout << "front element: " << qu.front() << std::endl;
		qu.dequeue();
		std::cout << "after dequeue 1: " << qu.front() << std::endl;
		qu.dequeue();
		std::cout << "after dequeue 2: " << qu.front() << std::endl;
		for (auto it = qu.begin(); it != qu.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << qu.toString();
		Queue<int> qu2(qu);
		std::cout << qu2.toString();
	}

	void QueueLTest() {
		QueueL<int> qu;
		qu.enqueue(0);
		for (int i = 0; i < 10; i++)
			qu.enqueue(i * 2 + 1);
		std::cout << "front element: " << qu.front() << std::endl;
		qu.dequeue();
		std::cout << "after dequeue 1: " << qu.front() << std::endl;
		qu.dequeue();
		std::cout << "after dequeue 2: " << qu.front() << std::endl;
		for (auto it = qu.begin(); it != qu.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << qu.toString();
		QueueL<int> qu2(qu);
		std::cout << qu2.toString();
	}

	void StackLTest() {
		StackL<int> st;
		st.push(0);
		for (int i = 0; i < 10; i++)
			st.push(i * 2 + 1);
		std::cout << "top element: " << st.top() << std::endl;
		st.pop();
		std::cout << "after pop 1: " << st.top() << std::endl;
		st.pop();
		std::cout << "after pop 2: " << st.top() << std::endl;
		for (auto it = st.begin(); it != st.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << st.toString();
		StackL<int> st2(st);
		std::cout << st2.toString();
	}
}