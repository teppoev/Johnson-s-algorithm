#include "fibheap.h"

const int SIZE = 31;

Fib_Heap* Make_Fib_Heap() {
	Fib_Heap* newFH = new Fib_Heap();
	newFH->min = nullptr;
	newFH->n = 0;
	return newFH;
}

void Fib_Heap_Insert(Fib_Heap* H, Node* x) {
	if (H->min == nullptr) {
		x->left = x;
		x->right = x;
		H->min = x;
	}
	else {
		H->min->right->left = x;
		x->right = H->min->right;
		x->left = H->min;
		H->min->right = x;
		if (x->key < H->min->key)
			H->min = x;
	}
	x->parent = nullptr;
	x->mark = false;
	++H->n;
}

Node* Fib_Heap_Minimum(Fib_Heap* H) {
	return H->min;
}

void Fib_Heap_Clean(Fib_Heap* H) {
	H->min = nullptr;
	H->n = 0;
}

void Union_Root(Fib_Heap* H, Node* x2, int nodes_amount) {
	if (!x2) return;
	if (!H->min) {
		H->min = x2;
		H->n = nodes_amount;
	}
	else {
		Node* L = x2->left;
		Node* R = H->min->right;
		H->min->right = x2;
		x2->left = H->min;
		L->right = R;
		R->left = L;
		H->n += nodes_amount;
	}
}

Fib_Heap* Fib_Heap_Union(Fib_Heap* H1, Fib_Heap* H2) {
	Fib_Heap* H = Make_Fib_Heap();
	H->min = H1->min;
	H->n = H1->n;
	Union_Root(H, H2->min, H2->n);
	if (H2->min->key < H->min->key)
		H->min = H2->min;
	Fib_Heap_Clean(H1);
	Fib_Heap_Clean(H2);
	return H;
}

void Consolidate(Fib_Heap* H) {
	Node* A[SIZE];
	for (int i = 0; i < SIZE; ++i) {
		A[i] = nullptr;
	}
	Node* x = H->min;
	int init_roots = H->n;
	int max_degree = 0;
	for (int i = 0; i < init_roots; ++i) {
		int d = x->degree;
		Node* next = x->right;
		while (A[d]) {
			Node* y = A[d];
			if (y->key < x->key)
			{
				Node* tmp = x;
				x = y;
				y = tmp;
			}
			if (y->left != y) {
				y->right->left = y->left;
				y->left->right = y->right;
			}
			--H->n;
			if (x->child) {
				x->child->right->left = y;
				y->right = x->child->right;
				y->left = x->child;
				x->child->right = y;
			}
			else {
				y->left = y;
				y->right = y;
				x->child = y;
			}
			y->parent = x;
			++x->degree;
			y->mark = false;
			A[d++] = nullptr;
		}
		A[d] = x;
		if (max_degree < d) max_degree = d;
		x = next;
	}
	H->min = nullptr;
	H->n = 0;
	for (int i = 0; i <= max_degree; ++i) {
		if (A[i]) {
			Fib_Heap_Insert(H, A[i]);
		}
	}
}

Node* Fib_Heap_Extract_Min(Fib_Heap* H) {
	Node* res = H->min;
	if (res) {
		while (res->child) {
			Node* x = res->child;
			if (res->child->right == res->child) {
				res->child = nullptr;
			}
			else {
				res->child->right->left = res->child->left;
				res->child = res->child->right;
				res->child->left->right = res->child;
			}
			Fib_Heap_Insert(H, x);
			--res->degree;
		}
		if (res->left != res) {
			res->right->left = res->left;
			res->left->right = res->right;
		}
		--H->n;
		if (res->right == res)
			H->min = nullptr;
		else {
			H->min = H->min->right;
			Consolidate(H);
		}
	}
	Node* ans = res ? res : nullptr;
	return ans;
}

void Cut(Fib_Heap* H, Node* x) {
	--x->parent->degree;
	x->parent->child = x->right == x ? nullptr : x->right;
	if (x->left != x) {
		x->right->left = x->left;
		x->left->right = x->right;
	}
	Fib_Heap_Insert(H, x);
	x->mark = false;
}

void Cascading_Cut(Fib_Heap* H, Node* cur) {
	Node* par = cur->parent;
	if (par) {
		if (!cur->mark)
			cur->mark = true;
		else {
			Cut(H, cur);
			Cascading_Cut(H, par);
		}
	}
}

void Fib_Heap_Change_Key(Fib_Heap* H, Node* x, int newKey) {
	if (newKey > x->key) {
		if (H->min == x || (x->parent && x->parent->key > newKey) ) {
			//ERROR
		}
		else {
			x->key = newKey;
		}
		return;
	}
	x->key = newKey;
	Node* par = x->parent;
	if (par && x->key < par->key) {
		Cut(H, x);
		Cascading_Cut(H, par);
	}
	if (x->key < H->min->key)
		H->min = x;
}

void Fib_Heap_Delete(Fib_Heap* H, Node* x) {

}