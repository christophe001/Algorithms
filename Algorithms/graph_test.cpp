#include "graph_test.h"

namespace algo {
	void UGtest() {
		Graph g(8);
		g.addEdge(0, 1);
		g.addEdge(2, 3);
		g.addEdge(4, 5);
		g.addEdge(6, 7);
		std::cout << g.toString();
		g.print();
		if (g.isBipartite())
			std::cout << "graph is bipartite.\n";
		else
			std::cout << "graph is not bipartite.\n";
		std::cout << "Total components: " << g.components() << std::endl;

		g.addEdge(1, 3);
		g.addEdge(0, 2);
		g.addEdge(4, 6);
		g.addEdge(5, 7);
		g.addEdge(0, 7);
		std::cout << g.toString();
		g.print();
		
		if (g.isBipartite())
			std::cout << "graph is bipartite.\n";
		else
			std::cout << "graph is not bipartite.\n";
		
		std::cout << "Total components: " << g.components() << std::endl;
	}
}