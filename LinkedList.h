
#pragma once
#include <exception>



template<typename T>
struct ListNode{
	T value;       //хранимое значение
	ListNode<T>* next; //указатель на следующий узел
	ListNode<T>* pred; //указатель на предыдущий узел
};

///Шаблонный класс двусвязанного списка
///Имеет два приватных поля:
/// head - указатель на начало списка
/// end - указатель на конец списка
template<typename T>
class LinkedList {
private:
	ListNode<T>* head;
	ListNode<T>* tail;
public:

	///конструктор без параметров
	///указателям присваисвается nullptr
	LinkedList() {
		head = nullptr;
		tail = head;
	}

	LinkedList(LinkedList<T>&& list) {
		this->head = list.head;
		this->tail = list.tail;
	}
	
	LinkedList (LinkedList<T>& list) {
		this->head = nullptr;
		this->tail = nullptr;
		ListNode<T>* tmp = list.head;
		while (tmp != nullptr) {
			this->add_back(tmp->value);
			tmp = tmp->next;
		}
	}
	
	///Добавление нового элемента в начало списка
	///data - значение, добавляемое в список
	void add_head(T data) {
		ListNode<T>* new_node = new ListNode<T>{ data,head,nullptr }; //указатель на новый элемент
		if (head != nullptr) {		//если список имеет хотя бы один элемент
			head->pred = new_node;  //то в pred первого элемента передаем указатель на новый элемент
		}
		if (tail == nullptr){		//если в списке нет элементов
			tail = new_node;			//то добавляемый элемент будет  и последним
		}
		head = new_node;			//указателю на начало списка присваиваем указательн на добавляемый узел

	}

	///Удаление элемента из начала списка
	void del_head() {
		if (head == nullptr) return; //если в список пустой, то сразу прекращаем выполнение метода

		ListNode<T>* tmp = head->next;   //указатель на элемент после удаляемого 
		if (tmp != nullptr){		 //если в списке больше одного узла
			tmp->pred = nullptr;	 //то в pred вторго узла помещаем нулевой указатель
			
		}
		else {						 //если же список состоит из одного элемент
			tail = nullptr;			 //в end кладем nullptr, тк в таком случае список будет очищен
		}
		delete head;				 //удаляем начальный узел 
		head = tmp;					 //в head кладем  tmp
	}

	///Добавление в конец списка
	///data - добавляемое значение
	void add_back(T data) {
		ListNode<T>* new_node = new ListNode<T>{ data,nullptr,tail };
		if (tail != nullptr) {
			tail->next = new_node;
		}
		if (head == nullptr) {
			head = new_node;
		}
		
		tail = new_node;
	}

	///Удаляет элемент из конца списка
	void del_back() {
		if (tail == nullptr) return;
		ListNode<T>* tmp = tail;
		if (tmp->pred != nullptr){
			tail = tmp->pred;
			tail->next = nullptr;
			
		}
		else {
			head = nullptr;
			tail = nullptr;
		}
		delete tmp;
		
	}

	///возвращает указатель на элемент по индексу idx
	ListNode<T>* get_ptr(size_t idx) const{
		ListNode<T>* temp = head;
		size_t n = 0;

		while (n != idx) {
			if (temp == nullptr) {
				return nullptr;
			}
			temp = temp->next;
			n++;
		}
		return temp;
	}
	///Удаление элемента по индексу idx
	void del(size_t idx) {
		ListNode<T>* delet = get_ptr(idx);

		if (delet == nullptr) {
			return;
		}
		if (delet->pred == nullptr) {
			del_head();
			return;
		}
		if (delet->next == nullptr) {
			del_back();
			return;
		}
		delet->pred->next = delet->next;
		delet->next->pred = delet->pred;
		
		delete delet;
	}

	///добавить число data в списко по индексу idx
	void add(size_t idx, T data) {
		ListNode<T>* nxt = get_ptr(idx);

		if (nxt == nullptr) {
			add_back(data);
			return;
		}

		if (nxt->pred == nullptr) {
			add_head(data);
			return;
		}

		ListNode<T>* new_node = new ListNode<T>{ data,nxt,nxt->pred };
		nxt->pred->next = new_node;
		nxt->pred = new_node;

	}
	///присоединение списка list2 к списку к которому вызывается метод
	void add(LinkedList &list2) {
	

		if (head == nullptr) {
			head = list2.head;
			tail = list2.tail;
			return;
		}
		tail->next = list2.head;
		tail = list2.tail;

	}

	T get(size_t idx) const {
		return get_ptr(idx)->value;
	}

	void clear() {
		while (this->head != nullptr) {
			this->del_back();
		}
	}
	///оператор присваивания копированием
	LinkedList<T>& operator=(const LinkedList<T>& list) {
		if (&list != this) {
			this->clear();
			ListNode<T>* tmp = list.head;
			while (tmp != nullptr) {
				this->add_back(tmp->value);
				tmp = tmp->next;
			}
		}
		return *this;
	}

