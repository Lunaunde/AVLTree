template<typename T>
class AVLTree
{
    static_assert(std::is_default_constructible_v<T>, "Type must be default constructible");
    static_assert(std::is_copy_constructible_v<T>, "Type must be copy constructible");

    // 最重要：确保类型支持比较操作
    static_assert(std::is_same_v<decltype(std::declval<T>() < std::declval<T>()), bool>,"Type must support < operator");
    static_assert(std::is_same_v<decltype(std::declval<T>() == std::declval<T>()), bool>,"Type must support == operator");

	private:
		struct Node;
		Node *root;
        bool static balanced;
        void deleteTree(Node *&node);
		int getHeight(Node *node);
        int calculateHeight(Node* node);
        void leftRotate(Node *&node);
        void rightRotate(Node *&node);
        void leftRightRotate(Node *&node);
        void rightLeftRotate(Node *&node);
        void insert(const T data, Node *&root);

        void safelyleftRotate(Node *&node);
        void safelyrightRotate(Node *&node);

        bool search(const T data, Node *node);
        void print(Node *node);

	public:
        AVLTree();
        ~AVLTree();
        void insert(const T data);
        bool search(const T data);
        void print();
};