class SeatManager {
private:
    int marker; 
    priority_queue<int, vector<int>, greater<int>> minHeap; 

public:
    SeatManager(int n) marker = 1;
    
    int reserve(){
        if (!minHeap.empty()){
            int seat = minHeap.top();
            minHeap.pop();
            return seat;
        }      
        int seat = marker;
        marker++;
        return seat;
    }
    
    void unreserve(int seatNumber){
        minHeap.push(seatNumber);
    }
};