	///оператор присваивания перемещением
	LinkedList<T>& operator=(const LinkedList<T>&& list) {
		if (&list != this) {
			this->head = list.head;
			this->tail = list.tail;
		}
		return *this;
	}

	bool isEmpty() const{
		if (head == nullptr) { return 1; };
		return 0;
	}

	size_t size() {
		if (head == nullptr) return 0;
		ListNode<T>* temp = head;
		size_t n = 0;

		while (temp != nullptr) {
			n++;
			temp = temp->next;
		}
		return n;
	}

	///производит поиск числа find в двусвязном списке методом последовательного поиска
	///если число найдено, то возращает индекс числа в списке
	///в противном случае возращает -1
	long long find(T find) {
		ListNode<T>* tmp = this->head;
		for (size_t i = 0; i < size(); i++) { //последовательно проходим по всем элементам массива
			if (tmp->value == find) {               //если искомое число найдено
				return i;                       //возращаем его индекс
			}
			tmp = tmp->next;
		}
		return -1;
	}

	///Класс итератора для связанного списка
	class iterator  {
	private:
		ListNode<T>* curr;//указатель на текущий элемент
	public:
		///конструктор класса
		iterator(ListNode<T>* beg = nullptr) {
			curr = beg;
		}

		///перегрузка оператора инкрементирования
		iterator operator ++() {
			curr = curr->next;
			return *this;
		}

		///перегрузка оператора "не равно"
		bool operator !=(const iterator & x) const{
			return this->curr != x.curr;
		}

		///перегрузка оператора "равно"
		bool operator ==(const iterator& x) const {
			return this->curr == x.curr;
		}

		///перегрузка оператора обращения к значению
		T& operator *() {
			return curr->value;
		}
	};

	///возращает итератор указывающий на начало
	iterator begin() {
		return iterator(this->head);
	}

	///возращает итератор указывающий на конец 
	iterator end() {
		return iterator();
	}

	void sort() {
		 MergeSort(*this);
	}

	~LinkedList() {
		this->clear();
	}
};




///Производит слияние двух половин области массива а между begin и end
///a - обрабатываемый массив
///begin - левая граница рассматриваемой области
///end - правая граница рассматриваемой области
template<typename T>
void merging(LinkedList<T> & result,LinkedList<T> &left, LinkedList<T> &right) {
	
	result.clear();
	ListNode<T>* lNode = left.get_ptr(0);
	ListNode<T>* rNode = right.get_ptr(0);
	while (lNode != nullptr && rNode != nullptr) {			//пока не достигнут конец одной из областей
		if (lNode -> value <= rNode->value) {				//сравниваются значения из областей

			result.add_back(lNode->value);						// если left меньше right, то в индекс i массива с помещаем значение из левой области
			lNode = lNode->next;
		}
		else {
			result.add_back(rNode->value);						// если left меньше right, то в индекс i массива с помещаем значение из левой области
			rNode = rNode->next;
		}
		
	}
	
	//помещаем оставшиеся значения в массив c
	if (lNode == nullptr) {							//если был достигнут конец левой части

		while (rNode != nullptr) {					//то помещаем значения из правой

			result.add_back(rNode->value);
			rNode = rNode->next;
		}
	}
	else if (rNode == nullptr) {					//если же был достигнут конец правой части

		while (lNode != nullptr) {				// то помеащем знаяения из левой

			result.add_back(lNode->value);
			lNode = lNode->next;
		}
	}
	
}

template<typename T>
void MergeSort(LinkedList<T>& list)  {
	size_t n = list.size();
	if (n > 1) {
		size_t md = n / 2;
		LinkedList<T> left;
		LinkedList<T> right;
		ListNode<T>* tmp = list.get_ptr(0);
		size_t i = 0;
		for (i;i < n;i++) {
			if (i < md) {
				left.add_back(tmp->value);
			}
			else {
				right.add_back(tmp->value);
			}
			tmp = tmp->next;
		}
		MergeSort(left);
		MergeSort(right);
		merging(list,left, right);
	}
}

void iter_test() {

	//для списка из 4 элементов
	LinkedList<int> l;
	l.add_back(5);
	l.add_back(7);
	l.add_back(9);
	l.add_back(11);

	auto tmp = l.begin();

	assert(*tmp == 5);
	++tmp;
	assert(*tmp == 7);
	++tmp;
	assert(*tmp == 9);
	++tmp;
	assert(*tmp == 11);
	++tmp;
	assert(tmp == l.end());

	//для пустого списка
	LinkedList<int> e;
	assert(e.begin() == e.end());


}