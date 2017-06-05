#pragma once
#include "quick_union.h"
#include "union_find.h"
#include "weighed_union.h"

class Percolate {
private:
	AbstractUF* m_uf;
	int* m_open;
	int m_num;
	int m_col;
	int m_count;
public:
	Percolate(const AbstractUF& uf);
	~Percolate();
	bool connected(int p, int q) const;
	bool percolates() const;
	bool is_open(int i) const;
	void open_site(int i, int j);
	int count() const;
	int get_col() const;
};