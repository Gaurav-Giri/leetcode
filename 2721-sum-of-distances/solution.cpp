class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, vector<int>> mp;

        // Step 1: Group indices
        for (int i = 0; i < n; i++) {
            mp[nums[i]].push_back(i);
        }

        vector<long long> ans(n, 0);

        // Step 2: Process each group
        for (auto &it : mp) {
            vector<int> &v = it.second;
            int m = v.size();

            // Prefix sum
            vector<long long> prefix(m, 0);
            prefix[0] = v[0];
            for (int i = 1; i < m; i++) {
                prefix[i] = prefix[i-1] + v[i];
            }

            // Compute distances
            for (int i = 0; i < m; i++) {
                long long left = (long long)v[i] * i - (i > 0 ? prefix[i-1] : 0);
                long long right = (prefix[m-1] - prefix[i]) - (long long)v[i] * (m - i - 1);
                ans[v[i]] = left + right;
            }
        }

        return ans;
    }
};
