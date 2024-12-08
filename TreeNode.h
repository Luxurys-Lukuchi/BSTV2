#pragma once
#include <exception>
#include <vector>
#include <cassert>
#include "Queque.h"
///Шаблонный класс узла бинарного дерева
template <typename T>
class TreeNode {
public:

	T value;//значение хранимое в узле дерева
	TreeNode* left;//левый потомок узла
	TreeNode* right;//правый потомок узла

	///конструктор без параметров
	TreeNode() {
		value = 0;
		left = nullptr;
		right = nullptr;
	}

	///Конструктор с параметром 
	///value - значение узла
	TreeNode(const T& value) {
		this->value = value;
		left = nullptr;
		right = nullptr;
	}

	///Метод прикрепления к узлу другого узла
	///Бросает исключение, если произведена попытка привязать узел к узлу с двумя потомками
	void attach(TreeNode* another) {
		if (this->left == nullptr) {
			this->left = another;
		}
		else if (this->right == nullptr) {
			this->right = another;
		}
		else {
			throw std::runtime_error("К этому узлу больше нельзя привязать другие узлы");
		}
	}

};

///Шаблонная функция удаления всех узлов бинарного дерева, работает рекурсивно
///root - указатель на корень удаляемого бинарного дерева
/// Использует LRN обход
/// Сложность: O(n)
template <typename T>
void deleteTree(TreeNode<T>* root) {
	if (root == nullptr) {
		return;
	}
	//если у узла есть левый потомок, то рекурсивно вызываем функцию для левого потомка
	if (root->left != nullptr) {
		deleteTree(root->left);
	}
	//если у узла есть правый потомок, то рекурсивно вызываем функцию для правого потомка
	if (root->right != nullptr) {
		deleteTree(root->right);
	}
	//удаление обьекта узла дерева
	delete root;
}


///Функция подсчета всех узлов бинарного дерева
///Использует NLR обход
/// Сложность: O(n)
template <typename T>
size_t countNodes(TreeNode<T>* root) {
	if (root == nullptr) { //дерево пустое
		return 0;//возращаем 0
	}


	size_t count = 0; //кол-во узлов
	if (root != nullptr) {
		count++;//увеличиваем count
	}

	if (root->left != nullptr) {
		count += countNodes(root->left);//рекурсивный вызов фукнции для левого потомка
	}
	if (root->right != nullptr) {
		count += countNodes(root->right);//рекурсивный вызов фукнции для левого потомка
	}
	return count;
}


///Функция вывода всех элементв дерева
///Используется LNR обход
/// Сложность: O(n)
template <typename T>
void printTreeLNR(TreeNode<T>* root) {
	//если дерево пустое, функция ничего не выведет
	if (root == nullptr) {
		return;
	}

	//рекурсивный вызов функции для левого потомка
	if (root->left != nullptr) {
		printTreeLNR(root->left);
	}

	//вывож значения узла
	if (root != nullptr) {
		std::cout << root->value << ' ';
	}

	//рекурсивный вызов функции для правого потомка
	if (root->right != nullptr) {
		printTreeLNR(root->right);
	}
}


///Функция вывода всех элементв дерева
///Используется LRN обход
/// Сложность: O(n)
template <typename T>
void printTreeLRN(TreeNode<T>* root) {
	if (root == nullptr) {//если дерево пустое, функция ничего не выведет
		return;
	}
	//рекурсивный вызов функции для левого потомка
	if (root->left != nullptr) {
		printTreeLRN(root->left);
	}
	//рекурсивный вызов функции для правого потомка
	if (root->right != nullptr) {
		printTreeLRN(root->right);
	}
	//вывод значения узла
	if (root != nullptr) {
		std::cout << root->value << ' ';
	}
}

///Функция вывода всех элементв дерева
///Используется NLR обход
/// Сложность: O(n)
template <typename T>
void printTreeNLR(TreeNode<T>* root) {
	//если дерево пустое, функция ничего не выведет
	if (root == nullptr) {
		return;
	}
	//вывод значения узла
	if (root != nullptr) {
		std::cout << root->value << ' ';
	}
	//рекурсивный вызов функции для левого потомка
	if (root->left != nullptr) {
		printTreeNLR(root->left);
	}
	//рекурсивный вызов функции для правого потомка
	if (root->right != nullptr) {
		printTreeNLR(root->right);
	}
}

///Функция применяющая функцию, переданную в качестве параметра ко всем узлам дерева
///Использует NLR обход
/// Сложность: O(n)
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

///Функция применяющая функцию, переданную в качестве параметра ко всем узлам дерева
///Использует LNR обход
/// Сложность: O(n)
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

///Функция применяющая функцию, переданную в качестве параметра ко всем узлам дерева
///Использует RLN обход
/// Сложность: O(n)
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


///Копирование значений из дерева root в массив dest
///Использует RLN обход
/// Сложность: O(n)
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

///Копирование значений из дерева root в массив dest
///Использует LNR обход
/// Сложность: O(n)
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

///Копирование значений из дерева root в массив dest
///Использует NRL обход
///Сложность: O(n)
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


