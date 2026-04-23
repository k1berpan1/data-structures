#include <iostream>
#include <math.h>
#include <algorithm>

enum Color_to_node  {red, black};

struct Node {
     
	int key;
	struct Node* left = nullptr;
	struct Node* right = nullptr;
	struct Node* dad = nullptr;
	Color_to_node color;
	Node(int k ,Color_to_node c,struct Node* d = nullptr, struct Node* l = nullptr, struct Node* r = nullptr){
		key = k;
		color =c;
		dad = d;
		left = l;
		right = r;
	}
};

struct RBtree {
	struct Node* root = nullptr;
	
	Node* llrotate(Node* node){
		Node* temp = node->left->right;
		node->left->right = node;
		node = node->left;
		if(node->right == root)
			root = node;
		
		if(node != root){
			if(node->right->dad->left== node->right)
				node->right->dad->left = node;
			else
				node->right->dad->right = node;
		}
		
		node->right->left = temp;
		if(temp!= nullptr)
			temp->dad = node->right->left;
		node->dad = node->right->dad;
		if (node->left)
			node->left->dad = node;
		node->right->dad = node;
		return node;
	}
	
	Node* rrrotate(Node* node){
		Node* temp = node->right->left;
		node->right->left = node;
		node = node->right;
		if(node->left == root)
			root = node;
		
		if(node != root){
			if(node->left->dad->left== node->left)
			node->left->dad->left = node;
			else
				node->left->dad->right = node;
		}
		
		node->left->right = temp;
		if(temp != nullptr)
			node->left->right->dad = node->left;
		node->dad = node->left->dad;
		node->left->dad = node;
		node->right->dad = node;
		return node;
	}
	Node* lrrotate(Node* node){
		Node* temp_right_of_chosen = node->left->right->right;
		Node* temp_future_left_child_of_chosen = node->left;
		Node* temp_left_of_chosen = node->left->right->left;
		node->left->right->right = node;
		node = node->left->right;
		node->dad = node->right->dad;
		if(node->right->dad->right == node->right)
			node->right->dad->right = node;
		else
			node->right->dad->left = node;
		node->right->left = temp_right_of_chosen;
		if(temp_right_of_chosen != nullptr)
			temp_right_of_chosen->dad = node->right;
		node->left = temp_future_left_child_of_chosen;
		if(temp_future_left_child_of_chosen!= nullptr)
			temp_future_left_child_of_chosen->dad = node;
		if(node->right == root)
			root = node;
		node->left->right = temp_left_of_chosen;
		if(temp_left_of_chosen != nullptr)
			temp_left_of_chosen->dad= node->left;
		node->left->dad = node;
		node->right->dad = node;
		return node;	
	}
	Node * rlrotate(Node* node){
		Node* temp_left_of_chosen = node->right->left->left;
		Node* temp_future_right_child_of_chosen = node->right;
		Node* temp_right_of_chosen = node->right->left->right;
		node->right->left->left = node;
		node = node->right->left;
		node->dad = node->left->dad;
		if(node->left->dad->right== node->left)
			node->left->dad->right = node;
		else
			node->left->dad->left = node;
		node->left->right = temp_left_of_chosen;
		if(temp_left_of_chosen != nullptr)
			temp_left_of_chosen->dad = node->left;
		node->right = temp_future_right_child_of_chosen;
		if(temp_future_right_child_of_chosen!= nullptr)
			temp_future_right_child_of_chosen->dad = node;
		if(node->left == root)
			root = node;
		node->right->left = temp_right_of_chosen;
		if(temp_right_of_chosen != nullptr)
			temp_right_of_chosen->dad= node->right;
		node->left->dad = node;
		node->right->dad = node;
		return node;
	}
	/*rotate*/
	void insert(Node *node, int key ){
		struct Node* nill;
		if (root == nullptr) {
			root = new Node(key, black);
			nill = new Node(NULL, black, root);
			root->left = nill;
			root->right = nill;

		}
		
		else {
			Node* new_node = new Node(key, red);
			Node* temp = root;
			while (true) {
				while (new_node->key < temp->key) {
				if (temp->left->key == NULL) {
					nill = new Node(NULL, black, new_node);
					new_node->left = nill;
					new_node->right = nill;
					nill->dad = new_node;
					temp->left = new_node;
					new_node->dad = temp;
					if(new_node->dad->color != black && new_node != root->left)
						fixinsert(new_node);
					return;
				}
				else {
					temp = temp->left;
				}
			}

				while (new_node->key > temp->key) {

					if (temp->right->key == NULL) {
						nill = new Node(NULL, black, new_node);
						new_node->left = nill;
						new_node->right = nill;
						nill->dad = new_node;
						temp->right = new_node;
						new_node ->dad = temp;
						if(new_node->dad->color != black  && new_node != root->right)
							fixinsert(new_node);
						return;
					}
					else {
						temp = temp->right;
					}
				}
			}
		}
	}
	void fixinsert(Node* new_node){
		if(new_node==root){
			new_node->color = black;
			return;
		}
		while(new_node != root && new_node->dad->color != black){
			if (new_node->dad == new_node->dad->dad->left){
				if(new_node->dad->dad->right!= nullptr && new_node->dad->dad->right->color==red){
					new_node->dad->color = black;
					new_node->dad->dad->right->color = black;
					new_node->dad->dad->color = red;
					fixinsert(new_node->dad->dad);
				}
				else{
					Color_to_node color_of_granddad = new_node->dad->dad->color;
					if(new_node == new_node->dad->left){
						Color_to_node color_of_dad = new_node->dad->color;			
						struct Node* node_after_rotation = llrotate(new_node->dad->dad);
						node_after_rotation->color = color_of_granddad;
						node_after_rotation->left->color =color_of_dad;
						node_after_rotation->right->color=color_of_dad; 
					}
					else if(new_node == new_node->dad->right){
						Color_to_node color_of_inserted = new_node->color;
						struct Node* node_after_rotation = lrrotate(new_node->dad->dad);
						node_after_rotation->color = color_of_granddad;
						node_after_rotation->right->color = color_of_inserted;
					}
				}
			}
			else{
				if(new_node->dad->dad->left!= nullptr && new_node->dad->dad->left->color==red){
					new_node->dad->color = black;
					new_node->dad->dad->left->color = black;
					new_node->dad->dad->color = red;
					fixinsert(new_node->dad->dad);
				}
				else{
					Color_to_node color_of_granddad = new_node->dad->dad->color;
					if(new_node == new_node->dad->right){
						Color_to_node color_of_dad = new_node->dad->color;			
						struct Node* node_after_rotation = rrrotate(new_node->dad->dad);
						node_after_rotation->color = color_of_granddad;
						node_after_rotation->left->color =color_of_dad;
						node_after_rotation->right->color=color_of_dad; 
					}
					else if(new_node == new_node->dad->left){
						Color_to_node color_of_inserted = new_node->color;
						struct Node* node_after_rotation = rlrotate(new_node->dad->dad);
						node_after_rotation->color = color_of_granddad;
						node_after_rotation->left->color = color_of_inserted;
					}
				}
			}
		}
		root->dad = nullptr;
		
	}
	void deletebt(Node* node) {
		if(node->key == NULL ){
			return;
		}
			
		if (node) {
			deletebt(node->left);
			deletebt(node->right);
			delete node;
		}
		
	}
		auto basic_situation_for_left(Node* sibling){
		sibling->color = sibling->dad->color;
		sibling->dad->color = black;
		struct Node* node_after_rotate =rrrotate(sibling->dad);
		node_after_rotate->right->color = black;
	}

