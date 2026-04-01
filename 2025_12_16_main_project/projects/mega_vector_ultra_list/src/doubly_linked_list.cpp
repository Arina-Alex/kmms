#include "doubly_linked_list.hpp"

#include <iostream>

using mal::DoublyLinkedList;

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node* current = begin;

	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
}

template<typename T>
std::size_t DoublyLinkedList<T>::get_size() const noexcept {
	std::size_t size = 0;
	Node* current = begin;

	while (current != nullptr) {
		size++;
		current = current->next;
	}

	return size;
}

template<typename T>
bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
	Node* current = begin;

	while (current != nullptr) {
		if (current->value == value) {
			return true;
		}
		current = current->next;
	}

	return false;
	
}

template<typename T>
void DoublyLinkedList<T>::print() const noexcept {
	std::cout << "[";
	Node* current = begin;

	while (current != nullptr) {
		std::cout << current->value;
		if (current->next != nullptr) {
			std::cout << ", ";
		}
		current = current->next;
	}

	std::cout << "]" << std::endl;
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
	Node* new_node = new Node(value);

	if (begin == nullptr) {
		begin = new_node;
		end = new_node;
	} else {
		end->next = new_node;
		new_node->prev = end;
		end = new_node;
	}

}

template<typename T>
bool DoublyLinkedList<T>::remove_first(const T& value) noexcept {
	Node* current = begin;

	while (current != nullptr) {
		if (current->value == value) {
			if (current == begin && current == end) {
				begin = nullptr;
				end = nullptr;
			} 
			else if (current == begin) {
				begin = current->next;
				begin->prev = nullptr;
			} 
			else if (current == end) {
				end = current->prev;
				end->next = nullptr;
			}
			else {
				Node* prev_node = current->prev;  
				Node* next_node = current->next; 

				prev_node->next = next_node;  
				next_node->prev = prev_node;  
			}

			delete current;
			return true;
		}
		current = current->next;
	}
	return false;
}
