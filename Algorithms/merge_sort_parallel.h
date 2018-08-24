#ifndef _ALGORITHM_MERGE_SORT_PARALLEL_
#define _ALGORITHM_MERGE_SORT_PARALLEL_

#include <algorithm>
#include <thread>
#include <vector>
namespace algo {

	class MergeSortP {
	private:
		MergeSortP() {}
		~MergeSortP() {}

		template<class _RandomAccessIter, class _Comparator, class _Elem>
		static void merge(std::vector<_Elem>& arr, _RandomAccessIter first,
			_Comparator comp, int p, int q, int r) {
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

		template<class _RandomAccessIter, class _Comparator, class _Elem>
		static void merge_sort(std::vector<_Elem>& arr, _RandomAccessIter first,
			_Comparator comp, int p, int r) {
			if (p < r - 1) {
				merge_sort(arr, first, comp, p, p + (r - p) / 2);
				merge_sort(arr, first, comp, p + (r - p) / 2, r);
				merge(arr, first, comp, p, p + (r - p) / 2, r);
			}
		}

	public:
		template <class _RandomAccessIter>
		static void sort(_RandomAccessIter first, _RandomAccessIter last) {
			sort(first, last, std::less< std::iterator_traits<_RandomAccessIter>::value_type >());
		}

		template <class _RandomAccessIter, class _Comparator>
		static void sort(_RandomAccessIter first, _RandomAccessIter last, _Comparator comp) {
			typedef std::iterator_traits<_RandomAccessIter>::value_type Elem;
			int num_threads = std::thread::hardware_concurrency();
			int n = last - first;
			std::vector<Elem> stack(n);
			merge_sort(stack, first, comp, 0, n);
		}


	};
}

#endif // !_MERGE_SORT_



