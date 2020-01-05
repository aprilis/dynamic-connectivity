#include <bits/stdc++.h>
#include "forest.h"
using namespace std;

const int L = 4;
const int N = 1<<L; //maximal number of vertices
const int M = 100; //maximal number of edge insertions
struct Holm {
	pair <int, int> Edge[M];
	bool Valid[M];
	int Lvl[M];
	Forest FT[L], FNT[L];
	
	int n, log, id;
	void init (int _n) {
		n = _n;
		log = 0;
		id = 0;
		while ((1<<log) < n) log++;
		
		for (int l=0; l<=log; l++) {
			F[l] = Forest(n);
		}
	}
	
	bool query (int a, int b) {
		return FT[0].sameTree(a,b);
	}
	
	void removeNonTreeEdge (int f, int eId) {
		
	}
	
	void removeTreeEdge (int f, int eId) {
		
	}
	
	
	bool getTreeEdge(int f, int v, int &eId) {
		
	}
	
	bool getNonTreeEdge(int f, int v, int &eId) {
		
	}
	
	void addTreeEdge(int f, int eId) {
		
	}
	
	void addNonTreeEdge(int f, int eId) {
		
		
	}
	
	bool addEdge (int a, int b) {
		
	}
	
	void removeEdge (int eId) {
		Valid[eId] = false;
		
	}
};	

int main() {

}
