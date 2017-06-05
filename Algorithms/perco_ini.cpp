#include "perco_ini.h"

QuickUF QuickFindIni(int n) {
	QuickUF quf(n * n + 2);
	for (int i = 1; i <= n; i++) {
		quf.union_part(i, 0);
		quf.union_part(n * n - i + 1, n * n + 1);
	}
}

QuickUnionUF QuickUnionIni(int n);

WeightedUnionUF WeightedUnionIni(int n);