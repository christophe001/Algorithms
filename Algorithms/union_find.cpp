#include "union_find.h"

namespace algo {
	QuickUF::QuickUF(int n) : m_n(n), m_count(n) {
		m_id = new int[n];
		for (int i = 0; i < n; i++)
			m_id[i] = i;
	}

	QuickUF::QuickUF(const QuickUF& qf)
		: m_n(qf.m_n), m_count(qf.m_count) {
		m_id = new int[qf.m_n];
		for (int i = 0; i < qf.m_n; i++)
			m_id[i] = qf.m_id[i];
	}

	QuickUF& QuickUF::operator=(const QuickUF& qf) {
		if (this != &qf) {
			m_n = qf.m_n;
			m_count = qf.m_count;
			delete[] m_id;
			m_id = new int[qf.m_n];
			for (int i = 0; i < qf.m_n; i++)
				m_id[i] = qf.m_id[i];
		}
		return *this;
	}

	QuickUF::~QuickUF() {
		delete[] m_id;
	}

	bool QuickUF::connected(int p, int q) const {
		return m_id[p] == m_id[q];
	}

	void QuickUF::unionPart(int p, int q) {
		int pid = m_id[p], qid = m_id[q];
		if (pid == qid) return;
		else {
			m_count--;
			for (int i = 0; i < m_n; i++) {
				if (m_id[i] == pid)
					m_id[i] = qid;
			}
		}
	}

	int QuickUF::find(int p) const {
		return m_id[p];
	}

	int QuickUF::count() const {
		return m_count;
	}

	int QuickUF::getNum() const {
		return m_n;
	}

	AbstractUF* QuickUF::clone() const {
		return new QuickUF(*this);
	}
}