#ifndef QUEUE_H
#define QUEUE_H
#include "Node.h"
#include <exception>
using namespace std;
// template for Queue
template<typename T>
class Queue{
public:
	Queue();
	~Queue();
	void insert(T);
	bool isEmpty();
	T remove();
	int size;
	node<T>* front;
	node<T>* back;

};
template<typename T>
Queue<T>::Queue(){
	size = 0;
	front = 0;
	back =0;

}
template<typename T>
Queue<T>::~Queue(){
	node<T>* temp = front;
	while(front != 0){
		temp = front;
		front->prev->next = 0;
		front = front->prev;
		delete temp;
	}
}
template<typename T>
void Queue<T>::insert(T data){
	node<T>* newNode = new node<T>(data);

	if (isEmpty())
	{
		front = back = newNode;
		size++;
	}else{
		back->prev = newNode;
		newNode->next = back;
		back = newNode;
		size++;
	}
}
template<typename T>
bool Queue<T>::isEmpty(){
	return(size == 0);
}
template<typename T>
T Queue<T>::remove(){
	node<T>* removed;
	T temp;
	if (isEmpty())
	{
		try{
			throw "Empty";
		}catch(const char* message){
			cerr << message << endl;
		}
	}
	if (size == 1)
	{
		removed = front;
		
		temp = front->data;
		front = back = 0;
		delete removed;
		
	}else{
		removed = front;
		front->prev->next = 0;
		temp = front->data;
		front = front->prev;
		delete removed;
	}
	size--;
	return temp;
	
}

#endif