#pragma once
#include <random>
#include "TreeNode.h"
#include "Stack.h"
#include "Queque.h"
///�������� ����� ��������� ������ ������
template <typename T>
class BinarySearchTree {
private:
	TreeNode<T>* root;//�������� ���� ������

	
public:
	///����������� ������
	BinarySearchTree() {
		root = nullptr;
	}

	///������� �������� � ������
	void insert(const T &value) {
		if (root == nullptr) {
			root = new TreeNode<T>(value);
			return;
		}
		insertion(value, this->root);
	}

	///����� �������� value � ������, ���������� ��������� �� ���� ������ � ����� ���������
	///���� �������� �� ������� ���������� ������� ���������
	TreeNode<T>* find(const T &value) const {
		return finding(value, this->root);
	}

	///����� ����������� ��������, ������� ������ value � ������, ���������� ��������� �� ���� ������ � ����� ���������
	///���� �������� �� ������� ���������� ������� ���������
	TreeNode<T>* successor(const T &value)const {
		return success(value,root);

	}

	///�������� �� ������ ���� �� ��������� value
	void remove(const T &value) {
		removing(value, this->root);
	}
	///����� ������ � NLR �������
	void print() const {
		printTreeNLR(root);
	}

	///���������� ���-�� ����� � ������
	size_t count()const {
		return countNodes(root);
	}

	///���������� ������� ������
	int depth() const {
		return depthOfBinTree(root);
	}
	///��������� ����� ���������. ������������ ����� � ������ ������ ���� ����� �������
	class iterator {
	private:
		Queque<TreeNode<T>*> nodeQueque;
		
	public:

		///����������� ������ ���������
		iterator(TreeNode<T>* root) {
			nodeQueque.push(root);
			
		}

		///���������� ����������� ��������� �����������
		iterator operator ++() {
			TreeNode<T>* tmp = nodeQueque.pop();
			if (tmp->left != nullptr) {
				nodeQueque.push(tmp->left);
			}
			if (tmp->right != nullptr) {
				nodeQueque.push(tmp->right);
			}
			if (nodeQueque.isEmpty()) {
				nodeQueque.push(nullptr);
			}
			return *this;
		}

		///���������� ��������� "�� �����"
		bool operator !=(const iterator& x) const {
			return this->nodeQueque.peek() != x.nodeQueque.peek();
		}

		///���������� ��������� "�����"
		bool operator ==(const iterator& x) const {
			return this->nodeQueque.peek() == x.nodeQueque.peek();
		}

		///���������� ��������� ��������� ��������
		T& operator *() {
			return nodeQueque.peek()->value;
		}
	};

	///���������� ��������, �������� ������ ������
	iterator begin() const {
		return iterator(root);
	}
	///���������� ��������, �������� ����� ������� �� ������
	iterator end() const {
		
		return iterator(nullptr);
	}

	~BinarySearchTree() {
		deleteTree(root);
	}
};


///������� ������ ���� �� ��������� value � ������ � ������ root
///���������� ��������� �� ��������� ����
/// ���� ���� �� ������, ���������� nullptr
/// C��������: O(log n) 
/// � ������ ������(������ ���������) - O(n)
template <typename T>
TreeNode<T>* finding(const T &value, TreeNode<T>* root) {
	if (root == nullptr) {
		return nullptr;
	}

	if (value == root->value) {
		return root;
	}

	if (value < root->value) {
		if (root->left != nullptr) {
			return finding(value, root->left);
		}
		else {
			return nullptr;
		}

	}
	else {
		if (root->right != nullptr) {
			return finding(value, root->right);
		}
		else {
			return nullptr;
		}
	}
}

///���������� ���� �� ��������� value � ������ � ������ root
///���������: O(log n)
///		� ������ ������(������ ���������) - O(n)
template <typename T>
void insertion(const T &value, TreeNode<T>* root) {
	if (value < root->value) {
		if (root->left == nullptr) {
			root->left = new TreeNode<T>(value);
			return;
		}
		else {
			insertion(value, root->left);
		}
	}
	else {
		if (root->right == nullptr) {
			root->right = new TreeNode<T>(value);
			return;
		}
		else {
			insertion(value, root->right);
		}
	}
}

