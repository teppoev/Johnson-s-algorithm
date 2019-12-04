#pragma once
#include "graph.h"

struct Node {
	int key, degree;
	Vertex* vertex;
	Node *parent, *child, *left, *right;
	bool mark;
};

struct Fib_Heap {
	Node *min;
	int n;
};

Fib_Heap* Make_Fib_Heap();

void Fib_Heap_Insert(Fib_Heap *H, Node *x);

Node* Fib_Heap_Minimum(Fib_Heap *H);

Fib_Heap* Fib_Heap_Union(Fib_Heap *H1, Fib_Heap *H2);

Node* Fib_Heap_Extract_Min(Fib_Heap *H);

void Fib_Heap_Change_Key(Fib_Heap *H, Node *x, int newKey);

void Fib_Heap_Delete(Fib_Heap *H, Node *x);