#include <iostream>
#include<string>
using namespace std;

struct Node
{
	struct Node* left = nullptr;
	struct Node* right = nullptr;
	int data;
};

int idx = 1;
int tower = 0;

Node* insert_node(const char* op)
{
	int num = 0;
	Node* root = nullptr;
	bool neg = false;

	if (op[idx] == '(')
		idx++;

	if (op[idx] == '-')
	{
		neg = true;
		idx++;
	}

	else if (op[idx] != '-')
		neg = false;

	if (isdigit(op[idx]))
	{
		num = 0;

		while (op[idx] != '(')
		{
			num = num * 10 + op[idx] - '0';
			idx++;

			if (!isdigit(op[idx]))
			{
				break;
			}
		}

		if (neg == true)
			num *= -1;

		root = new Node();
		root->data = num;

		if (op[idx] == '(')
		{
			idx++;

			if (op[idx] == ')')
			{
				root->left = nullptr;
				idx++;
			}

			else
			{
				root->left = insert_node(op);
				idx++;
			}
		}

		if (op[idx] == '(')
		{
			idx++;

			if (op[idx] == ')')
			{
				root->right = nullptr;
				idx++;
			}

			else
			{
				root->right = insert_node(op);
				idx++;
			}
		}
	}
	return root;
}

void preorder(Node* root)
{
	if (root != nullptr)
	{
		cout << root->data << ' ';
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(Node* root)
{
	if (root != nullptr)
	{
		inorder(root->left);
		cout << root->data << ' ';
		inorder(root->right);
	}
}

void postorder(Node* root)
{
	if (root != nullptr)
	{
		postorder(root->left);
		postorder(root->right);
		cout << root->data << ' ';
	}
}

int height_tree(Node* root)
{
	int left_height = 0;
	int right_height = 0;

	if (root != nullptr)
	{
		left_height = height_tree(root->left) + 1;
		right_height = height_tree(root->right) + 1;
	}

	return max(left_height, right_height);
}

bool foldable(Node* lft, Node* rgt)
{
	if (!lft || !rgt)
		return !lft && !rgt;

	return foldable(lft->left, rgt->right) && foldable(lft->right, rgt->left);
}

bool is_foldable(Node* root)
{
	return !root || foldable(root->left, root->right);
}

int weight_sum(Node* root)
{
	if (root != nullptr)
		return(root->data + weight_sum(root->left) + weight_sum(root->right));

	else
		return 0;
}

int solve(Node* root)
{
	if (root != nullptr)
	{
		int result;
		int lft = solve(root->left);
		int rgt = solve(root->right);

		if (lft == 0 || rgt == 0)
		{
			tower++;
			result = 2;
		}

		else if (lft == 2 || rgt == 2)
			result = 1;

		else
			result = 0;

		return result;
	}

	else
		return 1;
}

int binary_tower(Node* root)
{
	if (solve(root) == 0)
		tower++;

	return tower;
}

void MPS(Node* root, int& max_sum, int sum)
{
	if (root == nullptr)
		return;

	if (root->left == nullptr && root->right == nullptr)
	{
		if (root->data + sum >= max_sum)
			max_sum = root->data + sum;
	}

	MPS(root->left, max_sum, sum + root->data);
	MPS(root->right, max_sum, sum + root->data);
}

int maximum_path_sum(Node* root)
{
	int max = -2147483648;

	if (root == nullptr)
		max = 0;

	else
		MPS(root, max, 0);

	return max;
}

Node* delete_leaf(Node* root)
{
	if (root == nullptr)
		return nullptr;

	else
	{
		if (root->left == nullptr && root->right == nullptr)
		{
			delete root;
			return nullptr;
		}

		else
		{
			root->left = delete_leaf(root->left);
			root->right = delete_leaf(root->right);
		}
	}
	return root;
}

void delete_tree(Node* root)
{
	if (root != nullptr)
	{
		delete_tree(root->left);
		delete_tree(root->right);
		delete root;
	}
}

int main()
{
	string s;
	string cmd;

	while (cin >> s)
	{
		char* str = &s[0];
		Node* root = insert_node(str);

		while (cin >> cmd)
		{
			if (cmd == "Traverse")
			{
				preorder(root);
				cout << endl;
				inorder(root);
				cout << endl;
				postorder(root);
				cout << endl;
			}

			else if (cmd == "Height")
			{
				cout << height_tree(root) << endl;
			}

			else if (cmd == "WeightSum")
			{
				cout << weight_sum(root) << endl;
			}

			else if (cmd == "MaximumPathSum")
			{
				cout << maximum_path_sum(root) << endl;
			}

			else if (cmd == "BinaryTower")
			{
				cout << binary_tower(root) << endl;
			}

			else if (cmd == "DeleteLeaf")
			{
				root = delete_leaf(root);
			}

			else if (cmd == "Foldable")
			{
				if (is_foldable(root) == true)
					cout << "Yes" << endl;
				else if (is_foldable(root) == false)
					cout << "No" << endl;
			}

			else if (cmd == "End")
			{
				delete_tree(root);
				s = "";
				tower = 0;
				idx = 1;
				break;
			}
		}
	}
}



