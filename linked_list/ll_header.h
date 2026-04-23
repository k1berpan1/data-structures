#include <iostream>

struct Node {
	struct Node* next = nullptr;
	std::string key;
    int value;
};

struct Linkedlist {

	struct Node* head = nullptr;

    void info_of_ll(){
		if(!head){
			return;
		}
    	struct Node* temp_node = head;
        while(temp_node){
            std::cout << "key "<< temp_node->key << " value "<< temp_node->value<< std::endl;
            temp_node = temp_node->next;
        }
    }
	void find(std::string key) {
		if (!head) 
			return;
		
		else{
			struct Node* temp_node = head;
			while (temp_node->key != key) 
				temp_node = temp_node->next;
	
			std::cout << "key "<< temp_node->key << " value "<< temp_node->value<< std::endl;
		}
	}

	void pushback(std::string  key, int value) {
		if (!head)
		{
			head = new Node();
			head->key = key;
            head->value = value;
            return;
		}
		
		Node* new_node = new Node();
		new_node->key = key;
		new_node->value = value;

		struct Node* temp_node = head;
		while (temp_node->next)
			temp_node = temp_node->next;
		
		temp_node->next = new_node;
		
	}

	Node* delete_after(Node* temp_node, std::string key) {
		if(temp_node->key == key && key== head->key){
			delete head;
			head = nullptr;
			return head;
		}
		if(!temp_node){
			return temp_node;
		}
		if(temp_node->key == key)
			return temp_node->next;
		if(temp_node)
		    temp_node->next = delete_after(temp_node->next, key);
		return temp_node;
		
	}
	~Linkedlist()
	{
		if (head) {
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
		else 
			return;
	}
};
