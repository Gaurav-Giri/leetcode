class Solution {
public:
    int numberOfSets(int n, int k) {
        int MOD = 1e9 + 7;
        
        // We need to calculate (n + k - 1) Choose (2 * k)
        long long total_elements = n + k - 1;
        long long choose_elements = 2 * k;
        
        if (choose_elements > total_elements) return 0;
        
        // DP array to calculate the row of Pascal's triangle or standard combination calculation
        // Since k can be up to 1000, 2*k can be up to 2000. 
        // We can optimize the combination calculation using modular inverse.
        return nCr(total_elements, choose_elements, MOD);
    }

private:
    // Helper function to calculate modular inverse using Fermat's Little Theorem
    long long power(long long base, long long exp, int mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        }
        return res;
    }

    long long modInverse(long long n, int mod) {
        return power(n, mod - 2, mod);
    }

    int nCr(int n, int r, int mod) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        if (r > n - r) r = n - r; // Optimize symmetry

        long long num = 1, den = 1;
        for (int i = 0; i < r; i++) {
            num = (num * (n - i)) % mod;
            den = (den * (i + 1)) % mod;
        }

        return (num * modInverse(den, mod)) % mod;
    }
};

