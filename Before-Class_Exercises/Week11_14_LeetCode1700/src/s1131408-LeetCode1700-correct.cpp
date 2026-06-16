class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches){
        queue<int> q;
        for(int i : students){
            q.push(i);
        }
        
        int sandwichIdx = 0;
        int dislike = 0; 
        
        while(!q.empty() && dislike < q.size()){
            int current = q.front();
            q.pop();

            if(current == sandwiches[sandwichIdx]){
                sandwichIdx++;  
                dislike = 0; 
            } 
            else{
                q.push(current);
                dislike++;      
            }
        }
        return q.size();
    }
};