#include "perco_stat.h"
#include <time.h> 

namespace algo {

	PercoStat::PercoStat(const AbstractUF& uf, int num_test)
		: m_num_test(num_test), m_test(new int[num_test])
	{
		m_uf = uf.clone();
		m_prob = 0.0;
		m_stddev = 0.0;
	}

	PercoStat::~PercoStat() {
		delete m_uf;
		delete[] m_test;
	}

	double PercoStat::size() const {
		return double(m_uf->getNum() - 2);
	}

	double PercoStat::mean() const {
		double sum = 0;
		for (int i = 0; i < m_num_test; i++)
			sum += m_test[i];
		return sum / m_num_test;
	}

	double PercoStat::stddev() const {
		double mean_val = this->mean();
		double sum = 0;
		for (int i = 0; i < m_num_test; i++)
			sum += m_test[i] * m_test[i];
		return pow(sum - m_num_test * mean_val * mean_val, 0.5) / (size() * pow(m_num_test - 1, 0.5));
	}

	void PercoStat::run() {
		srand(time(NULL));
		for (int i = 0; i < m_num_test; i++) {
			Percolate per(*m_uf);
			int row, col;
			int m_col = per.getCol();
			while (!per.percolates()) {
				row = rand() % m_col;
				col = rand() % m_col;
				per.openSite(row, col);
			}
			m_test[i] = per.count();
		}
		m_prob = mean() / size();
		m_stddev = stddev();
	}

	double PercoStat::getProb() const {
		return m_prob;
	}

	double PercoStat::getStddev() const {
		return m_stddev;
	}
}