#pragma once
#include <exception>
#include <vector>
#include <cassert>
#include "Queque.h"
///��������� ����� ���� ��������� ������
template <typename T>
class TreeNode {
public:

	T value;//�������� �������� � ���� ������
	TreeNode* left;//����� ������� ����
	TreeNode* right;//������ ������� ����

	///����������� ��� ����������
	TreeNode() {
		value = 0;
		left = nullptr;
		right = nullptr;
	}

	///����������� � ���������� 
	///value - �������� ����
	TreeNode(const T& value) {
		this->value = value;
		left = nullptr;
		right = nullptr;
	}

	///����� ������������ � ���� ������� ����
	///������� ����������, ���� ����������� ������� ��������� ���� � ���� � ����� ���������
	void attach(TreeNode* another) {
		if (this->left == nullptr) {
			this->left = another;
		}
		else if (this->right == nullptr) {
			this->right = another;
		}
		else {
			throw std::runtime_error("� ����� ���� ������ ������ ��������� ������ ����");
		}
	}

};

///��������� ������� �������� ���� ����� ��������� ������, �������� ����������
///root - ��������� �� ������ ���������� ��������� ������
/// ���������� LRN �����
/// ���������: O(n)
template <typename T>
void deleteTree(TreeNode<T>* root) {
	if (root == nullptr) {
		return;
	}
	//���� � ���� ���� ����� �������, �� ���������� �������� ������� ��� ������ �������
	if (root->left != nullptr) {
		deleteTree(root->left);
	}
	//���� � ���� ���� ������ �������, �� ���������� �������� ������� ��� ������� �������
	if (root->right != nullptr) {
		deleteTree(root->right);
	}
	//�������� ������� ���� ������
	delete root;
}


///������� �������� ���� ����� ��������� ������
///���������� NLR �����
/// ���������: O(n)
template <typename T>
size_t countNodes(TreeNode<T>* root) {
	if (root == nullptr) { //������ ������
		return 0;//��������� 0
	}


	size_t count = 0; //���-�� �����
	if (root != nullptr) {
		count++;//����������� count
	}

	if (root->left != nullptr) {
		count += countNodes(root->left);//����������� ����� ������� ��� ������ �������
	}
	if (root->right != nullptr) {
		count += countNodes(root->right);//����������� ����� ������� ��� ������ �������
	}
	return count;
}


///������� ������ ���� �������� ������
///������������ LNR �����
/// ���������: O(n)
template <typename T>
void printTreeLNR(TreeNode<T>* root) {
	//���� ������ ������, ������� ������ �� �������
	if (root == nullptr) {
		return;
	}

	//����������� ����� ������� ��� ������ �������
	if (root->left != nullptr) {
		printTreeLNR(root->left);
	}

	//����� �������� ����
	if (root != nullptr) {
		std::cout << root->value << ' ';
	}

	//����������� ����� ������� ��� ������� �������
	if (root->right != nullptr) {
		printTreeLNR(root->right);
	}
}


///������� ������ ���� �������� ������
///������������ LRN �����
/// ���������: O(n)
template <typename T>
void printTreeLRN(TreeNode<T>* root) {
	if (root == nullptr) {//���� ������ ������, ������� ������ �� �������
		return;
	}
	//����������� ����� ������� ��� ������ �������
	if (root->left != nullptr) {
		printTreeLRN(root->left);
	}
	//����������� ����� ������� ��� ������� �������
	if (root->right != nullptr) {
		printTreeLRN(root->right);
	}
	//����� �������� ����
	if (root != nullptr) {
		std::cout << root->value << ' ';
	}
}

///������� ������ ���� �������� ������
///������������ NLR �����
/// ���������: O(n)
template <typename T>
void printTreeNLR(TreeNode<T>* root) {
	//���� ������ ������, ������� ������ �� �������
	if (root == nullptr) {
		return;
	}
	//����� �������� ����
	if (root != nullptr) {
		std::cout << root->value << ' ';
	}
	//����������� ����� ������� ��� ������ �������
	if (root->left != nullptr) {
		printTreeNLR(root->left);
	}
	//����������� ����� ������� ��� ������� �������
	if (root->right != nullptr) {
		printTreeNLR(root->right);
	}
}

///������� ����������� �������, ���������� � �������� ��������� �� ���� ����� ������
///���������� NLR �����
/// ���������: O(n)
template <typename T>
void funcToTreeNLR(TreeNode<T>* root, void (*func)(T*)) {
	if (root == nullptr) {
		return;
	}
	if (root != nullptr) {
		func(&root->value);
	}
	if (root->left != nullptr) {
		funcToTreeNLR(root->left, func);
	}
	if (root->right != nullptr) {
		funcToTreeNLR(root->right, func);
	}
}

