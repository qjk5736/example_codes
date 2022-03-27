//
// Copyright 2022 John I. Krassikoff
//
// This program is free software : you can redistribute itand /or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < https://www.gnu.org/licenses/>.
//

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
