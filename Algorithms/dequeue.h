#ifndef _DEQUEUE_
#define _DEQUEUE_

#include <vector>
template<class _Ty>
class Dequeue {
private:
	std::vector<_Ty> items;
public:
	Dequeue();
	~Dequeue();
	bool isEmpty();
	int size();
	void addFirst(_Ty item);
	void addLast(_Ty item);
	_Ty removeFirst();
	_Ty removeLast();
	std::vector<_Ty>::iterator Iterator();

};

#include "dequeue.cpp"

#endif
