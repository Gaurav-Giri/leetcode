class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        // If the required sum is impossible to achieve with 'num' digits
        if (num * 9 < sum) {
            return "";
        }
        
        // Calculate the number of 9s and the single remainder digit
        int k = sum / 9;
        int s = sum % 9;
        
        // Greedily place the 9s first to maximize value and position weight
        string ans(k, '9');
        
        // Place the remainder digit next if it is non-zero
        if (s > 0) {
            ans += to_string(s);
        }
        
        // Pad the remaining length with zeros to reach exactly 'num' digits
        ans.append(num - ans.length(), '0');
        
        return ans;
    }
};

