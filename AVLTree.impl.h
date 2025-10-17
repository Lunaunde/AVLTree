#include <iostream>

template <typename T>
struct AVLTree<T>::Node
{
	T data;
	Node* left;
	Node* right;
	short height;

	Node(const T& val) : data(val), left(nullptr), right(nullptr), height(-1) {}
};

template <typename T>
void AVLTree<T>::deleteTree(Node*& node)
{
	if (node != nullptr)
	{
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
		node = nullptr;
	}
}

template <typename T>
short AVLTree<T>::getHeight(Node* node)
{
	if (node == nullptr)
		return -1;
	else
		return node->height;
}

template <typename T>
short AVLTree<T>::calculateHeight(Node* node)
{
	int leftHeight = getHeight(node->left);
	int rightHeight = getHeight(node->right);
	return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

template <typename T>
void AVLTree<T>::leftRotate(Node*& node)
{
	Node* right = node->right;
	node->right = right->left;
	right->left = node;
	node = right;
}

template <typename T>
void AVLTree<T>::rightRotate(Node*& node)
{
	Node* left = node->left;
	node->left = left->right;
	left->right = node;
	node = left;
}

template <typename T>
void AVLTree<T>::leftRightRotate(Node*& node)
{
	Node* left = node->left;
	Node* leftRight = left->right;
	node->left = leftRight->right;
	left->right = leftRight->left;
	leftRight->right = node;
	leftRight->left = left;
	node = leftRight;
}

template <typename T>
void AVLTree<T>::rightLeftRotate(Node*& node)
{
	Node* right = node->right;
	Node* rightLeft = right->left;
	node->right = rightLeft->left;
	right->left = rightLeft->right;
	rightLeft->left = node;
	rightLeft->right = right;
	node = rightLeft;
}

template <typename T>
void AVLTree<T>::balanceInsert(Node*& node)
{
	short balance = getHeight(node->left) - getHeight(node->right);
	int nodeHeight = node->height;
	if (balance > 1)
	{
		if (getHeight(node->left->left) > getHeight(node->left->right))
		{
			rightRotate(node);
			node->right->height = (node->height) - 1;
		}
		else
		{
			leftRightRotate(node);
			node->left->height = node->height;
			node->right->height = node->height;
			(node->height)++;
		}
	}
	else if (balance < -1)
	{
		if (getHeight(node->right->right) > getHeight(node->right->left))
		{
			leftRotate(node);
			node->left->height = (node->height) - 1;
		}
		else
		{
			rightLeftRotate(node);
			node->right->height = node->height;
			node->left->height = node->height;
			(node->height)++;
		}
	}
	else
	{
		node->height = calculateHeight(node);
	}
	if (nodeHeight == node->height)
		balanced = true;
}
template <typename T>
void AVLTree<T>::balanceRemove(Node*& node)
{
	short balance = getHeight(node->left) - getHeight(node->right);
	int nodeHeight = node->height;
	if (balance > 1)
	{
		if (getHeight(node->left->left) > getHeight(node->left->right))
		{
			rightRotate(node);
			node->right->height = (node->height) - 1;
		}
		else if (getHeight(node->left->left) < getHeight(node->left->right))
		{
			leftRightRotate(node);
			node->left->height = node->height;
			node->right->height = node->height;
			(node->height)++;
		}
		else
		{
			rightRotate(node);
			node->right->height = (node->height);
			(node->height)++;
		}
	}
	else if (balance < -1)
	{
		if (getHeight(node->right->right) > getHeight(node->right->left))
		{
			leftRotate(node);
			node->left->height = (node->height) - 1;
		}
		else if (getHeight(node->right->right) < getHeight(node->right->left))
		{
			rightLeftRotate(node);
			node->right->height = node->height;
			node->left->height = node->height;
			(node->height)++;
		}
		else
		{
            leftRotate(node);
			node->left->height = (node->height);
			(node->height)++;
		}
	}
	else
	{
		node->height = calculateHeight(node);
	}
	if (nodeHeight == node->height)
		balanced = true;
}

template <typename T>
void AVLTree<T>::findAndRemoveMin(Node*& node) // Find Minimum and Remove
{
	if (node->left != nullptr)
		findAndRemoveMin(node->left);
	else
	{
		result = node->data;
		Node* temp = node;
		node = node->right;
		delete temp;
		return;
	}

	if (balanced)
		return;
	balanceRemove(node);
}

template <typename T>
void AVLTree<T>::insert(const T data, Node*& node)
{
	if (node == nullptr)
	{
		node = new Node(data);
		success = true;
	}
	else if (node->data > data)
		insert(data, node->left);
	else if (node->data < data)
		insert(data, node->right);
	else
		return;

	if (balanced)
		return;
	balanceInsert(node);
}

template <typename T>
void AVLTree<T>::remove(const T data, Node*& node)
{
	if (node == nullptr)
		return;
	if (node->data > data)
		remove(data, node->left);
	else if (node->data < data)
		remove(data, node->right);
	else
	{
		balanced = false;
		switch (getHeight(node))
		{
		case 0:
		{
			delete node;
			node = nullptr;
			success = true;
			return;
		}
		case 1:
		{
			if (node->left != nullptr)
			{
				node->data = node->left->data;
				delete node->left;
				node->left = nullptr;
				success = true;
				if (node->right == nullptr)
					node->height = 0;
			}
			else
			{
				node->data = node->right->data;
				delete node->right;
				node->right = nullptr;
				success = true;
				node->height = 0;
			}
			return;
		}
		default:
		{
			findAndRemoveMin(node->right);
			node->data = result;
			break;
		}
		}
	}

	if (balanced)
		return;
    balanceRemove(node);
}

template <typename T>
void AVLTree<T>::safelyleftRotate(Node*& node)
{
	leftRotate(node);
	node->height = calculateHeight(node);
	node->right->height = calculateHeight(node->right);
}

template <typename T>
void AVLTree<T>::safelyrightRotate(Node*& node)
{
	rightRotate(node);
	node->height = calculateHeight(node);
	node->left->height = calculateHeight(node->left);
}

template <typename T>
void AVLTree<T>::search(const T data, Node* node)
{
	if (node == nullptr)
		return;
	else if (node->data > data)
		search(data, node->left);
	else if (node->data < data)
		search(data, node->right);
	else 
        success = true;
}

template <typename T>
void AVLTree<T>::print(Node* node)
{
	if (node != nullptr)
	{
		if (node->left != nullptr)
			print(node->left);
		std::cout << "|data: " << node->data << " height: " << node->height << std::endl;
		if (node->right != nullptr)
			print(node->right);
	}
}

template <typename T>
AVLTree<T>::AVLTree()
{
	root = nullptr;
}

template <typename T>
AVLTree<T>::~AVLTree()
{
	deleteTree(root);
}


template <typename T>
bool AVLTree<T>::insert(const T data)
{
	balanced = false;
	success = false;
	insert(data, this->root);
	return success;
}

template <typename T>
bool AVLTree<T>::search(const T data)
{
	success = false;
	search(data, this->root);
	return success;
}

template <typename T>
bool AVLTree<T>::remove(const T data)
{
	success = false;
	remove(data, this->root);
	return success;
}

template <typename T>
void AVLTree<T>::print()
{
	print(this->root);
}

template <typename T>
void AVLTree<T>::checkBalance(Node* node, const std::string& path) {
	if (node == nullptr) return;

	int leftHeight = getHeight(node->left);
	int rightHeight = getHeight(node->right);
	int balance = leftHeight - rightHeight;

	if (abs(balance) > 1) {
		std::cout << "❌ 不平衡节点: " << node->data
			<< " balance: " << balance
			<< " path: " << path << std::endl;
	}

	checkBalance(node->left, path + "L->");
	checkBalance(node->right, path + "R->");
}

template <typename T>
void AVLTree<T>::checkBalance() 
{
	checkBalance(root, "");
}