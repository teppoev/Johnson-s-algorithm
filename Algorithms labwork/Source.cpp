#include <iostream>
#include <ctime>
#include <cstdlib>
#include "graph.h"
#include "fibheap.h"
#include "generator.h"
#include "jalgorithms.h"

void print(int n, int m, int** matrix);

int main() {
	srand(time(NULL));

	int n, m;
	int** matrix;
	std::list<Vertex*> vertices;
	std::list<Arc*> edges;

	for (int i = 0; i < 10000; ++i) {
		matrix = generate(n, m);
		fromMatrixToGraph(n, m, matrix, vertices, edges);
		//print(n, m, matrix);
		int* d = new int[vertices.size()];
		int** D, **D1 = new int* [vertices.size()];
		bool isEqual = true;
		for (unsigned int i = 0; i < vertices.size(); ++i) {
			D1[i] = new int[vertices.size()];
		}

		/*for (Vertex* vertex : vertices) {
			DijkstraSPF(vertices, edges, vertex, d);
			for (unsigned int k = 0; k < vertices.size(); ++k) {
				std::cout << '\t';
				if (d[k] == _INFINITY) std::cout << "Inf";
				else std::cout << d[k];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;*/

		for (Vertex* vertex : vertices) {
			bool BFbool = BellmanFordSPF(vertices, edges, vertex, d);
			if (BFbool) {
				for (unsigned int k = 0; k < vertices.size(); ++k) {
					D1[vertex->id - 1][k] = d[k];
				}
			}
			else {
				D1 = nullptr; break;
			}
		}

		D = JohnsonSPF(vertices, edges);

		if (D && D1) {
			for (unsigned int i = 0; i < vertices.size(); ++i) {
				for (unsigned int j = 0; j < vertices.size(); ++j) {
					if (D[i][j] != D1[i][j]) isEqual = false;
				}
			}
			if (isEqual) {
				//std::cout << "TRUE" << std::endl;
			}
			else {
				std::cout << "FALSE" << std::endl;
				print(n, m, matrix);
				std::cout << std::endl;
			}
		}
		else if (!D && !D1) {
			//std::cout << "TRUE" << std::endl;
		}
		else {
			std::cout << "FALSE" << std::endl;
			print(n, m, matrix);
			std::cout << std::endl;
		}
		//std::cout << std::endl << std::endl;
	}
}

void print(int n, int m, int** matrix) {
	std::cout << n << " " << m << std::endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cout << '\t';
			if (matrix[i][j] != NORIBS) std::cout << matrix[i][j];
			else std::cout << "NoArcs";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}