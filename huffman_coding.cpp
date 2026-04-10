#include <iostream>
#include <vector>
struct Node {
    int priority;
    char letter = NULL;
    struct Node* next = nullptr;
    struct Node* left = nullptr;
    struct Node* right = nullptr;
    
};
struct Priorityqueue {
    struct Node* head = nullptr;
    void push(char letter, int priority) {
        if (head == nullptr)
        {
            head = new Node();
            head->letter = letter;
            head->priority = priority;
        }
        else {
            Node* new_node = new Node();
            new_node->letter = letter;
            new_node->priority = priority;



            if (new_node->priority < head->priority) {
                struct Node* temp = head;

                new_node->next = temp;
                head = new_node;
                return;
            }
            struct Node* current = head;
            struct Node* parrent = head;

            while (parrent->next != new_node) {
                while ((current->priority < new_node->priority) && (current->next != nullptr)) {
                    parrent = current;
                    current = current->next;
                }
                if (current->priority == new_node->priority) {
                    new_node->next = current->next;
                    current->next = new_node;
                    return;
                }
                else if ((current->next == nullptr) && (current->priority < new_node->priority)) {
                    current->next = new_node;
                    return;
                }
                new_node->next = current;
                parrent->next = new_node;

            }
        }

    }
    void push(Node* &node) {
        if (node->priority < head->priority) {
            struct Node* temp = head;
            node->next = temp;
            head = node;
            return;
        }
        struct Node* current = head;
        struct Node* parrent = head;

        while (parrent->next != node) {
            while ((current->priority < node->priority) && (current->next != nullptr)) {
                parrent = current;
                current = current->next;
            }
            if (current->priority == node->priority) {
                node->next = current->next;
                current->next = node;
                return;
            }
            else if ((current->next == nullptr) && (current->priority < node->priority)) {
                current->next = node;
                return;
            }
            node->next = current;
            parrent->next = node;

        }

    }
    Node* peek() {
        return head;
    }
    int sizeofqueue() {
        int size = 0;
        if (head == nullptr) {
            size = 0;
        }
        else {
            struct Node* temp = head;
            while (temp != nullptr) {
                size++;
                temp = temp->next;
            }
        }
        return size;
    }


    void deletefirst() {
        if (head == nullptr) {
            std::cout << "priority queue is alreade cleaned";
        }
        else {
            Node* temp = head;
            head = head->next;
            delete temp;

        }
    }
    ~Priorityqueue() {
        if (head == nullptr) {
            std::cout << "priority queue is alreade cleaned" << std::endl;
        }
        else {
            while (head != nullptr) {
                deletefirst();
            }
            std::cout << "priority queue is cleaned" << std::endl;


        }
    }
};
void countthenumoflet(std::string words, Priorityqueue& queue) {
    char temp_let;
    int count = 0;
    int pos = 0;
    while (!words.empty()) {
        temp_let = words[0];
        int temp = words.length();
        count = 0;
        pos = 0;
        for (int i = 0; i < temp; i++) {
            if (temp_let == words[pos]) {
                count++;
                words.erase(pos, 1);
            }
            else {
                pos++;
            }
        }
        queue.push(temp_let, count);
    }

}

struct Hoffmantree {
    struct Node* root = nullptr;
    void push(Priorityqueue& pt) {
        root = new Node;
        Node* new_node_left = new Node;

        if(pt.peek()->letter != NULL){
            new_node_left->letter = pt.peek()->letter;
            new_node_left->priority = pt.peek()->priority;
            root->left = new_node_left;
            pt.deletefirst();
        }
        else{
            new_node_left->priority = pt.peek()->priority;
            new_node_left->left = pt.peek()->left;
            new_node_left->right = pt.peek()->right;
            root->left = new_node_left;
            pt.deletefirst();
        }
        Node* new_node_right = new Node;

        if(pt.peek()->letter != NULL){
            new_node_right->letter = pt.peek()->letter;
            new_node_right->priority = pt.peek()->priority;
            root->right = new_node_right;
            pt.deletefirst();
        }
        else{
            new_node_right->priority = pt.peek()->priority;
            new_node_right->left = pt.peek()->left;
            new_node_right->right = pt.peek()->right;
            root->right = new_node_right;
            pt.deletefirst();
        }

        root->priority = root->left->priority + root->right->priority;
        if(pt.sizeofqueue() != 0){
            pt.push(root);
        }

    }
    
    void inorder(Node* find_node, Node* current, std::string &addres) {
		if (current == NULL) {
            addres.pop_back();
			return;
        }
        if(find_node->letter == current->letter){
            std::cout << " letter "<<current->letter << " addres "<< addres<<std::endl;
            return;
        }
        addres.append("0");
		inorder(find_node, current->left, addres);
        addres.append("1");
		inorder(find_node, current->right, addres);
        addres.pop_back();
        
	}




    //  void inorder(Node* find_node, Node* current, std::string &addres) {
	// 	if (current == NULL) {
    //         addres.pop_back();
	// 		return;
    //     }
    //     if(find_node->letter == current->letter){
    //         std::cout << " letter "<<current->letter << " addres "<< addres<<std::endl;
    //         return;
    //     }
    //     else if(find_node->letter != current->letter && current->letter != NULL){
    //         addres.pop_back();
    //         return;
    //     }
    //     addres.append("0");
	// 	inorder(find_node, current->left, addres);
    //     if(current->priority == root->priority){
    //         addres= "";
    //     }
    //     addres.append("1");
    //     if(current->right->letter != find_node->letter && current->right->letter != NULL ){
    //         addres.pop_back();
    //         addres.pop_back();
    //         return;
    //     }
    //     else{
	// 	    inorder(find_node, current->right, addres);

    //     }

};


struct Nodetoarr{
    char letter;
    std::string addres;
};

int main() {
    setlocale(LC_ALL, "RU");
    Priorityqueue pt;
    pt.push('a', 1);
    pt.push('b', 4);
    pt.push('c', 5);
    pt.push('d', 2);
    pt.push('f', 0);
    std::string stroka = "Now it is work";
    Hoffmantree ht;
    Priorityqueue queuetostring, temp;

    countthenumoflet(stroka, queuetostring);
    while (queuetostring.sizeofqueue()!= 0)
    {
        ht.push(queuetostring);
    }
    //std::cout<<temp.sizeofqueue()<<std::endl;
    countthenumoflet(stroka, temp);
    // struct Node* temp_node;
    // temp_node = temp.peek();
    // std::cout<< "letter: "<< temp_node->letter<< " priority: "<< temp_node->priority<< std::endl;



    std::vector<Nodetoarr*> arrtoht;
    struct Node* temp_node;
    std::string addres;

    while(temp.sizeofqueue()!= 0){
        temp_node = temp.peek();
        addres = "";
        ht.inorder(temp_node, ht.root, addres);  
        Nodetoarr* new_node = new Nodetoarr;
        new_node->addres = addres;
        new_node->letter = temp_node->letter;
        arrtoht.push_back(new_node);
        temp.deletefirst();
    }

}
