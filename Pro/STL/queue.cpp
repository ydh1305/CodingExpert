#include <iostream>
using namespace std;

template <typename T>
class _queue {
public:
    struct Node {
        T v;
        Node *next;
        Node(T v):v(v), next(0) {}
        Node() {}
    };
    Node *head;
    Node *tail;
    int s;

    _queue() {
        head = tail = 0;
        s = 0;
    }
    void push(T v) {
        Node *temp = new Node(v);
        if(head == 0)
            head = tail = temp;
        else {
            tail->next = temp;
            tail = temp;
        }
        s++;
    }
    void pop() {
        Node *temp = head;
        head = head->next;
        delete temp;
        s--;
    }
    bool empty() const {
        return s == 0;
    }
    T front() const {
        return head->v;
    }
    T back() const {
        return tail->v;
    }
    int size() const {
        return s;
    }
};
