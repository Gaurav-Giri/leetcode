class Solution {
public:
    long long solveOrder(vector<int>& startA, vector<int>& durA,
                         vector<int>& startB, vector<int>& durB) {
        int m = startB.size();

        vector<pair<int,int>> ridesB;
        for (int i = 0; i < m; i++) {
            ridesB.push_back({startB[i], durB[i]});
        }

        sort(ridesB.begin(), ridesB.end());

        vector<int> starts(m);
        vector<long long> prefMinDur(m);
        vector<long long> suffMinFinish(m);

        for (int i = 0; i < m; i++) {
            starts[i] = ridesB[i].first;

            if (i == 0)
                prefMinDur[i] = ridesB[i].second;
            else
                prefMinDur[i] = min(prefMinDur[i - 1],
                                    (long long)ridesB[i].second);
        }

        for (int i = m - 1; i >= 0; i--) {
            long long val =
                (long long)ridesB[i].first + ridesB[i].second;

            if (i == m - 1)
                suffMinFinish[i] = val;
            else
                suffMinFinish[i] = min(suffMinFinish[i + 1], val);
        }

        long long ans = LLONG_MAX;

        int n = startA.size();

        for (int i = 0; i < n; i++) {
            long long t = (long long)startA[i] + durA[i];

            int pos = upper_bound(starts.begin(), starts.end(), t)
                      - starts.begin();

            long long best = LLONG_MAX;

            // starts <= t
            if (pos > 0) {
                best = min(best,
                           t + prefMinDur[pos - 1]);
            }

            // starts > t
            if (pos < m) {
                best = min(best,
                           suffMinFinish[pos]);
            }

            ans = min(ans, best);
        }

        return ans;
    }

    long long earliestFinishTime(vector<int>& landStartTime,
                                 vector<int>& landDuration,
                                 vector<int>& waterStartTime,
                                 vector<int>& waterDuration) {

        long long ans1 = solveOrder(
            landStartTime, landDuration,
            waterStartTime, waterDuration
        ); // land -> water

        long long ans2 = solveOrder(
            waterStartTime, waterDuration,
            landStartTime, landDuration
        ); // water -> land

        return min(ans1, ans2);
    }
};
