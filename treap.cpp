#include "treap.h"
#include <algorithm>

void treap::recalc()
{
    items = 1;
    max_value = value;
    if(left)
    {
        items += left->items;
        max_value = max(max_value, left->max_value);
    }
    if(right)
    {
        items += right->items;
        max_value = max(max_value, right->max_value);
    }
}

treap* treap::root()
{
    return parent ? parent->root() : this;
}

int treap::index()
{
    int ans = ::items(left);
    if(parent)
    {
        ans += parent->index() + 1;
        if(parent->left == this)
            ans -= items + 1;
    }
    return ans;
}

void treap::setValue(T val)
{
    value = val;
    treap *t = this;
    while(t)
    {
        t->recalc();
        t = t->parent;
    }
}

pair<treap*, treap*> split(treap *t, int k) //dzieli na prefiks dlugosci k i reszte
{
    if(!t) return make_pair(nullptr, nullptr);
    if(items(t->left) < k)
    {
        auto p = split(t->right, k - items(t->left) - 1);
        t->right = p.first;
        if(t->right) t->right->parent = t;
        t->parent = nullptr;
        t->recalc();
        return make_pair(t, p.second);
    }
    else
    {
        auto p = split(t->left, k);
        t->left = p.second;
        if(t->left) t->left->parent = t;
        t->parent = nullptr;
        t->recalc();
        return make_pair(p.first, t);
    }
}

treap* merge(treap *a, treap *b)
{
    if(!a) return b;
    if(!b) return a;
    if(a->rank > b->rank)
    {
        a->right = merge(a->right, b);
        a->right->parent = a;
        a->recalc();
        return a;
    }
    else
    {
        b->left = merge(a, b->left);
        b->left->parent = b;
        b->recalc();
        return b;
    }
}

treap::T select(treap *t, int k) //zwraca k-ty element
{
    if(!t) return treap::T();
    int i = items(t->left);
    if(i == k) return t->value;
    if(i > k) return select(t->left, k);
    return select(t->right, k - i - 1);
}

treap* insert(treap *t, treap::T val, int k) //wstaw val na pozycje k (liczac od 0)
{
    auto p = split(t, k);
    return merge(merge(p.first, new treap(val)), p.second);
}

treap* erase(treap *t, int k)
{
    auto p1 = split(t, k);
    auto p2 = split(p1.second, 1);
    return merge(p1.first, p2.second);
}