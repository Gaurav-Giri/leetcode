class Solution {
public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        long long MOD = 1e9 + 7;
        
        // Step 1: Precompute Pascal's Triangle for combinations (nCr % MOD)
        vector<vector<long long>> table(n + 1, vector<long long>(n + 1, 0));
        for (int i = 0; i <= n; i++) {
            table[i][0] = 1;
            for (int j = 1; j <= i; j++) {
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % MOD;
            }
        }
        
        // Step 2: Define the recursive divide-and-conquer function
        auto dfs = [&](auto& self, const vector<int>& arr) -> long long {
            int m = arr.size();
            if (m <= 2) return 1;
            
            vector<int> left, right;
            int root = arr[0];
            
            // Partition elements into left and right subtrees
            for (int i = 1; i < m; i++) {
                if (arr[i] < root) {
                    left.push_back(arr[i]);
                } else {
                    right.push_back(arr[i]);
                }
            }
            
            // Compute combinations and recursive subproblem results
            long long left_ways = self(self, left);
            long long right_ways = self(self, right);
            long long interleaving = table[m - 1][left.size()];
            
            return (((left_ways * right_ways) % MOD) * interleaving) % MOD;
        };
        
        // Step 3: Subtract 1 to exclude the original array permutation
        return (dfs(dfs, nums) - 1 + MOD) % MOD;
    }
};

