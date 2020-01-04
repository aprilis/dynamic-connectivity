#include <optional>
#include <utility>

class Forest 
{
    //type of elements stored in nodes (Andrzej mozesz zmienic jesli chcesz)
    typedef int T;

public:
    //creates a forest with isolated nodes 1 .. n
    Forest(int n);

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
