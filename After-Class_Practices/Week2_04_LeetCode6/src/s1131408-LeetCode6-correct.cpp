class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1 || numRows >= s.length()) {
            return s;
        }

        vector<string> rows(numRows);
        int currRow = 0;
        int step = 1; 

        for (char c : s) {
            rows[currRow] += c;
            
            if (currRow == 0) step = 1;      
            else if (currRow == numRows - 1) step = -1; 
            
            currRow += step;
        }

        string result = "";
        for (string row : rows) {
            result += row;
        }
        return result;
    }
};