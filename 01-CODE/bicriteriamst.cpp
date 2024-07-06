#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

double mid;

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
  
struct Edge
{
    int u, v, p, w;
};

class DSU
{
private:
    int *parent;
    int *rank;

public:
    DSU(int n)
    {
        parent = new int[n+2];
        rank = new int[n+2];

        for (int i = 0; i < n; i++)
        {
            parent[i] = -1;
            rank[i] = 1;
        }
    }

    // Find function
    int find(int i)
    {
        if (parent[i] == -1)
            return i;

        return parent[i] = find(parent[i]);
    }

    // Union function
    void unite(int x, int y)
    {
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2)
        {
            if (rank[s1] < rank[s2])
            {
                parent[s1] = s2;
            }
            else if (rank[s1] > rank[s2])
            {
                parent[s2] = s1;
            }
            else
            {
                parent[s2] = s1;
                rank[s1] += 1;
            }
        }
    }
};

bool compareEdges(const Edge &a, const Edge &b)
{
    return (a.p - mid * a.w) > (b.p - mid * b.w);
}

bool canConstructMST(double c, const vector<Edge> &edges, int N, int &totalProfit, int &totalWeight)
{
    DSU dsu(N);
    int selectedEdges = 0;

    for (const Edge &edge : edges)
    {
        if (dsu.find(edge.u) != dsu.find(edge.v))
        {
            dsu.unite(edge.u, edge.v);
            totalProfit += edge.p;
            totalWeight += edge.w;
            selectedEdges++;
        }

        if (selectedEdges == N - 1)
        {
            break; // We have constructed the MST
        }
    }
    //cout << totalProfit << " " << totalWeight << endl;
    return selectedEdges == N - 1 && totalProfit - c * totalWeight > 0;
}

void printEdges(const vector<Edge>& edges) {
    cout << "Edges:\n";
    for (const Edge& edge : edges) {
        cout << edge.u << " " << edge.v << " " << edge.p << " " << edge.w << endl;
    }
}

int main()
{
    int N, M;
    //N= 4; M = 5;
    cin >> N >> M;

     vector<Edge> edges(M);
    for (int i = 0; i < M; ++i)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].p >> edges[i].w;
    }
    // edges[0].u = 1; edges[0].v = 2; edges[0].p = 2; edges[0].w = 3;
    // edges[1].u = 2; edges[1].v = 3; edges[1].p = 3; edges[1].w = 1;
    // edges[2].u = 3; edges[2].v = 4; edges[2].p = 1; edges[2].w = 2;
    // edges[3].u = 4; edges[3].v = 1; edges[3].p = 2; edges[3].w = 1;
    // edges[4].u = 2; edges[4].v = 4; edges[4].p = 4; edges[4].w = 4;

    // Binary search for the maximum c
    double left = 0, right = 200; // Maximum value for the ratio
    double epsilon = 0.00000000001;

    int lastTotalProfit, lastTotalWeight;

    while (right - left >= epsilon)
    {
        mid = (left + right) / 2;
        sort(edges.begin(), edges.end(), compareEdges);
        //printEdges(edges);

        int totalProfit = 0;
        int totalWeight = 0;
        //cout << mid << endl;
        if (canConstructMST(mid, edges, N, totalProfit, totalWeight))
        {
            left = mid;
            lastTotalProfit = totalProfit;
            lastTotalWeight = totalWeight;
            //cout << lastTotalProfit << " " << lastTotalWeight << endl;
        }
        else
        {
            right = mid;
        }
        // cout << left << " " << right << endl << endl;
    }

    // Output the final result
    int greatestCommonDivisor = gcd(lastTotalProfit, lastTotalWeight);

    cout << lastTotalProfit / greatestCommonDivisor << " " << lastTotalWeight / greatestCommonDivisor << endl;

    return 0;
}