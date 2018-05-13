#include "directed_graph.h"
#include <assert.h>


namespace algo {

	Digraph::Digraph(int n) {
		m_children = std::vector<std::vector<int> >(n, std::vector<int>());
		m_parents = std::vector<std::vector<int> >(n, std::vector<int>());
		m_degree = std::vector<int>(n, 0);
		m_vertices = n;
		m_edges = 0;
	}

	Digraph::Digraph(const Digraph & dg) {
		this->m_vertices = dg.m_vertices;
		this->m_edges = dg.m_edges;
		this->m_children = dg.m_children;
		this->m_parents = dg.m_parents;
		this->m_degree = dg.m_degree;
	}

	Digraph & Digraph::operator=(const Digraph & dg) {
		this->m_vertices = dg.m_vertices;
		this->m_edges = dg.m_edges;
		this->m_children = dg.m_children;
		this->m_parents = dg.m_parents;
		this->m_degree = dg.m_degree;
		return *this;
	}

	bool Digraph::operator==(const Digraph & dg) {
		if (this->m_vertices != dg.m_vertices) return false;
		if (this->m_edges != dg.m_edges) return false;
		if (this->m_children != dg.m_children) return false;
		if (this->m_parents != dg.m_parents) return false;
		if (this->m_degree != dg.m_degree) return false;
		return true;
	}

	bool Digraph::operator!=(const Digraph & dg) {
		return !(*this == dg);
	}

	void Digraph::addEdge(int v, int e) {
		assert(v >= 0 && v < m_vertices);
		assert(e >= 0 && e < m_vertices);
		m_children[v].push_back(e);
		m_parents[e].push_back(v);
		m_degree[v]++;
		m_degree[e]++;
		m_edges++;
	}

	Digraph Digraph::reverse() {
		Digraph reversed(*this);
		reversed.m_children = this->m_parents;
		reversed.m_parents = this->m_children;
		return reversed;
	}

	std::string Digraph::toString() const {
		std::string s;
		for (int i = 0; i < m_vertices; i++) {
			for (auto j : m_children[i]) {
				s += std::to_string(i) + "->" + std::to_string(j) + "\n";
			}
		}
		return s;
	}
}