///������� ����������� �������, ���������� � �������� ��������� �� ���� ����� ������
///���������� LNR �����
/// ���������: O(n)
template <typename T>
void funcToTreeLNR(TreeNode<T>* root, void (*func)(T*)) {
	if (root == nullptr) {
		return;
	}
	if (root->left != nullptr) {
		funcToTreeLNR(root->left, func);
	}
	if (root != nullptr) {
		func(&root->value);
	}
	if (root->right != nullptr) {
		funcToTreeLNR(root->right, func);
	}
}

///������� ����������� �������, ���������� � �������� ��������� �� ���� ����� ������
///���������� RLN �����
/// ���������: O(n)
template <typename T>
void funcToTreeRLN(TreeNode<T>* root, void (*func)(T*)) {
	if (root == nullptr) {
		return;
	}
	if (root->right != nullptr) {
		funcToTreeRLN(root->right, func);
	}
	if (root->left != nullptr) {
		funcToTreeRLN(root->left, func);
	}
	if (root != nullptr) {
		func(&root->value);
	}

}


///����������� �������� �� ������ root � ������ dest
///���������� RLN �����
/// ���������: O(n)
template <typename T>
void treeToVectorRLN(TreeNode<T>* root, std::vector<T>* dest) {
	if (root == nullptr) {
		return;
	}
	if (root->right != nullptr) {
		treeToVectorRLN(root->right, dest);
	}
	if (root->left != nullptr) {
		treeToVectorRLN(root->left, dest);
	}
	if (root != nullptr) {
		dest->push_back(root->value);
	}
}

///����������� �������� �� ������ root � ������ dest
///���������� LNR �����
/// ���������: O(n)
template <typename T>
void treeToVectorLNR(TreeNode<T>* root, std::vector<T>* dest) {
	if (root == nullptr) {
		return;
	}

	if (root->left != nullptr) {
		treeToVectorLNR(root->left, dest);
	}

	if (root != nullptr) {
		dest->push_back(root->value);
	}
	if (root->right != nullptr) {
		treeToVectorLNR(root->right, dest);
	}

}

///����������� �������� �� ������ root � ������ dest
///���������� NRL �����
///���������: O(n)
template <typename T>
void treeToVectorNRL(TreeNode<T>* root, std::vector<T>* dest) {
	if (root == nullptr) {
		return;
	}

	if (root != nullptr) {
		dest->push_back(root->value);
	}
	if (root->right != nullptr) {
		treeToVectorNRL(root->right, dest);

	}

	if (root->left != nullptr) {
		treeToVectorNRL(root->left, dest);
	}

}


///������� ���������� ������� ������ root
template <typename T>
int depthOfBinTree(TreeNode<T>* root) {

	if (root == nullptr) { // ���� ������ ������
		return -1; //���������� -1
	}

	if (root->left == nullptr && root->right == nullptr) { //���� ������ ������� ������ �� ������ ����
		return 0;//���������� 0
	}

	int left = 0, right = 0;
	if (root->left != nullptr) { // ���� � ����� ���� ����� �������
		left = depthOfBinTree(root->left);//������� ������� ������ ���������
	}

	if (root->right != nullptr) { // ���� � ����� ���� ������ �������
		right = depthOfBinTree(root->right);//������� ������� ������� ���������
	}

	return (left > right ? left : right) + 1;//���������� ������� ������ ��������� �� ����������� + 1
}

///������� ����� ������ source � ��������� ��������� �� ������ ���������� ������
template <typename T>
TreeNode<T>* BinTreeCopy(TreeNode<T>* source) {
	if (source == nullptr) {//���� ������ ������
		return nullptr;//���������� nullptr
	}

	TreeNode<T>* destination = new TreeNode<int>(source->value);//������ � ������� ����� ����������� ���� ��������� ������

	destination->left = BinTreeCopy(source->left);  // ����������� ����� ������� ��� ������ ���������
	destination->right = BinTreeCopy(source->right);//����������� ����� ������� ��� ������� ���������

	return destination;//���������� ������ - ��������
}

///����� ���� ��������� ������ � ������ root � ������� � ������
///���������: O(n)
template <typename T>
void printTreeWidth(TreeNode<T>* root) {
	if (root == nullptr) {
		return;
	}
	Queque<TreeNode<T>*> que;//������� ��� ������
	TreeNode<int>* tmp;//���� � ������� ����� ������������ ��������
	que.push(root);/*�������� ������ � �������*/
	
	while (!que.isEmpty()) {//���� ������� �� �����
		tmp = que.pop();//��������� ������� ������ �� �������
		std::cout << tmp->value<<' ';//�����

		//�������� ����� �������
		if (tmp->left != nullptr) {
			que.push(tmp->left);
		}
		//�������� ������ ������
		if (tmp->right != nullptr) {
			que.push(tmp->right);
		}
	}
}