///����� ���������� ����������� ��� value � ������ � ������ root
///���������� ��������� �� ����, ���������� ��������� ����������
/// ���� ���� �� ��������� value � ������ ��� ��� �������� ����� �������� ����������, �� ��������� nullptr
/// 
template<typename T>
TreeNode<T>* success(const T &value,TreeNode<T>*root) {
	TreeNode<T>* value_node = finding(value,root);
	if (value_node == nullptr) {
		return nullptr;
	}

	TreeNode<T>* temp;

	if (value_node->right != nullptr) {
		temp = value_node->right;
		while (temp->left != nullptr) {
			temp = temp->left;
		}
		return temp;
	}
	else {
		Stack<TreeNode<T>*> path;
		temp = root;
		
		
		while (temp != nullptr) {
			if (temp == value_node) {
				break;
			}
			path.push(temp);
			if (temp->value > value) {
				temp = temp->left;
			}

			else {
				temp = temp->right;
			}
		}

		TreeNode<T>* parent;
		while (!path.isEmpty()) {
			parent = path.pop();
			if (parent->left == temp) {
				return parent;
			}
			temp = parent;
		}
	}

	return nullptr;
}

///����� �������� ���� child � ������ root
///���������� ��������� �� ��������
/// C��������: O(log n)
template<typename T>
TreeNode<T>* findParent(TreeNode<T>* root, TreeNode<T>* child) {

	if (child == root || root == nullptr) {
		return nullptr;
	}
	TreeNode<T>* temp = root;

	while (temp != nullptr) {
		if (temp->left == child || temp->right == child) {
			return temp;
		}

		if (temp->value > child->value) {
			temp = temp->left;
		}

		else {
			temp = temp->right;
		}
	}
	return nullptr;
}

///�������� ���� �� ��������� value �� ������ � ������ root
///���������: O(log n)
///	� ������ ������(������ ���������) - O(n)
template<typename T>
void removing(const T &value, TreeNode<T>*& root) {

	if (root == nullptr) {
		return;
	}
	TreeNode<T>* del = finding(value,root);//���� �� ��������� value
	if (del == nullptr) { //���� ���� �� ������ 
		return;//������ ������� ������������
	}
	TreeNode<T>* parent= findParent(root,del); // �������� ���������� ����
	
	//���� ���� �� ����� ��������
	if (del->left == nullptr && del->right == nullptr) {
		if (parent == nullptr) {
			root = nullptr;
		} else if (parent->left == del) {
			parent->left = nullptr;
		} else {
			parent->right = nullptr;
		}
		delete del;
		
		return;
	}
	
	//���� � ���� ������ ������ �������
	if (del->left == nullptr && del->right != nullptr) {
		if (parent == nullptr) {
			root = del->right;
		} else if (parent->left == del) {
			parent->left = del->right;
		} else {
			parent->right = del->right;
		}
		delete del;
		return;
	}

	//���� � ���� ������ ����� �������
	if (del->left != nullptr && del->right == nullptr) {
		if (parent == nullptr) {
			root = del->left;
		}else if (parent->left == del) {
			parent->left = del->left;
		} else {
			parent->right = del->left;
		}
		delete del;
		return;
	}

	//���� ���� ����� ���� ��������
	TreeNode<T>* repl = success(del->value, root);
	parent = findParent(del, repl);
	std::swap(repl->value, del->value);
	if (parent->left == repl) {
		parent->left = nullptr;
	}
	else {
		parent->right = nullptr;
	}
	delete repl;
}

template <typename T>
void randomBST(BinarySearchTree<T>& bst, size_t size,long min, long max) {
	for (size_t i = 0; i < size; i++) {
		bst.insert((rand() % (max - min) + min));
	}
}

