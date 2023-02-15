#include <iostream>

using namespace std;

class Point {
public:
    int x;
    int y;

    Point() { x = 0; y = 0; }
    Point(int x, int y) : x(x), y(y) {}

    void dump() {
        cout << "x=" << x << " y=" << y << endl;
    }
};

class Node {
public:
    int data;
    Node* next;

    Node() {
        data = 0;
        next = nullptr;
    }
    Node(int value) {
        this->data = value;
        this->next = nullptr;
    }
};

class ListList {
public:
    Node* head;

    ListList() {
        head = nullptr;
    }

    void add_front(int value) {
        Node* n = new Node(value);
        n->next = head;
        head = n;
    }

    void add_back(int value) {
        Node* p = head;
        Node* n = new Node(value);
        if (p == nullptr) {
            head = n;
        } else {
            while (p->next) {
                p = p->next;
            }
            p->next = n;
        }
    }

    bool pop_front(int* out) {
        if (head == nullptr) {
            return false;
        }
        *out = head->data;
        Node* next = head->next;
        delete(head);
        head = next;
        return true;
    }

    bool pop_end(int* out) {
        if (head == nullptr) {
            return false;
        }
        if (head->next == nullptr) {
            *out = head->data;
            delete(head);
            head = nullptr;
            return true;
        }
        Node *p = head;

        while (p->next->next) {
            p = p->next;
        }

        *out = p->next->data;
        delete(p->next);
        p->next = nullptr;
        return true;
    }

    void clear() {
        Node* p = head;
        Node* next;
        while (p) {
            next = p->next;
            delete(p);
            p = next;
        }
        head = nullptr;
    }

    void dump() {
        Node* p = head;
        while (p) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
};


int main() {
    /*************************************
        init
    **************************************/
    Point p;
    p.dump();

    ListList l;
    l.dump();
    l.add_back(0); // 0
    l.dump();
    l.add_front(1); // 1 0
    l.add_front(2); // 2 1 0
    l.add_front(3); // 3 2 1 0
    l.add_back(4);  // 3 2 1 0 4

    int data = 0;
    l.pop_front(&data);  // 2 1 0 4
    cout << "pop_front()=" << data << endl; // 3

    l.pop_end(&data); // 2 1 0
    cout << "pop_end()=" << data << endl; // 4

    l.clear();
    l.dump();

    return 0;
}
