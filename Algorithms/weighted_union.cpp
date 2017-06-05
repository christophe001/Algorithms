#include "weighed_union.h"

WeightedUnionUF::WeightedUnionUF(int n) 
	: m_n(n), m_count(n) {
	m_id = new int[n];
	m_size = new int[n];
	for (int i = 0; i < n; i++) {
		m_id[i] = i;
		m_size[i] = 1;
	}
}

WeightedUnionUF::WeightedUnionUF(const WeightedUnionUF& wuf)
	: m_n(wuf.m_n), m_count(wuf.m_count) {
	m_id = new int[wuf.m_n];
	m_size = new int[wuf.m_n];
	for (int i = 0; i < wuf.m_n; i++) {
		m_id[i] = wuf.m_id[i];
		m_size[i] = wuf.m_size[i];
	}
}

WeightedUnionUF& WeightedUnionUF::operator=(const WeightedUnionUF& wuf) {
	if (this != &wuf) {
		m_n = wuf.m_n;
		m_count = wuf.m_count;
		delete[] m_id;
		delete[] m_size;
		m_id = new int[wuf.m_n];
		m_size = new int[wuf.m_n];
		for (int i = 0; i < wuf.m_n; i++) {
			m_id[i] = wuf.m_id[i];
			m_size[i] = wuf.m_size[i];
		}
	}
	return *this;
}

WeightedUnionUF::~WeightedUnionUF() {
	delete[] m_id;
	delete[] m_size;
}

bool WeightedUnionUF::connected(int p, int q) const {
	return root(p) == root(q);
}

int WeightedUnionUF::root(int p) const {
	while (p != m_id[p])
		p = m_id[p];
	return p;
}

void WeightedUnionUF::union_part(int p, int q) {
	int pid = root(p);
	int qid = root(q);
	if (pid == qid) return;
	else {
		m_count--;
		if (m_size[pid] < m_size[qid]) {
			m_id[pid] = qid;
			m_size[qid] += m_size[pid];
		}
		else {
			m_id[qid] = pid;
			m_size[pid] += m_size[qid];
		}
	}
}

int WeightedUnionUF::count() const {
	return m_count;
}

int WeightedUnionUF::getNum() const {
	return m_n;
}

AbstractUF* WeightedUnionUF::clone() const {
	return new WeightedUnionUF(*this);
}