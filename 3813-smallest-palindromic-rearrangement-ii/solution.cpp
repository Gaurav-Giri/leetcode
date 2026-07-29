class Solution {
public:
    static const long long LIM = 1000001;

    long long comb(int n, int r) {
        if (r > n) return 0;
        r = min(r, n - r);

        long long res = 1;
        for (int i = 1; i <= r; i++) {
            res = res * (n - r + i) / i;
            if (res > LIM) return LIM;
        }
        return res;
    }

    long long countWays(vector<int>& cnt) {
        int total = 0;
        for (int x : cnt) total += x;

        long long ans = 1;
        int rem = total;

        for (int x : cnt) {
            if (x == 0) continue;
            ans *= comb(rem, x);
            if (ans > LIM) return LIM;
            rem -= x;
        }

        return min(ans, LIM);
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        string mid = "";

        vector<int> half(26, 0);
        for (int i = 0; i < 26; i++) {
            if (freq[i] & 1)
                mid.push_back('a' + i);

            half[i] = freq[i] / 2;
        }

        int halfLen = 0;
        for (int x : half) halfLen += x;

        long long totalPal = countWays(half);
        if (totalPal < k) return "";

        string left;

        for (int pos = 0; pos < halfLen; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0) continue;

                half[c]--;

                long long ways = countWays(half);

                if (ways >= k) {
                    left.push_back('a' + c);
                    break;
                }

                k -= ways;
                half[c]++;
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        return left + mid + right;
    }
};
