#ifndef _ALGO_STACK_
#define _ALGO_STACK_
#include <string>

namespace algo {
	template <class _Type>
	class Stack {
	private:
		typedef std::size_t _Size;
		_Size	m_size;
		_Type*	m_arr;
		_Size	m_cnt;
		void resize();
		void resize(_Size new_size);
		void trim();
		void free();

	public:
		typedef _Type* _Iter;
		typedef const _Type* _ConstIter;
		_Iter begin();
		_Iter end();
		_ConstIter begin() const;
		_ConstIter end() const;
		Stack();
		Stack(const Stack& stack);
		Stack(Stack&& stack);
		Stack& operator=(const Stack& stack);
		Stack& operator=(Stack&& stack);
		~Stack();
		void push(const _Type& elem);
		void push(_Type&& elem);
		void pop();
		const _Type top() const;
		bool isEmpty() const;
		const _Size arr_size() const { return m_size; }
		const _Size size() const { return m_cnt; }
		std::string toString() const;
	};

	template<class _Type>
	inline void Stack<_Type>::resize() {
		if (m_size == std::numeric_limits<_Size>::max())
			return;
		else if (m_size > std::numeric_limits<_Size>::max() - m_size / 2)
			resize(m_size + 1);
		else resize(m_size + (m_size / 2));
	}

	template<class _Type>
	inline void Stack<_Type>::resize(_Size new_size) {
		if (!isEmpty()) {
			m_size = new_size;
			_Type* new_vec = new _Type[m_cnt];
			for (_Size i = 0; i < m_cnt; i++)
				new_vec[i] = m_arr[i];
			free();
			m_arr = new _Type[new_size];
			for (_Size i = 0; i < m_cnt; i++)
				m_arr[i] = new_vec[i];
			delete[] new_vec;
		}
	}

	template<class _Type>
	inline void Stack<_Type>::trim() {
		if (m_cnt > 5 && m_cnt < m_size / 2) {
			_Size new_size = m_size / 2 > 5 ? m_size / 2 : 5;
			resize(new_size);
		}
	}

	template<class _Type>
	inline void Stack<_Type>::free() {
		if (m_arr != nullptr)
			delete[] m_arr;
	}

	template<class _Type>
	inline typename Stack<_Type>::_Iter Stack<_Type>::begin() {
		if (m_cnt > 0)
			return &m_arr[0];
		else {
			throw std::exception("empty stack!");
		}		
	}

	template<class _Type>
	inline typename Stack<_Type>::_Iter Stack<_Type>::end() {
		if (m_cnt > 0)
			return &m_arr[m_cnt];
		else {
			throw std::exception("empty stack!");
		}
	}

	template<class _Type>
	inline typename Stack<_Type>::_ConstIter Stack<_Type>::begin() const {
		if (!isEmpty())
			return &m_arr[0];
		else {
			throw std::exception("empty stack!");
		}
	}

	template<class _Type>
	inline typename Stack<_Type>::_ConstIter Stack<_Type>::end() const {
		if (!isEmpty())
			return &m_arr[m_cnt];
		else {
			throw std::exception("empty stack!");
		}
	}

	template<class _Type>
	inline Stack<_Type>::Stack() 
		: m_arr(nullptr), m_cnt(0), m_size(5) {
		m_arr = new _Type[m_size];
	}

	template<class _Type>
	inline Stack<_Type>::Stack(const Stack & stack) 
		: m_cnt(stack.m_cnt), m_size(stack.m_size) {
		m_arr = new _Type[m_size];
		for (_Size i = 0; i < m_cnt; i++)
			m_arr[i] = stack.m_arr[i];
	}

	template<class _Type>
	inline Stack<_Type>::Stack(Stack && stack) {
		this->m_arr = stack.m_arr;
		this->m_cnt = stack.m_cnt;
		this->m_size = stack.m_size;
		stack.m_arr = nullptr;
		stack.m_cnt = 0;
		stack.m_size = 0;
	}

	template<class _Type>
	inline Stack<_Type>& Stack<_Type>::operator=(const Stack& stack) {
		if (this != &stack) {
			free();
			m_cnt = stack.m_cnt;
			m_size = stack.m_size;
			m_arr = new _Type[m_size];
			for (_Size i = 0; i < m_cnt; i++)
				m_arr[i] = stack.m_arr[i];
		}
		return *this;
	}

	template<class _Type>
	inline Stack<_Type>& Stack<_Type>::operator= (Stack&& stack) {
		if (this != &stack) {
			free();
			this->m_arr = stack.m_arr;
			this->m_cnt = stack.m_cnt;
			this->m_size = stack.m_size;
			stack.m_arr = nullptr;
			stack.m_cnt = 0;
			stack.m_size = 0;
		}
		return *this;
	}

	template<class _Type>
	inline Stack<_Type>::~Stack() {
		free();
	}

	template<class _Type>
	inline void Stack<_Type>::push(const _Type & elem) {
		if (m_cnt >= m_size)
			resize();
		m_arr[m_cnt++] = elem;
	}

	template<class _Type>
	inline void Stack<_Type>::push(_Type && elem) {
		if (m_cnt >= m_size)
			resize();
		m_arr[m_cnt++] = std::move(elem);
	}

	template<class _Type>
	inline void Stack<_Type>::pop() {
		if (isEmpty()) {
			throw std::exception("empty stack!");
		}
		else {
			m_cnt--;
			trim();
		}
	}

	template<class _Type>
	inline const _Type Stack<_Type>::top() const {
		if (!isEmpty())
			return m_arr[m_cnt - 1];
		else {
			throw std::exception("empty stack!");
		}
	}

	template<class _Type>
	inline bool Stack<_Type>::isEmpty() const {
		return m_cnt == 0;
	}

	template<class _Type>
	inline std::string Stack<_Type>::toString() const {
		std::string s;
		if (!isEmpty()) {
			for (_Size i = 0; i < m_cnt - 1; i++)
				s += std::to_string(m_arr[i]) + " - ";
			s += std::to_string(m_arr[m_cnt - 1]) + "\n";
		}
		return s;			
	}
}
#endif // !_ALGO_STACK_

