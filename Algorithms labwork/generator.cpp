#include <vector>
#include "generator.h"

void generate(int& n, int& m, int min_n, int max_n, int min_m, int max_m) {
	n = rand() % (max_n - min_n + 1) + min_n;
	m = rand() % (max_m - min_m + 1) + min_m;
}

int** generate(int n, int m) {
	int** matrix = new int* [n];
	for (int i = 0; i < n; ++i) {
		matrix[i] = new int[n];
		for (int j = 0; j < n; ++j) {
			matrix[i][j] = i == j ? 0 : NORIBS;
		}
	}

	for (int k = 0; k < m; ++k) {
		int i, j;
		do {
			i = rand() % n;
			j = rand() % n;
		} while (i == j || matrix[i][j] != NORIBS);
		matrix[i][j] = rand() % 21;
		//matrix[i][j] = rand() % 21 - 5;
	}

	return matrix;
}

/*int** generate1(int& n, int& m) {
	n = 3; m = 2;
	int** matrix = new int* [n];
	for (int i = 0; i < n; ++i) {
		matrix[i] = new int[n];
	}
	matrix[0][0] = 0; matrix[0][1] = NORIBS; matrix[0][2] = -2; //matrix[0][3] = NORIBS; matrix[0][4] = -4;
	matrix[1][0] = NORIBS; matrix[1][1] = 0; matrix[1][2] = NORIBS; //matrix[1][3] = 12; matrix[1][4] = NORIBS;
	matrix[2][0] = -2; matrix[2][1] = NORIBS; matrix[2][2] = 0; //matrix[2][3] = NORIBS; matrix[2][4] = NORIBS;
	//matrix[3][0] = 0; matrix[3][1] = 8; matrix[3][2] = 6; matrix[3][3] = 0; matrix[3][4] = NORIBS;
	//matrix[4][0] = NORIBS; matrix[4][1] = 14; matrix[4][2] = 14; matrix[4][3] = NORIBS; matrix[4][4] = 0;
	return matrix;
}*/

void fromMatrixToGraph(int n, int m, int** matrix, std::list<Vertex*>& vertices, std::list<Arc*>& edges) {
	vertices.clear(); edges.clear();
	std::vector<Vertex*> _vertices;
	Arc* edge; Vertex* begin, * end;
	for (int i = 0; i < n; ++i) {
		begin = new Vertex();
		begin->id = (i + 1);
		_vertices.push_back(begin);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (matrix[i][j] != NORIBS && i != j) {
				begin = _vertices[i];
				end = _vertices[j];
				edge = new Arc();
				edge->begin = begin;
				edge->end = end;
				edge->weight = matrix[i][j];
				begin->incidentArcs.push_back(edge);
				edges.push_back(edge);
			}
		}
	}
	for (auto vertex : _vertices) {
		vertices.push_back(vertex);
	}
	_vertices.clear();
}

void fromGraphToMatrix(std::list<Vertex*> vertices, std::list<Arc*> edges, int& n, int& m, int** matrix) {
	n = vertices.size();
	m = edges.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			matrix[i][j] = i == j ? 0 : NORIBS;
		}
	}
	for (Arc* var : edges) {
		matrix[var->begin->id - 1][var->end->id - 1] = var->weight;
	}
}