#include "forest.h"
#include <cassert>
using namespace std;

treap* make_first(treap *t)
{
    if(!t) return nullptr;
    int ind = t->index();
    auto [a, b] = split(t->root(), ind);
    return merge(b, a);
}

treap* root(treap *t)
{
    return t ? t->root() : nullptr;
}

void Forest::setRepr(int v)
{
    treap *r = edges[v].empty() ? nullptr : edges[v].begin()->second;
    repr[v] = r;
    if(r && !storage[v].empty()) r->setValue(v);
}

Forest::Forest(int n) : edges(n + 1), repr(n + 1), storage(n + 1)
{

}

Forest::~Forest()
{
    for(auto &v: edges)
        for(auto [_, e]: v)
            delete e;
}

void Forest::addEdge(int a, int b)
{
    auto ab = new treap, ba = new treap;
    edges[a][b] = ab;
    edges[b][a] = ba;
    auto ra = make_first(repr[a]), rb = make_first(repr[b]);
    merge(merge(ra, ab), merge(rb, ba));
    if(!repr[a]) setRepr(a);
    if(!repr[b]) setRepr(b);
}

void Forest::removeEdge(int a, int b)
{
    auto ab = edges[a][b], ba = edges[b][a];
    edges[a].erase(b);
    edges[b].erase(a);
    auto i1 = ab->index(), i2 = ba->index();
    if(i1 > i2) swap(i1, i2);
    auto r = ab->root();
    auto [r12, pr3] = split(r, i2);
    auto [r1, pr2] = split(r12, i1);
    auto [s1, r2] = split(pr2, 1);
    auto [s2, r3] = split(pr3, 1);
    assert((s1 == ab && s2 == ba) || (s1 == ba && s2 == ab));
    merge(r1, r3);
    if(repr[a] == ab) setRepr(a);
    if(repr[b] == ba) setRepr(b);
    delete ab;
    delete ba;
}

int Forest::getSize(int v)
{
    return repr[v] ? (repr[v]->root()->items / 2 + 1) : 1;
}

bool Forest::hasEdge(int a, int b)
{
    return edges[a].count(b);
}

bool Forest::sameTree(int a, int b)
{
    if(!repr[a] || !repr[b]) return false;
    return repr[a]->root() == repr[b]->root();
}

void Forest::store(int v, T x)
{
    storage[v].push_back(x);
    if(storage[v].size() == 1 && repr[v]) repr[v]->setValue(v);
}

optional<Forest::T> Forest::get(int v)
{
    if(v == 0) return {};
    if(storage[v].empty())
        return repr[v] ? get(repr[v]->root()->max_value) : nullopt;
    T ans = storage[v].back();
    storage[v].pop_back();
    if(repr[v] && storage[v].empty())
        repr[v]->setValue(0);
    return ans;
}