#include <iostream>  
#include <vector>  
#include <limits.h>  
#include <queue>  
  
using namespace std;  
  
#define max_N 8000  
#define max30_N 100000  
  
int N, pre[max30_N];  
long long p[max30_N], s[max30_N];  
vector<pair<int, int>> adj[max_N];  
vector<long long> dist, delay;  
  
void bfs(int start) {  
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;  
    pq.push({0, start});  
  
    dist[start] = 0;  
    pre[start] = -1;  
  
    while (!pq.empty()) {  
        int curr = pq.top().second;  
        long long curr_dist = pq.top().first;  
        pq.pop();  
  
        if (curr_dist > dist[curr])  
            continue;  
  
        for (const auto& edge : adj[curr]) {  
            int next = edge.first;  
            long long edge_weight = edge.second;  
  
            if (dist[curr] + edge_weight < dist[next]) {  
                dist[next] = dist[curr] + edge_weight;  
                pre[next] = curr;  
                pq.push({dist[next], next});  
            }  
        }  
    }  
}  
  
int main() {  
    scanf("%d", &N);  
  
    dist.resize(N, LLONG_MAX);  
    delay.resize(N);  
  
    for (int i = 0; i < N - 1; i++) {  
        int vi, vj, d;  
        scanf("%d %d %d", &vi, &vj, &d);  
        adj[vi - 1].emplace_back(vj - 1, d);  
        adj[vj - 1].emplace_back(vi - 1, d);  
    }  
  
    p[0] = s[0] = 0;  
  
    for (int i = 1; i < N; i++) {  
        scanf("%lld %lld", &p[i], &s[i]);  
    }  
  
    bfs(0);  
    delay[0] = 0;  
  
    for (int i = 1; i < N; i++) {  
        long long dist_v1 = p[i] + s[i] * dist[i];  
        long long dist_vj = LLONG_MAX;  
        int previous = pre[i];  
  
        while (previous >= 0) {  
            long long temp = p[i] + s[i] * (dist[i] - dist[previous]) + delay[previous];  
            previous = pre[previous];  
  
            if (temp < dist_vj)  
                dist_vj = temp;  
        }  
  
        if (dist_v1 < dist_vj)  
            delay[i] = dist_v1;  
        else  
            delay[i] = dist_vj;  
    }  
  
    for (int i = 1; i < N - 1; i++)  
        printf("%lld ", delay[i]);  
  
    printf("%lld\n", delay[N - 1]);  
    return 0;  
}