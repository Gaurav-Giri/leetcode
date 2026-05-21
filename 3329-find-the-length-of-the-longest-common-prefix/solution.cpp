class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        unordered_set<string> prefixes;

        // Store all prefixes of arr1 numbers
        for (int num : arr1) {
            string s = to_string(num);
            string pref = "";

            for (char c : s) {
                pref += c;
                prefixes.insert(pref);
            }
        }

        int ans = 0;

        // Check prefixes of arr2 numbers
        for (int num : arr2) {
            string s = to_string(num);
            string pref = "";

            for (char c : s) {
                pref += c;

                if (prefixes.count(pref)) {
                    ans = max(ans, (int)pref.length());
                }
            }
        }

        return ans;
    }
};
