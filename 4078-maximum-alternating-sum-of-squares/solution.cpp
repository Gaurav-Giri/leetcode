#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

class Solution {
public:
    long long maxAlternatingSum(std::vector<int>& nums) {
        // Transform each number into its square
        std::vector<long long> squares;
        for (long long x : nums) {
            squares.push_back(x * x);
        }
        
        // Sort the squares in ascending order
        std::sort(squares.begin(), squares.end());
        
        int n = squares.size();
        int k = n / 2; // Number of elements to subtract
        
        long long subtractSum = 0;
        long long addSum = 0;
        
        // First k elements go to the subtraction side
        for (int i = 0; i < k; ++i) {
            subtractSum += squares[i];
        }
        
        // Remaining elements go to the addition side
        for (int i = k; i < n; ++i) {
            addSum += squares[i];
        }
        
        return addSum - subtractSum;
    }
};

