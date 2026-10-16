class Solution {
private:
    int n;
    long long kMod = 1e9 + 7;
    vector<long long> treeSum;
    vector<long long> treeSqSum;
    vector<long long> lazy;

    void propagate(int node, int start, int end) {
        if (lazy[node] == 0) return;

        long long val = lazy[node];
        long long len = end - start + 1;

        // Formula: (x + val)^2 = x^2 + 2*val*x + val^2 * len
        treeSqSum[node] = (treeSqSum[node] + 2 * val * treeSum[node] % kMod + val * val % kMod * len % kMod) % kMod;
        treeSum[node] = (treeSum[node] + val * len) % kMod;

        if (start != end) {
            lazy[2 * node + 1] = (lazy[2 * node + 1] + val) % kMod;
            lazy[2 * node + 2] = (lazy[2 * node + 2] + val) % kMod;
        }
        lazy[node] = 0;
    }

    void updateRange(int node, int start, int end, int l, int r, long long val) {
        propagate(node, start, end);
        if (start > r || end < l) return;

        if (start >= l && end <= r) {
            lazy[node] = (lazy[node] + val) % kMod;
            propagate(node, start, end);
            return;
        }

        int mid = start + (end - start) / 2;
        updateRange(2 * node + 1, start, mid, l, r, val);
        updateRange(2 * node + 2, mid + 1, end, l, r, val);

        treeSum[node] = (treeSum[2 * node + 1] + treeSum[2 * node + 2]) % kMod;
        treeSqSum[node] = (treeSqSum[2 * node + 1] + treeSqSum[2 * node + 2]) % kMod;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        treeSum.assign(4 * n, 0);
        treeSqSum.assign(4 * n, 0);
        lazy.assign(4 * n, 0);

        unordered_map<int, int> lastPos;
        long long totalSum = 0;

        for (int i = 0; i < n; ++i) {
            // Find the boundary where the current element has already contributed +1
            int leftIdx = lastPos.count(nums[i]) ? lastPos[nums[i]] + 1 : 0;
            
            // Add 1 to the distinct counts of all valid subarrays ending at index i
            updateRange(0, 0, n - 1, leftIdx, i, 1);
            
            // Accumulate the current aggregate sum of squares from the root node
            totalSum = (totalSum + treeSqSum[0]) % kMod;
            
            // Update the history map
            lastPos[nums[i]] = i;
        }

        return totalSum;
    }
};

