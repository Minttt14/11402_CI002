class Solution {
public:
    int maximumSwap(int num) {
        string s = to_string(num);
        int maxNum = num;
        
        for (int i = 0; i < s.length(); i++) {
            for (int j = i + 1; j < s.length(); j++) {
                swap(s[i], s[j]);
                maxNum = max(maxNum, stoi(s));
                swap(s[i], s[j]); 
            }
        }  
        return maxNum;
    }
};