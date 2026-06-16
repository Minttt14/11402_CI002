class MyCircularQueue {
private:
    vector<int> q;   
    int head;        
    int count;       
    int capacity;    

public:
    MyCircularQueue(int k){
        capacity = k;
        q.assign(k, 0); 
        head = 0;      
        count = 0;     
    }
    
    bool enQueue(int value){
        if (isFull()) return false; 

        int tailIndex = (head + count) % capacity;
        q[tailIndex] = value;
        count++; 
        
        return true;
    }
    
    bool deQueue(){
        if(isEmpty()) return false; 
        
        head = (head + 1) % capacity;
        count--; 
        
        return true;
    }
    
    int Front(){
        if(isEmpty()) return -1;
        return q[head];
    }
    
    int Rear(){
        if(isEmpty()) return -1;
        int tailIndex = (head + count - 1) % capacity;
        return q[tailIndex];
    }
    
    bool isEmpty(){
        return count == 0;
    }
    
    bool isFull(){
        return count == capacity;
    }
};