#pragma once
#include <list>
#include "graph.h"

void DijkstraSPF(std::list<Vertex*> vertices, std::list<Arc*> arcs, Vertex* source, int* d);

bool BellmanFordSPF(std::list<Vertex*> vertices, std::list<Arc*> arcs, Vertex* source, int* d);

int** JohnsonSPF(std::list<Vertex*> vertices, std::list<Arc*> arcs);