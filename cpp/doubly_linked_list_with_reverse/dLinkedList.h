/*
Copyright (c) 2022 John I. Krassikoff

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#ifndef dLinkedList_h_
#define dLinkedList_h_

#include <iostream>
#include <exception>

struct List_Is_Empty_Exception : public std::exception {
	const char* what() const throw () {
		return "Invalid delete from an empty list.";
	}
};

template<class T> class dLinkedList {
private:
	struct Node {
	public:
		T data;
		Node* prev;
		Node* next;

		Node(T val, Node* p = nullptr, Node* n = nullptr) 
			: data(val)
			, prev(p)
			, next(n)
		{}
	};
	Node* head;

public:
	dLinkedList() : head(nullptr) {}
	~dLinkedList() {}
	bool is_the_list_empty() const { return head == nullptr; }
	void insert_head_node(const T& val);
	void insert_last_node(const T& val);
	void delete_node(const T& val);
	T delete_head_node();
	void reverse_list();
	void display_list();
};

template<class T> 
void dLinkedList<T>::insert_head_node(const T& val) {
	Node* n = new Node(val);
	n->next = head;
	if (head != nullptr)
		head->prev = nullptr;
	head = n;
}

template<class T> 
void dLinkedList<T>::insert_last_node(const T& val) {
	if (head == nullptr)
	{
		return insert_head_node(val);
	}
	Node* n = new Node(val);
	Node* m = head;
	while (m->next != nullptr) {
		m = m->next;
	}
	m->next = n;
	n->prev = m;
}

template<class T>
void dLinkedList<T>::reverse_list() {
	if ((head == nullptr) || (head->next == nullptr)) return;
	Node* p = nullptr;
	Node* q = head;
	Node* r = head->next;
	head->next = nullptr;
	while (r != nullptr) {
		p = q;
		q = r;
		if (r != nullptr) {
			r = r->next;
			if (r != nullptr) r->prev = p;
			q->next = p;
			q->prev = nullptr;
			p->prev = q;
		}
		head = q;
	}
}

template<class T> 
void dLinkedList<T>::display_list() {
	std::cout << " [ ";
	for (Node* i = head; i != nullptr; i = i->next) {
		std::cout << i->data << " ";
	}
	std::cout << "]" << std::endl;
}

template<class T>
T dLinkedList<T>::delete_head_node() {
	if (head == nullptr) {
		throw List_Is_Empty_Exception();
	}
	Node* n = head;
	T val = n->data;
	head = head->next;
	if (head != nullptr) head->prev = nullptr;
	delete n;
	return val;
}

template<class T> 
void dLinkedList<T>::delete_node(const T& val) {
	if (head == nullptr) {
		throw List_Is_Empty_Exception();
	}
	if (head->data == val) {
		delete_head_node();
		return;
	}
	Node* n = head;
	while ((n != nullptr) && (n->data != val)) {
		n = n->next;
	}
	if (n == nullptr) return;
	Node* p = n->prev;
	Node* m = n->next;
	delete n;
	p->next = m;
}

#endif
