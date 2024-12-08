#pragma once
#include <random>
#include "TreeNode.h"
#include "Stack.h"
#include "Queque.h"
///Шаблонны класс бинарного дерева поиска
template <typename T>
class BinarySearchTree {
private:
	TreeNode<T>* root;//корневой узел дерева

	
public:
	///конструктор класса
	BinarySearchTree() {
		root = nullptr;
	}

	///вставка элемента в дерево
	void insert(const T &value) {
		if (root == nullptr) {
			root = new TreeNode<T>(value);
			return;
		}
		insertion(value, this->root);
	}

	///Поиск значения value в дереве, возвращает указатель на узел дерева с таким значением
	///Если значение не найдено возвращает нулевой указатель
	TreeNode<T>* find(const T &value) const {
		return finding(value, this->root);
	}

	///Поиск наименьшего значения, которое больше value в дереве, возвращает указатель на узел дерева с таким значением
	///Если значение не найдено возвращает нулевой указатель
	TreeNode<T>* successor(const T &value)const {
		return success(value,root);

	}

	///Удаление из дерева узла со значением value
	void remove(const T &value) {
		removing(value, this->root);
	}
	///Вывод дерева с NLR обходом
	void print() const {
		printTreeNLR(root);
	}

	///Возвращает кол-во узлов в дереве
	size_t count()const {
		return countNodes(root);
	}

	///ВОзвращает глубину дерева
	int depth() const {
		return depthOfBinTree(root);
	}
	///Вложенный класс итератора. Используется обход в ширину сверху вниз слева направо
	class iterator {
	private:
		Queque<TreeNode<T>*> nodeQueque;
		
	public:

		///Конструктор класса итератора
		iterator(TreeNode<T>* root) {
			nodeQueque.push(root);
			
		}

		///перегрузка префискного оператора инкремеента
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

		///перегрузка оператора "не равно"
		bool operator !=(const iterator& x) const {
			return this->nodeQueque.peek() != x.nodeQueque.peek();
		}

		///перегрузка оператора "равно"
		bool operator ==(const iterator& x) const {
			return this->nodeQueque.peek() == x.nodeQueque.peek();
		}

		///перегрузка оператора получения значения
		T& operator *() {
			return nodeQueque.peek()->value;
		}
	};

	///возвращает оператор, хранящий начало дерева
	iterator begin() const {
		return iterator(root);
	}
	///возвращает оператор, хранящий конец прохода по дереву
	iterator end() const {
		
		return iterator(nullptr);
	}

	~BinarySearchTree() {
		deleteTree(root);
	}
};


///Функция поиска узла со значением value в дереве с корнем root
///Возвращает указатель на найденным узел
/// Если узел не найден, возвращает nullptr
/// Cложность: O(log n) 
/// В худшем случае(дерево вырождено) - O(n)
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

///Добавление узла со значением value в дерево с корнем root
///Сложность: O(log n)
///		В худшем случае(дерево вырождено) - O(n)
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

///Поиск ближайшего наибольшего для value в дереве с корнем root
///Возвращает указатель на узел, содержащий ближайшее наибольшее
/// Если узла со значением value в дереве нет или заданное число является наибольшим, то возращает nullptr
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

///Поиск родителя узла child в дереве root
///Возвращает указатель на родителя
/// Cложность: O(log n)
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

