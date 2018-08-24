#ifndef _ALGORITHM_INSERTION_SORT_
#define _ALGORITHM_INSERTION_SORT_
#include <algorithm>

namespace algo {
	class InsertionSort {
	private:
		InsertionSort() {}
		~InsertionSort() {}

	public:
		template <class _RandomAccessIter>
		static void sort(_RandomAccessIter first, _RandomAccessIter last) {
			sort(first, last, std::less< std::iterator_traits<_RandomAccessIter>::value_type >());
		}

		template <class _RandomAccessIter, class _Comparator>
		static void sort(_RandomAccessIter first, _RandomAccessIter last, _Comparator comp) {
			for (auto i = first; i != last; i++) {
				for (auto j = i; j != first; j--) {
					if (comp(*j, *(j - 1)))
						std::swap(*j, *(j - 1));
					else break;
				}
			}
		}
	};
}

#endif // !_ALGORITHM_INSERTION_SORT_

