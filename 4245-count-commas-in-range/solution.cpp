class Solution {
public:
    int countCommas(int n) {
        // Since n <= 10^5, any number >= 1000 has exactly 1 comma.
        // We can instantly calculate the total count in O(1) time complexity.
        return max(0, n - 999);
    }
};

