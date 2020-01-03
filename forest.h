class Forest 
{
public:
    //creates a forest with isolated nodes 1 .. n
    Forest(int n);

    void addEdge(int a, int b);
    void removeEdge(int a, int b);

    bool sameTree(int a, int b);

    //store element x in node v
    void store(int v, int x);

    //get any element stored in a vertex connected to v and remove it
    //returns 0 if there are no such elements
    int get(int v);
};