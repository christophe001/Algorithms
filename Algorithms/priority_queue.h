#ifndef _ALGO_PQ_
#define _ALGO_PQ_
#include <string>

namespace algo {
	template <class _Type, class _Pr = std::less<_Type> >
	class PriorityQueue {
	private:
		typedef std::size_t _Size;
		_Type* m_arr;
		_Size  m_cnt;
		_Pr	   m_pr;
		_Size  m_size;

		bool prior(int i, int j) const {
			return m_pr(m_arr[i], m_arr[j]);
		}

		void exch(int i, int j);

		void swim(int k);

		void sink(int k);

		void resize(_Size size);

		void free();
	
	public:
		PriorityQueue()
			: m_cnt(0), m_size(1) {
			m_arr = new _Type[m_size + 1];
		}
		
		PriorityQueue(const _Pr& pr)
			: m_cnt(0), m_size(1), m_pr(pr) {
			m_arr = new _Type[m_size + 1];
		}
		
		~PriorityQueue() {
			free();
		}
		
		void insert(_Type val);

		_Type deletePriority();

		int size() const { return m_cnt; }

		bool isEmpty() const { return m_cnt == 0; }

		const _Type getPriority() const;

	};

	template<class _Type, class _Pr>
	inline void PriorityQueue<_Type, _Pr>::exch(int i, int j) {
		_Type temp = m_arr[i];
		m_arr[i] = m_arr[j];
		m_arr[j] = temp;
	}

	template<class _Type, class _Pr>
	inline void PriorityQueue<_Type, _Pr>::swim(int k) {
		while (k > 1 && prior(k, k / 2)) {
			exch(k / 2, k);
			k = k / 2;
		}
	}


	template<class _Type, class _Pr>
	inline void PriorityQueue<_Type, _Pr>::sink(int k) {
		while (2 * k <= m_cnt) {
			int j = 2 * k;
			if (j < m_cnt && prior(j + 1, j))
				j++;
			if (!prior(j, k)) break;
			exch(j, k);
			k = j;
		}
	}


	template<class _Type, class _Pr>
	inline void PriorityQueue<_Type, _Pr>::resize(_Size size) {
		m_size = size;
		_Type* new_heap = new _Type[size + 1];
		for (int i = 1; i <= m_cnt; i++) {
			new_heap[i] = m_arr[i];
		}
		free();
		m_arr = new_heap;
	}

	template<class _Type, class _Pr>
	inline void PriorityQueue<_Type, _Pr>::free() {
		if (m_arr != nullptr)
			delete[] m_arr;
	}


	template<class _Type, class _Pr>
	inline void PriorityQueue<_Type, _Pr>::insert(_Type val) {
		if (m_cnt == m_size) {
			resize(m_size * 2);
		}
		m_arr[++m_cnt] = val;
		swim(m_cnt);
	}

	template<class _Type, class _Pr>
	inline _Type PriorityQueue<_Type, _Pr>::deletePriority() {
		if (isEmpty())
			throw std::exception("empty queue, cannot find priority!\n");
		_Type item = m_arr[1];
		exch(1, m_cnt--);
		sink(1);
		if ((m_cnt > 0) && (m_cnt <= m_size / 4))
			resize(m_size / 2 + 1);
		return item;
	}
	template<class _Type, class _Pr>
	inline const _Type PriorityQueue<_Type, _Pr>::getPriority() const {
		if (isEmpty())
			throw std::exception("empty queue, cannot find priority!\n");
		return m_arr[1];
	}
}

#endif // !_ALGO_PQ_

