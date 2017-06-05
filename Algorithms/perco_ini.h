#pragma once
#include "quick_union.h"
#include "weighed_union.h"
#include "union_find.h"

template <class T>
T  PercoIni(int n) {
	T uf(n * n + 2);
	for (int i = 1; i <= n; i++) {
		uf.union_part(i, 0);
		uf.union_part(n * n - i + 1, n * n + 1);
	}
	return uf;
}
