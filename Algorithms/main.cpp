#include <iostream>
#include <fstream>
#include "perco_stat.h"
#include "perco_ini.h"
#include "undirected_graph.h"
#include "container_test.h"
#include "graph_test.h"
//#include "random_permutation.h"
#include "merge_sort_bu.h"
#include <thread>

using namespace std;
using namespace algo;

int main(){
	//PercoExperiment();
	unsigned int n = std::thread::hardware_concurrency();
	std::cout << n << " concurrent threads are supported.\n";
	std::vector<int> arr{ 12, 9, 6, 4, 5, 7, 11 , 1, 2, 44};
	int arr2[10] = { 12, 9, 6, 4, 5, 7, 11, 1, 2, 44};
	MergeSortBU::sort(arr.begin(), arr.end());
	MergeSortBU::sort(arr2, arr2 + 10);
	for (int i = 0; i < 10; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
	for (int i = 0; i < 10; i++)
		std::cout << arr2[i] << " ";
	std::cout << std::endl;
	system("pause");
}