#include <bits/stdc++.h>

using namespace std;

#define ll long long

class Node
{
public:
    int a;
    int b;
    int c;
    Node(int p, int q) : a(p), b(q), c(p + q) {}
    bool operator<(const Node &o2) const
    {
        return c > o2.c;
    }
};

struct CmpNodes
{
    bool operator()(const Node *n1, const Node *n2) const
    {
        return n1->c > n2->c;
    }
};

void print(priority_queue<Node *, vector<Node *>, CmpNodes> pq)
{
    while (!pq.empty())
    {
        auto top = pq.top();
        pq.pop();
        printf("a: %d; b: %d; c: %d\n", top->a, top->b, top->c);
    }
}

void solve()
{
    cout << "HI";
    priority_queue<Node *, vector<Node *>, CmpNodes> pq;
    pq.push(new Node(3, 2));
    pq.push(new Node(6, 1));
    pq.push(new Node(9, 0));
    pq.push(new Node(5, 9));
    pq.push(new Node(9, 4));
    pq.push(new Node(2, 7));
    pq.push(new Node(1, 2));
    pq.push(new Node(3, 5));
    print(pq);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++)
    {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}