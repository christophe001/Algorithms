#ifndef _ALGORITHM_MERGE_SORT_BU_
#define _ALGORITHM_MERGE_SORT_BU_

#include <algorithm>
#include <vector>

namespace algo {
	class MergeSortBU {
	private:
		MergeSortBU() {}
		~MergeSortBU() {}
		template <class _RandomAccessIter, class _Comparator, class _Elem>
		static void merge( std::vector<_Elem>& arr, _RandomAccessIter first,
			_Comparator comp, int p, int q, int r) {
			int left = q - p, right = r - q;
			int id = p;
			auto it1 = first + p, it2 = first + q;
			for (; it1 != first + q && it2 != first + r; ) {
				if (comp(*it1, *it2)) {
					arr[id++] = *(it1++);
				}
				else arr[id++] = *(it2++);
			}
			if (it1 == first + q)
				while (it2 != first + r) {
					arr[id++] = *(it2++);
				}
			else {
				while (it1 != first + q) {
					arr[id++] = *(it1++);
				}
			}
			for (int i = p; i != r; i++)
				first[i] = arr[i];
		}

	public:
		template <class _RandomAccessIter>
		static void sort(_RandomAccessIter first, _RandomAccessIter last) {
			sort(first, last, std::less< std::iterator_traits<_RandomAccessIter>::value_type >());
		}

		template <class _RandomAccessIter, class _Comparator> 
		static void sort(_RandomAccessIter first, _RandomAccessIter last, _Comparator comp) {
			typedef std::iterator_traits<_RandomAccessIter>::value_type Elem;
			int n = last - first;
			std::vector<Elem> stack(n);
			for (int sz = 1; sz < n; sz *= 2)
				for (int lo = 0; lo < n - sz; lo += 2 * sz)
					merge(stack, first, comp,  lo, lo + sz, std::min(lo + 2 * sz, n));
		}
	};
}

#endif // !_ALGORITHM_MERGE_SORT_BU_

