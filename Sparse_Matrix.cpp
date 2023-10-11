#include <bits/stdc++.h>
using namespace std;

struct ColumnNode{
    int data{};
    int idx{};
    ColumnNode *next{};
    ColumnNode *prev{};
    ColumnNode(int Data, int index):
            data(Data), idx(index){
    }
};

class ColumnLinkedList{
private:
    ColumnNode *first{};
    ColumnNode *last{};
    int length{};
    int cols{};

    void link(ColumnNode *fir, ColumnNode *sec){
        if(fir)
            fir->next = sec;
        if(sec)
            sec->prev = fir;
    }

    ColumnNode* push_after(ColumnNode *before, int data, int idx){
        ColumnNode* mid = new ColumnNode(data, idx);
        length++;
        ColumnNode* after = before->next;
        link(before, mid);
        if(!after)
            last = mid;
        else
            link(mid, after);
        return mid;
    }

    ColumnNode* get_col(int col, bool create) {
        ColumnNode* pre = first;
        while (pre->next && pre->next->idx < col)
            pre = pre->next;
        bool found = pre->next && pre->next->idx == col;
        if(found)
            return pre->next;
        if(!create)
            return nullptr;
        return push_after(pre, 0, col);
    }
public:
    ColumnLinkedList(int array_length) :
            cols(array_length) {
        first = last = new ColumnNode(0, -1);
        ++length;
    }

    void clear(){
        while(first){
            ColumnNode* tmp = first;
            first = first->next;
            tmp = tmp->next = tmp->prev = nullptr;
            delete tmp;
        }
        delete first;
        delete last;
    }

    void print_row(){
        ColumnNode *cur = first->next;
        for (int i = 0; i < cols ; ++i) {
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
    void print_row_nonzero(){
        for (ColumnNode *cur = first->next ; cur ; cur = cur->next) {
            cout << cur->data << " ";
        }
        cout << endl;
    }
    void set_value(int data, int index) {
        get_col(index, true)->data = data;
    }
    int get_value(int index){
        ColumnNode *node = get_col(index, false);
        if(node)
            return node->data;
        else
            return 0;
    }
    void add(ColumnLinkedList &other){
        assert(cols == other.cols);
        for (ColumnNode *o_cur = other.first->next ; o_cur ; o_cur = o_cur->next) {
            ColumnNode* node = get_col(o_cur->idx, true);
            node->data += o_cur->data;
            node = nullptr;
            delete node;
        }
    }
};

struct RowNode {
    int row { };
    ColumnLinkedList col_list;

    RowNode* next { };
    RowNode* prev { };

    RowNode(int row, int cols) :
            row(row), col_list(cols) {
    }
};

class SparseMatrix{
private:
    RowNode* first{};
    RowNode* last{};
    int length = 0;
    int rows{};
    int cols{};

    void link(RowNode *fir, RowNode *sec){
        if(fir)
            fir->next = sec;
        if(sec)
            sec->prev = fir;
    }

    RowNode* push_after(RowNode *before, int data, int idx){
        RowNode* mid = new RowNode(idx, cols);
        length++;
        RowNode* after = before->next;
        link(before, mid);
        if(!after)
            last = mid;
        else
            link(mid, after);
        return mid;
    }

    RowNode* get_row(int r, bool create) {
        RowNode* pre = first;
        while (pre->next && pre->next->row < r)
            pre = pre->next;
        bool found = pre->next && pre->next->row == r;
        if(found)
            return pre->next;
        if(!create)
            return nullptr;
        return push_after(pre, 0, r);
    }
public:
    SparseMatrix(int r, int c) :
        rows(r), cols(c){
        first = last = new RowNode(-1, c);
        length++;
    }
    ~SparseMatrix(){
        while(first){
            RowNode* tmp = first;
            first = first->next;
            tmp->col_list.clear();
            tmp = tmp->next = tmp->prev = nullptr;
            delete tmp;
        }
        delete first;
        delete last;
    }
    void set_value(int data, int row, int col){
        assert(row >= 0 && row <= rows);
        assert(col >= 0 && col <= cols);
        RowNode* node = get_row(row, true);
        node->col_list.set_value(data, col);
    }
    int get_value(int row, int col){
        assert(row >= 0 && row <= rows);
        assert(col >= 0 && col <= cols);
        RowNode* node = get_row(row, false);
        if(!node)
            return 0;
        return node->col_list.get_value(col);
    }
    void print_matrix(){
        cout << "\nPrint Matrix: " << rows << " x " << cols << endl;
        RowNode *cur = first->next;
        for (int i = 0; i < rows ; ++i) {
            if(cur && cur->row == i){
                cur->col_list.print_row();
                cur = cur->next;
            }
            else{
                for (int j = 0; j < cols; ++j)
                    cout << "0 ";
                cout << endl;
            }
        }
        cout << endl;
        cur = nullptr;
        delete cur;
    }
    void print_matrix_nonzero(){
        for (RowNode *cur = first->next ; cur ; cur = cur->next) {
            cur->col_list.print_row_nonzero();
        }
        cout << endl;
    }
    void add(SparseMatrix &other){
        assert(rows == other.rows && cols == other.cols);
        for (RowNode *o_cur = other.first->next ; o_cur ; o_cur = o_cur->next) {
            RowNode* node = get_row(o_cur->row, true);
            node->col_list.add(o_cur->col_list);
            node = nullptr;
            delete node;
        }
    }
};

void test_sparse() {
    SparseMatrix mat(10, 10);
    mat.set_value(5, 3, 5);
    mat.set_value(7, 3, 7);
    mat.set_value(2, 3, 2);
    mat.set_value(0, 3, 2);
    mat.set_value(6, 5, 6);
    mat.set_value(4, 5, 4);
    mat.set_value(3, 7, 3);
    mat.set_value(1, 7, 1);
    mat.print_matrix();
    mat.print_matrix_nonzero();

    SparseMatrix mat2(10, 10);
    mat2.set_value(5, 1, 9);
    mat2.set_value(6, 3, 8);
    mat2.set_value(9, 9, 9);
    mat2.set_value(5, 3, 2);
    mat.add(mat2);
    mat.print_matrix_nonzero();
}

int main() {
    test_sparse();
    cout << "\n\n\nNO RTE\n";
    return 0;
}