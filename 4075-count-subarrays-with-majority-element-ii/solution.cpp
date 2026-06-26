class Solution {
public:
    struct BIT {
        int n;
        vector<int> bit;

        BIT(int sz) {
            n = sz;
            bit.assign(n + 1, 0);
        }

        void update(int idx, int val) {
            while (idx <= n) {
                bit[idx] += val;
                idx += idx & -idx;
            }
        }

        int query(int idx) {
            int res = 0;
            while (idx > 0) {
                res += bit[idx];
                idx -= idx & -idx;
            }
            return res;
        }
    };

    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();

        BIT bit(2 * n + 5);
        int offset = n + 2;

        long long ans = 0;
        int pref = 0;

        bit.update(offset, 1);

        for (int x : nums) {
            if (x == target)
                pref++;
            else
                pref--;

            ans += bit.query(pref + offset - 1);
            bit.update(pref + offset, 1);
        }

        return ans;
    }
};
