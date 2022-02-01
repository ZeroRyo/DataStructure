#ifndef _FISH_AVL_TREE_
#define _FISH_AVL_TREE_

#include "bucket.h"
#include "stack.h"
//==================================================
//==========          AVL Tree          ==========
template <class key, class value>
class AVLTree {
	class node {
	public:
		node* left, * right;
		bucket<key, value> info;
		unsigned char height;

		//Khởi tạo
		node(const bucket<key, value>& newInfo) :
			info{ newInfo },
			left{ nullptr },
			right{ nullptr },
			height{ 1 }{};

		//Method
		void countHeight() {	//Count height again
			unsigned char leftHeight = left == nullptr ? 0 : left->height;
			unsigned char rightHeight = right == nullptr ? 0 : right->height;
			height = std::max(leftHeight, rightHeight) + 1;
		}

		void copyBucket(const bucket<key, value>& newBucket) {
			info = newBucket;
		}

		//Count left->height - right->height
		char countTilt() {
			char leftHeight = left == nullptr ? 0 : left->height;
			char rightHeight = right == nullptr ? 0 : right->height;
			return leftHeight - rightHeight;
		}

		//Static Function
		//Rotate Left
		static void rotateLeft(node*& root) {
			if (root == nullptr)
				return;

			if (root->right == nullptr)
				return;
			//Rotate Right
			node* childLeft = root;
			root = root->right;
			childLeft->right = root->left;
			root->left = childLeft;
			//Count height again
			childLeft->countHeight();
			root->countHeight();
		}

		//Rotate Right
		static void rotateRight(node*& root) {
			if (root == nullptr)
				return;

			if (root->left == nullptr)
				return;
			//Rotate Left
			node* childRight = root;
			root = root->left;
			childRight->left = root->right;
			root->right = childRight;
			//Count height again
			childRight->countHeight();
			root->countHeight();
		}

		//Balance Root
		static void balanceRoot(node*& root) {
			if (root == nullptr)
				return;

			char tilt = root->countTilt();
			//Right tilt -> Rotate Left
			if (tilt < -1) {
				if (root->right->countTilt() <= 0)	//Right subtree is right tilt
					rotateLeft(root);
				else {	//Right subtree is left tilt
					rotateRight(root->right);
					rotateLeft(root);
				}
			}
			else if (tilt > 1) {//Left tilt -> Rotate Right
				if (root->left->countTilt() >= 0)	//Left subtree is left tilt
					rotateRight(root);
				else {	//Left subtree is right tilt
					rotateLeft(root->left);
					rotateRight(root);
				}
			}
		}

		static void poorChildLeft(node*& root) {
			if (root == nullptr || root->left == nullptr)
				return;

			stack<node*&> st;
			st.push(root->left);
			while (st.get()->right != nullptr)
				st.push(st.get()->right);

			node*& temp = st.pop();
			root->info = temp->info;
			node* p = temp;
			temp = temp->left;
			delete p;

			while (!st.isEmpty())
				balanceRoot(st.pop());
		}

		static void poorChildRight(node*& root) {
			if (root == nullptr || root->right == nullptr)
				return;

			stack<node*&> st;
			st.push(root->right);
			while (st.get()->left != nullptr)
				st.push(st.get()->left);

			node*& temp = st.pop();
			root->info = temp->info;
			node* p = temp;
			temp = temp->right;
			delete p;

			while (!st.isEmpty())
				balanceRoot(st.get());
		}
	};
	//=====     Tree     =====
	node* root;
	int size, weightOut;

	//Hàm tĩnh
	static bool pushRecursive(node*& root, const bucket<key, value>& newBucket);
	static bool popRecursive(node*& root, bucket<key, value>& newBucket);
	static void outputRecursiveLNR(node*& root, const int& weight, int count, bool leftChild);
	static void clear(node* root);

public:
	//Khởi tạo
	AVLTree(int setWeight = 10) :
		root{ nullptr }, size{ 0 }, weightOut{ setWeight }
	{
		if (weightOut < 10)
			weightOut = 10;
	};

