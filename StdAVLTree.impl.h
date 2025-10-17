template<typename T>
struct StdAVLTree<T>::Node
{
	T data;
	Node* left;
	Node* right;
	short height;

	Node(const T& val) : data(val), left(nullptr), right(nullptr), height(0) {}
};

template<typename T>
void StdAVLTree<T>::deleteTree(Node*& node)
{
	if (node != nullptr)
	{
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
		node = nullptr;
	}
}

template<typename T>
short StdAVLTree<T>::getHeight(Node* node)
{
	if (node == nullptr)
		return -1;
	else
		return node->height;
}

template<typename T>
short StdAVLTree<T>::calculateHeight(Node* node)
{
	if (node == nullptr)
		return -1;
	short leftHeight = getHeight(node->left);
	short rightHeight = getHeight(node->right);
	return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

template<typename T>
void StdAVLTree<T>::leftRotate(Node*& node)
{
	Node* right = node->right;
	node->right = right->left;
	right->left = node;
	node = right;
	node->height = calculateHeight(node);
	node->left->height = calculateHeight(node->right);
}

template<typename T>
void StdAVLTree<T>::rightRotate(Node*& node)
{
	Node* left = node->left;
	node->left = left->right;
	left->right = node;
	node = left;
	node->height = calculateHeight(node);
	node->right->height = calculateHeight(node->left);
}

template<typename T>
void StdAVLTree<T>::leftRightRotate(Node*& node)
{
	leftRotate(node->left);
	rightRotate(node);
}

template<typename T>
void StdAVLTree<T>::rightLeftRotate(Node*& node)
{
	rightRotate(node->right);
	leftRotate(node);
}

template<typename T>
void StdAVLTree<T>::balance(Node*& node)
{
	short balance = getHeight(node->left) - getHeight(node->right);
	if (balance > 1)
	{
		if (getHeight(node->left->left) > getHeight(node->left->right))
			rightRotate(node);
		else if (getHeight(node->left->left) < getHeight(node->left->right))
			leftRightRotate(node);
		else
			rightRotate(node);
	}
	else if (balance < -1)
	{
		if (getHeight(node->right->right) > getHeight(node->right->left))
			leftRotate(node);
		else if (getHeight(node->right->right) < getHeight(node->right->left))
			rightLeftRotate(node);
		else
			leftRotate(node);
	}
	else
	{
		node->height = calculateHeight(node);
	}
}

template<typename T>
void StdAVLTree<T>::findAndRemoveMin(Node*& node)
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

	balance(node);
}

template<typename T>
void StdAVLTree<T>::insert(const T data, Node*& node)
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

	balance(node);
}

template<typename T>
void StdAVLTree<T>::remove(const T data, Node*& node)
{
	if (node == nullptr)
		return;
	if (node->data > data)
		remove(data, node->left);
	else if (node->data < data)
		remove(data, node->right);
	else
	{
		success = true;
		switch (getHeight(node))
		{
		case 0:
			delete node;
			node = nullptr;
			return;
		default:
			if (node->right == nullptr)
			{
				Node* temp = node->left;
				delete node;
				node = temp;
				return;
			}
			else
			{
				findAndRemoveMin(node->right);
				node->data = result;
			}
		}
	}

	balance(node);
}

template<typename T>
void StdAVLTree<T>::search(const T data, Node* node)
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

template<typename T>
StdAVLTree<T>::StdAVLTree()
{
	root = nullptr;
}

template<typename T>
StdAVLTree<T>::~StdAVLTree()
{
	deleteTree(root);
}

template<typename T>
bool StdAVLTree<T>::insert(const T data)
{
	success = false;
	insert(data, root);
	return success;
}

template<typename T>
bool StdAVLTree<T>::search(const T data)
{
	success = false;
	search(data, root);
	return success;
}

template<typename T>
bool StdAVLTree<T>::remove(const T data)
{
	success = false;
	remove(data, root);
	return success;
}