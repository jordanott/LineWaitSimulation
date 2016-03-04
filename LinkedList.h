
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include "Node.h"
using namespace std;

template<typename T>
class LinkedList{
public:
	int size;
	node<T>* list_head;
	node<T>* list_tail;
	LinkedList(T);
	~LinkedList();
	void insertBack(T);
	void insertFront(T);
	T removeFront();
	T removeBack();
	void remove(T);
	bool search(T);
};

template<typename T>
LinkedList<T>::LinkedList(T data){
	node<T>* firstNode = new node<T>(data);
	size = 1;
	list_head = firstNode;
	list_tail = firstNode;
}

template<typename T>
LinkedList<T>::~LinkedList(){
	node<T>* temp = list_head;
	while(list_head != 0){
		temp = list_head;
		list_head->next->prev = 0;
		list_head = list_head->prev;
		// cout << temp->data << endl;
		delete temp;
	}
}

template<typename T>
void LinkedList<T>::insertBack(T data){
	node<T>* newNode = new node<T>(data);
	list_tail->next = newNode;
	newNode->prev = list_tail;
	list_tail = newNode;
	size++;
}
template<typename T>
void LinkedList<T>::insertFront(T data){
	node<T>* newNode = new node<T>(data);
	list_head->prev = newNode;
	newNode->next = list_head;
	list_head = newNode;
	size++;
}
template<typename T>
T LinkedList<T>::removeFront(){
	T returnVal = list_head->data;
	node<T>* temp = list_head;
	list_head = list_head->next;
	list_head->prev = 0;
	delete temp;
	size--;
	return returnVal;
}
template<typename T>
T LinkedList<T>::removeBack(){
	T returnVal = list_tail->data;
	node<T>* temp = list_tail;
	list_tail = list_tail->prev;
	list_tail->next = 0;
	delete temp;
	size--;
	return returnVal;
}
template<typename T>
void LinkedList<T>::remove(T dataRemove){
	node<T>* temp = list_head;
	if (dataRemove == temp->data)
	{
		list_head = list_head->next;
		delete temp;
	}
	else{
		while(temp->next != 0 && temp->next->data != dataRemove){
			temp = temp->next;
		}
		node<T>* target = temp->next;
		if (target != 0)
		{
			temp->next = target->next;
			target->next->prev = temp;
			delete target;
		}
	}
	size--;
}

template<typename T>
bool LinkedList<T>::search(T dataSearch){
	bool condition = false;
	node<T>* temp = list_head;
	if (dataSearch == temp->data)
	{
		list_head = list_head->next;
		
	}
	else{
		while(temp->next != 0 && temp->next->data != dataSearch){
			temp = temp->next;
			if (temp->next!=0 && temp->next->data == dataSearch)
			{
				condition = true;
			}
		}
	}
	return condition;
}

#endif