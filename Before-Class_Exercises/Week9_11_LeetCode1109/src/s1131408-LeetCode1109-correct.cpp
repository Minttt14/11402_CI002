class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> diff(n, 0);
        
        for(const auto& booking : bookings){
            int first = booking[0] - 1;
            int last = booking[1] - 1;  
            int seats = booking[2];
            
            diff[first] += seats;
            
            if(last + 1 < n) diff[last + 1] -= seats;
        }
        
        for(int i=1; i<n; ++i){
            diff[i] += diff[i - 1];
        }
        return diff;
    }
};