#ifndef _QUICK_UNION_
#define _QUICK_UNION_

#include "abstract_uf.h"

namespace algo {
	class QuickUnionUF : public AbstractUF {
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
		virtual void unionPart(int p, int q);
		virtual int count() const;
		virtual int getNum() const;
		virtual AbstractUF* clone() const;
	};
}

#endif // !_QUICK_UNION_