	~AVLTree() {
		clear(root);
		root = nullptr;
		size = 0;
	}

	//Phương thức
	void output() const;
	void push(const bucket<key, value>& newBucket);
	bool isEmpty() const { return root == nullptr; }
	int length() const { return size; }
	bucket<key, value> pop(const key& code);
	bucket<key, value> find(const key& code) const;
};

template <class key, class value>
void AVLTree<key, value>::clear(node* root)
{
	if (root == nullptr)
		return;
	clear(root->left);
	clear(root->right);
	delete root;
}

template <class key, class value>
bucket<key, value> AVLTree<key, value>::find(const key& code) const
{
	node* p = root;
	while (p != nullptr)
	{
		if (p->info.getKey() == code)
			return p->info;
		else if (p->info.getKey() > code)	//Tìm sang cây con trái
			p = p->left;
		else
			p = p->right;
	}
	//Không tìm thấy
	return bucket<key, value>(status::notFound);
}

template <class key, class value>
bucket<key, value> AVLTree<key, value>::pop(const key& code)
{
	bucket<key, value> res{ code };
	if (popRecursive(root, res)) {	//Exist
		size--;
		return res;
	}

	return bucket<key, value>(status::notFound);
}

template <class key, class value>
void AVLTree<key, value>::push(const bucket<key, value>& newBucket)
{
	if (!newBucket.isFull())
		return;

	if (pushRecursive(root, newBucket))
		size++;
}

template <class key, class value>
void AVLTree<key, value>::outputRecursiveLNR(node*& root, const int& weight, int count, bool leftChild)
{
	if (root == nullptr)
		return;

	outputRecursiveLNR(root->right, weight, count + 1, true);

	if (count)
		for (int i = weight * count; i > 0; i--)
			putchar(' ');
	std::cout << (leftChild ? '/' : '\\');
	std::cout << std::setw(weight - 2) << root->info.getKey() << "|\n";

	outputRecursiveLNR(root->left, weight, count + 1, false);
}

template <class key, class value>
bool AVLTree<key, value>::popRecursive(node*& root, bucket<key, value>& newBucket)
{
	if (root == nullptr)
		return false;

	bool getValue;
	if (root->info == newBucket)
	{
		newBucket = root->info;
		if (root->left == nullptr && root->right == nullptr)	//Leaf node
		{
			delete root;
			root = nullptr;
			return true;
		}

		if (root->countBalance() >= 0)	//Left tilt 
			node::poorChildLeft(root);
		else
			node::poorChildRight(root);
		return true;
	}
	else if (newBucket < root->info)	//Recursive to left subtree
		getValue = popRecursive(root->left, newBucket);
	else
		getValue = popRecursive(root->right, newBucket);//Recursive to right subtree

	node::balanceRoot(root);
	return getValue;
}

template <class key, class value>
bool AVLTree<key, value>::pushRecursive(node*& root, const bucket<key, value>& newBucket)
{
	if (root == nullptr)
	{
		root = new node(newBucket);
		return true;
	}

	bool getValue;
	if (root->info == newBucket)
	{
		root->info = newBucket;
		return false;
	}
	else if (root->info < newBucket)	////Recursive to right subtree
		getValue = pushRecursive(root->right, newBucket);
	else////Recursive to left subtree
		getValue = pushRecursive(root->left, newBucket);

	//Balance node
	root->countHeight();
	node::balanceRoot(root);
	return getValue;
}

template <class key, class value>
void AVLTree<key, value>::output() const
{
	if (root == nullptr)
	{
		std::cout << "Tree is empty\n";
		return;
	}

	outputRecursiveLNR(root->right, weightOut, 1, true);
	std::cout << '|' << std::setw(weightOut - 2) << root->info.getKey() << "|\n";
	outputRecursiveLNR(root->left, weightOut, 1, false);
}
//==================================================
#endif	//_FISH_AVL_TREE_
