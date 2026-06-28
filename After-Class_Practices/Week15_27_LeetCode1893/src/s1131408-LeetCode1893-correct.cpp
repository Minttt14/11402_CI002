class Solution {
public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        for (int i = left; i <= right; i++) {
            bool isCovered = false; 
            
            for (auto& range : ranges) {
                if (i >= range[0] && i <= range[1]) {
                    isCovered = true; 
                    break;            
                }
            }

            if (!isCovered) return false;       
        }
        return true;
    }
};