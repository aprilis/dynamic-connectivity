#include <bits/stdc++.h>
using namespace std;

const int N = 1e3;
vector <int> Edge[N][N];

int main (int argc, char *argv[])
{
    if (argc!=6){
        printf ("usage: ./gen <n> <events> <queries> <blocks> <seed>\n");
        return 1;
    }
    int n = atoi(argv[1]);
    int add = atoi(argv[2]);
    int query = atoi(argv[3]);
    int blocks = atoi(argv[4]);
    int seed = atoi(argv[5]);

    srand(seed);

    printf ("%d %d\n", n, (add+query)*blocks);

    vector <pair <int, int> > ask;
    for (int i=1; i<=n; i++) for (int j=1; j<i; j++) ask.push_back({i, j});
    set <int> curr;
    int id = 0;

    int E = (int)ask.size();
    
    for (int b = 0; b< blocks; b++) {
        
        for (int i = 0; i<add; i++) {
            if (rand()%(3*n) >= (int)curr.size()) {
                int v = rand()%n+1;
                int u = rand()%n+1;

                if (u==v) {
                    if (u==1) v++;
                    else v--;
                }

                printf ("! %d %d\n", u, v);
                
                curr.insert(id++);
            }
            else
            {
                int k = rand()%(int)curr.size();
                for (int x: curr) if ((k--)==0) {
                     k = x;
                     break;
                }

                curr.erase(k);
                printf ("X %d\n", k);
            }
        }

        random_shuffle(ask.begin(), ask.end());
        for (int i=0; i<query; i++) 
        {
            printf ("? %d %d\n", ask[i%E].first, ask[i%E].second);
        }
    }
}