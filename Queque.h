
#pragma once
#include "LinkedList.h"

///����� �������. ���������� �� ������ ����������� ������
template<typename T>
class Queque {
private:
	LinkedList<T> list; //������,�������� ������ 
public:
	Queque() : list() {}
	
	///���������� �������� � �������
	void push(T data) {
		list.add_back(data);
	}

	//���������� true, ���� ������� �����,false � ��������� ������
	bool isEmpty() const{
		if (list.isEmpty()) {
			return 1;
		}
		return 0;
	}

	///���������� �������� �������� � ������� �������
	T peek() const{
		if (isEmpty()) {
			throw std::out_of_range("Queque is empty");
		}
		return list.get(0);
	}

	///���������� �������� �� �������
	T pop() {
		if (isEmpty()) {
			throw std::out_of_range("Error: Trying to pop from empty queque");
		}
		T value = list.get(0);
		list.del_head();
		return value;
	}

	///������� �������
	void clear() {
		list.clear();
	}

	///���������� ����� ��������� � �������
	size_t size() const{
		return list.size();
	}
};