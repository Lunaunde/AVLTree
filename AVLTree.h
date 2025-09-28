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
        void deleteTree(Node *&node);
		int getHeight(Node *node);
        void insert(const T data, Node *&root);

	public:
        AVLTree();
        ~AVLTree();
        void insert(const T data);
};