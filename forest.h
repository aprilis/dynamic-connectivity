#include <optional>
#include <utility>
#include <vector>
#include <unordered_map>
#include "treap.h"

class Forest 
{
    //type of elements stored in nodes (Andrzej mozesz zmienic jesli chcesz)
    typedef int T;

    vector<unordered_map<int, treap*>> edges;
    vector<treap*> repr;
    vector<vector<T>> storage;

    void setRepr(int v);

public:
    //creates a forest with isolated nodes 1 .. n
    Forest(int n);
    
    ~Forest();
    
    //returns the number of vertices in the same tree as v
    int getSize(int v);

    void addEdge(int a, int b);
    void removeEdge(int a, int b);

    //returns true if there is edge between a and b in the forest
    bool hasEdge(int a, int b);

    bool sameTree(int a, int b);

    //store element x in node v
    void store(int v, T x);

    //get any element stored in a vertex connected to v and remove it
    std::optional<T> get(int v);
};
