class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() <= 1) return intervals;

        sort(intervals.begin(), intervals.end());

        vector<vector<int>> result;
        result.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); i++) {
            vector<int>& lastMerged = result.back();
            vector<int>& current = intervals[i];

            if (current[0] <= lastMerged[1]) lastMerged[1] = max(lastMerged[1], current[1]);
            else result.push_back(current);
        }
        return result;
    }
};