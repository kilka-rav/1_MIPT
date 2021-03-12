#include <iostream>
#include <list>
#include <iterator>

class Hash {
    private:
        std::list<std::string>* table;
        int num;
    public:
        Hash(int x) { 
            num = x;
            table = new std::list<std::string>[num];
        }
        Hash() {
            num = 0;
            table = new std::list<std::string>[num];
        }
        void insert(std::string blob);
        bool delete_item(std::string blob);
        int hash_function(std::string blob) const;
        void display() const;
        ~Hash() {
            delete[] table;
        }
};

void Hash::insert(std::string blob) {
    int id = hash_function(blob);
    table[id].push_back(blob);
}

bool Hash::delete_item(std::string blob) {
    int id = hash_function(blob);
    for(std::list<std::string>::iterator It = table[id].begin(); It != table[id].end(); ++It) {
        if ( *It == blob ) {
            table[id].erase(It);
            return true;
        }
    }
    return false;
}

int sum(std::string s) {
    int x = 0;
    int count = 16;
    if ( s.length() < 16 ) {
        count = s.length();
    }
    for(int i = 0; i < count; ++i) {
            x += s[i] - '0';
        }
    return x;
}

int Hash::hash_function(std::string blob) const {
    int x = sum(blob);
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
    std::string a[] = {"1111", "0000", "101", "101010101", "00001", "1000000"};
    int n = sizeof(a)/sizeof(a[0]);
    Hash h(7);
    for (int i = 0; i < n; i++) {
        h.insert(a[i]);
    }
    h.display();
    h.delete_item("1111");
    std::cout << "AFTER delete 1111\n";
    h.display();
    return 0;
}


