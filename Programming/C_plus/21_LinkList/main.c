#include <iostream>

using namespace std;

class Node {
    int val;
    Node* next;

    Node() {
        val = 0;
        next = nullptr;
    }
    Node(int val) {
        this->val = val;
        next = nullptr;
    }
    friend class LinkList;
};

class LinkList {
    Node* head;

public:
    LinkList() {
        head = nullptr;
    }

    void push_front(int val) {
        Node* n = new Node(val);
        n->next = head;
        head = n;
    }

    void push_back(int val) {
        Node* n = new Node(val);
        if (head == nullptr) {
            head = n;
            return;
        }
        Node* p = head;
        while (p->next) {
            p = p->next;
        }
        p->next = n;
    }

    bool pop_front() {
        if (head == nullptr) {
            return false;
        }
        Node *p = head->next;
        delete head;
        head = p;
        return true;
    }

    bool pop_back() {
        if (head == nullptr) {
            return false;
        }
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return true;
        }
        Node* p = head;
        while (p->next->next) {
            p = p->next;
        }
        delete p->next;
        p->next = nullptr;
        return true;
    }

    bool at(int index, int* out) {
        Node* p = head;
        while (p && index) {
            index--;
            p = p->next;
        }
        if (p == nullptr) return false;
        else {
            *out = p->val;
            return true;
        }
    }

    void clear() {
        if (head == nullptr) return;
        while (head) {
            Node* to_del = head;
            head = head->next;
            delete to_del;
        }
        head = nullptr;
    }

    int size() {
        int count = 0;
        Node* p = head;
        while (p) {
            count++;
            p = p->next;
        }
        return count;
    }

    void dump() {
        Node* p = head;
        cout << "dump ";
        while(p) {
            cout << p->val << " ";
            p = p->next;
        }
        cout << endl;
    }
};

int main() {
    LinkList list;

    list.push_back(1); // 1
    list.push_back(2); // 1->2
    list.push_back(3); // 1->2->3

    cout << list.pop_back() << endl; // true 1->2
    cout << list.pop_back() << endl; // true 1
    cout << list.pop_back() << endl; // true
    cout << list.pop_back() << endl; // false
    
    list.push_front(1); // 1
    list.push_front(2); // 2->1
    list.push_front(3); // 3->2->1

    cout << list.pop_front() << endl; // true 2->1
    cout << list.pop_front() << endl; // true 1
    cout << list.pop_front() << endl; // true
    cout << list.pop_front() << endl; // false

    list.push_front(1); // 1
    list.push_front(2); // 2->1
    list.push_front(3); // 3->2->1

    for (int i = 0; i < list.size(); i++) {
        int val = 0;
        cout << "index=" << i << " ret=" << list.at(i, &val) << " val=" << val << endl;
        // index=0 ret=1 val=3
        // index=1 ret=1 val=2
        // index=2 ret=1 val=1
    }

    return 0;
}
