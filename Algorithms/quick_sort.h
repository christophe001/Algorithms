#ifndef _ALGORITHM_QUICK_SORT_
#define _ALGORITHM_QUICK_SORT_

#include <algorithm>

namespace algo {
	class QuickSort {
	private:
		QuickSort() {}
		~QuickSort() {}
	
	public:
		template <class _RandomAccessIter>
		static void sort(_RandomAccessIter first, _RandomAccessIter last) {
			sort(first, last, std::less< std::iterator_traits<_RandomAccessIter>::value_type >());
		}

		template <class _RandomAccessIter, class _Comparator>
		static void sort(_RandomAccessIter first, _RandomAccessIter last, _Comparator comp) {

		}
	};
}
#endif
