#include "quick_union.h"

namespace algo {
	QuickUnionUF::QuickUnionUF(int n) : m_n(n) {
		m_id = new int[n];
		m_count = n;
		for (int i = 0; i < n; i++)
			m_id[i] = i;
	}

	QuickUnionUF::QuickUnionUF(const QuickUnionUF& quf)
		: m_n(quf.m_n), m_count(quf.m_count) {
		m_id = new int[quf.m_n];
		for (int i = 0; i < quf.m_n; i++)
			m_id[i] = quf.m_id[i];

	}

	QuickUnionUF& QuickUnionUF::operator=(const QuickUnionUF& quf) {
		if (this != &quf) {
			m_n = quf.m_n;
			m_count = quf.m_count;
			delete[] m_id;
			m_id = new int[quf.m_n];
			for (int i = 0; i < quf.m_n; i++)
				m_id[i] = quf.m_id[i];
		}
		return *this;
	}

	QuickUnionUF::~QuickUnionUF() {
		delete[] m_id;
	}

	int QuickUnionUF::root(int p) const {
		while (p != m_id[p])
			p = m_id[p];
		return p;
	}

	bool QuickUnionUF::connected(int p, int q) const {
		return root(p) == root(q);
	}

	void QuickUnionUF::unionPart(int p, int q) {
		int i = root(p);
		int j = root(q);
		if (i == j) return;
		else {
			m_count--;
			m_id[i] = j;
		}
	}

	int QuickUnionUF::count() const {
		return m_count;
	}

	int QuickUnionUF::getNum() const {
		return m_n;
	}

	AbstractUF* QuickUnionUF::clone() const {
		return new QuickUnionUF(*this);
	}
}