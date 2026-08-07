#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string smallestNumber(string num, long long t) {
        const auto [primeCount, isDivisible] = getPrimeCount(t);

        if (!isDivisible)
            return "-1";

        const unordered_map<int, int> factorCount =
            getFactorCount(primeCount);

        if (sumValues(factorCount) > (int)num.length())
            return construct(factorCount);

        unordered_map<int, int> primeCountPrefix =
            getPrimeCount(num);

        int firstZeroIndex = num.find('0');

        if (firstZeroIndex == (int)string::npos) {
            firstZeroIndex = num.length();

            if (isSubset(primeCount, primeCountPrefix))
                return num;
        }

        for (int i = (int)num.length() - 1; i >= 0; --i) {
            const int d = num[i] - '0';

            // Remove the current digit's factors.
            primeCountPrefix =
                subtract(primeCountPrefix, kFactorCounts.at(d));

            const int spaceAfterThisDigit =
                (int)num.length() - 1 - i;

            if (i > firstZeroIndex)
                continue;

            for (int biggerDigit = d + 1;
                 biggerDigit < 10;
                 ++biggerDigit) {

                // Factors still required after keeping the prefix
                // and choosing biggerDigit.
                const unordered_map<int, int> factorsAfterReplacement =
                    getFactorCount(
                        subtract(
                            subtract(primeCount, primeCountPrefix),
                            kFactorCounts.at(biggerDigit)
                        )
                    );

                if (sumValues(factorsAfterReplacement)
                    <= spaceAfterThisDigit) {

                    const int fillOnes =
                        spaceAfterThisDigit -
                        sumValues(factorsAfterReplacement);

                    return num.substr(0, i) +
                           to_string(biggerDigit) +
                           string(fillOnes, '1') +
                           construct(factorsAfterReplacement);
                }
            }
        }

        // No solution of the same length.
        // Extend the number by one digit.
        const unordered_map<int, int> factorsAfterExtension =
            getFactorCount(primeCount);

        int required = sumValues(factorsAfterExtension);

        if (required > (int)num.length() + 1)
            return "-1";

        return string(
                   num.length() + 1 - required,
                   '1'
               ) +
               construct(factorsAfterExtension);
    }

private:

    // Prime factors of each digit.
    static const unordered_map<int, unordered_map<int, int>>
        kFactorCounts;

    // Returns prime factor counts of t and whether
    // t contains only 2, 3, 5 and 7.
    pair<unordered_map<int, int>, bool>
    getPrimeCount(long long t) {

        unordered_map<int, int> count{
            {2, 0},
            {3, 0},
            {5, 0},
            {7, 0}
        };

        for (int prime : {2, 3, 5, 7}) {
            while (t % prime == 0) {
                t /= prime;
                ++count[prime];
            }
        }

        return {count, t == 1};
    }

    // Returns prime factor counts of num.
    unordered_map<int, int>
    getPrimeCount(const string& num) {

        unordered_map<int, int> count{
            {2, 0},
            {3, 0},
            {5, 0},
            {7, 0}
        };

        for (char d : num) {
            for (const auto& [prime, freq] :
                 kFactorCounts.at(d - '0')) {

                count[prime] += freq;
            }
        }

        return count;
    }

    // Converts prime factor counts into the minimum
    // number of digits needed.
    unordered_map<int, int>
    getFactorCount(
        const unordered_map<int, int>& count
    ) {
        unordered_map<int, int> res;

        // 2^3 = 8
        const int count8 = count.at(2) / 3;
        const int remaining2 = count.at(2) % 3;

        // 3^2 = 9
        const int count9 = count.at(3) / 2;
        int count3 = count.at(3) % 2;

        // 2^2 = 4
        int count4 = remaining2 / 2;
        int count2 = remaining2 % 2;

        // Combine 2 and 3 into 6.
        int count6 = 0;

        if (count2 == 1 && count3 == 1) {
            count2 = 0;
            count3 = 0;
            count6 = 1;
        }

        // Combine 3 and 4 into 2 and 6.
        if (count3 == 1 && count4 == 1) {
            count2 = 1;
            count6 = 1;
            count3 = 0;
            count4 = 0;
        }

        return {
            {2, count2},
            {3, count3},
            {4, count4},
            {5, count.at(5)},
            {6, count6},
            {7, count.at(7)},
            {8, count8},
            {9, count9}
        };
    }

    // Construct digits in increasing order.
    string construct(
        const unordered_map<int, int>& factors
    ) {
        string res;

        for (int digit = 2; digit < 10; ++digit) {
            res += string(
                factors.at(digit),
                char('0' + digit)
            );
        }

        return res;
    }

    // Returns true if every required factor in a
    // is available in b.
    bool isSubset(
        const unordered_map<int, int>& a,
        const unordered_map<int, int>& b
    ) {
        for (const auto& [key, value] : a) {
            if (b.at(key) < value)
                return false;
        }

        return true;
    }

    // Returns max(a - b, 0) for every factor.
    unordered_map<int, int> subtract(
        unordered_map<int, int> a,
        const unordered_map<int, int>& b
    ) {
        for (const auto& [key, value] : b) {
            a[key] = max(0, a[key] - value);
        }

        return a;
    }

    // Sum all factor counts.
    int sumValues(
        const unordered_map<int, int>& count
    ) {
        int result = 0;

        for (const auto& [key, value] : count)
            result += value;

        return result;
    }
};

// Definition of the static factor table.
const unordered_map<int, unordered_map<int, int>>
Solution::kFactorCounts = {
    {0, {}},
    {1, {}},
    {2, {{2, 1}}},
    {3, {{3, 1}}},
    {4, {{2, 2}}},
    {5, {{5, 1}}},
    {6, {{2, 1}, {3, 1}}},
    {7, {{7, 1}}},
    {8, {{2, 3}}},
    {9, {{3, 2}}}
};
