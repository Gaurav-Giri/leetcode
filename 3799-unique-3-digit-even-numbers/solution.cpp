class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        // Count the frequency of each digit in the given array
        vector<int> availableCount(10, 0);
        for (int d : digits) {
            availableCount[d]++;
        }
        
        int matchCount = 0;
        
        // Loop through all possible 3-digit even numbers
        for (int num = 100; num <= 999; num += 2) {
            int d3 = num % 10;          // Units digit
            int d2 = (num / 10) % 10;   // Tens digit
            int d1 = num / 100;         // Hundreds digit
            
            // Count frequencies required for the current number
            vector<int> requiredCount(10, 0);
            requiredCount[d1]++;
            requiredCount[d2]++;
            requiredCount[d3]++;
            
            // Verify if we have enough available digits to form 'num'
            bool canForm = true;
            for (int i = 0; i < 10; ++i) {
                if (requiredCount[i] > availableCount[i]) {
                    canForm = false;
                    break;
                }
            }
            
            if (canForm) {
                matchCount++;
            }
        }
        
        return matchCount;
    }
};

