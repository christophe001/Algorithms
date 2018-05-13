#ifndef _ABSTRACT_UF_
#define _ABSTRACT_UF_

namespace algo {
	class AbstractUF {
	public:
		AbstractUF() {}
		virtual ~AbstractUF() {}
		virtual bool connected(int p, int q) const = 0;
		virtual void unionPart(int p, int q) = 0;
		virtual int count() const = 0;
		virtual int getNum() const = 0;
		virtual AbstractUF* clone() const = 0;
	};
}
#endif // !_ABSTRACT_UF_