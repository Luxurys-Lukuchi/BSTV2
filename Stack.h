
#pragma once

#include<stdexcept>
template<typename T>
struct Node {
	T value;       //хранимое значение
	Node<T>* next; //указатель на следующий узел
};

template<typename T>
class Stack {
private:
	Node<T>* top;
public:
	Stack() {
		top = nullptr;
	}

	///Проверка на то, пуст ли стек
	///Возвращает true, если стек пуст
	/// Возвраает false, если стек НЕ пуст
	bool isEmpty() const{
		if (top == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	///Добавление элемента в стек
	void push(T data) {
		Node<T>* new_node = new Node<T>{ data,top}; //указатель на новый элемент
		top = new_node;			//указателю на начало списка присваиваем указательн на добавляемый узел
	}

	///Извлечение элемента из стека
	T pop() {
		if (isEmpty()) {
			throw std::out_of_range("Error: trying to pop from empty stack");
		}
		T pop_value = top->value;
		Node<T>* tmp = top->next;   //указатель на элемент после удаляемого 
		
		delete top;				 //удаляем начальный узел 
		top = tmp;
		return pop_value;
	}

	///Получение значения из вершины стека
	T peek() const {
		if (isEmpty()) {
			throw std::out_of_range("Error: trying to get peek from empty stack");
		}
		return top->value;
	}

	///Очистка стека
	void clear() {
		while (top != nullptr) {
			pop();
		}
	}

	///Возвращает размер стека
	size_t size() const {
		Node<T>* tmp = top;
		size_t count = 0;
		while (tmp != nullptr) {
			count++;
			tmp = tmp->next;
		}
		return count;
	}
	///деструктор стека
	~Stack() {
		clear();
	}

};