#include <iostream>
#include <list>
#include <iterator>

class Hash {
    private:
        std::list<int>* table;
        int num;
    public:
        Hash(int x) { 
            num = x;
            table = new std::list<int>[num];
        }
        Hash() {
            num = 0;
            table = new std::list<int>[num];
        }
        void insert(int x);
        bool delete_item(int x);
        int hash_function(int x) const;
        void display() const;
        ~Hash() {
            delete[] table;
        }
};

void Hash::insert(int x) {
    int id = hash_function(x);
    table[id].push_back(x);
}

bool Hash::delete_item(int x) {
    int id = hash_function(x);
    for(std::list<int>::iterator It = table[id].begin(); It != table[id].end(); ++It) {
        if ( *It == x ) {
            table[id].erase(It);
            return true;
        }
    }
    return false;
}

int Hash::hash_function(int x) const {
    return x % num;
}

void Hash::display() const {
  for (int i = 0; i < num; ++i) {
      std::cout << i;
      for (auto x : table[i]) {
          std::cout << " -> " << x;
      }
      std::cout << std::endl;
  }
}



int main() {
    int a[] = {15, 11, 27, 8, 12};
  int n = sizeof(a)/sizeof(a[0]);

  Hash h(7);
  for (int i = 0; i < n; i++)
    h.insert(a[i]);

  // delete 12 from hash table
  h.delete_item(12);

  // display the Hash table
  h.display();

  return 0;

}


