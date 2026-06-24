class Solution {
public:
    static const int MOD = 1000000007;

    struct Matrix {
        int n;
        vector<vector<long long>> a;

        Matrix(int n, bool identity = false) : n(n) {
            a.assign(n, vector<long long>(n, 0));
            if (identity) {
                for (int i = 0; i < n; i++) a[i][i] = 1;
            }
        }

        Matrix operator*(const Matrix &other) const {
            Matrix res(n);
            for (int i = 0; i < n; i++) {
                for (int k = 0; k < n; k++) {
                    if (!a[i][k]) continue;
                    for (int j = 0; j < n; j++) {
                        res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j]) % MOD;
                    }
                }
            }
            return res;
        }
    };

    Matrix power(Matrix base, long long exp) {
        int sz = base.n;
        Matrix res(sz, true);

        while (exp > 0) {
            if (exp & 1) res = res * base;
            base = base * base;
            exp >>= 1;
        }

        return res;
    }

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        Matrix U(m), D(m);

        // U[i][j] = 1 if j > i
        // D[i][j] = 1 if j < i
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) U.a[i][j] = 1;
            for (int j = 0; j < i; j++) D.a[i][j] = 1;
        }

        Matrix B = U * D;

        long long edges = n - 1;
        long long pairs = edges / 2;

        Matrix P = power(B, pairs);

        long long ans = 0;

        if (edges % 2 == 0) {
            // answer = 2 * sum(B^(edges/2))
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < m; j++) {
                    ans += P.a[i][j];
                    if (ans >= MOD) ans -= MOD;
                }
            }
            ans = (2 * ans) % MOD;
        } else {
            // answer = 2 * sum(B^(edges/2) * U)
            Matrix C = P * U;

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < m; j++) {
                    ans += C.a[i][j];
                    if (ans >= MOD) ans -= MOD;
                }
            }
            ans = (2 * ans) % MOD;
        }

        return (int)ans;
    }
};
