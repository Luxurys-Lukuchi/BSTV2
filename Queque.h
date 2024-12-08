
#pragma once
#include "LinkedList.h"

///Класс очереди. Реализован на основе двусвязного списка
template<typename T>
class Queque {
private:
	LinkedList<T> list; //список,хранящий данные 
public:
	Queque() : list() {}
	
	///добавление элемента в очередь
	void push(T data) {
		list.add_back(data);
	}

	//Возвращает true, если очередь пуста,false в противном случае
	bool isEmpty() const{
		if (list.isEmpty()) {
			return 1;
		}
		return 0;
	}

	///Возвращает значение элемента с вершины очереди
	T peek() const{
		if (isEmpty()) {
			throw std::out_of_range("Queque is empty");
		}
		return list.get(0);
	}

	///Извлечение элемента из очереди
	T pop() {
		if (isEmpty()) {
			throw std::out_of_range("Error: Trying to pop from empty queque");
		}
		T value = list.get(0);
		list.del_head();
		return value;
	}

	///Очистка очереди
	void clear() {
		list.clear();
	}

	///Возвращает число элементов в очереди
	size_t size() const{
		return list.size();
	}
};