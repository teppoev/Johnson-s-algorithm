#include <iostream>
#include <ctime>
#include <cstdlib>
#include "fibheap.h"
#include "generator.h"
#include "graph.h"
#include "jalgorithms.h"

void print(int n, int m, int** matrix);

void test();

int main() {
	srand(time(NULL));

	test();

	return 0;
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

void test() {
	const int NUM_OF_TESTS = 10;
	const int MIN_N = 100, MAX_N = 1000, STEP_N = 100;
	const int MIN_M = 0, MAX_M = 9000, STEP_M = 1000;

	unsigned long midDuration; //with graphs with negative-weight cycles;
	//unsigned long midDuration1; //without graphs with negative-weight cycles;
	//int numOfGraphsWNWC; //without negative-weight cycles

	for (int n = MIN_N; n < MAX_N + 1; n += STEP_N) {
		for (int m = MIN_M; m < MAX_M + 1; m += STEP_M) {
			int** matrix;
			std::list<Vertex*> vertices;
			std::list<Arc*> edges;

			//numOfGraphsWNWC = 0;
			midDuration = 0UL;
			//midDuration1 = 0UL;

			for (int i = 0; i < NUM_OF_TESTS; ++i) {
				matrix = generate(n, m);
				fromMatrixToGraph(n, m, matrix, vertices, edges);

				unsigned long time = clock();
				int** D = JohnsonSPF(vertices, edges);
				time = clock() - time;

				midDuration += time;
				/*if (D) {
					++numOfGraphsWNWC;
					midDuration1 += time;
				}*/
				delete[] matrix;
				delete[] D;
			}

			std::cout << "N = " << n << "; M = " << m << ";\r\nAverage time = " << midDuration / NUM_OF_TESTS;
			/*std::cout << " ms;\r\nGraphs without neg-w cycles: " << numOfGraphsWNWC;
			if (numOfGraphsWNWC) std::cout << ";\r\nAverage time for those graphs: " << midDuration1 / numOfGraphsWNWC << " ms";
			std::cout << ".\r\n\r\n";*/
			std::cout << " ms.\r\n\r\n";
		}
		std::cout << std::endl;
	}
}