#include <iostream>
#include <vector>
#include <mutex>

using namespace std;

class FixedCapacityQueue {
private:
    int front, rear;
    int capacity;
    vector<int> queue;

    bool pause_;
    std::mutex mutex_;

public:
    FixedCapacityQueue(int size) {
        front = rear = -1;
        capacity = size;
        queue.resize(capacity);
        pause_ = false;
    }

    void enqueue(int item) {
        if (pause_)
            return;

        // Lock the mutex to protect access to the shared variable
        std::lock_guard<std::mutex> lock(mutex_);

        if ((front == 0 && rear == capacity - 1) || (rear == front - 1)) {
            cout << "Queue is full. Removing oldest record.\n";
            dequeue();
        }
        if (front == -1) {
            front = rear = 0;
            queue[rear] = item;
        }
        else if (rear == capacity - 1 && front != 0) {
            rear = 0;
            queue[rear] = item;
        }
        else {
            rear++;
            queue[rear] = item;
        }
    }
    void dequeue() {
        if (front == -1) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Removing " << queue[front] << " from the queue.\n";
        if (front == rear) {
            front = rear = -1;
        }
        else if (front == capacity - 1) {
            front = 0;
        }
        else {
            front++;
        }
    }
    void display() {
        pause_ = true;
        if (front == -1) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Elements in the queue are: ";
        if (rear >= front) {
            for (int i = front; i <= rear; i++) {
                cout << queue[i] << " ";
            }
        }
        else {
            for (int i = front; i < capacity; i++) {
                cout << queue[i] << " ";
            }
            for (int i = 0; i <= rear; i++) {
                cout << queue[i] << " ";
            }
        }
        cout << endl;
    }
};

