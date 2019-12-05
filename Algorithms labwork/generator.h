#pragma once
#include<list>
#include "graph.h"

void generate(int& n, int& m, int min_n, int max_n, int min_m, int max_m);

int** generate(int n, int m);

//int** generate1(int& n, int& m);

void fromMatrixToGraph(int n, int m, int** matrix, std::list<Vertex*>& vertices, std::list<Arc*>& edges);

void fromGraphToMatrix(std::list<Vertex*> vertices, std::list<Arc*> edges, int& n, int& m, int** matrix);