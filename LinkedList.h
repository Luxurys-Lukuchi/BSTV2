
#pragma once
#include <exception>



template<typename T>
struct ListNode{
	T value;       //�������� ��������
	ListNode<T>* next; //��������� �� ��������� ����
	ListNode<T>* pred; //��������� �� ���������� ����
};

///��������� ����� ������������� ������
///����� ��� ��������� ����:
/// head - ��������� �� ������ ������
/// end - ��������� �� ����� ������
template<typename T>
class LinkedList {
private:
	ListNode<T>* head;
	ListNode<T>* tail;
public:

	///����������� ��� ����������
	///���������� �������������� nullptr
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
	
	///���������� ������ �������� � ������ ������
	///data - ��������, ����������� � ������
	void add_head(T data) {
		ListNode<T>* new_node = new ListNode<T>{ data,head,nullptr }; //��������� �� ����� �������
		if (head != nullptr) {		//���� ������ ����� ���� �� ���� �������
			head->pred = new_node;  //�� � pred ������� �������� �������� ��������� �� ����� �������
		}
		if (tail == nullptr){		//���� � ������ ��� ���������
			tail = new_node;			//�� ����������� ������� �����  � ���������
		}
		head = new_node;			//��������� �� ������ ������ ����������� ���������� �� ����������� ����

	}

	///�������� �������� �� ������ ������
	void del_head() {
		if (head == nullptr) return; //���� � ������ ������, �� ����� ���������� ���������� ������

		ListNode<T>* tmp = head->next;   //��������� �� ������� ����� ���������� 
		if (tmp != nullptr){		 //���� � ������ ������ ������ ����
			tmp->pred = nullptr;	 //�� � pred ������ ���� �������� ������� ���������
			
		}
		else {						 //���� �� ������ ������� �� ������ �������
			tail = nullptr;			 //� end ������ nullptr, �� � ����� ������ ������ ����� ������
		}
		delete head;				 //������� ��������� ���� 
		head = tmp;					 //� head ������  tmp
	}

	///���������� � ����� ������
	///data - ����������� ��������
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

	///������� ������� �� ����� ������
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

	///���������� ��������� �� ������� �� ������� idx
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
	///�������� �������� �� ������� idx
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

	///�������� ����� data � ������ �� ������� idx
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
	///������������� ������ list2 � ������ � �������� ���������� �����
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
	///�������� ������������ ������������
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

	///�������� ������������ ������������
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

	///���������� ����� ����� find � ���������� ������ ������� ����������������� ������
	///���� ����� �������, �� ��������� ������ ����� � ������
	///� ��������� ������ ��������� -1
	long long find(T find) {
		ListNode<T>* tmp = this->head;
		for (size_t i = 0; i < size(); i++) { //��������������� �������� �� ���� ��������� �������
			if (tmp->value == find) {               //���� ������� ����� �������
				return i;                       //��������� ��� ������
			}
			tmp = tmp->next;
		}
		return -1;
	}

	///����� ��������� ��� ���������� ������
	class iterator  {
	private:
		ListNode<T>* curr;//��������� �� ������� �������
	public:
		///����������� ������
		iterator(ListNode<T>* beg = nullptr) {
			curr = beg;
		}

		///���������� ��������� �����������������
		iterator operator ++() {
			curr = curr->next;
			return *this;
		}

		///���������� ��������� "�� �����"
		bool operator !=(const iterator & x) const{
			return this->curr != x.curr;
		}

		///���������� ��������� "�����"
		bool operator ==(const iterator& x) const {
			return this->curr == x.curr;
		}

		///���������� ��������� ��������� � ��������
		T& operator *() {
			return curr->value;
		}
	};

	///��������� �������� ����������� �� ������
	iterator begin() {
		return iterator(this->head);
	}

	///��������� �������� ����������� �� ����� 
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




///���������� ������� ���� ������� ������� ������� � ����� begin � end
///a - �������������� ������
///begin - ����� ������� ��������������� �������
///end - ������ ������� ��������������� �������
template<typename T>
void merging(LinkedList<T> & result,LinkedList<T> &left, LinkedList<T> &right) {
	
	result.clear();
	ListNode<T>* lNode = left.get_ptr(0);
	ListNode<T>* rNode = right.get_ptr(0);
	while (lNode != nullptr && rNode != nullptr) {			//���� �� ��������� ����� ����� �� ��������
		if (lNode -> value <= rNode->value) {				//������������ �������� �� ��������

			result.add_back(lNode->value);						// ���� left ������ right, �� � ������ i ������� � �������� �������� �� ����� �������
			lNode = lNode->next;
		}
		else {
			result.add_back(rNode->value);						// ���� left ������ right, �� � ������ i ������� � �������� �������� �� ����� �������
			rNode = rNode->next;
		}
		
	}
	
	//�������� ���������� �������� � ������ c
	if (lNode == nullptr) {							//���� ��� ��������� ����� ����� �����

		while (rNode != nullptr) {					//�� �������� �������� �� ������

			result.add_back(rNode->value);
			rNode = rNode->next;
		}
	}
	else if (rNode == nullptr) {					//���� �� ��� ��������� ����� ������ �����

		while (lNode != nullptr) {				// �� �������� �������� �� �����

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

	//��� ������ �� 4 ���������
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

	//��� ������� ������
	LinkedList<int> e;
	assert(e.begin() == e.end());


}