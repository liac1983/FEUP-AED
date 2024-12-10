#include <string>
#include "hashTableOA.h"

// Read hash table and then q operations
template <typename KeyType>
void read() {
  int n;
  std::cin >> n;
  std::hash<KeyType> h;
  HashTableOA<KeyType> hashTable(n, h);

  int q;
  std::cin >> q;
  for (int i=0; i<q; i++) {
    std::string op;
    KeyType k;
    std::cin >> op;
    if (op == "CONTAINS") {
      std::cin >> k;
      std::cout << "contains(" << k << "): " << hashTable.contains(k) << std::endl;
    } else if (op == "INSERT") {
      std::cin >> k;
      std::cout << "insert(" << k << "): " << hashTable.insert(k) << std::endl;
    } else if (op == "REMOVE") {
      std::cin >> k;
      std::cout << "remove(" << k << "): " << hashTable.remove(k) << std::endl;
    } else if (op == "SHOW") {
      std::cout << "showContents():" << std::endl;
      hashTable.showContents();
    }
  }
}

int main() {

  std::string type;
  std::cin >> type;
  if (type == "int") read<int>();
  else if (type == "string") read<std::string>();
  
  return 0;
}
