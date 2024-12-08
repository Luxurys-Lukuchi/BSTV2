
#pragma once

#include<stdexcept>
template<typename T>
struct Node {
	T value;       //�������� ��������
	Node<T>* next; //��������� �� ��������� ����
};

template<typename T>
class Stack {
private:
	Node<T>* top;
public:
	Stack() {
		top = nullptr;
	}

	///�������� �� ��, ���� �� ����
	///���������� true, ���� ���� ����
	/// ��������� false, ���� ���� �� ����
	bool isEmpty() const{
		if (top == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	///���������� �������� � ����
	void push(T data) {
		Node<T>* new_node = new Node<T>{ data,top}; //��������� �� ����� �������
		top = new_node;			//��������� �� ������ ������ ����������� ���������� �� ����������� ����
	}

	///���������� �������� �� �����
	T pop() {
		if (isEmpty()) {
			throw std::out_of_range("Error: trying to pop from empty stack");
		}
		T pop_value = top->value;
		Node<T>* tmp = top->next;   //��������� �� ������� ����� ���������� 
		
		delete top;				 //������� ��������� ���� 
		top = tmp;
		return pop_value;
	}

	///��������� �������� �� ������� �����
	T peek() const {
		if (isEmpty()) {
			throw std::out_of_range("Error: trying to get peek from empty stack");
		}
		return top->value;
	}

	///������� �����
	void clear() {
		while (top != nullptr) {
			pop();
		}
	}

	///���������� ������ �����
	size_t size() const {
		Node<T>* tmp = top;
		size_t count = 0;
		while (tmp != nullptr) {
			count++;
			tmp = tmp->next;
		}
		return count;
	}
	///���������� �����
	~Stack() {
		clear();
	}

};