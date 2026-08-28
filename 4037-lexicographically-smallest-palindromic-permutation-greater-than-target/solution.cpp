class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        // Validate if a palindromic permutation can even be formed
        int odd_count = 0;
        int mid_idx = -1;
        for (int i = 0; i < 26; ++i) {
            if (count[i] % 2 != 0) {
                odd_count++;
                mid_idx = i;
            }
        }
        if (odd_count > 1) return "";

        // Halve the remaining frequencies to match the left half structure
        vector<int> half_count(26, 0);
        for (int i = 0; i < 26; ++i) {
            half_count[i] = count[i] / 2;
        }

        int half_len = n / 2;
        string current_half = "";
        string result = "";

        // Standard backtracking loop targeting the left half construction
        auto dfs = [&](auto& self, int idx, bool is_greater) -> bool {
            if (idx == half_len) {
                string full_str = current_half;
                if (n % 2 != 0) {
                    full_str += (char)('a' + mid_idx);
                }
                string right_half = current_half;
                reverse(right_half.begin(), right_half.end());
                full_str += right_half;

                if (full_str > target) {
                    result = full_str;
                    return true;
                }
                return false;
            }

            char min_allowed = is_greater ? 'a' : target[idx];
            for (char ch = min_allowed; ch <= 'z'; ++ch) {
                int c_idx = ch - 'a';
                if (half_count[c_idx] > 0) {
                    half_count[c_idx]--;
                    current_half.push_back(ch);

                    bool next_greater = is_greater || (ch > target[idx]);
                    if (self(self, idx + 1, next_greater)) {
                        return true;
                    }

                    // Backtrack sequence
                    current_half.pop_back();
                    half_count[c_idx]++;
                }
            }
            return false;
        };

        if (dfs(dfs, 0, false)) {
            return result;
        }
        return "";
    }
};

