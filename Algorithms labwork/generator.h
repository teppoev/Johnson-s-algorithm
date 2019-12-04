#pragma once
#include<list>
#include "graph.h"

int** generate(int& n, int& m);

int** generate1(int& n, int& m);

void fromMatrixToGraph(int n, int m, int** matrix, std::list<Vertex*>& vertices, std::list<Arc*>& edges);

void fromGraphToMatrix(std::list<Vertex*> vertices, std::list<Arc*> edges, int& n, int& m, int** matrix);