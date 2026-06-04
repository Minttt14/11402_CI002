class Solution {
public:
    int search(vector<int>& nums, int target){
        auto it = lower_bound(nums.begin(), nums.end(), target);
        
        if(it != nums.end() && *it == target){
            return distance(nums.begin(), it);
        }
        return -1;
    }
};