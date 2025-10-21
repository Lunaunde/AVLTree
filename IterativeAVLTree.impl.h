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
	}
}

template<typename T>
IterativeAVLTree<T>::IterativeAVLTree() : root(nullptr);

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
	FixedStack<Node**> nodeStack(getHeight(root));
	Node** nodePtr = &root;
	while (true)
	{
		if (*node == nullptr)
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
		if(balanceInsert(nodeStack.top()))
			break;
        nodeStack.pop();
	}
    return true;
}