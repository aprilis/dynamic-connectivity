#include <bits/stdc++.h>
using namespace std;

const int N = 1e3;
const int M = 1e6;
pair <int, int> Edge[M];
int E[N][N];
vector <int> vst;
int n;
bool dfs (int from, int to) {
    
    vst[from]++;
    if (from==to) return true;
    for (int i=1; i<=n; i++) if (vst[i]==0 && E[from][i] && dfs(i, to)) return true;
    return false;
}

int main ()
{
    int m;
    scanf ("%d %d", &n, &m);
    int id = 0;
    for (int i=0; i<m; i++)
    {
        int a, b, no;
        char c;
        scanf (" %c", &c);
        if (c=='!') {
            scanf ("%d %d", &a, &b);
            E[a][b]++;
            E[b][a]++;
            Edge[id] = {a,b};
            id++;
        }
        if (c=='?') {
            scanf ("%d %d", &a, &b);
            vst.clear();
            vst.resize(n+1, 0);
            if (dfs(a,b)) printf ("YES\n");
            else printf ("NO\n");
        }
        if (c=='X') {
            scanf ("%d", &no);
            a = Edge[no].first;
            b = Edge[no].second;
            E[a][b]--;
            E[b][a]--;
        }
    }
}