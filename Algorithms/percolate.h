#ifndef _PERCOLATE_
#define _PERCOLATE_

#include "quick_union.h"
#include "union_find.h"
#include "weighed_union.h"

namespace algo {
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
		bool isOpen(int i) const;
		void openSite(int i, int j);
		int count() const;
		int getCol() const;
	};
}

#endif // !_PERCOLATE_