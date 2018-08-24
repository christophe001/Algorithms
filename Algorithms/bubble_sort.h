#ifndef _ALGORITHM_BUBBLE_SORT_
#define _ALGORITHM_BUBBLE_SORT_

namespace algo {
	class BubbleSort {
	private:
		BubbleSort() {}
		~BubbleSort() {}

	public:
		template <class _RandomAccessIter>
		static void sort(_RandomAccessIter first, _RandomAccessIter last) {
			sort(first, last, std::less< std::iterator_traits<_RandomAccessIter>::value_type >());
		}

		template <class _RandomAccessIter, class _Comparator>
		static void sort(_RandomAccessIter first, _RandomAccessIter last, _Comparator comp) {
			bool swapped;
			for (auto i = last - 1; i != first; i--) {
				swapped = false;
				for (auto j = first; j != i; j++) {
					if (comp(*(j+1), *j)) {
						std::swap(*j, *(j + 1));
						swapped = true;
					}
				}
				if (!swapped) break;
			}
		}
	};
}

#endif // !_ALGORITHM_BUBBLE_SORT_

