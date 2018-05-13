#ifndef _UNDIRECTED_GRAPH_
#define _UNDIRECTED_GRAPH_
#include <vector>
#include <string>
#include <iostream>

namespace algo {
	class Graph {
	private:
		int m_vertices;
		int m_edges;
		std::vector<std::vector<int> > m_adjacency;
		std::vector<int> m_degree;
		std::vector<bool> m_visited;
	public:
		Graph(int n);
		Graph(const Graph& g);
		Graph& operator=(const Graph& g);
		bool operator==(const Graph& g);
		bool operator!=(const Graph& g);
		void resetVisited();
		typedef void(Graph::*action)(int i);
		void printPath(int i) { std::cout << i << " "; }
		void dfs(int i, action a);
		void bfs(int i, action a);
		~Graph() {}
		void addEdge(int v, int e);
		const int vertices() const { return m_vertices; }
		const int edges() const { return m_edges; }
		std::vector<int> adj(int i) const { return m_adjacency[i]; }
		const int degree(int i) const { return m_degree[i]; }
		std::string toString() const;
		bool isBipartite() const;
		int components() const;
	};
}
#endif // !_UNDIRECTED_GRAPH_
