class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;
        
        sort(intervals.begin(), intervals.end());
        
        int removeCount = 0;       
        int prevEnd = intervals[0][1]; 
        
        for (int i = 1; i < intervals.size(); i++) {
            int currentStart = intervals[i][0];
            int currentEnd = intervals[i][1];
            
            if (currentStart >= prevEnd)  prevEnd = currentEnd;
            else {
                removeCount++;
                prevEnd = min(prevEnd, currentEnd);
            }
        } 
        return removeCount;
    }
};