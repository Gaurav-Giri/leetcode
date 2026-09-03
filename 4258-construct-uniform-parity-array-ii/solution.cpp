class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int min_val = INT_MAX;
        bool all_even = true;

        for (int x : nums1) {
            min_val = min(min_val, x);
            if (x % 2 != 0) {
                all_even = false;
            }
        }

        // If the smallest element is odd, every even element can be made odd
        // by subtracting this minimum odd element (even - odd = odd).
        // If the minimum is even, no element smaller than it exists, so no odd
        // number can be converted to even (odd - even = odd, odd - odd = even requires a smaller odd).
        // Hence, all numbers must already be even.
        return (min_val % 2 != 0) || all_even;
    }
};

