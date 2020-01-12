#include <utility>
#include <cstdlib>
using namespace std;

struct treap
{
    typedef int T;
    treap *left = nullptr, *right = nullptr, *parent = nullptr;
    
    int rank, items = 1;
    T value, max_value;
    
    treap(T val = T()) : rank(rand()), value(val), max_value(val) { }
    
    void recalc();

    treap* root();

    int index();

    void setValue(T val);
};

inline int items(treap *t) { return t ? t->items : 0; }

pair<treap*, treap*> split(treap *t, int k);
treap* merge(treap *a, treap *b);
treap::T select(treap *t, int k);
treap* insert(treap *t, treap::T val, int k);
treap* erase(treap *t, int k);