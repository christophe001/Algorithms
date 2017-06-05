#pragma once
#include "abstract_uf.h"
class QuickUnionUF : public AbstractUF{
private:
	int * m_id;
	int m_n;
	int m_count;
	int root(int p) const;
public:
	QuickUnionUF(int n);
	QuickUnionUF(const QuickUnionUF& quf);
	QuickUnionUF& operator=(const QuickUnionUF& quf);
	virtual ~QuickUnionUF();
	virtual bool connected(int p, int q) const;
	virtual void union_part(int p, int q);
	virtual int count() const;
	virtual int getNum() const;
	virtual AbstractUF* clone() const;
};