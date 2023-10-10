#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data{};
    int idx{};
    Node *next{};
    Node *prev{};
    Node(int Data, int index):
            data(Data), idx(index){
    }
};

class ArrayLinkedList{
private:
    Node *first{};
    Node *last{};
    int length{};
    int array_length{};

    void link(Node *fir, Node *sec){
        if(fir)
            fir->next = sec;
        if(sec)
            sec->prev = fir;
    }

    Node* push_after(Node *before, int data, int idx){
        Node* mid = new Node(data, idx);
        length++;
        Node* after = before->next;
        link(before, mid);
        if(!after)
            last = mid;
        else
            link(mid, after);
        return mid;
    }

    Node* get_index(int index, bool create) {
        Node* pre = first;
        while (pre->next && pre->next->idx < index)
            pre = pre->next;
        bool found = pre->next && pre->next->idx == index;
        if(found)
            return pre->next;
        if(!create)
            return nullptr;
        return push_after(pre, 0, index);
    }
public:
    ArrayLinkedList(int array_length) :
            array_length(array_length) {
        first = last = new Node(0, -1);
        ++length;
    }

    ~ArrayLinkedList(){
        while(first){
            Node* tmp = first;
            first = first->next;
            tmp = tmp->next = tmp->prev = nullptr;
            delete tmp;
        }
        delete first;
        delete last;
    }

    void print_array(){
        Node *cur = first->next;
        for (int i = 0; i < array_length ; ++i) {
            if(cur && cur->idx == i){
                cout << cur->data << " ";
                cur = cur->next;
            }
            else
                cout << "0 ";
        }
        cout << endl;
        cur = nullptr;
        delete cur;
    }
    void print_array_nonzero(){
        for (Node *cur = first->next ; cur ; cur = cur->next) {
            cout << cur->data << " ";
        }
        cout << endl;
    }
    void set_value(int data, int index) {
        get_index(index, true)->data = data;
    }
    int get_value(int index){
        Node *node = get_index(index, false);
        if(node)
            return node->data;
        else
            return 0;
    }
    void add(ArrayLinkedList &other){
        assert(array_length == other.array_length);
        for (Node *o_cur = other.first->next ; o_cur ; o_cur = o_cur->next) {
            Node* node = get_index(o_cur->idx, true);
            node->data += o_cur->data;
            node = nullptr;
            delete node;
        }
    }
};

void test_index() {
    ArrayLinkedList array(10);	// length 10
    array.set_value(50, 5);
    array.set_value(20, 2);
    array.set_value(70, 7);
    array.set_value(40, 4);
    array.print_array();
    // 0 0 20 0 40 50 0 70 0 0
    array.print_array_nonzero();
    // 20 40 50 70
    cout << array.get_value(7) << "\n";	// 70

    ArrayLinkedList array2(10);
    array2.set_value(1, 4);
    array2.set_value(3, 7);
    array2.set_value(4, 6);

    array.add(array2);
    array.print_array();
    // 0 0 20 0 41 50 4 73 0 0
}

int main() {
    test_index();

    cout << "\n\nNO RTE\n";

    return 0;
}

