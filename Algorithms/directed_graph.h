#ifndef _DIRECTED_GRAPH_
#define _DIRECTED_GRAPH_
#include <vector>
#include <string>

namespace algo {
	class Digraph {
	private:
		int m_vertices;
		int m_edges;
		std::vector<std::vector<int> > m_children;
		std::vector<std::vector<int> > m_parents;
		std::vector<int> m_degree;
	public:
		Digraph(int n);
		Digraph(const Digraph& dg);
		Digraph& operator=(const Digraph& dg);
		bool operator==(const Digraph& dg);
		bool operator!=(const Digraph& dg);
		~Digraph() {}
		void addEdge(int v, int e);
		const int vertices() const { return m_vertices; }
		const int edges() const { return m_edges; }
		std::pair<std::vector<int>, std::vector<int> > adj(int i) const {
			return std::make_pair(m_parents[i], m_children[i]);
		}
		const int degree(int i) const { return m_degree[i]; }
		Digraph reverse();
		std::string toString() const;
		bool isBipartite() const;
	};
}

#endif // !_DIRECTED_GRAPH_

