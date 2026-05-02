class Solution {
public:
    int rotatedDigits(int n) {
        // Allowed digits for valid rotation
        unordered_set<char> valid_digits = {'0', '1', '2', '5', '6', '8', '9'};
        // Digits that change after rotation
        unordered_set<char> changing_digits = {'2', '5', '6', '9'};
        
        int count = 0;
        
        for (int num = 1; num <= n; num++) {
            string num_str = to_string(num);
            
            // Check if all digits are valid
            bool all_valid = true;
            for (char digit : num_str) {
                if (valid_digits.find(digit) == valid_digits.end()) {
                    all_valid = false;
                    break;
                }
            }
            
            if (all_valid) {
                // Check if at least one digit changes after rotation
                bool has_changing = false;
                for (char digit : num_str) {
                    if (changing_digits.find(digit) != changing_digits.end()) {
                        has_changing = true;
                        break;
                    }
                }
                
                if (has_changing) {
                    count++;
                }
            }
        }
        
        return count;
    }
};
