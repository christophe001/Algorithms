#ifndef _ALGORITHM_HEAP_SORT_
#define _ALGORITHM_HEAP_SORT_

#include <algorithm>

namespace algo {

	class HeapSort {
	private:
		HeapSort() {}
		~HeapSort() {}
		template <class _RandomAccessIter, class _Comparator>
		static void heapify(_RandomAccessIter first, _RandomAccessIter last, _Comparator comp, int i) {
			auto cur = first + i - 1;
			auto left = first + 2 * i - 1;
			auto right = first + 2 * i;
			int size = last - first;
			auto largest = first;
			if (2 * i - 1 < size && comp(*cur, *left))
				largest = left;
			else largest = first + i - 1;
			if (2 * i < size && comp(*largest, *right))
				largest = right;
			if (largest != cur) {
				std::swap(*cur, *largest);
				heapify(first, last, comp, largest - first + 1);
			}
		}

		template <class _RandomAccessIter, class _Comparator>
		static void build_heap(_RandomAccessIter first, _RandomAccessIter last, _Comparator comp) {
			int size = last - first;
			for (int i = size / 2 ; i >= 1; i--)
				heapify(first, last, comp, i);
		}

	public:
		template <class _RandomAccessIter>
		static void sort(_RandomAccessIter first, _RandomAccessIter last) {
			sort(first, last, std::less< std::iterator_traits<_RandomAccessIter>::value_type >());
		}

		template <class _RandomAccessIter, class _Comparator>
		static void sort(_RandomAccessIter first, _RandomAccessIter last, _Comparator comp) {
			build_heap<_RandomAccessIter, _Comparator>(first, last, comp);
			for (auto it = last - 1; it != first; it--) {
				std::swap(*first, *it);
				heapify<_RandomAccessIter, _Comparator>(first, it, comp, 1);
			}
		}


	};
}

#endif // !_ALGORITHM_HEAP_SORT_