///����������� �������� �� ������ root � ������ dest
///���������� NRL �����
///���������: O(n)
template <typename T>
void treeToVectorWidth(TreeNode<T>* root, std::vector<TreeNode<T>*>* dest) {
	if (root == nullptr) {
		return;
	}
	Queque<TreeNode<T>*> que;//������� ��� ������
	TreeNode<T>* tmp;//���� � ������� ����� ������������ ��������
	que.push(root);/*�������� ������ � �������*/

	while (!que.isEmpty()) {//���� ������� �� �����
		tmp = que.pop();//��������� ������� ������ �� �������
		dest->push_back(tmp);

		//�������� ����� �������
		if (tmp->left != nullptr) {
			que.push(tmp->left);
		}
		//�������� ������ ������
		if (tmp->right != nullptr) {
			que.push(tmp->right);
		}
	}
}

namespace bin_tree{
	void test() {
		//������, ��������� �� 5 �����
		TreeNode<int>* a = new TreeNode<int>(2),
			* b = new TreeNode<int>(4),
			* c = new TreeNode<int>(8),
			* d = new TreeNode<int>(16),
			* e = new TreeNode<int>(32);

		TreeNode<int>* em = nullptr;//������ ������

		TreeNode<int>* vd = new TreeNode<int>(2);//����������� ������

		vd->attach(new TreeNode<int>(4));
		vd->left->attach(new TreeNode<int>(8));
		vd->left->left->attach(new TreeNode<int>(16));
		vd->left->left->left->attach(new TreeNode<int>(32));

		a->attach(b);
		a->attach(c);
		b->attach(d);
		b->attach(e);

		//�������� ������������ ����� ����� � ������
		assert(a->value == 2);
		assert(a->left->value == 4);
		assert(a->right->value == 8);
		assert(a->left->left->value == 16);
		assert(a->left->right->value == 32);

		//�������� ���������� ������� ��� ������� ���� ������
		funcToTreeRLN<int>(a, [](int* a)->void { *a /= 2; });
		assert(a->value == 1);
		assert(a->left->value == 2);
		assert(a->right->value == 4);
		assert(a->left->left->value == 8);
		assert(a->left->right->value == 16);

		//�������� ������ ������� ����������  ������� ������
		assert(depthOfBinTree(a) == 2);
		assert(depthOfBinTree(em) == -1);
		assert(depthOfBinTree(vd) == 4);

		//�������� ������ ������� ���������� ���-�� ����� ������
		assert(countNodes(a) == 5);
		assert(countNodes(vd) == 5);
		assert(countNodes(em) == 0);

		std::vector<int> arrt;

		//�������� ����������� �������� ����� �������� � ������
		treeToVectorLNR(a, &arrt);
		assert(arrt[0] == 8 && arrt[1] == 2 && arrt[2] == 16 && arrt[3] == 1 && arrt[4] == 4);
		arrt.clear();
		treeToVectorNRL(a, &arrt);
		assert(arrt[0] == 1 && arrt[1] == 4 && arrt[2] == 2 && arrt[3] == 16 && arrt[4] == 8);
		arrt.clear();
		treeToVectorRLN(a, &arrt);
		assert(arrt[0] == 4 && arrt[1] == 16 && arrt[2] == 8 && arrt[3] == 2 && arrt[4] == 1);
		arrt.clear();


		treeToVectorNRL(vd, &arrt);
		assert(arrt[0] == 2 && arrt[1] == 4 && arrt[2] == 8 && arrt[3] == 16 && arrt[4] == 32);
		arrt.clear();
		treeToVectorLNR(em, &arrt);
		assert(arrt.size() == 0);

		//�������� ������� ����������� ������
		em = BinTreeCopy(a);
		assert(em->value == 1);
		assert(em->left->value == 2);
		assert(em->right->value == 4);
		assert(em->left->left->value == 8);
		assert(em->left->right->value == 16);

		deleteTree(em);
		//�������� ������� ����������� ������������ ������
		em = BinTreeCopy(vd);
		assert(em->value == 2);
		assert(em->left->value == 4);
		assert(em->left->left->value == 8);
		assert(em->left->left->left->value == 16);

		//�������� ������ ������� ��� ������, ���������� �� ������ ����
		TreeNode<int>* stub = new TreeNode<int>(52);
		assert(countNodes(stub) == 1);
		assert(depthOfBinTree(stub) == 0);
		funcToTreeRLN<int>(stub, [](int* a)->void { *a /= 2; });
		assert(stub->value == 26);

		arrt.clear();
		treeToVectorLNR(stub, &arrt);
		assert(arrt[0] == 26);
		arrt.clear();
		treeToVectorNRL(stub, &arrt);
		assert(arrt[0] == 26);
		arrt.clear();
		treeToVectorRLN(stub, &arrt);
		assert(arrt[0] == 26);
		assert(arrt.size() == 1);
		arrt.clear();
		deleteTree(em);
		deleteTree(a);
		deleteTree(stub);
		deleteTree(vd);
	}
}