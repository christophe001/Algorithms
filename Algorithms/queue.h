#ifndef _ALGO_QUEUE_
#define _ALGO_QUEUE_

#include <string>

namespace algo {
	template <class _Type>
	class Queue {
	private:
		typedef std::size_t _Size;
		_Size	m_size;
		_Type*	m_arr;
		_Size	m_back;
		_Size	m_front;
		void resize();
		void resize(_Size new_size);
		void shift();
		void free();

	public:
		typedef _Type* _Iter;
		typedef const _Type* _ConstIter;
		Queue();
		Queue(const Queue& queue);
		Queue(Queue&& queue);
		Queue& operator=(const Queue& queue);
		Queue& operator=(Queue&& queue);
		~Queue();
		_Iter begin();
		_Iter end();
		_ConstIter begin() const;
		_ConstIter end() const;
		void enqueue(const _Type& elem);
		void enqueue(_Type && elem);
		void dequeue();
		const _Type front() const;
		bool isEmpty() const;
		const _Size arr_size() const { return m_size; }
		const _Size size() const { return m_back - m_front; }
		std::string toString() const;
	};

	template<class _Type>
	inline void Queue<_Type>::resize() {
		if (m_size == std::numeric_limits<_Size>::max())
			return;
		else if (m_size > std::numeric_limits<_Size>::max() - m_size / 2)
			resize(m_size + 1);
		else { 
			_Size new_size = m_size / 2 > 1 ? m_size + m_size / 2 : m_size + 1;
			resize(new_size);
		};
	}

	template<class _Type>
	inline void Queue<_Type>::resize(_Size new_size) {
		if (!isEmpty()) {
			m_size = new_size;
			_Size s = size();
			_Type* new_vec = new _Type[new_size];
			for (_Size i = m_front; i < m_back; i++)
				new_vec[i - m_front] = m_arr[i];
			free();
			m_front = 0;
			m_back = s;
			m_arr = new_vec;
		}
	}

	template<class _Type>
	inline void Queue<_Type>::shift() {
		if (size() > 5 && size() < m_size / 4) {
			_Size new_size = m_size / 2 > 5 ? m_size / 2 : 5;
			resize(new_size);
		}
	}

	template<class _Type>
	inline void Queue<_Type>::free() {
		if (m_arr != nullptr)
			delete[] m_arr;
	}

	template<class _Type>
	inline Queue<_Type>::Queue()
		: m_arr(nullptr), m_front(0), m_back(0), m_size(5) {
		m_arr = new _Type[m_size];
	}

	template<class _Type>
	inline Queue<_Type>::Queue(const Queue & queue) {
		m_front = queue.m_front;
		m_back = queue.m_back;
		m_size = queue.m_size;
		m_arr = new _Type[m_size];
		for (_Size i = m_front; i != m_back; i++) {
			m_arr[i] = queue.m_arr[i];
		}
	}

	template<class _Type>
	inline Queue<_Type>::Queue(Queue && queue) {
		m_front = queue.m_front;
		m_back = queue.m_back;
		m_size = queue.m_size;
		m_arr = queue.m_arr;
		queue.m_arr = nullptr;
		queue.m_size = 0;
		queue.m_front = 0;
		queue.m_back = 0;
	}

	template<class _Type>
	inline Queue<_Type>& Queue<_Type>::operator=(const Queue & queue) {
		if (this != &queue) {
			m_front = queue.m_front;
			m_back = queue.m_back;
			m_size = queue.m_size;
			m_arr = new _Type[m_size];
			for (_Size i = m_front; i < m_back; i++) {
				m_arr[i] = queue.m_arr[i];
			}
		}
		return *this;
	}
	template<class _Type>
	inline Queue<_Type>& Queue<_Type>::operator=(Queue && queue) {
		if (this != &queue) {
			m_front = queue.m_front;
			m_back = queue.m_back;
			m_size = queue.m_size;
			m_arr = queue.m_arr;
			queue.m_arr = nullptr;
			queue.m_size = 0;
			queue.m_front = 0;
			queue.m_back = 0;
		}
		return *this;
	}

	template<class _Type>
	inline Queue<_Type>::~Queue() {
		free();
	}

	template<class _Type>
	inline typename Queue<_Type>::_Iter Queue<_Type>::begin() {
		if (!isEmpty()) {
			return &m_arr[m_front];
		}
		else {
			throw std::exception("empty queue!");
		}
	}

	template<class _Type>
	inline typename Queue<_Type>::_Iter Queue<_Type>::end() {
		if (!isEmpty()) {
			return &m_arr[m_back];
		}
		else {
			throw std::exception("empty queue!");
		}
	}

	template<class _Type>
	inline typename Queue<_Type>::_ConstIter Queue<_Type>::begin() const {
		if (!isEmpty()) {
			return &m_arr[m_front];
		}
		else {
			throw std::exception("empty queue!");
		}
	}

	template<class _Type>
	inline typename Queue<_Type>::_ConstIter Queue<_Type>::end() const {
		if (!isEmpty()) {
			return &m_arr[m_back];
		}
		else {
			throw std::exception("empty queue!");
		}
	}

	template<class _Type>
	inline void Queue<_Type>::enqueue(const _Type & elem) {
		if (m_back >= m_size)
			resize();
		m_arr[m_back++] = elem;
	}

	template<class _Type>
	inline void Queue<_Type>::enqueue(_Type && elem) {
		if (m_back >= m_size)
			resize();
		m_arr[m_back++] = std::move(elem);
	}

	template<class _Type>
	inline void Queue<_Type>::dequeue() {
		if (isEmpty()) {
			throw std::exception("empty queue!");
		}
		else {
			m_front++;
			shift();
		}
	}

	template<class _Type>
	inline const _Type Queue<_Type>::front() const {
		if (!isEmpty()) {
			return m_arr[m_front];
		}
		else {
			throw std::exception("empty queue!");
		}
	}

	template<class _Type>
	inline bool Queue<_Type>::isEmpty() const {
		return size() == 0;
	}

	template<class _Type>
	inline std::string Queue<_Type>::toString() const {
		std::string s;
		if (!isEmpty()) {
			for (_Size i = m_front; i < m_back - 1; i++)
				s += std::to_string(m_arr[i]) + " - ";
			s += std::to_string(m_arr[m_back - 1]) + "\n";
		}
		return s;
	}
}

#endif // !_ALGO_QUEUE_

