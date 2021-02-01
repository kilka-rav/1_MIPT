#include <iostream>

namespace tree {
    template <typename T>
    class Node {
        public:
            T key;
            Node<T>* left;
            Node<T>* right;
    };
    
    template <typename T>
    class Tree {
        private:
            Node<T>* root;
            void delete_tree(Node<T>* t);
            void insert(Node<T>* t, T data);
            void print_tree(Node<T>* t) const;
            void search(Node<T>* t, T data) const;
        public:
            Tree() : root(nullptr) {}
            void insert(T data);
            void delete_tree();
            void search(T data) const;
            void print_tree() const;
    };
}

namespace tree {
    template <typename T>
    void Tree<T>::search(T data) const {
        search(root, data);
    }
    
    template <typename T>
    void Tree<T>::search(Node<T>* t, T data) const {
        if ( t == nullptr ) {
            std::cout << "false\n";
        }
        else if ( t->key == data ) {
            std::cout << "true\n";
        }
        else if ( t->key > data ) {
            search(t->left, data);
        }
        else if ( t->key < data ) {
            search(t->right, data);
        }
        else {
            std::cout << "false\n";
        }
    }

    template<typename T>
    void Tree<T>::insert(T data) {
        if ( root != nullptr ) {
            insert(root, data);
        }
        else {
            root = new Node<T>;
            root->key = data;
            root->left = nullptr;
            root->right = nullptr;
        }
    }

    template<typename T>
    void Tree<T>::insert(Node<T>* t, T data){
        if ( data < t->key) {
		    if ( t->left != nullptr ) {
			    insert(t->left, data);
		    } 
            else {
			    t->left = new Node<T>;
			    t->left->key = data;
			    t->left->left = nullptr;
			    t->left->right = nullptr;
	    	}
	    }
        else if ( data > t->key ) {
		    if( t->right != nullptr ) {
			    insert(t->right, data);
		    }
            else {
			    t->right = new Node<T>;
			    t->right->key = data;
			    t->right->right = nullptr;
			    t->right->left = nullptr;
		    }
	    }
    }

    
    template <typename T>
    void Tree<T>::print_tree() const {
        print_tree(root);
    }

    template <typename T>
    void Tree<T>::delete_tree() {
        delete_tree(root);
    }

    template <typename T>
    void Tree<T>::print_tree(Node<T>* root) const {
        if ( root != nullptr ) {
            print_tree(root->left);
            std::cout << root->key << std::endl;
            print_tree(root->right);
        }
    }

    template <typename T>
    void Tree<T>::delete_tree(Node<T>* t) {
        if ( t != nullptr ) {
            delete_tree(t->left);
            delete_tree(t->right);
            delete t;
        }
    }
        
}


int main() {
    tree::Tree<int> t;
    int j = 0;
    for(int i = 0; i < 1000; ++i) {
        j = rand() % 1000;
        t.insert(j);
    }
    t.delete_tree();
    return 0;
}
