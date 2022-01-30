#ifndef _FISH_RED_BLACK_TREE_
#define _FISH_RED_BLACK_TREE_

#include "bucket.h"
//==================================================
//==========          Red Black Tree          ==========
template <class key, class value>
class RBTree {
	enum class colors { RED, BLACK };

	class node {
	public:
		bucket<key, value> info;
		node* left, * right, * parent;
		colors color;

		//Constructor
		node(const bucket<key, value>& newBucket) {
			info = newBucket;
			left = right = parent = nullptr;
			color = colors::RED;
		}

		//Method
		void connectLeft(node* leftChild) {
			left = leftChild;
			if (leftChild)
				leftChild->parent = this;
		}

		void connectRight(node* rightChild) {
			right = rightChild;
			if (rightChild)
				rightChild->parent = this;
		}

		//Static function
		static void rotateRight(node*& root) {
			if (root->left == nullptr)
				return;

			node* rootParent = root->parent;
			node* temp = root->left;
			root->connectLeft(temp->right);
			temp->connectRight(root);
			root = temp;
			temp->parent = rootParent;
		}

		static void rotateLeft(node*& root) {
			if (root->right == nullptr)
				return;

			node* rootParent = root->parent;
			node* temp = root->right;
			root->connectRight(temp->left);
			temp->connectLeft(root);
			root = temp;
			temp->parent = rootParent;
		}

		static bool isBlack(node* root) {
			return root == nullptr || root->color == colors::BLACK;
		}

		static bool isRed(node* root) {
			return root != nullptr && root->color == colors::RED;
		}

		static node* uncle(node* n) {
			if (n->parent == n->parent->parent->left)
				return n->parent->parent->right;
			return n->parent->parent->left;
		}

		static node* sibling(node* n) {
			if (n == n->parent->left)
				return n->parent->right;
			return n->parent->left;
		}

		static node*& refSibling(node* n) {
			if (n == n->parent->left)
				return n->parent->right;
			return n->parent->left;
		}

		static node*& refParent(node* n) {
			node* Parent = n->parent;
			if (Parent == Parent->parent->left)
				return Parent->parent->left;
			return Parent->parent->right;
		}

		static node*& refGrandParent(node* n) {
			node* grandParent = n->parent->parent;
			if (grandParent == grandParent->parent->left)
				return grandParent->parent->left;
			return grandParent->parent->right;
		}

		//n == Root
		static void insertCase1(node*& root, node*& n) {
			if (n->parent == nullptr)
				n->color = colors::BLACK;
			else
				insertCase2(root, n);
		}

		//Parent is black
		static void insertCase2(node*& root, node*& n) {
			if (n->parent->color == colors::BLACK)
				return;
			insertCase3(root, n);
		}

		//n, parent, uncle is red
		static void insertCase3(node*& root, node*& n) {
			node* Uncle = uncle(n);
			if (Uncle != nullptr && Uncle->color == colors::RED)
			{
				Uncle->color = n->parent->color = colors::BLACK;
				n->parent->parent->color = colors::RED;

				if (n->parent->parent == root)
					insertCase1(root, n->parent->parent);
				else
					insertCase1(root, refGrandParent(n));
			}
			else
				insertCase4(root, n);
		}

		//n, parent is red, uncle is black
		static void insertCase4(node*& root, node*& n) {
			node* grandParend = n->parent->parent;
			if (n == n->parent->right && n->parent == grandParend->left) {
				rotateLeft(grandParend->left);
				insertCase5(root, grandParend->left->left);
				return;
			}
			else if (n == n->parent->left && n->parent == grandParend->right) {
				rotateRight(grandParend->right);
				insertCase5(root, grandParend->right->right);
				return;
			}

			insertCase5(root, n);
		}

		static void insertCase5(node*& root, node*& n) {
			node* grandParent = n->parent->parent;
			grandParent->color = colors::RED;
			n->parent->color = colors::BLACK;

			if (n == n->parent->left && n->parent == grandParent->left) {
				if (grandParent == root) rotateRight(root);
				else rotateRight(refGrandParent(n));
			}
			else {
				if (grandParent == root) rotateLeft(root);
				else rotateLeft(refGrandParent(n));
			}
		}

