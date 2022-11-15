#include <iostream>
#include <random>
#include <string>
using namespace std;

class hashItem {
public:
  int key;
  string senha;
};

class HashT {
private:
  int n; // Numero de itens na table
  hashItem *senhas;

public:
  HashT(int n);
  int hashIndex(int key);
  bool confereIndex(int ind);
  bool procuraSenha(string str);
  void insereItem(string str, int k);
  bool removeItem(int index);
  void imprimeHashT();
  ~HashT();
};

HashT::HashT(int n) {
  this->n = n;
  hashItem lista[n];
  for (int i = 0; i < n; i++) {
    lista[i].senha = "";
    lista[i].key = 0;
  }
  senhas = lista;
}

int HashT::hashIndex(int key) {
  int x = key % n;
  return x;
}

bool HashT::confereIndex(int ind) { // true: index liberado
  for (int i = 0; i < n; i++) {     // false: index ocupado
    if (senhas[i].senha == "") {
      return true;
    }
  }
  return false;
}

bool HashT::procuraSenha(string str) { // true: senha encontrada
  for (int i = 0; i < n; i++) {
    if (senhas[i].senha == str) {
      return true;
    }
  }
  return false;
}

void HashT::insereItem(string str, int k) {
  int x = hashIndex(k);
  if (!procuraSenha(str)) {
    while (!confereIndex(x)) {
      x++;
    }
    senhas[x].senha = str;
    senhas[x].key = k;
  }
}

bool HashT::removeItem(int index) {
  if (senhas[index].senha != "") {
    senhas[index].senha = "";
    senhas[index].key = 0;
    return true;
  }
  return false;
}

void HashT::imprimeHashT() {
  cout << '{' << endl;
  for (int i = 0; i < n; i++) {
    if (senhas[i].senha == "") {
      cout << i << ": [Nada armazenado aqui]" << endl;
    } else {
      cout << i << ": [" << senhas[i].key << ", " << senhas[i].senha << "]"
           << endl;
    }
  }
  cout << "}\nImpressao finalizada" << endl;
}

HashT::~HashT() {
  this->n = 0;
  for (int i = 0; i < n; i++) {
    senhas[i].senha = nullptr;
    senhas[i].key = 0;
  }
  cout << "Memoria liberada" << endl;
}

int main() {
  int x, y;
  string s = "";
  string teste_busca[2];
  char chars[36] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
                    'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  random_device a;
  mt19937 gerador(a());
  uniform_int_distribution<int> alfa(0, 35);
  uniform_int_distribution<int> tam(10, 50);
  uniform_int_distribution<int> keys(1, 50);
  HashT hash(50);
  for (int i = 0; i < 50; i++) {
    x = keys(gerador);
    y = tam(gerador);
    for (int j = 0; j < y; j++) {
      s += chars[alfa(gerador)];
    }
    hash.insereItem(s, x);
    if (i >= 48) {
      teste_busca[i - 48] = s;
    }
    s = "";
  }
  cout << "Hash Table: " << endl;
  hash.imprimeHashT();
  for (int i = 0; i < 2; i++) {
    if (hash.procuraSenha(teste_busca[i])) {
      cout << "\nResultado da busca pela senha " << teste_busca[i] << ": True"
           << endl;
    } else {
      cout << "\nResultado da busca pela senha " << teste_busca[i] << ": False"
           << endl;
    }
  }
  for (int i = 0; i < 5; i++) {
    if (hash.removeItem(i)) {
      cout << "\nItem do indice " << i << " removido com sucesso" << endl;
    } else {
      cout << "\nNenhum item econtrado no indice " << i << endl;
    }
  }
  cout << "\nHash Table pos remocao do item: " << endl;
  hash.imprimeHashT();
}
