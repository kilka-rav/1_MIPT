#include <iostream>


struct Node {
    int data;
    Node *next;
};

class List {
    private:
        Node *head;
    public:
        List() : head(nullptr) {}
        void insert(int _data);
        void print() const;
        void cycle();
        bool check_ios() const;
        ~List();
};

void List::insert(int _data) {
    Node* temp = new Node;
    temp->data = _data;
    temp->next = head;
    head = temp;
}

void List::cycle() {
    Node* temp = head;
    while ( temp->next != nullptr ) {
        temp = temp->next;
    }
    temp->next = head;
    
}

void List::print() const {
    Node* temp = head;
    while ( temp != nullptr ) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

List::~List() {
    while ( head != nullptr ) {
        Node* temp = head->next;
        delete head;
        head = temp;
    }
}

bool List::check_ios() const {
    Node* rabbit1;
    Node* rabbit2;
    rabbit1 = head;
    rabbit2 = head;
    while( rabbit2->next != nullptr ) {
        rabbit1 = rabbit1->next;
        rabbit2 = rabbit2->next;
        if ( rabbit2->next == nullptr ) {
            return false;
        }
        rabbit2 = rabbit2->next;
        if ( rabbit1->data == rabbit2->data ) {
            return true;
        }
    }
    return false;
}

int main() {
    List lst;
    for(int i = 0; i < 15; ++i) {
        lst.insert(i);
    }
    lst.insert(5);
    std::cout << lst.check_ios() << std::endl;
    lst.print();
    lst.cycle();
    std::cout << lst.check_ios() << std::endl;
    exit(1);
    return 0;
}
    
