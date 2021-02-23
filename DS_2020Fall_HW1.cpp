#include <iostream>
#include<string>

using namespace std;

class List
{
private:
    struct Node
    {
        Node* next;
        int data;
    };

    Node* head;

public:
    List();
    ~List();

    void InsertFront(int val);
    void InsertBack(int val);
    void InsertBefore(int pos, int val);
    void InsertAfter(int pos, int val);
    void DeleteFront();
    void DeleteBack();
    void Delete(int val);
    void Reverse(int front, int back);
    void Clear();
    void Print();

    bool EmptyList()
    {
        return head == nullptr;
    }
};

List::List()
{
    head = nullptr;
}

List::~List()
{
    Clear();
    delete head;
    head = nullptr;
}

void List::InsertFront(int val)
{
    if (EmptyList())
    {
        Node* new_node = new Node();
        new_node->data = val;
        new_node->next = nullptr;
        head = new_node;
    }

    else
    {
        Node* new_node = new Node();
        new_node->data = val;
        new_node->next = head;
        head = new_node;
    }
}

void List::InsertBack(int val)
{
    Node* new_node = new Node();
    new_node->data = val;
    new_node->next = nullptr;

    if (!EmptyList())
    {
        Node* next_node = head;

        while (next_node->next != nullptr)
        {
            next_node = next_node->next;
        }

        next_node->next = new_node;
    }

    else
    {
        head = new_node;
    }
}

void List::InsertBefore(int pos, int val)
{
    if (EmptyList())
        return;

    else
    {
        Node* cur = head;
        Node* prev_node = nullptr;

        if (cur->data == pos)
        {
            InsertFront(val);
            return;
        }

        while (cur->data != pos)
        {
            prev_node = cur;
            cur = cur->next;

            if (cur == nullptr)
                return;
        }
        prev_node->next = new Node();
        prev_node->next->data = val;
        prev_node->next->next = cur;
    }
}

void List::InsertAfter(int pos, int val)
{
    if (EmptyList())
        return;

    else
    {
        Node* cur = head;
        Node* next_node = head->next;
        Node* new_node = new Node();

        while (cur->data != pos)
        {
            cur = cur->next;

            if (cur == nullptr)
                return;

            next_node = cur->next;
        }

        cur->next = new_node;
        cur->next->data = val;
        cur->next->next = next_node;
    }
}

void List::DeleteFront()
{
    if (EmptyList())
        return;

    else
    {
        if (head->next == nullptr)
        {
            delete(head);
            head = nullptr;
            return;
        }

        Node* temp = head;
        head = head->next;
        delete(temp);
        temp = nullptr;
    }
}

void List::DeleteBack()
{
    if (EmptyList())
        return;

    else
    {
        if (head->next == nullptr)
        {
            delete(head);
            head = nullptr;
            return;
        }

        Node* cur = head;
        Node* prev_node = nullptr;

        while (cur->next != nullptr)
        {
            prev_node = cur;
            cur = cur->next;
        }

        prev_node->next = nullptr;
        delete(cur);
        cur = nullptr;
    }
}

void List::Delete(int val)
{
    if (EmptyList())
        return;

    else
    {
        Node* cur = head;
        Node* prev_node = head;
        Node* next_node = head->next;

        if (cur->data == val)
        {
            DeleteFront();
        }

        else if (cur->next == nullptr)
        {
            DeleteBack();
        }

        else
        {
            while (cur->data != val)
            {
                prev_node = cur;
                cur = cur->next;

                if (cur == nullptr)
                    return;

                next_node = cur->next;
            }

            prev_node->next = next_node;
            delete(cur);
            cur = nullptr;
        }
    }
}

void List::Reverse(int front, int back)
{
    if (EmptyList())
        return;

    else
    {
        if (front == back)
            return;

        Node* begin = head;
        Node* end = head;
        Node* prev_node = nullptr;

        while (begin->data != front)
        {
            prev_node = begin;

            if (begin == nullptr || begin->data == back)
                return;

            begin = begin->next;
        }

        while (end->data != back)
        {
            end = end->next;

            if (end == nullptr)
                return;
        }

        Node* begin_prev = prev_node;
        Node* new_tail = begin;

        Node* temp;
        Node* cur = begin;

        if (begin_prev != nullptr && end != nullptr)
        {
            while (cur->data != end->data)
            {
                temp = begin->next;
                cur = cur->next;
                begin->next = prev_node;
                prev_node = begin;
                begin = temp;
            }

            if (begin_prev)
                begin_prev->next = prev_node;
            else
                head = prev_node;

            new_tail->next = begin;

            new_tail->next = cur->next;
            cur->next = begin_prev->next;
            begin_prev->next = cur;
        }

        else if (begin_prev == nullptr && end->next == nullptr)
        {
            if (head == nullptr)
                return;

            Node* cur = head;
            Node* prev_node = nullptr;
            Node* next_node = nullptr;

            while (cur != nullptr)
            {
                next_node = cur->next;
                cur->next = prev_node;

                prev_node = cur;
                cur = next_node;
            }
            head = prev_node;
        }

        else if (begin_prev == nullptr && end->next != nullptr)
        {
            while (cur->data != end->data)
            {
                temp = begin->next;
                cur = cur->next;
                begin->next = prev_node;
                prev_node = begin;
                begin = temp;
            }

            head = cur;

            new_tail->next = cur->next;
            cur->next = prev_node;
        }

        else if (begin_prev != nullptr && end->next == nullptr)
        {
            while (cur->data != end->data)
            {
                temp = begin->next;
                cur = cur->next;
                begin->next = prev_node;
                prev_node = begin;
                begin = temp;
            }

            if (begin_prev)
                begin_prev->next = prev_node;
            else
                head = prev_node;

            cur->next = begin_prev->next;
            begin_prev->next = cur;
        }
    }
}

void List::Clear()
{
    if (EmptyList())
        return;

    else
    {
        Node* cur = head;

        while (cur != nullptr)
        {
            Node* temp = cur;
            cur = cur->next;
            delete(temp);
            temp = nullptr;
        }

        head = nullptr;
    }
}

void List::Print()
{
    Node* cur = head;

    while (cur != nullptr)
    {
        cout << cur->data << ' ';
        cur = cur->next;
    }
    cout << endl;
}

int main()
{
    List lst = *(new List());
    string cmd;
    int pos, val;

    while (cin >> cmd)
    {
        if (cmd == "InsertFront")
        {
            cin >> val;
            lst.InsertFront(val);
        }

        else if (cmd == "InsertBack")
        {
            cin >> val;
            lst.InsertBack(val);
        }

        else if (cmd == "InsertBefore")
        {
            cin >> pos >> val;
            lst.InsertBefore(pos, val);
        }

        else if (cmd == "InsertAfter")
        {
            cin >> pos >> val;
            lst.InsertAfter(pos, val);
        }

        else if (cmd == "DeleteFront")
        {
            lst.DeleteFront();
        }

        else if (cmd == "DeleteBack")
        {
            lst.DeleteBack();
        }

        else if (cmd == "Delete")
        {
            cin >> val;
            lst.Delete(val);
        }

        else if (cmd == "Reverse")
        {
            cin >> pos >> val;
            lst.Reverse(pos, val);
        }

        else if (cmd == "Clear")
        {
            lst.Clear();
        }

        else if (cmd == "Print")
        {
            lst.Print();
        }
    }
}
