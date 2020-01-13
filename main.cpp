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
			eId = FT[f].get(v).value_or(-1);
			
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
		assert(Lvl[eId]==f);
		Lvl[eId] = -1;
	}
	
	
	
	public:
	
	bool query (int a, int b) {
		return FT[0].sameTree(a,b);
	}
	
	int addEdge (int a, int b) {
		Lvl[id] = -1;
		Tree[id] = false;
		Edge[id] = {a,b};
		
		if (!FT[0].sameTree(a,b)) {
			storeTreeEdge(0, id);
			Tree[id] = true;
		}
		else {
			storeNonTreeEdge(0, id);
		}
		
		return id++;
	}
	
	void removeEdge (int eId) {
		
		if (!Tree[eId]) {
			assert(Lvl[eId]>=0);
			removeNonTreeEdge(Lvl[eId], eId);
		}
		else {	/*it was a tree edge */
			
			/*erase */
			int a = Edge[eId].first;
			int b = Edge[eId].second;
			int lvl = Lvl[eId];
			Lvl[eId] = -1; //not valid anymore
			
			for (int i=0; i<=lvl; i++) {
				FT[i].removeEdge(a, b);
				FNT[i].removeEdge(a,b);
			}
			
			/*find replacement edge */
			
			for (int i=0; i<=lvl; i++) {
				
				/*find the smaller tree */
				int smaller = a, larger = b;
				if (FT[i].getSize(smaller) > FT[i].getSize(larger)) {
					swap(smaller,larger);
				}
				
				int treeId, repId;
				
				/*increase the ranks of tree edges which are level i */
				while (getTreeEdge(i, smaller, treeId)) {
					storeTreeEdge(i+1, treeId);
				}
				
				while (getNonTreeEdge(i, smaller, repId)) {
					
					if (FT[i].sameTree(Edge[repId].first, Edge[repId].second)) {
						/* increase the level to pay for this operation */
						removeNonTreeEdge(i, repId);
						storeNonTreeEdge(i+1, repId);
					}
					else {
						/*I have found the replacement */
						storeTreeEdge(i, repId);
						Tree[repId] = true;
						
						/*add it on all lower levels */
						for (int lower = 0; lower < i; i++) {
							addTreeEdge(lower, repId);
						}
						/* no need to look further */
						return;
					}
				}
			}
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

//Holm DC;
int main() {
	
	/*
	n -- number of vertices numbered 1..n 
	m -- number of operations: ! a b, ? a b, X a
	add en edge between a and b, query a and b, remove the \(i\)-th added edge (0-indexed)
	*/
	/*
	int n, m;
	scanf ("%d %d", &n, &m);
	DC.init(n);
	for (int i=0; i<m; i++)
	{
		int a, b;
		char c;
		scanf (" %c", &c);
		if (c=='!') {
			scanf ("%d %d", &a, &b);
			DC.addEdge(a,b);
		}
		if (c=='?') {
			scanf ("%d %d", &a, &b);
			if (DC.query(a, b)) printf ("YES\n");
			else printf ("NO\n");
		}
		if (c=='X') {
			scanf ("%d", &a);
			DC.removeEdge(a);
		}
	}
	*/
}
