#pragma once
#include <list>

const int NORIBS = INT_MAX;
const int _INFINITY = INT_MAX;

struct Vertex;
struct Arc;

struct Vertex {
	int id;
	std::list<Arc*> incidentArcs;
};

struct Arc {
	int weight;
	Vertex* begin;
	Vertex* end;
};