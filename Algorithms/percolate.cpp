#include "percolate.h"
#include <cmath>
#include <assert.h> 

Percolate::Percolate(const AbstractUF& uf) {
	m_uf = uf.clone();
	m_num = uf.getNum();
	m_col = sqrt(m_num - 2);
	m_count = 0;
	m_open = new int[m_num];
	for (int i = 0; i < m_num; i++)
		m_open[i] = 0;
}

Percolate::~Percolate() {
	delete[] m_open;
	delete m_uf;
}

bool Percolate::connected(int p, int q) const {
	return m_uf->connected(p, q);
}

bool Percolate::percolates() const {
	return m_uf->connected(0, m_num - 1);
}

bool Percolate::is_open(int p) const {
	assert(p >= 0 && p < m_num);
	return m_open[p] == 1;
}


void Percolate::open_site(int i, int j) {
	assert(i >= 0 && i < m_col);
	assert(j >= 0 && j < m_col);
	int id = i * m_col + j + 1;
	if (m_open[id] == 1)
		return;
	else {
		m_open[id] = 1;
		m_count++;
		if (i > 0) {
			if (m_open[id - m_col])
				m_uf->union_part(id, id - m_col);
		}
		if (i < m_col - 1) {
			if (m_open[id + m_col])
				m_uf->union_part(id, id + m_col);
		}
		if (j > 0) {
			if (m_open[id - 1])
				m_uf->union_part(id, id - 1);
		}
		if (j < m_col - 1) {
			if (m_open[id + 1])
				m_uf->union_part(id, id + 1);
		}
	}
}


int Percolate::count() const {
	return m_count;
}

int Percolate::get_col() const {
	return m_col;
}