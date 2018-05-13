#ifndef _ALGO_QUEUE_L_
#define _ALGO_QUEUE_L_

#include <string>
namespace algo {
	template <class _Type>
	class QueueL {
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
		Node* m_last;
		_Size m_size;
	public:
		struct QueueIter {
			const Node* m_node;
			QueueIter() noexcept : m_node(nullptr) {}
			QueueIter(const Node* node) noexcept : m_node(node) {}
			QueueIter& operator=(const Node* node) {
				this->m_node = node;
				return *this;
			}

			QueueIter& operator++() {
				if (m_node) {
					m_node = m_node->m_next;
				}
				return *this;
			}
			
			QueueIter operator++(int) {
				QueueIter iter(m_node);
				++*this;
				return iter;
			}

			bool operator==(const QueueIter& iter) {
				return m_node == iter.m_node;
			}

			bool operator!=(const QueueIter& iter) {
				return m_node != iter.m_node;
			}

			_Type operator*() {
				return m_node->m_item;
			}
		};

		QueueIter begin() const {
			return QueueIter(m_first);
		}
		QueueIter end() const {
			return QueueIter(nullptr);
		}

		QueueL();
		QueueL(const QueueL& queue);
		QueueL(QueueL&& queue);
		QueueL& operator=(const QueueL& queue);
		QueueL& operator=(QueueL && queue);
		~QueueL();
		bool isEmpty() const;
		const _Size size() const { return m_size; }
		void enqueue(const _Type& elem);
		void enqueue(_Type && elem);
		void dequeue();
		const _Type front() const;
		std::string toString() const;

	};

	template<class _Type>
	inline QueueL<_Type>::QueueL() 
		: m_first(nullptr), m_last(nullptr), m_size(0) {}

	template<class _Type>
	inline QueueL<_Type>::QueueL(const QueueL & queue) 
		: m_size(queue.m_size), m_first(nullptr), m_last(nullptr) {
		if (!queue.isEmpty()) {
			Node* curr_l = queue.m_first;
			m_first = new Node(curr_l->m_item);
			Node* curr = m_first;
			while (curr_l->m_next != nullptr) {
				curr_l = curr_l->m_next;
				curr->m_next = new Node(curr_l->m_item);
				curr = curr->m_next;
			}
			m_last = new Node(queue.m_last->m_item);
		}
	}

	template<class _Type>
	inline QueueL<_Type>::QueueL(QueueL && queue) {
		m_size = queue.m_size;
		m_first = queue.m_first;
		m_last = queue.m_last;
		queue.m_size = 0;
		queue.m_last = nullptr;
		queue.m_first = nullptr;
	}

	template<class _Type>
	inline QueueL<_Type>& QueueL<_Type>::operator=(const QueueL & queue) {
		if (this != &queue) {
			m_size = queue.m_size;
			m_first = nullptr;
			m_last = nullptr;
			if (!queue.isEmpty()) {
				Node* curr_l = queue.m_first;
				m_first = new Node(curr_l->m_item);
				Node* curr = m_first;
				while (curr_l->m_next != nullptr) {
					curr_l = curr_l->m_next;
					curr->next = new Node(curr_l->m_item);
					curr = curr->m_next;
				}
				m_last = new Node(queue.m_last->m_item);
			}
		}
		return *this;
	}

	template<class _Type>
	inline QueueL<_Type>& QueueL<_Type>::operator=(QueueL && queue) {
		if (this != &queue) {
			m_size = queue.m_size;
			m_first = queue.m_first;
			m_last = queue.m_last;
			queue.m_size = 0;
			queue.m_last = nullptr;
			queue.m_first = nullptr;
		}
		return *this;
	}

	template<class _Type>
	inline QueueL<_Type>::~QueueL() {
		while (m_first != nullptr) {
			Node* temp = m_first;
			m_first = m_first->m_next;
			delete temp;
		}
		m_last = nullptr;
	}

	template<class _Type>
	inline bool QueueL<_Type>::isEmpty() const {
		return m_first == nullptr;
	}

	template<class _Type>
	inline void QueueL<_Type>::enqueue(const _Type & elem) {
		if (isEmpty()) {
			m_first = new Node(elem);
			m_last = m_first;
		}
		else {
			m_last->m_next = new Node(elem);
			m_last = m_last->m_next;
		}
		m_size++;
	}

	template<class _Type>
	inline void QueueL<_Type>::enqueue(_Type && elem) {
		if (isEmpty()) {
			m_first = new Node(elem);
			m_last = m_first;
		}
		else {
			m_last->m_next = new Node(elem);
			m_last = m_last->m_next;
		}
		m_size++;
	}

	template<class _Type>
	inline void QueueL<_Type>::dequeue() {
		if (!isEmpty()) {
			Node * pre = m_first;
			m_first = m_first->m_next;
			m_size--;
			delete pre;
		}
		else {
			throw std::exception("empty queue!");
		}
		if (isEmpty()) {
			m_last = nullptr;
		}
	}

	template<class _Type>
	inline const _Type QueueL<_Type>::front() const {
		if (!isEmpty()) {
			return m_first->m_item;
		}
		else {
			throw std::exception("empty queue!");
		}
	}

	template<class _Type>
	inline std::string QueueL<_Type>::toString() const {
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

