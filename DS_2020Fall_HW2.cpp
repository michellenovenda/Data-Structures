#include <iostream>
#include<string>
#include<string.h>

using namespace std;

class Queue
{
private:
	struct Node
	{
		char data;
		Node* next;
		Node* prev;
	};
	Node* front;
	Node* rear;

public:
	Queue()
	{
		front = new Node();
		rear = front;
	}

	~Queue()
	{
		delete(front);
		delete(rear);
		front = nullptr;
		rear = nullptr;
	}

	void enqueue(const char& E)
	{
		rear->next = new Node();
		rear->next->data = E;
		rear->next->prev = rear;
		rear = rear->next;
	}

	void dequeue(int N)
	{
		if (front->next != nullptr)
		{
			while (N != 0)
			{
				Node* temp = front->next;
				delete front;
				front = temp;
				front->prev = nullptr;
				N--;
			}
		}
	}

	string show()
	{
		string result;

		Node* cur = front->next;

		if (cur != nullptr)
		{
			while (cur != nullptr)
			{
				result += cur->data;
				cur = cur->next;
			}
			return result;
		}

		else
		{
			result = "none";
			return result;
		}
	}
};

template<class T>
class Stack
{
private:
	T* stack;
	int top;
	int capacity;

public:
	Stack()
	{
		stack = new T[1500];
		capacity = 1500;
		top = -1;
	}

	~Stack() {}

	bool isEmpty()
	{
		return top == -1;
	}

	void push(const T& c)
	{
		if (top < capacity - 1)
		{
			stack[++top] = c;
		}
	}

	T pop()
	{
		if (top >= 0)
		{
			int val = stack[top--];
			return val;
		}
	}

	T topmost()
	{
		if (top >= 0)
		{
			return stack[top];
		}
	}
};

bool parentheses_match(string exp)
{
	int count = 0;
	int len = exp.length();

	for (int i = 0; i < len; i++)
	{
		if (exp[i] == '(')
			count++;

		else if (exp[i] == ')')
			count--;

		if (count < 0)
		{
			return false;
		}
	}

	if (count != 0)
		return false;

	return true;
}

bool top_operator(string exp)
{
	int len = exp.length();
	char c = exp[len - 1];
	char a = exp[0];

	if (c == '+' || c == '-' || c == '*' || c == '/' ||
		a == '+' || a == '-' || a == '*' || a == '/')
		return false;

	return true;
}

int precedence(char op)
{
	if (op == '*' || op == '/')
		return 1;

	else if (op == '+' || op == '-')
		return 2;
}

string infix_to_postfix(string op)
{
	Stack<char> s;
	int flag_out = 0;
	int flag_int = 0;
	int len = op.length();
	char c;
	string output;
	string invalid = "Invalid";

	for (int i = 0; i < len; i++)
	{
		c = op[i];

		if (isdigit(c) && flag_int != 1)
		{
			output += c;
			flag_out = 1;
			flag_int = 1;
		}

		else if (isdigit(c) && flag_int == 1)
		{
			flag_int = 0;
			return invalid;
		}

		else
		{
			flag_int = 0;

			if (c == '(')
			s.push(c);

			else if (c == ')')
			{
				while (s.topmost() != '(')
				{
					output += s.pop();
					flag_out = 1;
				}
				s.pop();
			}

			else if (!s.isEmpty() && !isdigit(s.topmost()) && !isdigit(c) && flag_out == 0)
				return invalid;

			else
			{
				while (!s.isEmpty() && s.topmost() != '(')
				{
					if (precedence(s.topmost()) <= precedence(c))
					{
						output += s.pop();
						flag_out = 1;
					}

					else
						break;
				}
				s.push(c);
				flag_out = 0;
			}
		}
	}
	while (!s.isEmpty())
		output += s.pop();

	return output;
}

void result(string op)
{
	string exp = infix_to_postfix(op);

	if (exp != "Invalid")
	{
		Stack<int> st;

		char c;
		int op1, op2;

		int i = 0;
		int len = exp.length();
		while (i < len)
		{
			c = exp[i];

			if (isdigit(c))
			{
				st.push(c - '0');
			}

			else
			{
				op2 = st.pop();
				op1 = st.pop();

				if (c == '+')
					st.push(op1 + op2);

				else if (c == '-')
					st.push(op1 - op2);

				else if (c == '*')
					st.push(op1 * op2);

				else if (c == '/')
					st.push(op1 / op2);
			}
			i++;
		}
		cout << st.pop();
	}

	else
		return;
}

int main()
{
	Queue q;

	string exp;
	char command[20];
	char enq;
	int deq;
	int print_flag = 0;

	cin >> exp;
	int len = exp.length();

	int i = 0;
	int j = i + 1;

	for (int i = 0; i < len; i++)
	{
		q.enqueue(exp[i]);
	}

	while (cin >> command)
	{
		if (strcmp(command, "Dequeue") == 0)
		{
			cin >> deq;
			q.dequeue(deq);
		}

		if (strcmp(command, "Enqueue") == 0)
		{
			cin >> enq;
			q.enqueue(enq);
		}

		if (strcmp(command, "Print") == 0)
		{
			if (print_flag == 0)
				print_flag = 1;

			else if(print_flag == 1)
				cout << endl;

			if (parentheses_match(q.show()) == false || top_operator(q.show()) == false)
			{
				cout << q.show() << endl;
				cout << "Invalid";
			}

			else
			{
				if (q.show() != "none")
					cout << q.show() << endl;
				else if (q.show() == "none")
					cout << endl;

				if (infix_to_postfix(q.show()) != "Invalid")
					cout << infix_to_postfix(q.show()) << endl;
				else if (infix_to_postfix(q.show()) == "Invalid")
					cout << infix_to_postfix(q.show());

				result(q.show());
			}
		}
	}
	return 0;
}