	void basic_situation_for_right(Node* sibling){
		sibling->color = sibling->dad->color;
		sibling->dad->color = black;
		struct Node* node_after_rotate =llrotate(sibling->dad);
		node_after_rotate->left->color = black;
	}

	Node* find_sibling(Node* current){
		struct Node* sibling;
		if(current->dad->right == current)
			sibling = current->dad->left;
		else
			sibling = current->dad->right;
		return sibling;
	}
	bool is_it_left(Node* current){
		if(current->dad->left == current)
			return true;
		return false;
	}
	auto delete_chield_of_dad(Node* current){
		
		if(current->dad->right == current){
			current->dad->right = current->right;
			current->right->dad = current->dad; 
			delete current;
			return current->dad->right;
		}
		else{
			current->dad->left = current->left;
			current->left->dad = current->dad;
			delete current;
			return current->dad->left;
		}		
	}
	std::string are_children_black(Node* current){
		
		if(current->right->color == black && current->left->color == black)
			return "both";
		else if(current->left->color == black)
			return "left";
		
		else if(current->right->color == black)
			return "right";
		else
			return "both are red";
	}

	void case_situation(Node* current){
		if(current->color ==red){
			current->color = black;
			return;
		}
		struct Node* sibling = find_sibling(current);

		if(current->color == black && sibling->color == red){
			sibling->color = black;
			current->dad->color = red;
			if(is_it_left(current))
				rrrotate(current->dad);				
			else
				llrotate(current);
			case_situation(current);	
			return;
		}
		else if(current->color == black && sibling->color == black && are_children_black(sibling)== "both"){
			sibling->color = red;
			current = current->dad;
			if(current->color == black && current->dad == root)
				return;
			case_situation(current);
			return;
		}
		else if (current->color == black && sibling->color ==black && ((is_it_left(current) && sibling->left->color == red && sibling->right->color == black))||(!is_it_left(current) && sibling->right->color == red && sibling->left->color == black)){
			if(is_it_left(current))
				sibling->left->color = black;
			else
				sibling->right->color = black;
			sibling->color = red;
			if(is_it_left(current))
				llrotate(sibling);
			else
				rrrotate(sibling);
			case_situation(current);
		}
		else if(current->color == black && sibling->color == black && ((is_it_left(current) && sibling->right->color == red)|| (!is_it_left(current) && sibling->left->color == red))){
			sibling->color = current->dad->color;
			current->dad->color = black;
			if(is_it_left(current)){
				sibling->right->color = black;
				rrrotate(current->dad);
			}
			else{
				sibling->left->color = black;
				llrotate(current->dad);
			}	
			return;
		}
		
	}
	void delete_second_step(Node* current, Node* replacement){
		current->key = replacement->key;
		if(current->color == red && (replacement->color == red || replacement->key == NULL)){
			if(replacement->key == NULL)
				delete_chield_of_dad(current);

			else
				delete_chield_of_dad(replacement);
			return;
		}
		if(current->color == red && (replacement->key != NULL && replacement->color == black)){
			current->color = red;
			delete_chield_of_dad(replacement);
			case_situation(current->right);
			return;
		}
		else if(current->color == black && replacement->color == red){
			current->color = black;
			delete_chield_of_dad(replacement);
			return;
		}
		else if(current->color == black && replacement->color== black && replacement == root){
			delete_chield_of_dad(replacement);
			return;
		}
		else if(current->color == black && replacement->color == black && replacement != root){
			if(replacement->key == NULL){
				delete replacement;
				replacement =  current;
			}
			else{
				replacement = delete_chield_of_dad(replacement);
			}
			case_situation(replacement);
			return;
		}
	}
	void delete_first_step(Node* current){
		//first step	
		struct Node* replacement;
		if(current->right->key ==NULL && current->left->key ==NULL){
			replacement = current->left;
			delete_second_step(current, replacement);
			return;
		}
		else if(current->right->key ==NULL && current->left->key != NULL || current->right->key != NULL && current->left->key == NULL){
			if(current->right->key != NULL)
				replacement = current->right;
			else
				replacement = current->left;
			delete_second_step(current, replacement);
			return;
		}
		else{
			replacement = current->right;
			if(replacement->left->key != NULL){
				while(replacement->left->key != NULL){
					replacement = replacement->left;
				}
			}
			delete_second_step(current, replacement);
			return;
		}	
	}
	
	
	void delete_zero_step(Node* node, int key){		
		if (root == nullptr){
			return;
		} 
		
		Node* current = root;
		while ((current->key != NULL)&&(current->key != key)) {
			if (current->key > key)
				current = current->left;
			else if (current->key < key)
				current = current->right;	
		}
		if (current == nullptr){
			return;
		} 
		delete_first_step(current);		
	}


	~RBtree() {
		if (root == nullptr) {
			return;
		}
		else {
			deletebt(root);
		}
	}
};

int main() {
	RBtree rb;
	rb.insert(rb.root, 13);
	rb.insert(rb.root, 8);
	rb.insert(rb.root, 17);
	rb.insert(rb.root, 1);
	rb.insert(rb.root, 11);
	rb.delete_zero_step(rb.root, 13);
}