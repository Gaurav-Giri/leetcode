class Solution {
public:
    bool checkDivisibility(int n) {
        int digitSum = 0;
        int digitProduct = 1;
        int temp = n;
        
        // Extract each digit mathematically from right to left
        while (temp > 0) {
            int digit = temp % 10;
            digitSum += digit;
            digitProduct *= digit;
            temp /= 10;
        }
        
        // Return true if n is evenly divisible by the sum of its digit sum and product
        return n % (digitSum + digitProduct) == 0;
    }
};

