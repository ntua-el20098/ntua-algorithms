#include <iostream>  
#include <vector>  
#include <algorithm>  
  
using namespace std;  
  
int maxProfit(int N, int K, const vector<int>& prices) {  
    vector<int> dp(N, 0);  
  
    for (int k = 1; k <= K; ++k) {  
        int maxDiff = -prices[0];  
  
        for (int i = 1; i < N; ++i) {  
            int temp = dp[i];  // Store the value before updating dp[i]  
            dp[i] = max(dp[i - 1], prices[i] + maxDiff);  
            maxDiff = max(maxDiff, temp - prices[i]);  
        }  
    }  
  
    return dp[N - 1];  
}  
  
int main() {  
    int N, K;  
    cin >> N >> K;  
  
    vector<int> prices(N);  
    for (int i = 0; i < N; ++i) {  
        cin >> prices[i];  
    }  
  
    int result = maxProfit(N, K, prices);  
  
    cout << result << endl;  
  
    return 0;  
}