void test() {
	// ������������ ������� �� ������ � 5 ������
	BinarySearchTree<int> bst;
	bst.insert(4); // ���������� �������� 4
	bst.insert(3); // ���������� �������� 3
	bst.insert(15); // ���������� �������� 15
	bst.insert(5); // ���������� �������� 5
	bst.insert(20); // ���������� �������� 20

	// �������� ������ ���������
	assert(bst.find(4)->value == 4); // ������ ������� 4
	assert(bst.find(3)->value == 3); // ������ ������� 3
	assert(bst.find(20)->value == 20); // ������ ������� 20
	assert(bst.find(45) == nullptr); // ������� 45 �����������

	// �������� ���������� ���������� (successor)
	assert(bst.successor(3)->value == 4); // ��������� ����� 3 - ��� 4
	assert(bst.successor(15)->value == 20); // ��������� ����� 15 - ��� 20
	assert(bst.successor(4)->value == 5); // ��������� ����� 4 - ��� 5
	assert(bst.successor(20) == nullptr); // � 20 ��� ����������
	assert(bst.successor(33) == nullptr); // �������� 33 ��� � ������

	// �������� ���������� ����� � ������� ������
	assert(bst.count() == 5); // ����� 5 �����
	assert(bst.depth() == 2); // ������� ������ 2

	// �������� ���������
	bst.remove(15); // �������� �������� 15
	assert(bst.find(15) == nullptr); // ������� 15 �����������
	bst.remove(4); // �������� �������� 4
	assert(bst.find(4) == nullptr); // ������� 4 �����������
	bst.remove(20); // �������� �������� 20
	assert(bst.find(20) == nullptr); // ������� 20 �����������
	bst.remove(234); // ������� ������� �������������� �������
	assert(bst.count() == 2); // �������� 2 ��������
	assert(bst.depth() == 1); // ������� ������ 1

	// ������������ ������� �� ������ ������
	BinarySearchTree<int> bst_e;

	assert(bst_e.count() == 0); // � ������ ������ 0 �����
	assert(bst_e.depth() == -1); // ������� ������� ������ -1

	assert(bst_e.find(45) == nullptr); // �������� 45 ���
	assert(bst_e.find(0) == nullptr); // �������� 0 ���
	assert(bst_e.find(12) == nullptr); // �������� 12 ���

	assert(bst_e.successor(20) == nullptr); // � 20 ��� ����������
	assert(bst_e.successor(33) == nullptr); // � 33 ��� ����������

	// ������������ ������� �� ������ � ����� �����
	BinarySearchTree<int> bst_s;

	bst_s.insert(123); // ���������� ������������� �������� 123

	assert(bst_s.count() == 1); // � ������ 1 ����
	assert(bst_s.depth() == 0); // ������� ������ 0

	assert(bst_s.find(45) == nullptr); // �������� 45 ���
	assert(bst_s.find(123)->value == 123); // ������ ������� 123
	assert(bst_s.find(12) == nullptr); // �������� 12 ���

	assert(bst_s.successor(123) == nullptr); // � 123 ��� ����������
	assert(bst_s.successor(33) == nullptr); // �������� 33 ���

	bst_s.remove(123); // �������� �������� 123
	bst_s.remove(123); // ��������� �������� �������� 123
	assert(bst_s.find(123) == nullptr); // ������� 123 �����������

	// ������������ ������� �� ����������� ������
	BinarySearchTree<int> bst_deg;

	bst_deg.insert(8); // ���������� ������������ ������
	bst_deg.insert(7);
	bst_deg.insert(6);
	bst_deg.insert(5);
	bst_deg.insert(4);
	assert(bst_deg.count() == 5); // 5 ����� � ������
	assert(bst_deg.depth() == 4); // ������� ������ 4

	assert(bst_deg.find(45) == nullptr); // �������� 45 ���
	assert(bst_deg.find(8)->value == 8); // ������ ������� 8
	assert(bst_deg.find(7)->value == 7); // ������ ������� 7
	assert(bst_deg.find(6)->value == 6); // ������ ������� 6
	assert(bst_deg.find(5)->value == 5); // ������ ������� 5
	assert(bst_deg.find(4)->value == 4); // ������ ������� 4
	assert(bst_deg.find(12) == nullptr); // �������� 12 ���

	bst_deg.remove(4); // �������� �������� 4
	assert(bst_deg.find(4) == nullptr); // ������� 4 �����������
	bst_deg.remove(6); // �������� �������� 6
	assert(bst_deg.find(6) == nullptr); // ������� 6 �����������
	bst_deg.remove(8); // �������� �������� 8
	assert(bst_deg.find(8) == nullptr); // ������� 8 �����������

	assert(bst_deg.count() == 2); // �������� 2 ��������
	assert(bst_deg.depth() == 1); // ������� ������ 1

	// ������������ ����������
	BinarySearchTree<int> l;
	l.insert(4); // ���������� ����� ��� �����
	l.insert(2);
	l.insert(6);
	l.insert(5);
	l.insert(3);
	l.insert(1);

	auto tmp = l.begin(); // ��������� ��������
	++tmp;
	assert(tmp != l.begin()); // �������� �����������

	assert(*tmp == 2); // �������� �������� ���� 2
	++tmp;
	assert(*tmp == 6); // �������� �������� ���� 6
	++tmp;
	assert(*tmp == 1); // �������� �������� ���� 1
	++tmp;
	assert(*tmp == 3); // �������� �������� ���� 3
	++tmp;
	assert(*tmp == 5); // �������� �������� ���� 5
	++tmp;
	assert(tmp == l.end()); // �������� ������ �����

	// ��� ������� ������
	BinarySearchTree<int> e;
	assert(e.begin() == e.end()); // �������� ������� ������ ����� end
	std::cout << "all test complete!\n";
}
