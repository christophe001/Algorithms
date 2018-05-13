#ifndef _PERCO_INI_
#define _PERCO_INI_

#include "quick_union.h"
#include "weighed_union.h"
#include "union_find.h"
#include <iostream>
#include "perco_stat.h"

namespace algo {
	template <class _Type>
	_Type  PercoIni(int n) {
		_Type uf(n * n + 2);
		for (int i = 1; i <= n; i++) {
			uf.unionPart(i, 0);
			uf.unionPart(n * n - i + 1, n * n + 1);
		}
		return uf;
	}

	void PercoExperiment() {
		int n, num;
		const double p = 0.592746;
		std::cout << "Input column number: " << std::endl;
		std::cin >> n;
		std::cout << "Input test number: " << std::endl;
		std::cin >> num;
		AbstractUF& af = PercoIni<WeightedUnionUF>(n);
		PercoStat pc(af, num);
		pc.run();
		double tstat = (pc.getProb() - p) / (pc.getStddev() / sqrt(num));
		std::cout << "Mean prob is " << pc.getProb() << std::endl;
		std::cout << "The stddev is " << pc.getStddev() << std::endl;
		std::cout << "t-distribution test statistic U is " << tstat << std::endl;
	}
}
#endif // !_PERCO_INI_