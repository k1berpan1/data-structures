#include <iostream>;
struct Node {
	int key;
	struct Node* left = nullptr;
	struct Node* right = nullptr;
	Node(int k){
		key = k;
		struct Node* left = nullptr;
		struct Node* right = nullptr;
	}
};

struct AVL_tree{
    struct Node* root = nullptr;

	void inorder(Node* node) {
		if (node == NULL) 
			return;
		inorder(node->left);
		std::cout << node->key << std::endl;
		inorder(node->right);
		
	}
	


    int getHeight(Node* node){
        if(node == NULL)
            return 0;
        return 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
    int balancefactor(Node*node){
        return getHeight(node->right) - getHeight(node->left);
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


	/*rotate*/


	Node* llrotate(Node* node){
		Node* temp = node->left->right;
		node->left->right = node;
		node = node->left;
		node->right->left = temp;
		if(node->right ==root)
			root = node;
		return node;
	}
	Node* lrrotate(Node* node){
		//std::cout<< "right child of left is heavy"<< std::endl;			
		Node* temp_right_of_chosen = node->left->right->right;
		Node* temp_future_left_child_of_chosen = node->left;
		Node* temp_left_of_chosen = node->left->right->left;
		node->left->right->right = node;
		node = node->left->right;
		node->right->left = temp_right_of_chosen;
		node->left = temp_future_left_child_of_chosen;
		if(node->right == root)
			root = node;
		node->left->right = temp_left_of_chosen;
		return node;	
	}
	Node* rrrotate(Node* node){
		Node* temp = node->right->left;
		node->right->left = node;
		node = node->right;
		node->left->right = temp;
		if(node->left == root)
			root = node;
		return node;
	}
	Node * rlrotate(Node* node){
		Node* temp_left_of_chosen = node->right->left->left;
		Node* temp_future_right_child_of_chosen = node->right;
		Node* temp_right_of_chosen = node->right->left->right;
		node->right->left->left = node;
		node = node->right->left;
		node->left->right = temp_left_of_chosen;
		node->right = temp_future_right_child_of_chosen;
		if(node->left == root)
			root = node;
		node->right->left = temp_right_of_chosen;
		return node;
	}
	/*rotate*/
	Node* insert(Node *node, int key ){
		if(root == NULL){
			root = new Node(key); 
			return root;
		}
		if (node == nullptr) 
        	return new Node(key); 

		if (key < node->key) 
			node->left = insert(node->left, key); 
		else if (key > node->key) 
			node->right = insert(node->right, key); 
		else // Equal keys are not allowed in BST 
			return node; 

		//std::cout<<"родитель"<< node->key<<std::endl;

		int bf = balancefactor(node);
        if(bf == -1 || bf == 0 || bf==1 ){
			//std::cout<<"all okey"<< std::endl;
			return node;	
		}
		else if(bf<-1){
			//less than 0: The node is "left heavy".
			if(balancefactor(node->left) < 0){
				node = llrotate(node);
				return node;
			}
			else{
				node = lrrotate(node);
				return node;		
			}
		}
		else if(bf>1){
            //more than 0: The node is "right heavy".
			if(balancefactor(node->right) < 0){
				//std::cout<< "left child of right is heavy"<< std::endl;
				node = rlrotate(node);
				return node;
			}
			else{
				//std::cout<< "right child of right is heavy"<< std::endl;
				node = rrrotate(node);	
				return node;		
			}
        }
	}
	Node* Delete(Node* node, int key){
		
		/*do smth when deleted node is root*/
		
		if (node == NULL) 
        	return NULL; 
		if(key == root->key && ((root->left == nullptr)&&(root->right == nullptr)) ){
			delete root;
			root = nullptr;
			return root;
		}
			

		if (key < node->key) 
			node->left = Delete(node->left, key); 
		else if (key > node->key) 
			node->right = Delete(node->right, key); 
		else if(key == node->key){
			if ((node->left == nullptr) && (node->right == nullptr)) {
					node = NULL;
					return node;
			}
			else if((node->left != nullptr) && (node->right != nullptr)){
				if (node->right->left == nullptr) {
					node->right->left = node->left;
					Node* temp = node;
					node = node->right;
					if(root->key==temp->key){
						root = node;
					}
					delete temp;
					temp = nullptr;
					return node;
				}
				else{
					Node* temp_node = node->right;
					while(temp_node->left != nullptr){
						temp_node = temp_node->left;
					}
					node->key = temp_node->key;
					Delete(node->right,temp_node->key );
					return node;
				}
			}
			else if ((node->left != nullptr) || (node->right != nullptr)) {
				if(node->left != nullptr){
					node->key = node->left->key;
					node->right = node->left->right;
					Node* temp = node->left->left;
					Node* temp_2 = node;
					if(root->key==temp_2->key){
						root = node;
					}
					delete temp_2;
					temp_2 = nullptr;
					delete node->left;
					node->left = temp;
					return node; 
				}
				else{
					node->key = node->right->key;
					node->left = node->right->left;
					Node* temp = node->right->right;
					delete node->right;
					node->right = temp;
					return node;
				}
			}
		}
		int bf = balancefactor(node);
        if(bf == -1 || bf == 0 || bf==1 ){
			//std::cout<<"all okey"<< std::endl;
			return node;	

		}
		else if(bf<-1){
			//less than 0: The node is "left heavy".
			if(balancefactor(node->left) < 0){
				node = llrotate(node);
				return node;
			}
			else{
				node = lrrotate(node);
				return node;		
			}
		}
		else if(bf>1){
            //more than 0: The node is "right heavy".
			if(balancefactor(node->right) < 0){
				//std::cout<< "left child of right is heavy"<< std::endl;
				node = rlrotate(node);
				return node;
			}
			else{
				//std::cout<< "right child of right is heavy"<< std::endl;
				node = rrrotate(node);	
				return node;		
			}
        }
		
		return node;

	}


	void deletebt(Node* node) {
		
		if (node) {
			deletebt(node->left);
			deletebt(node->right);
			delete node;
		}
		
	}
	
	~AVL_tree() {
		if (root == nullptr) {
			std::cout << "bt is empty";
		}
		else {
			deletebt(root);
		}
	}
};

int main() {
	setlocale(LC_ALL, "RU");
	
	AVL_tree bt;
	
	
	bt.insert(bt.root, 1);
	bt.insert(bt.root, 2);
	bt.insert(bt.root, 3);
	bt.insert(bt.root, 4);
	bt.insert(bt.root, 5);
	bt.insert(bt.root, 6);
	std::cout<<bt.root->key<< std::endl;

	
}		