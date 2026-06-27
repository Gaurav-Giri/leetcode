class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> freq;

        for (int x : nums)
            freq[x]++;

        int ans = 1;

        // Special case for 1
        if (freq.count(1))
            ans = max(ans, (freq[1] & 1) ? freq[1] : freq[1] - 1);

        for (auto &[x, cnt] : freq) {
            if (x == 1) continue;

            long long cur = x;
            int len = 1;   // current number as the center

            while (freq[cur] >= 2) {
                if (cur > 1000000000LL / cur) break;

                long long nxt = cur * cur;

                if (!freq.count(nxt))
                    break;

                len += 2;
                cur = nxt;
            }

            ans = max(ans, len);
        }

        return ans;
    }
};
