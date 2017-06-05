#pragma once
class AbstractUF {
public:
	AbstractUF() {}
	virtual ~AbstractUF() {}
	virtual bool connected(int p, int q) const = 0;
	virtual void union_part(int p, int q) = 0;
	virtual int count() const = 0;
	virtual int getNum() const = 0;
	virtual AbstractUF* clone() const = 0;
};