		static void deleteNode(node*& root, node*& n) {
			node* oneChild = n->left != nullptr ? n->left : n->right;

			if (n->color == colors::BLACK) {
				if (isBlack(oneChild))
					deleteCase1(root, n);//
				else
					oneChild->color = colors::BLACK;
			}

			if (n == root) {
				delete root;
				root = oneChild;
				if (root)
					root->parent = nullptr;
				return;
			}

			node* temp = n;
			if (n == n->parent->left)
				n->parent->connectLeft(oneChild);
			else
				n->parent->connectRight(oneChild);
			delete temp;
		}

		static void deleteCase1(node*& root, node*& n) {
			if (n->parent == nullptr)
				return;
			deleteCase2(root, n);
		}

		static void deleteCase2(node*& root, node*& n) {
			node* Sibling = sibling(n);

			if (Sibling->color == colors::RED)
			{
				n->parent->color = colors::RED;
				Sibling->color = colors::BLACK;

				node*& refNodeParent = n->parent == root ? root : refParent(n);
				if (n == n->parent->left)
					rotateLeft(refNodeParent);
				else
					rotateRight(refNodeParent);
			}

			deleteCase3(root, n);
		}

		static void deleteCase3(node*& root, node*& n) {
			node* Sibling = sibling(n);	//n, nP, nS, 2 subtree of nS is black
			if (n->parent->color == colors::BLACK &&
				Sibling->color == colors::BLACK &&
				isBlack(Sibling->left) && isBlack(Sibling->right))
			{
				Sibling->color = colors::RED;
				if (n->parent == root)
					deleteCase1(root, root);
				else
					deleteCase1(root, refParent(n));
			}
			else
				deleteCase4(root, n);
		}

		static void deleteCase4(node*& root, node*& n) {
			node* Sibling = sibling(n);	//n, nS, 2 subtree of nS is black, nP is red
			if (n->parent->color == colors::RED &&
				Sibling->color == colors::BLACK &&
				isBlack(Sibling->left) && isBlack(Sibling->right))
			{
				n->parent->color = colors::BLACK;
				Sibling->color = colors::RED;
			}
			else
				deleteCase5(root, n);
		}

		static void deleteCase5(node*& root, node*& n) {
			node* Sibling = sibling(n);
			if (n == n->parent->left && Sibling->color == colors::BLACK &&
				isRed(Sibling->left) && isBlack(Sibling->right))
			{
				Sibling->color = colors::RED;
				Sibling->left->color = colors::BLACK;
				rotateRight(refSibling(n));
			}
			else if (n == n->parent->right && Sibling->color == colors::BLACK &&
				isRed(Sibling->right) && isBlack(Sibling->left))
			{
				Sibling->color = colors::RED;
				Sibling->right->color = colors::BLACK;
				rotateLeft(refSibling(n));
			}

			deleteCase6(root, n);
		}

		static void deleteCase6(node*& root, node*& n) {
			node* Sibling = sibling(n);
			Sibling->color = n->parent->color;
			n->parent->color = colors::BLACK;

			node*& refNodeParent = n->parent == root ? root : refParent(n);
			if (n == n->parent->left) {
				Sibling->right->color = colors::BLACK;
				rotateLeft(refNodeParent);
			}
			else {
				Sibling->left->color = colors::BLACK;
				rotateRight(refNodeParent);
			}
		}

		//Delete node have two child
		static void findPoorLeftChild(node*& root, node* nodeDelete) {
			if (nodeDelete->left->right == nullptr)
			{
				nodeDelete->info = nodeDelete->left->info;
				deleteNode(root, nodeDelete->left);
				return;
			}

			node* temp = nodeDelete->left;
			for (; temp->right->right; temp = temp->right);
			nodeDelete->info = temp->right->info;
			deleteNode(root, temp->right);
		}
	};

	static void outputRecursiveLNR(node*& root, const int& weight, int count, bool leftChild);
	static void clear(node* root);

	node* root;
	int size, weightOut;
public:
	//Constructor
	RBTree(int setWeight = 10) :
		root{ nullptr }, size{ 0 }, weightOut{ setWeight }
	{
		if (weightOut < 10)
			weightOut = 10;
	}

