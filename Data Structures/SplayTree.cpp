#include <bits/stdc++.h>

using namespace std;

const int nn = 1e5 + 1;

int n, m, t[nn];

void update(int i, int x) {
    for( ; i <= n; i += i & -i) t[i] = max(t[i], x);
}

int get(int i) {
    int res = 0;
    for( ; i; i -= i & -i) res = max(res, t[i]);
    return res;
}

struct node {
    static node *null;
    int v = 0, c = 0;
    node *p = null, *l = null, *r = null;

    node() {};

    node(int l, int r, node *p) {
        int mid = (l + r) / 2;
        this->v = mid;
        this->c = r - l + 1;
        this->p = p;
        if (l < mid) this->l = new node(l, mid-1, this);
        else this->l = null;
        if (mid < r) this->r = new node(mid+1, r, this);
        else this->r = null;
    }

    void match(node *t, int direction) {
        if (t != null) t->p = this;
        if (this != null)
        {
            if (direction == 1) l = t; else r = t;
            c = l->c + r->c + 1;
        }
    }

    void upnode() {
        node *p1 = p, *p2 = p1->p;
        if (p2->l == p1) p2->match(this, 1); else p2->match(this, 2);
        if (this == p1->l) {
            node *t = r;
            p1->match(t, 1);
            match(p1, 2);
        }
        else {
            node *t = l;
            p1->match(t, 2);
            match(p1, 1);
        }
    }

    void splay() {
        while (p != null) {
            node *p1 = p, *p2 = p1->p;
            if (p2 != null)
                if ((p2->l == p1) == (p1->l == this)) p1->upnode();
                else upnode();
            upnode();
        }
    };

    node *find(int x) {
        if (!x || x > c) return null;
        if (x <= l->c) return l->find(x);
        x -= l->c;
        if (x == 1) return this;
        return r->find(x-1);
    }

    void cut(node *t) {
        t->p = null;
        if (t == l) l = null; else r = null;
        if (this != null) c -= t->c;
    };

    void extract() {
        if (l != null) l->extract();
        update(v, get(v-1)+1);
        if (r != null) r->extract();
    }
} *root;

node *node::null = new node();

void shuf(int i, int j) {
    node *key = root->find(i), *ir = root->find(i+1);
    if (ir != node::null) {
        ir->splay();
        node *ii = ir->l;
        ir->cut(ii);
    }
    key->splay();
    node *il = key->l;
    key->cut(il);
    ir->match(il, 1);
    if (ir != node::null) root = ir;
    else (root = il)->splay();
    if (j == n) {
        key->match(root, 1);
        root = key;
        return;
    }
    node *jj = root->find(j);
    jj->splay();
    node *jl = jj->l;
    jj->cut(jl);
    key->match(jl, 1);
    jj->match(key, 1);
    root = jj;
}

int main() {
    cin >> n >> m;
    root = new node(1, n, node::null);
    while (m--) {
        int i, j;
        cin >> i >> j;
        shuf(i, j);
    }
    root->extract();
    cout << n - get(n);
}