///Функция нахождения глубины дерева root
template <typename T>
int depthOfBinTree(TreeNode<T>* root) {

	if (root == nullptr) { // если дерево пустое
		return -1; //возвращаем -1
	}

	if (root->left == nullptr && root->right == nullptr) { //есил дерево состоит только из одного узла
		return 0;//возвращаем 0
	}

	int left = 0, right = 0;
	if (root->left != nullptr) { // если у корня есть левый потомок
		left = depthOfBinTree(root->left);//находим глубины левого поддерева
	}

	if (root->right != nullptr) { // если у корня есть правый потомок
		right = depthOfBinTree(root->right);//находим глубину правого поддерева
	}

	return (left > right ? left : right) + 1;//возвращаем глубины самого глубокого из поддеревьев + 1
}

///Создает копию дерева source и возращает указатель на корень созданного дерева
template <typename T>
TreeNode<T>* BinTreeCopy(TreeNode<T>* source) {
	if (source == nullptr) {//если дерево пустое
		return nullptr;//возвращаем nullptr
	}

	TreeNode<T>* destination = new TreeNode<int>(source->value);//дерево в которое будут скопированы узлы исходного дерева

	destination->left = BinTreeCopy(source->left);  // рекурсивный вызов функции для левого поддерева
	destination->right = BinTreeCopy(source->right);//рекурсивный вызов функции для правого поддерева

	return destination;//возвращаем дерево - приемник
}

///Вывод всех элементов дерева с корнем root с обходом в ширину
///Сложность: O(n)
template <typename T>
void printTreeWidth(TreeNode<T>* root) {
	if (root == nullptr) {
		return;
	}
	Queque<TreeNode<T>*> que;//очередь для обхода
	TreeNode<int>* tmp;//узел с которым будет производится операция
	que.push(root);/*помещаем корень в очередь*/
	
	while (!que.isEmpty()) {//пока очередь не пуста
		tmp = que.pop();//извлекаем элемент дерева из очереди
		std::cout << tmp->value<<' ';//вывод

		//помещаем левый потомок
		if (tmp->left != nullptr) {
			que.push(tmp->left);
		}
		//помещаем правый потомк
		if (tmp->right != nullptr) {
			que.push(tmp->right);
		}
	}
}

///Копирование значений из дерева root в массив dest
///Использует NRL обход
///Сложность: O(n)
template <typename T>
void treeToVectorWidth(TreeNode<T>* root, std::vector<TreeNode<T>*>* dest) {
	if (root == nullptr) {
		return;
	}
	Queque<TreeNode<T>*> que;//очередь для обхода
	TreeNode<T>* tmp;//узел с которым будет производится операция
	que.push(root);/*помещаем корень в очередь*/

	while (!que.isEmpty()) {//пока очередь не пуста
		tmp = que.pop();//извлекаем элемент дерева из очереди
		dest->push_back(tmp);

		//помещаем левый потомок
		if (tmp->left != nullptr) {
			que.push(tmp->left);
		}
		//помещаем правый потомк
		if (tmp->right != nullptr) {
			que.push(tmp->right);
		}
	}
}

namespace bin_tree{
	void test() {
		//дерево, состоящее из 5 узлов
		TreeNode<int>* a = new TreeNode<int>(2),
			* b = new TreeNode<int>(4),
			* c = new TreeNode<int>(8),
			* d = new TreeNode<int>(16),
			* e = new TreeNode<int>(32);

		TreeNode<int>* em = nullptr;//пустое дерево

		TreeNode<int>* vd = new TreeNode<int>(2);//вырожденное дерево

		vd->attach(new TreeNode<int>(4));
		vd->left->attach(new TreeNode<int>(8));
		vd->left->left->attach(new TreeNode<int>(16));
		vd->left->left->left->attach(new TreeNode<int>(32));

		a->attach(b);
		a->attach(c);
		b->attach(d);
		b->attach(e);

		//проверка прикрепления новых узлов к дереву
		assert(a->value == 2);
		assert(a->left->value == 4);
		assert(a->right->value == 8);
		assert(a->left->left->value == 16);
		assert(a->left->right->value == 32);

		//проверка выполнения функции для каждого узла дерева
		funcToTreeRLN<int>(a, [](int* a)->void { *a /= 2; });
		assert(a->value == 1);
		assert(a->left->value == 2);
		assert(a->right->value == 4);
		assert(a->left->left->value == 8);
		assert(a->left->right->value == 16);

		//проверка работы функции нахождения  глубины дерева
		assert(depthOfBinTree(a) == 2);
		assert(depthOfBinTree(em) == -1);
		assert(depthOfBinTree(vd) == 4);

		//проверка работы функции нахождения кол-ва узлов дерева
		assert(countNodes(a) == 5);
		assert(countNodes(vd) == 5);
		assert(countNodes(em) == 0);

		std::vector<int> arrt;

		//проверка копирования значений узлов деревьев в массив
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

		//проверка функции копирования дерева
		em = BinTreeCopy(a);
		assert(em->value == 1);
		assert(em->left->value == 2);
		assert(em->right->value == 4);
		assert(em->left->left->value == 8);
		assert(em->left->right->value == 16);

		deleteTree(em);
		//проверка функции копирования вырожденного дерева
		em = BinTreeCopy(vd);
		assert(em->value == 2);
		assert(em->left->value == 4);
		assert(em->left->left->value == 8);
		assert(em->left->left->left->value == 16);

		//проверка работы функций для дерева, состоящего из одного узла
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