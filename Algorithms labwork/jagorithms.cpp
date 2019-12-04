#include "jalgorithms.h"
#include "fibheap.h"

void DijkstraSPF(std::list<Vertex*> vertices, std::list<Arc*> arcs, Vertex* source, int* d) {
	auto U = Make_Fib_Heap();
	Node** nodes = new Node * [vertices.size()];
	bool* isInFibHeap = new bool[vertices.size()];
	for (Vertex* vertex : vertices) {
		nodes[vertex->id - 1] = new Node();
		nodes[vertex->id - 1]->vertex = vertex;
		nodes[vertex->id - 1]->key = vertex->id != source->id ? _INFINITY : 0;
		isInFibHeap[vertex->id - 1] = true;
		Fib_Heap_Insert(U, nodes[vertex->id - 1]);
	}
	while (U->n > 0) {
		Node* v = Fib_Heap_Extract_Min(U);
		auto arcs = v->vertex->incidentArcs;
		if (U->n != 0) {
			for (auto edge : arcs) {
				auto u = nodes[edge->end->id - 1];
				if (isInFibHeap[u->vertex->id - 1]) {
					int newKey = v->key == _INFINITY ? _INFINITY : v->key + edge->weight;
					if (u->key > newKey)
						Fib_Heap_Change_Key(U, u, newKey);
				}
			}
		}
		d[v->vertex->id - 1] = v->key;
		isInFibHeap[v->vertex->id - 1] = false;
	}
	for (int i = 0; i < vertices.size(); ++i) delete nodes[i];
	delete[] nodes;
}

bool BellmanFordSPF(std::list<Vertex*> vertices, std::list<Arc*> arcs, Vertex* source, int* d) {
	for (Vertex* vertex : vertices) {
		d[vertex->id - 1] = vertex->id == source->id ? 0 : _INFINITY;
	}
	for (int i = 1; i < vertices.size(); ++i) {
		for (Arc* edge : arcs) {
			if (d[edge->begin->id - 1] != _INFINITY && d[edge->end->id - 1] > d[edge->begin->id - 1] + edge->weight)
				d[edge->end->id - 1] =  d[edge->begin->id - 1] + edge->weight;
		}
	}
	for (Arc* edge : arcs) {
		if (d[edge->end->id - 1] > d[edge->begin->id - 1] + edge->weight && d[edge->begin->id - 1] != _INFINITY)
			return false; //Graph contains a negative-weight cycle
	}
	return true;
}

Vertex* CreateNewGraph(std::list<Vertex*> vertices, std::list<Arc*> arcs, std::list<Vertex*>& _vertices, std::list<Arc*>& _arcs) {
	_vertices = std::list<Vertex*>(vertices);
	Vertex* s = new Vertex();
	s->id = 0;
	_vertices.push_front(s);
	_arcs = std::list<Arc*>(arcs);
	Arc* arc;
	for (auto vertex : vertices) {
		arc = new Arc();
		arc->begin = s;
		arc->end = vertex;
		arc->weight = 0;
		s->incidentArcs.push_back(arc);
		_arcs.push_back(arc);
	}
	return s;
}

int** JohnsonSPF(std::list<Vertex*> vertices, std::list<Arc*> arcs) {
	int** D = new int* [vertices.size()];
	for (int i = 0; i < vertices.size(); ++i) {
		D[i] = new int[vertices.size()];
	}

	std::list<Vertex*> _vertices; std::list<Arc*> _arcs;
	Vertex* source = CreateNewGraph(vertices, arcs, _vertices, _arcs);
	
	int* h = new int[_vertices.size()];
	if (!BellmanFordSPF(_vertices, _arcs, source, h)) {
		return nullptr; //Graph contains a negative-weight cycle
	}
	else {
		for (auto arc : _arcs) {
			arc->weight += h[arc->begin->id - 1] - h[arc->end->id - 1];
		}
		_arcs.remove_if([source](auto arc) { return arc->begin->id == source->id; });
		_vertices.remove(source);

		int* d = new int[_vertices.size()];
		for (auto u : vertices) {
			DijkstraSPF(_vertices, _arcs, u, d);
			for (auto v : vertices) {
				D[u->id - 1][v->id - 1] = d[v->id - 1] == _INFINITY ? _INFINITY : d[v->id - 1] + h[v->id - 1] - h[u->id - 1];
			}
		}
		_vertices.clear(); _arcs.clear();
		return D;
	}
}