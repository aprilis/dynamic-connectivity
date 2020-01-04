#include <bits/stdc++.h>
#include "forest.h"
using namespace std;

//doubly linked list for storing edges incident with a vertex
struct LNode {
	int id;
	LNode *nxt, *prv;
	
	void add(LNode *ptr) {
		ptr->nxt = nxt;
		nxt = ptr;
		ptr->prv = this;
	}
	void erase() { /* Assuming this not called on a head of a queue*/
		assert(id!=-1);
		prv->nxt = nxt;
		if (nxt) nxt->prv = prv;
	}
};

const int L = 4;
const int N = 1<<L; //maximal number of vertices
const int M = 100; //maximal number of edge insertions
struct Holm {
	pair <int, int> Edge[M];
	bool Valid[M];
	pair <LNode, LNode> LNodes[M];
	LNode TreeEdges[N+1][L+1], NonTreeEdes[N+1][L+1];
	Forest F[L];
	
	int n, log, id;
	
	void init (int _n) {
		n = _n;
		log = 0;
		id = 0;
		while ((1<<log) < n) log++;
		for (int i=1; i<=n; i++) for (int l=0; l<=log; l++) {
			TreeEdges[i][l] = {-1, NULL, NULL};
			NonTreeEdges[i][l] = {-1, NULL, NULL};
		}
		for (int l=0; l<=log; l++) {
			F[l] = Forest(n);
		}
	}
	
	bool query (int a, int b) {
		return F[0].sameTree(a,b);
	}
	
	void removeNonTree (int f, int eId) {
		
	}
	
	void removeTree (int f, int eId) {
		
	}
	
	void addTree(int f, int eId) {
	
	}
	
	void addNonTree(int f, int eId) {
		int a = Edge[eId].first;
		int b = Edge[eId].second;
		NonTreeEdges[a][f].add(&LNodes[eId].first);
		NonTreeEdges[b][f].add(&LNodes[eId].second);
		
		//TODO: mark those edges in F[f]
		/*
		F[f].store1(a, eId);
		F[f].store1(b, eId);
		*/
	}
	
	bool addEdge (int a, int b) {
		LNodes[id].first = {id, NULL, NULL};
		LNodes[id].second = {id, NULL, NULL};
		Edge[id] = {a,b};
		Valid[id] = true;
		
		bool ret = !F[0].sameTree(a, b);
		
		if (ret) { /* Add the edge to the biggest Forest */
			
		}
		else { /* Add a non-tree edge */
			
		}
		
		id++;
		return ret;ss
	}
	
	void removeEdge (int eId) {
		Valid[eId] = false;
	}
};	

int main() {

}
