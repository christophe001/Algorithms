#ifndef _ALGORITHM_RANDOM_PERMUTATION_
#define _ALGORITHM_RANDOM_PERMUTATION_

#include <ctime>
#include <algorithm>

class Shuffle {
private:
	Shuffle() {}
	~Shuffle() {}
public:

	template <class _RandomAccessIter>
	static void shuffle(_RandomAccessIter first, _RandomAccessIter last) {
		int n = last - first;
		srand(time(0));
		for (int i = n - 1; i > 0; i--) {
			std::swap(first[i], first[std::rand() % (i + 1)]);
		}
	}
};
#endif // !_ALGORITHM_RANDOM_PERMUTATION_

