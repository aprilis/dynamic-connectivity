#include <bits/stdc++.h>
#include "forest.h"
using namespace std;

const int L = 4;
const int N = 1<<L; //maximal number of vertices
const int M = 100; //maximal number of edge insertions
class Holm {
	pair <int, int> Edge[M];
	bool Tree[M];
	int Lvl[M], n, log, id;
	Forest FT[L], FNT[L];
	
	bool getTreeEdge(int f, int v, int &eId) {
		do {
			eId = FNT[f].get(v).value_or(-1);
			
			if (eId==-1) return false;
			
		}while (Lvl[eId]!=f);
		
		return true;
	}
	
	bool getNonTreeEdge(int f, int v, int &eId) {	
		do {
			eId = FNT[f].get(v).value_or(-1);
			
			if (eId==-1) return false;
		}while (Lvl[eId]!=f);
		
		return true;
	}
	
	void addTreeEdge(int f, int eId) {
		
		FT[f].addEdge(Edge[eId].first, Edge[eId].second);
		FNT[f].addEdge(Edge[eId].first, Edge[eId].second);
	}
	
	void storeTreeEdge(int f, int eId) {
		FT[f].store(Edge[eId].first, eId);
		FT[f].store(Edge[eId].second, eId);
		Lvl[eId] = f;
		
		addTreeEdge(f, eId);
	}
	
	void storeNonTreeEdge(int f, int eId) {
		FNT[f].store(Edge[eId].first, eId);
		FNT[f].store(Edge[eId].second, eId);
		assert(Lvl[eId]==-1);
		Lvl[eId] = f;
	}
	
	void removeNonTreeEdge (int f, int eId) {
		Lvl[eId] = -1;
	}
	
	
	
	public:
	
	bool query (int a, int b) {
		return FT[0].sameTree(a,b);
	}
	
	bool addEdge (int a, int b) {
		Lvl[id] = -1;
		Tree[id] = false;
		Edge[id] = {a,b};
		
		bool ret = !FT[0].sameTree(a,b);
		
		if (ret) {
			storeTreeEdge(0, id);
			Tree[id] = true;
		}
		else {
			storeNonTreeEdge(0, id);
		}
		
		id++;
		return ret;
	}
	
	void removeEdge (int eId) {
		
		if (!Tree[eId]) {
			assert(Lvl[eId]>=0);
			removeNonTreeEdge(Lvl[eId], eId);
		}
		else {	/*it was a tree edge */
		
			
		}	
	}
	
	void init (int _n) {
		n = _n;
		log = 0;
		id = 0;
		while ((1<<log) < n) log++;
		
		for (int l=0; l<=log; l++) {
			FT[l] = Forest(n);
			FNT[l] = Forest(n);
		}
	}
};	

int main() {

}
