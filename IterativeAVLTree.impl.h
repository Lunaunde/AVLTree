#include<queue>

template<typename T>
FixedStack<T>::FixedStack(int capacity)
{
	this->capacity = capacity;
	stack = new T[capacity];
	index = -1;
}

template<typename T>
FixedStack<T>::~FixedStack()
{
	delete[] stack;
}

template<typename T>
bool FixedStack<T>::push(T data)
{
	if (index >= capacity - 1)
		return false;
	stack[++index] = data;
	return true;
}

template<typename T>
bool FixedStack<T>::pop()
{
	if (index < 0)
		return false;
	index--;
	return true;
}

template<typename T>
T FixedStack<T>::top()
{
	if (index < 0)
		return T();
	return stack[index];
}

template<typename T>
bool FixedStack<T>::empty()
{
	return index < 0;
}

template<typename T>
struct IterativeAVLTree<T>::Node
{
	T data;
	Node* left, * right;
	short height;
	Node(T data) : data(data), left(nullptr), right(nullptr), height(-1) {}
};

template<typename T>
short IterativeAVLTree<T>::getHeight(Node* node)
{
	if (node == nullptr)
		return -1;
	return node->height;
}

template<typename T>
short IterativeAVLTree<T>::calculateHeight(Node* node)
{
	int leftHeight = getHeight(node->left);
	int rightHeight = getHeight(node->right);
	return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

template<typename T>
void IterativeAVLTree<T>::leftRotate(Node** nodePtr)
{
	Node* right = (*nodePtr)->right;
	(*nodePtr)->right = right->left;
	right->left = *nodePtr;
	*nodePtr = right;
}

template<typename T>
void IterativeAVLTree<T>::rightRotate(Node** nodePtr)
{
	Node* left = (*nodePtr)->left;
	(*nodePtr)->left = left->right;
	left->right = *nodePtr;
	*nodePtr = left;
}

template <typename T>
void IterativeAVLTree<T>::leftRightRotate(Node** nodePtr)
{
	Node* left = (*nodePtr)->left;
	Node* leftRight = left->right;
	(*nodePtr)->left = leftRight->right;
	left->right = leftRight->left;
	leftRight->right = (*nodePtr);
	leftRight->left = left;
	(*nodePtr) = leftRight;
}

template<typename T>
void IterativeAVLTree<T>::rightLeftRotate(Node** nodePtr)
{
	Node* right = (*nodePtr)->right;
	Node* rightLeft = right->left;
	(*nodePtr)->right = rightLeft->left;
	right->left = rightLeft->right;
	rightLeft->left = (*nodePtr);
	rightLeft->right = right;
	(*nodePtr) = rightLeft;
}

template<typename T>
bool IterativeAVLTree<T>::balanceInsert(Node** nodePtr)
{
	short nodeHeight = getHeight(*nodePtr);
	short balance = getHeight(*nodePtr->left) - getHeight(*nodePtr->right);
	switch (balance)
	{
	default:
		(*nodePtr)->height = calculateHeight(*nodePtr);
		break;
	case 2:
		if (getHeight((*nodePtr)->left->left) > getHeight((*nodePtr)->left->right))
		{
			rightRotate(*nodePtr);
			(*nodePtr)->right->height = ((*nodePtr)->height) - 1;
		}
		else
		{
			leftRightRotate(*nodePtr);
			(*nodePtr)->left->height = (*nodePtr)->height;
			(*nodePtr)->right->height = (*nodePtr)->height;
			((*nodePtr)->height)++;
		}
		break;
	case -2:
		if (getHeight((*nodePtr)->right->right) > getHeight((*nodePtr)->right->left))
		{
			leftRotate(*nodePtr);
			(*nodePtr)->left->height = ((*nodePtr)->height) - 1;
		}
		else
		{
			rightLeftRotate(*nodePtr);
			(*nodePtr)->left->height = (*nodePtr)->height;
			(*nodePtr)->right->height = (*nodePtr)->height;
			((*nodePtr)->height)++;
		}
		break;
	}
	if(nodeHeight != (*nodePtr)->height)
		return false;
	else
		return true;
}

template<typename T>
bool IterativeAVLTree<T>::balanceRemove(Node** nodePtr)
{
	short nodeHeight = (*nodePtr)->height;
	short balance = getHeight((*nodePtr)->left) - getHeight((*nodePtr)->right);
	switch (balance)
	{
	default:
		(*nodePtr)->height = calculateHeight(*nodePtr);
		break;
	case 2:
        if (getHeight((*nodePtr)->left->left) > getHeight((*nodePtr)->left->right))
		{
			rightRotate(nodePtr);
			(*nodePtr)->right->height = ((*nodePtr)->height) - 1;
		}
		else if (getHeight((*nodePtr)->left->left) < getHeight((*nodePtr)->left->right))
		{
			leftRightRotate(nodePtr);
			(*nodePtr)->left->height = (*nodePtr)->height;
			(*nodePtr)->right->height = (*nodePtr)->height;
			((*nodePtr)->height)++;
		}
		else
		{
			rightRotate(nodePtr);
			(*nodePtr)->right->height = ((*nodePtr)->height);
			((*nodePtr)->height)++;
		}
		break;
	case -2:
		if (getHeight((*nodePtr)->right->right) > getHeight((*nodePtr)->right->left))
		{
            leftRotate(nodePtr);
			(*nodePtr)->left->height = ((*nodePtr)->height) - 1;
		}
		else if (getHeight((*nodePtr)->right->right) < getHeight((*nodePtr)->right->left))
		{
			rightLeftRotate(nodePtr);
			(*nodePtr)->left->height = (*nodePtr)->height;
			(*nodePtr)->right->height = (*nodePtr)->height;
			((*nodePtr)->height)++;
		}
		else
		{
			leftRotate(nodePtr);
			(*nodePtr)->left->height = ((*nodePtr)->height);
			((*nodePtr)->height)++;
		}
		break;
	}
	if (nodeHeight != (*nodePtr)->height)
		return false;
	else
		return true;
}

template <typename T>
T IterativeAVLTree<T>::findAndRemoveMin(Node** nodePtr) // Find Minimum and Remove
{
	FixedStack<Node**> nodeStack(getHeight(root) + 1);
	while ((*nodePtr)->left != nullptr)
	{
		nodeStack.push(nodePtr);
		nodePtr = &(*nodePtr)->left;
	}

	T min = (*nodePtr)->data;

	while (!nodeStack.empty())
	{
		if (balanceRemove(nodeStack.top()))
			break;
		nodeStack.pop();
	}
	return min;
}

template<typename T>
IterativeAVLTree<T>::IterativeAVLTree() : root(nullptr) {};

template<typename T>
IterativeAVLTree<T>::~IterativeAVLTree()
{
	if (root == nullptr)
		return;
	queue<Node*> nodeQueue;
	nodeQueue.push(root);
	while (!nodeQueue.empty())
	{
		if (nodeQueue.front()->left != nullptr)
			nodeQueue.push(nodeQueue.front()->left);
		if (nodeQueue.front()->right != nullptr)
			nodeQueue.push(nodeQueue.front()->right);
		delete nodeQueue.front();
		nodeQueue.pop();
	}
	root = nullptr;
}

template<typename T>
bool IterativeAVLTree<T>::insert(const T data)
{
	FixedStack<Node**> nodeStack(getHeight(root) + 1);
	Node** nodePtr = &root;
	while (true)
	{
		if (*nodePtr == nullptr)
		{
			*nodePtr = new Node(data);
			break;
		}
		else if (data < (*node)->data)
		{
			nodeStack.push(node);
			nodePtr = &(*node)->left;
		}
		else if (data > (*node)->data)
		{
			nodeStack.push(node);
			nodePtr = &(*node)->right;
		}
		else
			return false;
	}

	while (!nodeStack.empty())
	{
		if (balanceInsert(nodeStack.top()))
			break;
		nodeStack.pop();
	}
	return true;
}

template<typename T>
bool IterativeAVLTree<T>::search(const T data)
{
	Node* node = root;
	while (node != nullptr)
	{
		if (data < node->data)
			node = node->left;
		else if (data > node->data)
			node = node->right;
		else
			return true;
	}
	return false;
}

template<typename T>
bool IterativeAVLTree<T>::remove(const T data)
{
	FixedStack<Node**> nodeStack(getHeight(root) + 1);
	Node** nodePtr = &root;
    while (true)
    { 
        if (*nodePtr == nullptr)
            return false;
		else if (data < (*nodePtr)->data)
		{
			nodeStack.push(nodePtr);
			nodePtr = &(*nodePtr)->left;
		}
		else if (data > (*nodePtr)->data)
		{
			nodeStack.push(nodePtr);
			nodePtr = &(*nodePtr)->right;
		}
		else
		{
			(*nodefindAndRemoveMin(nodePtr);
		}
    }
}
