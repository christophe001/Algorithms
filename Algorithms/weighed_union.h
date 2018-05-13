#ifndef _WEIGHTED_UNION_
#define _WEIGHTED_UNION_

#include "abstract_uf.h"

namespace algo {
	class WeightedUnionUF : public AbstractUF {
	private:
		int* m_id;
		int* m_size;
		int m_n;
		int m_count;
		int root(int p) const;
	public:
		WeightedUnionUF(int n);
		WeightedUnionUF(const WeightedUnionUF& wuf);
		WeightedUnionUF& operator=(const WeightedUnionUF& wuf);
		virtual ~WeightedUnionUF();
		virtual bool connected(int p, int q) const;
		virtual void unionPart(int p, int q);
		virtual int count() const;
		virtual int getNum() const;
		virtual AbstractUF* clone() const;
	};
}
#endif // !_WEIGHTED_UNION_
