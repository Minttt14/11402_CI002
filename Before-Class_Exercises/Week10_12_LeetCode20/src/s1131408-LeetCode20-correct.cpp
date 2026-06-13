class Solution {
public:
    bool isValid(string s){
        if(s.length() % 2 != 0) return false;
        
        stack<char> st;
        
        for(char c : s){
            if(c == '(' || c == '[' || c == '{') st.push(c);
            else{
                if(st.empty()) return false;
                
                char top = st.top();
                
                if(c == ')' && top != '(') return false; 
                else if(c == ']' && top != '[') return false; 
                else if(c == '}' && top != '{') return false; 

                st.pop();
            }
        }
        return st.empty();
    }
};