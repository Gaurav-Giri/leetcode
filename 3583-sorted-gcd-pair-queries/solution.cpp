class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<long long> freq(mx + 1, 0);
        for (int x : nums) {
            freq[x]++;
        }

        // cntDiv[d] = how many numbers are divisible by d
        vector<long long> cntDiv(mx + 1, 0);
        for (int d = 1; d <= mx; d++) {
            for (int multiple = d; multiple <= mx; multiple += d) {
                cntDiv[d] += freq[multiple];
            }
        }

        // exactGcd[g] = number of pairs whose gcd is exactly g
        vector<long long> exactGcd(mx + 1, 0);

        for (int g = mx; g >= 1; g--) {
            long long pairs = cntDiv[g] * (cntDiv[g] - 1) / 2;

            for (int multiple = 2 * g; multiple <= mx; multiple += g) {
                pairs -= exactGcd[multiple];
            }

            exactGcd[g] = pairs;
        }

        // Prefix count of gcd values in sorted gcdPairs
        vector<long long> prefix(mx + 1, 0);
        for (int g = 1; g <= mx; g++) {
            prefix[g] = prefix[g - 1] + exactGcd[g];
        }

        vector<int> answer;
        answer.reserve(queries.size());

        for (long long q : queries) {
            // Find smallest gcd value g such that
            // number of elements <= g is greater than q
            int g = lower_bound(prefix.begin() + 1, prefix.end(), q + 1) - prefix.begin();
            answer.push_back(g);
        }

        return answer;
    }
};
