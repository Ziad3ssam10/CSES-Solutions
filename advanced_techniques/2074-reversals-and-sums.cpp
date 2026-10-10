#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template<typename T>
using orderedset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define int long long
#define ll long long
#define ld long double
#define endl '\n'
#define fast_io                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

void files() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
}


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    Node *l, *r;
    int val, sum;
    int lazy_add;
    bool rev;
    int idx;
    int sz;
    unsigned int pri;

    Node(int v,int id = 0
    ) : l(nullptr), r(nullptr), val(v), sum(v),
        lazy_add(0), rev(false), sz(1), pri(rng()), idx(id) {
    }
};

Node *root = nullptr;

inline int get_sz(Node *t) {
    return t ? t->sz : 0;
}

inline int get_sum(Node *t) {
    return t ? t->sum : 0LL;
}

void update(Node *t) {
    if (!t) return;
    t->sz = 1 + get_sz(t->l) + get_sz(t->r);
    t->sum = t->val + get_sum(t->l) + get_sum(t->r);
}

void apply_rev(Node *t) {
    if (!t) return;
    swap(t->l, t->r);
    t->rev ^= 1;
}

void apply_add(Node *t, int val) {
    if (!t) return;
    t->val += val;
    t->sum += val * t->sz;
    t->lazy_add += val;
}

void push(Node *t) {
    if (!t) return;
    if (t->rev) {
        apply_rev(t->l);
        apply_rev(t->r);
        t->rev = false;
    }
    if (t->lazy_add != 0) {
        apply_add(t->l, t->lazy_add);
        apply_add(t->r, t->lazy_add);
        t->lazy_add = 0;
    }
}

void split(Node *t, int k, Node *&x, Node *&y) {
    if (!t) {
        x = y = nullptr;
        return;
    }
    push(t);
    if (get_sz(t->l) >= k) {
        y = t;
        split(t->l, k, x, y->l);
    } else {
        x = t;
        split(t->r, k - get_sz(t->l) - 1, x->r, y);
    }
    update(t);
}

Node *merge(Node *x, Node *y) {
    if (!x || !y) return x ? x : y;
    push(x);
    push(y);
    if (x->pri > y->pri) {
        x->r = merge(x->r, y);
        update(x);
        return x;
    } else {
        y->l = merge(x, y->l);
        update(y);
        return y;
    }
}

long long range_sum(int L, int R) {
    Node *A, *B, *C;
    split(root, L - 1, A, B);
    split(B, R - L + 1, B, C);

    long long ans = get_sum(B);

    root = merge(merge(A, B), C);
    return ans;
}

void range_reverse(int L, int R) {
    Node *A, *B, *C;
    split(root, L - 1, A, B);
    split(B, R - L + 1, B, C);

    apply_rev(B);

    root = merge(merge(A, B), C);
}

void range_add(int L, int R, long long val) {
    Node *A, *B, *C;
    split(root, L - 1, A, B);
    split(B, R - L + 1, B, C);

    apply_add(B, val);

    root = merge(merge(A, B), C);
}

Node *swap_elements(int a, int b,int n) {
    if (a >= b) return root;
    int len = min(b - a, n - b + 1);
    if (len <= 0) return root;
    Node *P, *X, *Y, *Z, *S;
    Node *tmp1, *tmp2, *tmp3;
    split(root, a - 1, P, tmp1);
    split(tmp1, len, X, tmp2);
    split(tmp2, b - a - len, Y, tmp3);
    split(tmp3, len, Z, S);
    return merge(P, merge(Z, merge(Y, merge(X, S))));
}

pair<int,int> query(int idx, Node *&Root) {
    Node *A, *node, *C, *tmp;
    split(Root, idx - 1, A, tmp);
    split(tmp, 1, node, C);
    int ans = node->val;
    int temp = node->idx;
    Root = merge(A, merge(node, C));
    return {ans, temp};
}

void print_array(Node *t) {
    if (!t) return;
    push(t);
    print_array(t->l);
    cout << t->val << " ";
    print_array(t->r);
}

int getlower(int x,int n) {
    int l = 1, r = n;
    int ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (query(mid, root).first <= x) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}


int getupper(int x,int n) {
    int l = 1, r = n;
    int ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (query(mid, root).first >= x) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

void insert(int val,int idx,int n) {
    int temp = getlower(val, n);
    Node *A, *B = new Node(val, idx), *C;
    split(root, temp, A, C);
    root = merge(A, merge(B, C));
}

void clear(Node * &t) {
    if (!t) return;

    clear(t->l);
    clear(t->r);

    delete t;
    t = nullptr;
}

void solve(int tc) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        root = merge(root, new Node(x));
    }
    while (m--) {
        int t;
        cin >> t;
        int l, r;
        cin >> l >> r;
        if (t == 1) {
            range_reverse(l, r);
        }else {
            cout << range_sum(l,r) << endl;
        }
    }
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