	~RBTree() {
		clear(root);
		root = nullptr;
		size = 0;
	}

	//Method
	void output() const;
	void push(const bucket<key, value>& newBucket);
	int length() const { return size; };
	bucket<key, value> pop(const key& code);
	bucket<key, value> find(const key& code) const;
};

template <class key, class value>
bucket<key, value> RBTree<key, value>::find(const key& code) const
{
	node* p = root;
	while (p != nullptr)
	{
		if (p->info.getKey() == code)
			return p->info;
		else if (p->info.getKey() > code)
			p = p->left;
		else
			p = p->right;
	}
	//Not found
	return bucket<key, value>(status::notFound);
}

template <class key, class value>
void RBTree<key, value>::clear(node* root)
{
	if (root == nullptr)
		return;

	clear(root->left);
	clear(root->right);
	delete root;
}

template <class key, class value>
bucket<key, value> RBTree<key, value>::pop(const key& code)
{
	if (root == nullptr)
		return bucket<key, value>(status::notFound);

	bucket<key, value> getBucket(code);
	if (root->info == getBucket) {
		getBucket = root->info;
		if (root->left && root->right)
			node::findPoorLeftChild(root, root);
		else
			node::deleteNode(root, root);
		size--;
		return getBucket;
	}

	node* p = root;
	while (true) {
		if (p->info > getBucket) {	//Bucket in left subtree
			if (p->left == nullptr)	break;
			if (p->left->info == getBucket) {
				getBucket = p->left->info;

				if (p->left->left && p->left->right)
					node::findPoorLeftChild(root, p->left);
				else
					node::deleteNode(root, p->left);
				size--;
				return getBucket;
			}
			p = p->left;
		}
		else {	//Bucket in right subtree
			if (p->right == nullptr)	break;
			if (p->right->info == getBucket) {
				getBucket = p->right->info;

				if (p->right->left && p->right->right)
					node::findPoorLeftChild(root, p->right);
				else
					node::deleteNode(root, p->right);
				size--;
				return getBucket;
			}
			p = p->right;
		}
	}
	return bucket<key, value>(status::notFound);
}

template <class key, class value>
void RBTree<key, value>::push(const bucket<key, value>& newBucket)
{
	if (!newBucket.isFull())
		return;

	if (root == nullptr)
	{
		root = new node(newBucket);
		root->color = colors::BLACK;
		size = 1;
		return;
	}

	node* p = root;
	while (p)
	{
		if (p->info == newBucket)
		{
			p->info = newBucket;
			return;
		}
		else if (p->info > newBucket) {
			if (p->left == nullptr)
			{
				p->connectLeft(new node(newBucket));
				node::insertCase1(root, p->left);
				size++;
				return;
			}
			p = p->left;
		}
		else {
			if (p->right == nullptr)
			{
				p->connectRight(new node(newBucket));
				node::insertCase1(root, p->right);
				size++;
				return;
			}
			p = p->right;
		}
	}
}

template <class key, class value>
void RBTree<key, value>::outputRecursiveLNR(node*& root, const int& weight, int count, bool leftChild)
{
	if (root == nullptr)
		return;

	outputRecursiveLNR(root->right, weight, count + 1, true);

	if (count)
		for (int i = weight * count; i > 0; i--)
			putchar(' ');
	std::cout << (leftChild ? '/' : '\\');
	std::cout << std::setw(weight - 2) << root->info.getKey();
	if (root->color == colors::BLACK)
		std::cout << "]\n";
	else
		std::cout << ")\n";

	outputRecursiveLNR(root->left, weight, count + 1, false);
}

template <class key, class value>
void RBTree<key, value>::output() const
{
	if (root == nullptr)
	{
		std::cout << "Tree is empty\n";
		return;
	}

	outputRecursiveLNR(root->right, weightOut, 1, true);
	std::cout << '[' << std::setw(weightOut - 2) << root->info.getKey() << "]\n";
	outputRecursiveLNR(root->left, weightOut, 1, false);
}
//==================================================
#endif	//_FISH_RED_BLACK_TREE_
