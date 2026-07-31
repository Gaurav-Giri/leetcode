class Solution {
public:
    int minimumPushes(string word) {
        vector<int> freq(26, 0);

        for (char c : word)
            freq[c - 'a']++;

        sort(freq.begin(), freq.end(), greater<int>());

        long long ans = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] == 0) break;

            int cost = i / 8 + 1;   // 0-7 -> 1, 8-15 -> 2, ...
            ans += 1LL * freq[i] * cost;
        }

        return (int)ans;
    }
};
