#ifndef _QUICK_FIND_
#define _QUICK_FIND_

#include "abstract_uf.h"
namespace algo {
	class QuickUF : public AbstractUF {
	private:
		int* m_id;
		int m_n;
		int m_count;
	public:
		QuickUF(int n);
		QuickUF(const QuickUF& qf);
		QuickUF& operator=(const QuickUF& qf);
		virtual ~QuickUF();
		virtual bool connected(int p, int q) const;
		virtual void unionPart(int p, int q);
		int find(int p) const;
		virtual int count() const;
		virtual int getNum() const;
		virtual AbstractUF* clone() const;
	};
}
#endif // !_QUICK_FIND_


