#include <iostream>
#include <fstream>
#include "perco_stat.h"
#include "perco_ini.h"
using namespace std;

int main(){
	int n , num ;
	const double p = 0.592746;
	cout << "Input column number: " << endl;
	cin >> n;
	cout << "Input test number: " << endl;
	cin >> num;
	AbstractUF& af = PercoIni<WeightedUnionUF>(n);
   	PercoStat pc(af, num);
	pc.run();
	double tstat = (pc.getProb() - p) / (pc.getStddev() / sqrt(num - 1));
	cout << "Mean prob is " << pc.getProb() << endl;
	cout << "The stddev is " << pc.getStddev() << endl;
	cout << "t-distribution test statistic U is " << tstat << endl;
	system("pause");
}