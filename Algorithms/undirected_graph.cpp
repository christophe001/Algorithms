#include "undirected_graph.h"
#include <assert.h>
#include "queue.h"
#include <queue>
namespace algo {
	Graph::Graph(int n) {
		m_adjacency = std::vector<std::vector<int> >(n, std::vector<int>());
		m_degree = std::vector<int>(n, 0);
		m_vertices = n;
		m_edges = 0;
		m_visited = std::vector<bool>(n, false);
	}

	Graph::Graph(const Graph & g) {
		this->m_vertices = g.m_vertices;
		this->m_edges = g.m_edges;
		this->m_adjacency = g.m_adjacency;
		this->m_degree = g.m_degree;
		this->m_visited = g.m_visited;
	}

	Graph & Graph::operator=(const Graph & g) {
		this->m_vertices = g.m_vertices;
		this->m_edges = g.m_edges;
		this->m_adjacency = g.m_adjacency;
		this->m_degree = g.m_degree;
		this->m_visited = g.m_visited;
		return *this;
	}

	bool Graph::operator==(const Graph & g) {
		if (this->m_vertices != g.m_vertices) return false;
		if (this->m_edges != g.m_edges) return false;
		if (this->m_adjacency != g.m_adjacency) return false;
		if (this->m_degree != g.m_degree) return false;
		return true;
	}

	bool Graph::operator!=(const Graph & g) {
		return !(*this == g);
	}

	void Graph::resetVisited() {
		for (int i = 0; i < m_vertices; i++) {
			m_visited[i] = false;
		}
	}

	void Graph::print() {
		resetVisited();  
		dfs(0, &Graph::printPath);
		std::cout << std::endl;
	}

	void Graph::dfs(int i, action a) {
		m_visited[i] = true;
		std::vector<int> adj_i = m_adjacency[i];
		(this->*a)(i);
		for (auto adj : adj_i) {
			if (!m_visited[adj])
				dfs(adj, a);
		}
	}

	void Graph::bfs(int i, action a) {

	}

	void Graph::addEdge(int v, int e) {
		assert(v >= 0 && v < m_vertices);
		assert(e >= 0 && e < m_vertices);
		m_adjacency[e].push_back(v);
		m_adjacency[v].push_back(e);		
		m_degree[v]++;
		m_degree[e]++;
		m_edges++;
	}

	std::string Graph::toString() const {
		std::string s;
		for (int i = 0; i < m_vertices; i++) {
			for (auto j : m_adjacency[i]) {
				if (i < j) {
					s += std::to_string(i) + "--" + std::to_string(j) + "\n";
				}
			}
		}
		return s;
	}

	bool Graph::isBipartite() {
		std::vector<int> colors(m_vertices, -1);
		resetVisited();
		for (int i = 0; i < m_vertices; i++) {
			if (!m_visited[i]) {
				m_visited[i] = true;
				colors[i] = 1;
				Queue<int> q;
				q.enqueue(i);
				while (!q.isEmpty()) {
					int j = q.front();
					q.dequeue();
					for (auto c : adj(j)) {
						if (c == j)
							return false;
						if (colors[c] == -1) {
							colors[c] = 1 - colors[j];
							m_visited[c] = true;
							q.enqueue(c);
						}
						else if (colors[c] == colors[j])
							return false;
					}
				}
			}
		}
		return true;
	}

	int Graph::components() {
		int components = 0;
		resetVisited();
		for (int i = 0; i < m_vertices; i++) {
			if (!m_visited[i]) {
				components++;
				dfs(i);
			}
		}
		return components;
	}
}