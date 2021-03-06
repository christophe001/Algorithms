#ifndef _ALGORITHM_SELECTION_SORT_
#define _ALGORITHM_SELECTION_SORT_

namespace algo {
	class SelectionSort {
	private:
		SelectionSort() {}
		~SelectionSort() {}

	public:
		template <class _RandomAccessIter>
		static void sort(_RandomAccessIter first, _RandomAccessIter last) {
			sort(first, last, std::less< std::iterator_traits<_RandomAccessIter>::value_type >());
		}

		template <class _RandomAccessIter, class _Comparator>
		static void sort(_RandomAccessIter first, _RandomAccessIter last, _Comparator comp) {
			for (auto i = first; i != last; i++) {
				auto k = i;
				for (auto j = i + 1; j != last; j++) {
					if (comp(*j, *k))
						k = j;
				}
				std::swap(*k, *i);
			}
		}
	};
}

#endif // !_ALGORITHM_SELECTION_SORT_

