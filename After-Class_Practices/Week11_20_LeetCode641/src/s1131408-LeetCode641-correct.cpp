class MyCircularDeque {
private:
    vector<int> q; 
    int head;        
    int count;       
    int capacity;    

public:
    MyCircularDeque(int k) {
        capacity = k;
        q.assign(k, 0);
        head = 0;
        count = 0;
    }
    
    bool insertFront(int value){
        if(isFull()) return false;
        
        head = (head - 1 + capacity) % capacity;
        q[head] = value;
        count++; 
        
        return true;
    }
    
    bool insertLast(int value){
        if (isFull()) return false;
        
        int tailIndex = (head + count) % capacity;
        q[tailIndex] = value;
        count++; 
        
        return true;
    }

    bool deleteFront(){
        if(isEmpty()) return false;
        
        head = (head + 1) % capacity;
        count--;
        
        return true;
    }

    bool deleteLast(){
        if(isEmpty()) return false;

        count--; 
        
        return true;
    }

    int getFront(){
        if(isEmpty()) return -1;
        return q[head];
    }

    int getRear(){
        if(isEmpty()) return -1;

        int tailIndex = (head + count - 1 + capacity) % capacity;
        return q[tailIndex];
    }
    
    bool isEmpty(){
        return count == 0;
    }

    bool isFull(){
        return count == capacity;
    }
};