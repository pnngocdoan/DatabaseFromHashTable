#include <iostream>
#include <string>
#include <vector>
#include "hashFunction.h"
using namespace std;

const int MAX = 1e9;
struct Node {
  string key;
  int intPointer = -1;
  vector<string> arrPointer;
};

struct HashTable {
  Node* head = NULL;
  int count = 0;
};

int col, row;
HashTable* columns;
HashTable* hashTable;
string keys[MAX];

Node* createNode (string key) {
  Node* newNode = new Node();
  newNode->key = key;
  return newNode;
}

void insertKey(char type, string key, int i) {
  if (type == 'c') {
      int index = JSHash(key) % MAX;
      while (columns[index].count == 1) index = (index+1) % MAX;
      Node* newNode = createNode(key);
      columns[index].head = newNode;
      columns[index].count = 1;
      columns[index].head->intPointer = i;
  }
  else {
    int index = JSHash(key) % MAX;
   // cout << index << " " << key;
    while (hashTable[index].count == 1) index = (index+1) % MAX;
    Node* newNode = createNode(key);
    hashTable[index].head = newNode;
    hashTable[index].count = 1;
  }
}

void insertRow(string value[], string id) {
  int index = JSHash(id) % MAX;
  while (hashTable[index].head->key != id) index = (index+1) % MAX;
  for (int i = 1; i < col; i++) hashTable[index].head->arrPointer.push_back(value[i]); 
}

int searchKey(char type, string key) {
  if (type == 'h') {
    int index = JSHash(key) % MAX;
    if (hashTable[index].count == 0) return -2;
    while (index < MAX && hashTable[index].head->key != key) index = (index + 1) % MAX;
    if (hashTable[index].head->key == key) return index;
    return -2;
  }
  else {
    int index = JSHash(key) % MAX;
    if (columns[index].count == 0) return -2;
    while (index < MAX && columns[index].head->key != key) index = (index + 1) % MAX;
    if (columns[index].head->key == key) return columns[index].head->intPointer-1;
    return -2;
  }

}
string searchValue(string column, string id) {
  int indexCol = -1, indexRow = -1;
  if (searchKey('c', column) != -1) indexCol = searchKey('c', column);
  if (searchKey('h', id) != -1) indexRow = searchKey('h', id);
  if (indexCol != -1 && indexRow != -1) return hashTable[indexRow].head->arrPointer[indexCol];
  return "None";
}

void printHashTable() {
  for (int i = 0; i < col-1; i++) cout << keys[i] << " || ";
  cout << keys[col-1] << endl;

  for (int i = 0; i < 100; i++) {
    if (hashTable[i].count == 0 or !hashTable[i].head) continue;
    cout << hashTable[i].head->key << " || ";
    for (int j = 0; j < col-1; j++) cout << hashTable[i].head->arrPointer[j] << " || ";
    cout << hashTable[i].head->arrPointer[col-1] << endl;
  }
}

void createHashTable() {
  cout << "Enter the number of columns and rows of your database: ";
  cin >> col >> row;
  columns = new HashTable[MAX];
  hashTable = new HashTable[MAX];
  cout << "Enter the names of the columns in one row. The first column must be the unique ID. For example: StudentID FirstName LastName Grade" << endl;
  for (int i = 0; i < col; i++) {
    cin >> keys[i];
    insertKey('c', keys[i], i);
 //   insertColumnIndex(keys[i], i);
  }
  cout << "Enter the values of each column in one row. For example: 0001 Ngoc Doan 10" << endl;
  string id;
  for (int i = 0; i < row; i++) {
    cin >> id;
    insertKey('h', id, -1);
    string values[col];
    for (int j = 1; j < col;  j++) cin >> values[j];
    insertRow(values, id);
  }
}
