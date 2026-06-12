class NumArray{
private:
    vector<int> pre;

public:
    NumArray(vector<int>& nums){
        pre.resize(nums.size() + 1, 0);
        
        for(int i=0; i<nums.size(); ++i){
            pre[i + 1] = pre[i] + nums[i];
        }
    }
    
    int sumRange(int left, int right){
        return pre[right + 1] - pre[left];
    }
};