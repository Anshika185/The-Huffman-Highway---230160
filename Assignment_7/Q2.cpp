#include <bits/stdc++.h>
using namespace std;

// Function to solve the complex knapsack problem
int knapsack(int N, int W, vector<int>& weights, vector<int>& values, vector<int>& dependencies, vector<int>& categories, vector<int>& limits) {
    int max_categories = *max_element(categories.begin(), categories.end()) + 1;
    int category_mask = 1 << max_categories;
    
    // dp[w][c] - maximum value achievable with weight w and category mask c
    vector<vector<int>> dp(W + 1, vector<int>(category_mask, 0));
    
    // Iterate over each item
    for (int i = 0; i < N; ++i) {
        for (int count = limits[i]; count > 0; --count) {
            for (int w = W; w >= weights[i]; --w) {
                for (int c = 0; c < category_mask; ++c) {
                    int cat = categories[i];
                    int mask = 1 << cat;
                    
                    // Ensure that the category mask is valid
                    if ((c & mask) == 0) {
                        int dep = dependencies[i];
                        if (dep == -1 || ((c & (1 << categories[dep])) != 0)) {
                            dp[w][c | mask] = max(dp[w][c | mask], dp[w - weights[i]][c] + values[i]);
                        }
                    }
                }
            }
        }
    }

    // Find the maximum value in dp[W][*] (all possible category combinations)
    int maxValue = 0;
    for (int c = 0; c < category_mask; ++c) {
        maxValue = max(maxValue, dp[W][c]);
    }

    return maxValue;
}

int main() {
    int N ;
    cout<<"Enter the number of items: ";
    cin>>N;

    int W;
    cout<< "Enter the maximum weight knapsack can hold: ";
    cin>>W;
    vector<int> weights(N), values(N), dependencies(N), categories(N), limits(N);

    cout << "Enter the weights of the items: ";
    for (int i = 0; i < N; ++i) {
        cin >> weights[i];
    }

    cout << "Enter the values of the items: ";
    for (int i = 0; i < N; ++i) {
        cin >> values[i];
    }

    cout << "Enter the dependencies of the items (use -1 if no dependency): ";
    for (int i = 0; i < N; ++i) {
        cin >> dependencies[i];
    }

    cout << "Enter the categories of the items: ";
    for (int i = 0; i < N; ++i) {
        cin >> categories[i];
    }

    cout << "Enter the maximum limits of the items: ";
    for (int i = 0; i < N; ++i) {
        cin >> limits[i];
    }

    int result = knapsack(N, W, weights, values, dependencies, categories, limits);
    cout << "Maximum Knapsack Value: " << result << endl;
    
    return 0;
}
