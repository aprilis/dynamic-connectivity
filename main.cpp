#include <bits/stdc++.h>
#include "forest.h"
using namespace std;

const int L = 20;
const int N = 1<<L; //maximal number of vertices
const int M = 1000000; //maximal number of edge insertions
class Holm {
	pair <int, int> Edge[M];
	bool Tree[M];
	int Lvl[M], n, log, id;
	//Forest FT[L], FNT[L];
	vector <Forest> FT, FNT;
	
	public:
	
	void printEdges() {
		fprintf(stderr, "Print edges: \n");
		for (int i = 0; i<id; i++) if (Lvl[i]>=0){
			fprintf(stderr, "%d: (%d %d) [%d] - lvl %d\n", i, Edge[i].first, Edge[i].second, (int)Tree[i], Lvl[i]);
		}
		fprintf(stderr, "\n");
	}

	private:

	void printSizesPriv(int f) {
		fprintf(stderr, "\nprintSizes[%d]: ", f);
		for (int i=1; i<=n; i++) {
			fprintf(stderr, "%d ", FT[f].getSize(i));
		}
		fprintf (stderr, "\n\n");
	}

	bool getTreeEdge(int f, int v, int &eId) {

		fprintf(stderr, "getTreeEdge(%d %d)\n", f, v);

		do {
			eId = FT[f].get(v).value_or(-1);
			
			fprintf(stderr, "got %d\n", eId);

			if (eId==-1) return false;
			
		}while (Lvl[eId]!=f);
		
		return true;
	}
	
	bool getNonTreeEdge(int f, int v, int &eId) {

		fprintf(stderr, "getNonTreeEdge(%d %d)\n", f, v);

		do {
			eId = FNT[f].get(v).value_or(-1);
			
			fprintf(stderr, "got %d\n", eId);

			if (eId==-1) return false;
		}while (Lvl[eId]!=f);
		
		return true;
	}
	
	void addTreeEdge(int f, int eId) {
		fprintf(stderr, "addTreeEdge(%d %d): %d %d\n", f, eId, Edge[eId].first, Edge[eId].second);

		FT[f].addEdge(Edge[eId].first, Edge[eId].second);
		FNT[f].addEdge(Edge[eId].first, Edge[eId].second);
	}
	
	/*stores and adds this tree edge */
	void storeTreeEdge(int f, int eId) {
		fprintf(stderr, "storeTreeEdge(%d %d): %d %d\n", f, eId, Edge[eId].first, Edge[eId].second);

		FT[f].store(Edge[eId].first, eId);
		FT[f].store(Edge[eId].second, eId);
		Lvl[eId] = f;
		
		addTreeEdge(f, eId);
	}
	
	void storeNonTreeEdge(int f, int eId) {
		
		fprintf(stderr, "storeNonTreeEdge(%d, %d)\n", f, eId);
		assert(!FNT[f].sameTree(!Edge[eId].first, Edge[eId].second));

		FNT[f].store(Edge[eId].first, eId);
		FNT[f].store(Edge[eId].second, eId);
		assert(Lvl[eId]==-1);
		Lvl[eId] = f;
	}
	
	void removeNonTreeEdge (int f, int eId) {
		
		fprintf(stderr, "invalidate non tree edge %d from %d", eId, f);

		assert(Lvl[eId]==f);
		Lvl[eId] = -1;
	}
	
	void removeTreeEdge(int f, int eId) {

		fprintf(stderr, "removeTreeEdge(%d %d): %d %d\n", f, eId, Edge[eId].first, Edge[eId].second);

		FT[f].removeEdge(Edge[eId].first, Edge[eId].second);
		FNT[f].removeEdge(Edge[eId].first, Edge[eId].second);
	}

	public:
	

	bool query (int a, int b) {

		fprintf(stderr,"sametree[0]: %d %d\n", a, b);

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
				removeTreeEdge(i, eId);
				
				//printSizesPriv(i);
			}
			
			/*find replacement edge */
			/* searching from the topmost level */
			
			for (int i=lvl; i>=0; i--) {

				/*find the smaller tree */
				int smaller = a, larger = b;
				if (FT[i].getSize(smaller) > FT[i].getSize(larger)) {
					swap(smaller,larger);
				}
				
				fprintf(stderr, "lvl %d: smaller: %d, bigger: %d\n", i, smaller, larger);

				int treeId, repId;
				
				/*increase the ranks of tree edges which are level i */
				while (getTreeEdge(i, smaller, treeId)) {
					storeTreeEdge(i+1, treeId);
				}
				
				while (getNonTreeEdge(i, smaller, repId)) {
					
					fprintf(stderr, "sameTree[%d]: %d %d\n", i, Edge[repId].first, Edge[repId].second);

					if (FT[i].sameTree(Edge[repId].first, Edge[repId].second)) {
						/* increase the level to pay for this operation */
						removeNonTreeEdge(i, repId);
						storeNonTreeEdge(i+1, repId);
					}
					else {
						/*I have found the replacement */

						fprintf(stderr, "Found replacement\n");

						storeTreeEdge(i, repId);
						Tree[repId] = true;
						
						/*add it on all lower levels */
						for (int lower = 0; lower < i; lower++) {
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
		
		FT.resize(log+1, Forest(n));
		FNT.resize(log+1, Forest(n));
		/*
		for (int l=0; l<=log; l++) {
			FT[l] = Forest(n);
			FNT[l] = Forest(n);
		}
		*/
	}

	void printSizes() {
		fprintf(stderr, "\nprintSizes: ");
		for (int i=1; i<=n; i++) {
			fprintf(stderr, "%d ", FT[0].getSize(i));
		}
		fprintf (stderr, "\n\n");
	}

	Holm () {};
};	

Holm DC;
int main() {
	
	/*
	n -- number of vertices numbered 1..n 
	m -- number of operations: ! a b, ? a b, X a
	add en edge between a and b, query a and b, remove the \(i\)-th added edge (0-indexed)
	*/
	
	int n, m;

	scanf ("%d %d", &n, &m);

	DC.init(n);

	
	for (int i=0; i<m; i++)
	{
		
		fprintf (stderr, "\nNowe zapytanie - %d \n", i);

		int a, b;
		char c;
		scanf (" %c", &c);
		if (c=='!') {
			scanf ("%d %d", &a, &b);
			int id = DC.addEdge(a,b);

			fprintf(stderr, "Added %d %d: id = %d\n", a, b, id);
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

		DC.printEdges();
	}
	
}
