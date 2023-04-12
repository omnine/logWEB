#include <iostream>
#include <vector>
#include <mutex>

using namespace std;

// A circular buffer queue, fixed capacity
class LogCollector {
private:
    int front, rear;
    int capacity;
    vector<string> queue;

    bool pause_;
    std::mutex mutex_;

// filters
    string clientIP_;
    string level_;
    string node_;


public:
    LogCollector(int size) {
        front = rear = -1;
        capacity = size;
        queue.resize(capacity);
        pause_ = false;
    }

    void setFilters(string clientIP, string level,  string node) {
        clientIP_ = clientIP;
        level_ = level;
        node_ = node;
    }

    void enqueue(string item) {
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

    void fetch(std::vector<string>& bucket) {
        pause_ = true;
        if (front == -1) {
 //           cout << "Queue is empty.\n";
            return;
        }
        cout << "Elements in the queue are: ";
        if (rear >= front) {
            for (int i = front; i <= rear; i++) {
                bucket.push_back(queue[i]);
 //               cout << queue[i] << " ";
            }
        }
        else {
            for (int i = front; i < capacity; i++) {
                bucket.push_back(queue[i]);
//                cout << queue[i] << " ";
            }
            for (int i = 0; i <= rear; i++) {
                bucket.push_back(queue[i]);
//                cout << queue[i] << " ";
            }
        }
        cout << endl;
    }


private:
    // If  json library is used, then it is not necessary.
    std::string escape_string(const std::string& str) {
        std::string escaped_str;
        for (char c : str) {
            switch (c) {
            case '\\':
                escaped_str += "\\\\";
                break;
            case '"':
                escaped_str += "\\\"";
                break;
            case '\b':
                escaped_str += "\\b";
                break;
            case '\f':
                escaped_str += "\\f";
                break;
            case '\n':
                escaped_str += "\\n";
                break;
            case '\r':
                escaped_str += "\\r";
                break;
            case '\t':
                escaped_str += "\\t";
                break;
            default:
                escaped_str += c;
                break;
            }
        }
        return escaped_str;
    }

};