///удаление узла со значением value из дерева с корнем root
///Сложность: O(log n)
///	В худшем случае(дерево вырождено) - O(n)
template<typename T>
void removing(const T &value, TreeNode<T>*& root) {

	if (root == nullptr) {
		return;
	}
	TreeNode<T>* del = finding(value,root);//узел со значением value
	if (del == nullptr) { //если узел не найден 
		return;//работа функции прекращается
	}
	TreeNode<T>* parent= findParent(root,del); // родитель удаляемого узла
	
	//если узел не имеет потомков
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
	
	//если у узла только правый потомок
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

	//если у узла только левый потомок
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

	//если узел имеет двух потомков
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
	// Тестирование методов на дереве с 5 узлами
	BinarySearchTree<int> bst;
	bst.insert(4); // Добавление элемента 4
	bst.insert(3); // Добавление элемента 3
	bst.insert(15); // Добавление элемента 15
	bst.insert(5); // Добавление элемента 5
	bst.insert(20); // Добавление элемента 20

	// Проверка поиска элементов
	assert(bst.find(4)->value == 4); // Найден элемент 4
	assert(bst.find(3)->value == 3); // Найден элемент 3
	assert(bst.find(20)->value == 20); // Найден элемент 20
	assert(bst.find(45) == nullptr); // Элемент 45 отсутствует

	// Проверка нахождения следующего (successor)
	assert(bst.successor(3)->value == 4); // Следующий после 3 - это 4
	assert(bst.successor(15)->value == 20); // Следующий после 15 - это 20
	assert(bst.successor(4)->value == 5); // Следующий после 4 - это 5
	assert(bst.successor(20) == nullptr); // У 20 нет следующего
	assert(bst.successor(33) == nullptr); // Элемента 33 нет в дереве

	// Проверка количества узлов и глубины дерева
	assert(bst.count() == 5); // Всего 5 узлов
	assert(bst.depth() == 2); // Глубина дерева 2

	// Удаление элементов
	bst.remove(15); // Удаление элемента 15
	assert(bst.find(15) == nullptr); // Элемент 15 отсутствует
	bst.remove(4); // Удаление элемента 4
	assert(bst.find(4) == nullptr); // Элемент 4 отсутствует
	bst.remove(20); // Удаление элемента 20
	assert(bst.find(20) == nullptr); // Элемент 20 отсутствует
	bst.remove(234); // Попытка удалить несуществующий элемент
	assert(bst.count() == 2); // Осталось 2 элемента
	assert(bst.depth() == 1); // Глубина дерева 1

	// Тестирование методов на пустом дереве
	BinarySearchTree<int> bst_e;

	assert(bst_e.count() == 0); // В пустом дереве 0 узлов
	assert(bst_e.depth() == -1); // Глубина пустого дерева -1

	assert(bst_e.find(45) == nullptr); // Элемента 45 нет
	assert(bst_e.find(0) == nullptr); // Элемента 0 нет
	assert(bst_e.find(12) == nullptr); // Элемента 12 нет

	assert(bst_e.successor(20) == nullptr); // У 20 нет следующего
	assert(bst_e.successor(33) == nullptr); // У 33 нет следующего

	// Тестирование методов на дереве с одним узлом
	BinarySearchTree<int> bst_s;

	bst_s.insert(123); // Добавление единственного элемента 123

	assert(bst_s.count() == 1); // В дереве 1 узел
	assert(bst_s.depth() == 0); // Глубина дерева 0

	assert(bst_s.find(45) == nullptr); // Элемента 45 нет
	assert(bst_s.find(123)->value == 123); // Найден элемент 123
	assert(bst_s.find(12) == nullptr); // Элемента 12 нет

	assert(bst_s.successor(123) == nullptr); // У 123 нет следующего
	assert(bst_s.successor(33) == nullptr); // Элемента 33 нет

	bst_s.remove(123); // Удаление элемента 123
	bst_s.remove(123); // Повторное удаление элемента 123
	assert(bst_s.find(123) == nullptr); // Элемент 123 отсутствует

	// Тестирование методов на вырожденном дереве
	BinarySearchTree<int> bst_deg;

	bst_deg.insert(8); // Построение вырожденного дерева
	bst_deg.insert(7);
	bst_deg.insert(6);
	bst_deg.insert(5);
	bst_deg.insert(4);
	assert(bst_deg.count() == 5); // 5 узлов в дереве
	assert(bst_deg.depth() == 4); // Глубина дерева 4

	assert(bst_deg.find(45) == nullptr); // Элемента 45 нет
	assert(bst_deg.find(8)->value == 8); // Найден элемент 8
	assert(bst_deg.find(7)->value == 7); // Найден элемент 7
	assert(bst_deg.find(6)->value == 6); // Найден элемент 6
	assert(bst_deg.find(5)->value == 5); // Найден элемент 5
	assert(bst_deg.find(4)->value == 4); // Найден элемент 4
	assert(bst_deg.find(12) == nullptr); // Элемента 12 нет

	bst_deg.remove(4); // Удаление элемента 4
	assert(bst_deg.find(4) == nullptr); // Элемент 4 отсутствует
	bst_deg.remove(6); // Удаление элемента 6
	assert(bst_deg.find(6) == nullptr); // Элемент 6 отсутствует
	bst_deg.remove(8); // Удаление элемента 8
	assert(bst_deg.find(8) == nullptr); // Элемент 8 отсутствует

	assert(bst_deg.count() == 2); // Осталось 2 элемента
	assert(bst_deg.depth() == 1); // Глубина дерева 1

	// Тестирование итераторов
	BinarySearchTree<int> l;
	l.insert(4); // Добавление узлов для теста
	l.insert(2);
	l.insert(6);
	l.insert(5);
	l.insert(3);
	l.insert(1);

	auto tmp = l.begin(); // Начальный итератор
	++tmp;
	assert(tmp != l.begin()); // Итератор продвинулся

	assert(*tmp == 2); // Значение текущего узла 2
	++tmp;
	assert(*tmp == 6); // Значение текущего узла 6
	++tmp;
	assert(*tmp == 1); // Значение текущего узла 1
	++tmp;
	assert(*tmp == 3); // Значение текущего узла 3
	++tmp;
	assert(*tmp == 5); // Значение текущего узла 5
	++tmp;
	assert(tmp == l.end()); // Итератор достиг конца

	// Для пустого дерева
	BinarySearchTree<int> e;
	assert(e.begin() == e.end()); // Итератор пустого дерева равен end
	std::cout << "all test complete!\n";
}
