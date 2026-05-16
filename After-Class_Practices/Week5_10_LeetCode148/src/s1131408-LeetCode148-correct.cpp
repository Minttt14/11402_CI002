class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next){
            return head;
        }
        
        vector<int> values;
        ListNode* cur = head;
        while(cur){
            values.push_back(cur->val);
            cur = cur->next;
        }
        
        sort(values.begin(), values.end());
        
        cur = head;
        int i = 0;
        while(cur){
            cur->val = values[i];
            i++;
            cur = cur->next;
        }
        return head; 
    }
};