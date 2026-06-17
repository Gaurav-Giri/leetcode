class Solution {
public:
    char processStr(string s, long long k) {
        const long long LIMIT = (long long)1e15 + 1;
        int n = s.size();
        vector<long long> len(n);

        long long curLen = 0;

        // Compute length after each operation
        for (int i = 0; i < n; i++) {
            char c = s[i];

            if ('a' <= c && c <= 'z') {
                if (curLen < LIMIT) curLen++;
            }
            else if (c == '*') {
                if (curLen > 0) curLen--;
            }
            else if (c == '#') {
                curLen = min(LIMIT, curLen * 2);
            }
            // '%' does not change length

            len[i] = curLen;
        }

        if (k >= curLen) return '.';

        // Work backwards to find the kth character
        for (int i = n - 1; i >= 0; i--) {
            char c = s[i];
            long long afterLen = len[i];
            long long beforeLen = (i == 0 ? 0 : len[i - 1]);

            if ('a' <= c && c <= 'z') {
                if (k == afterLen - 1)
                    return c;
            }
            else if (c == '#') {
                if (beforeLen > 0)
                    k %= beforeLen;
            }
            else if (c == '%') {
                if (beforeLen > 0)
                    k = beforeLen - 1 - k;
            }
            // '*' needs no action because k < afterLen always
        }

        return '.';
    }
};
