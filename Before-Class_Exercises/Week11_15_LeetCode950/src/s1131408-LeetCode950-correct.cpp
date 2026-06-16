class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck){
        int n = deck.size();
        sort(deck.begin(), deck.end());
        
        queue<int> q;
        for(int i=0; i<n; ++i){
            q.push(i);
        }
        
        vector<int> result(n);
        
        for(int num : deck){
            result[q.front()] = num;
            q.pop();
            
            if(!q.empty()){
                q.push(q.front());
                q.pop();
            }
        }
        return result;
    }
};