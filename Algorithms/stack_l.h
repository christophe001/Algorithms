#ifndef _ALGO_STACK_L_
#define _ALGO_STACK_L_
#include <string>

namespace algo {
	template <class _Type>
	class StackL {
	private:
		typedef std::size_t _Size;
		struct Node {
			_Type m_item;
			Node* m_next;
			Node(const _Type& item)
				: m_item(item), m_next(nullptr) {}
			Node(_Type&& item)
				: m_next(nullptr) {
				m_item = std::move(item);
			}
			Node(const Node& node)
				: m_item(node.m_item), m_next(node.m_next) {}
			Node(Node&& node) {
				m_item = std::move(node.m_item);
				m_next = node.m_next;
				node.m_next = nullptr;
			}
			Node& operator=(const Node& node) {
				m_item = node.m_item;
				m_next = node.m_next;
				return *this;
			}
			Node& operator=(Node && node) {
				m_item = std::move(node.m_item);
				m_next = node.m_next;
				return *this;
			}
		};
		Node* m_first;
		_Size m_size;

	public:
		struct StackIter {
			const Node* m_node;
			StackIter() noexcept : m_node(nullptr) {}
			StackIter(const Node* node) noexcept : m_node(node) {}
			StackIter& operator=(const Node* node) {
				this->m_node = node;
				return *this;
			}

			StackIter& operator++() {
				if (m_node) {
					m_node = m_node->m_next;
				}
				return *this;
			}

			StackIter operator++(int) {
				StackIter iter(m_node);
				++*this;
				return iter;
			}

			bool operator==(const StackIter& iter) {
				return m_node == iter.m_node;
			}

			bool operator!=(const StackIter& iter) {
				return m_node != iter.m_node;
			}

			_Type operator*() {
				return m_node->m_item;
			}
		};

		StackIter begin() const {
			return StackIter(m_first);
		}

		StackIter end() const {
			return StackIter(nullptr);
		}

		StackL();
		StackL(const StackL& stack);
		StackL(StackL&& stack);
		StackL& operator=(const StackL& stack);
		StackL& operator=(StackL&& stack);
		~StackL();
		bool isEmpty() const;
		const _Size size() const { return m_size; }
		void push(const _Type& elem);
		void push(_Type&& elem);
		void pop();
		const _Type top() const;
		std::string toString() const;
	};

	template<class _Type>
	inline StackL<_Type>::StackL()
		: m_size(0), m_first(nullptr) {}

	template<class _Type>
	inline StackL<_Type>::StackL(const StackL & stack)
		: m_size(stack.m_size), m_first(nullptr) {
		if (!stack.isEmpty()) {
			Node * curr_s = stack.m_first;
			m_first = new Node(curr_s->m_item);
			Node * curr = m_first;
			while (curr_s->m_next != nullptr) {
				curr_s = curr_s->m_next;
				curr->m_next = new Node(curr_s->m_item);
				curr = curr->m_next;
			}
		}
	}

	template<class _Type>
	inline StackL<_Type>::StackL(StackL && stack) {
		m_size = stack.m_size;
		m_first = stack.m_first;
		stack.m_size = 0;
		stack.m_first = nullptr;
	}

	template<class _Type>
	inline StackL<_Type> & StackL<_Type>::operator=(const StackL & stack) {
		if (this != &stack) {
			m_size = stack.m_size;
			m_first = nullptr;
			if (!stack.isEmpty()) {
				Node * curr_s = stack.m_first;
				m_first = new Node(curr_s->m_item);
				Node * curr = m_first;
				while (curr_s->m_next != nullptr) {
					curr_s = curr_s->m_next;
					curr->m_next = new Node(curr_s->m_item);
					curr = curr->m_next;
				}
			}
		}
		return *this;
	}

	template<class _Type>
	inline StackL<_Type> & StackL<_Type>::operator=(StackL && stack) {
		if (this != &stack) {
			m_size = stack.m_size;
			m_first = stack.m_first;
			stack.m_size = 0;
			stack.m_first = nullptr;
		}
		return *this;
	}

	template<class _Type>
	inline StackL<_Type>::~StackL() {
		while (m_first != nullptr) {
			Node* node = m_first;
			m_first = m_first->m_next;
			delete node;
		}
	}

	template<class _Type>
	inline bool StackL<_Type>::isEmpty() const {
		return m_first == nullptr;
	}

	template<class _Type>
	inline void StackL<_Type>::push(const _Type & elem) {
		if (isEmpty()) {
			m_first = new Node(elem);
		}
		else {
			Node * temp = m_first;
			m_first = new Node(elem);
			m_first->m_next = temp;
		}
		m_size++;
	}

	template<class _Type>
	inline void StackL<_Type>::push(_Type && elem) {
		if (isEmpty()) {
			m_first = new Node(elem);
		}
		else {
			Node * temp = m_first;
			m_first = new Node(elem);
			m_first->m_next = temp;
		}
		m_size++;
	}

	template<class _Type>
	inline void StackL<_Type>::pop() {
		if (!isEmpty()) {
			Node* pre = m_first;
			m_first = m_first->m_next;
			delete pre;
			m_size--;
		}
		else {
			throw std::exception("empty stack");
		}
	}

	template<class _Type>
	inline const _Type StackL<_Type>::top() const {
		if (!isEmpty()) {
			return m_first->m_item;
		}
		else {
			throw std::exception("empty stack!");
		}
	}

	template<class _Type>
	inline std::string StackL<_Type>::toString() const
	{
		std::string s;
		if (!isEmpty()) {
			for (auto it = this->begin(); it != this->end(); it++) {
				s += std::to_string(*it) + " - ";
			}
		}
		s.erase(s.end() - 3, s.end());
		return s + "\n";
	}
}

#endif // !_ALGO_STACK_L_

