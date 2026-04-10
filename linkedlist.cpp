#include <iostream>
#include <time.h>



struct Node {
	struct Node* next = NULL;
	int data;
};


struct Linkedlist {

	struct Node* head = nullptr;
	void get_info() {
		if (head == nullptr) {
			std::cout << "linkedlist is empty"<< std::endl;
		}
		else {
			struct Node* last = head;
			while (last->next != nullptr) {
				std::cout << "data " << last->data << " -->";
				last = last->next;

			}
			std::cout << "data " << last->data;
		}
		
	}

	void at(int data) {
		if (head == nullptr) {
			std::cout << "linkedlist is empty" << std::endl;
		}
		
		else{
			struct Node* last = head;
			while (last->data != data) {
				last = last->next;

			}
			std::cout << "Íàéäåí ýëåìåíò " << last->data << " ñëåäóþùèé " << std::endl;
		}
	}

	void pushback(int data) {

		if (head == nullptr)
		{
			head = new Node();
			head->data = data;
		}

		else {
			Node* new_node = new Node();
			new_node->data = data;

			struct Node* last = head;
			while (last->next != nullptr) {
				last = last->next;
			}
			last->next = new_node;

			new_node->next = nullptr;
			
		}
	

		//âûäåëÿòü ïàìÿòü íå â ñòýêå, à â êó÷å. ß ñîõðàíÿþ àäðåñ ïåðåìåííîé, êîòîðàÿ óäàëÿåòñÿ ïðè âûõîäå èç ôóíêöèè.

	}
	void pushfirst(int data) {
		if (head == nullptr)
		{
			head = new Node();
			head->data = data;
		}
		else {
			Node* new_node = new Node();
			new_node->data = data;

			new_node->next = head;
			head = new_node;
			

			
		}
	}
	void popafter() {
		
		struct Node* last = head;
		if (head->next == nullptr) {		
			head = nullptr;
		}
		else {
			while (last->next->next != nullptr) {
				last = last->next;
			}
			delete last->next;
			last->next = nullptr;
		}
	}
	void deletefirst() {
		if (head->next == nullptr) {
			delete head;
			head = nullptr;

		}
		else {
			struct Node* first = head;
			head = head->next;
			delete first;
			first = nullptr;
		}
	}


	~Linkedlist()
	{
		if (head != nullptr) {
			struct Node* last = head;
			struct Node* a = head;
			while (last->next != nullptr) {
				a = last;
				last = last->next;
				delete a;
				a = nullptr;
			}
			
			delete last;
			last = nullptr;
			
		}
		else {
			std::cout << "Ýëåìåíò óäàëåí" << std::endl;
		}
	}
};


int main() { 
	
	setlocale(LC_ALL, "RU");
	Linkedlist ll;
	ll.pushback(4);
	ll.pushback(5);
	ll.pushback(6);
	ll.pushback(7);
	ll.pushfirst(3);
	ll.pushfirst(2);
	ll.pushfirst(1);
	ll.popafter();
	//ll.deletefirst();
	ll.at(6);
	ll.get_info();
	
	//
	//ll.popafter();
	//ll.popafter();
	//ll.popafter();
	//ll.get_info();
}