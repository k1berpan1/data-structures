#include <iostream>

//search = log2(n)   insert = log2(n)	remove = log2(N) . Ýòî âñå ñïðàâåäëèâî äëÿ ñáàëîíñèðîâàííîãî äåðåâà.  h- càìûé äëèíûé ïóòü îò êîðíÿ äî óçëà íà íèæíåì óðîâíå. Äëÿ íàõîæäåíèÿ ìàêñèìàëüíîãî êîîëè÷åñòâà ýëåìåíòîâ 2^(h+1) - 1
// if in bt n nodes, max heights  =  n-1
struct Node {
	int key;
	std::string data = "";
	struct Node* left = nullptr;
	struct Node* right = nullptr;
};
struct Binarytree {
	struct Node* root = nullptr;

	void inorder(Node* node) {
		if (node == NULL) 
			return;
		inorder(node->left);
		std::cout << node->key << std::endl;
		inorder(node->right);
		
	}
	void preodrder(Node* node) {
		if (node == NULL)
			return;

		std::cout << node->key << std::endl;

		preodrder(node->left);

		preodrder(node->right);
	}
	auto find(int key) {
		if (root == nullptr) {
			std::cout << "Binary tree has already been cleared";
		}
		else {
			Node* temp = root;
			
			while (temp != nullptr) {
				if (temp->key > key)
					temp = temp->left;
				

				else if (temp->key < key)
					temp = temp->right;

				else {
					//std::cout << "data: " << temp->data << std::endl;
					return temp;
				}
			
			}
			std::cout << " Don't find" << std::endl;

			
		}
	}
	void add(int key, std::string data ="") {
		if (root == nullptr) {
			root = new Node;
			root->key = key;
			root->data = data;

		}
		else {
			Node* new_node = new Node;
			new_node->key = key;
			new_node->data = data;
			Node* temp = root;
			while ((temp->left != new_node) && (temp->right !=new_node)) {
				while (new_node->key < temp->key) {

					if (temp->left == nullptr) {
						temp->left = new_node;
						break;
					}
					else {
						temp = temp->left;
					}
				}

				while (new_node->key > temp->key) {
					if (temp->right == nullptr) {
						temp->right = new_node;
						break;
					}
					else {
						temp = temp->right;
					}
				}	
			}
		}
	}
	void deletenode(int key) {
		if (root == nullptr) {
			std::cout << "Binary tree has already been cleared";
		}
		
		else {
			Node* current = root;
			Node* parent = nullptr;

			while ((current != nullptr)&&(current->key != key)) {
				parent = current;
				if (current->key > key)
					current = current->left;


				else if (current->key < key)
					current = current->right;	
			}
			if (current == nullptr) {
				std::cout << "ther isn't this element";

			}
			
			else {endl
				if ((current->left == nullptr) && (current->right == nullptr)) {
					if (parent->left == current) {
						current->data.clear();
						delete parent->left;
						parent->left = nullptr;
					}
					else {
						current->data.clear();
						delete parent->right;
						parent->right = nullptr;
					}


				}
				else if ((current->left != nullptr) && (current->right != nullptr)) {
					
					if (current->right->left == nullptr) {
						current->data = current->right->data;
						current->key = current->right->key;
						delete current->right;
						current->right = nullptr;
					}
					else {
						Node* temp = current->right->left;

						while (temp->left->left!= nullptr) {
							temp = temp->left;
						}
						/*temp ->left = parent->right->left;
						temp->right = parent->right->right;*/
						current->data = temp->left->data;
						current->key = temp->left->key;
						if (temp->left->right != nullptr) {
							temp->left = temp->left->right;
							delete temp->left->right;
							temp->left->right = nullptr;
						}
						else {
							delete temp->left;
							temp->left = nullptr;
						}
						
							
						/*current =temp;
						parent->right = current;
						delete current->right->left;
						current->right->left = nullptr;*/
					}
					

				}
				else if ((current->left != nullptr) || (current->right != nullptr)) {
					if (parent->left == current) {
						if (current->left != nullptr) {
							parent->left = current->left;
						}
						else {
							parent->left = current->right;
						}
						delete current;
						current = nullptr;
					}
					else {
						if (current->left != nullptr) {
							parent->right = current->left;
						}
						else {
							parent->right = current->right;

						}
						delete current;
						current = nullptr;
					}			
				}
			}
		}
	}
	void deletebt(Node* node) {
		
		if (node) {
			deletebt(node->left);
			deletebt(node->right);
			delete node;
		}
		
	}
	
	~Binarytree() {
		if (root == nullptr) {
			std::cout << "linked list is empty";
		}
		else {
			deletebt(root);
		}
	}
};

int main() {
	setlocale(LC_ALL, "RU");
	Binarytree bt;

	bt.add(1000, "el 1000");
	bt.add(1001, "el 1001");
	bt.add(5, "el 5");
	bt.add(4, "el 4");
	bt.add(7, "el 7");
	bt.add(6, "el 6");
	bt.add(999, "el 999");
	bt.add(950, "el 950");
	bt.add(900, "el 900");
	bt.add(925, "el 925");

	//bt.inorder(bt.root);
	bt.preodrder(bt.root);
	//bt.Delete(7);
	/*bt.Delete(3);
	std::cout << bt.find(3);*/
	/*auto a = bt.find(4);
	std::cout << a->data;*/
}																																																										