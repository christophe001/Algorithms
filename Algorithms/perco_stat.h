#pragma once
#include "percolate.h"
#include <cmath>
#include <random>
class PercoStat {
private:
	int m_num_test;
	AbstractUF* m_uf;
	int* m_test;
	double m_prob;
	double m_stddev;
public:
	PercoStat(const AbstractUF& uf, int num);
	~PercoStat();
	double size() const;
	void run();
	double mean() const;
	double stddev() const;
	double getProb() const;
	double getStddev() const;
};