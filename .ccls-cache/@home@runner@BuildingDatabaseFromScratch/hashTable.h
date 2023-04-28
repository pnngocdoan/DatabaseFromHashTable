#include <iostream>
#include <string>
#include <vector>
#include "hashFunction.h"
using namespace std;

struct Node {
  string key;
  int intPointer;
  vector<string> arrPointer;
};

struct HashTable {
  Node* head = NULL;
  int count = 0;
};

int col, row;
HashTable* columns;
HashTable* hashTable;
string keys[100];

Node* createNode (string key) {
  Node* newNode = new Node();
  newNode->key = key;
//  newNode->arrPointer = NULL;
//  newNode->intPointer = NULL;
  return newNode;
}

void insertKey(char type, string key) {
  if (type == 'c') {
      int index = JSHash(key) % 100;
      Node* newNode = createNode(key);
      if (!columns[index].head) {
        columns[index].head = newNode;
        return;
      }
  }
  else {
    int index = JSHash(key) % 100;
    Node* newNode = createNode(key);
    if (!hashTable[index].head) {
      hashTable[index].head = newNode;
      hashTable[index].count = 1;
      return;
    }
  }
}

void insertRow(string value[], string id) {
  int index = JSHash(id) % 100;
  for (int i = 0; i < col - 1; i++) hashTable[index].head->arrPointer.push_back(value[i]); 
}

void insertColumnIndex(string key, int i) {
  int index = JSHash(key) % 100;
  columns[index].head->intPointer = i;
}

int searchKey(char type, string key) {
  if (type == 'h') {
    int index = JSHash(key) % 100;
    Node* myNode = hashTable[index].head;
    if (myNode && myNode->key == key) return index;
    return -1;
  }
  else {
    int index = JSHash(key) % 100;
    Node* myNode = columns[index].head;
    if (myNode && myNode->key == key) return index;
    return -1;
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

  for (int i = 0; i < row; i++) {
    if (hashTable[i].count == 0) continue;
    Node* id = hashTable[i].head;
    if (!id) continue;
    cout << id->key << " || ";
    for (int j = 0; j < col-1; j++) {
      cout << id->arrPointer[j] << " || ";
    }
    cout << id->arrPointer[col-1] << endl;
  }
}

int createHashTable() {
  cout << "Enter the number of columns and rows of your database: ";
  cin >> col >> row;
  columns = new HashTable[col];
  hashTable = new HashTable[row];
  cout << "Enter the names of the columns in one row. The first column must be the unique ID. For example: StudentID FirstName LastName Grade" << endl;
  for (int i = 0; i < col; i++) {
    cin >> keys[i];
    insertKey('c', keys[i]);
    insertColumnIndex(keys[i], i);
  }
  cout << "Enter the values of each column in one row. For example: 0001 Ngoc Doan 10" << endl;
  string id;
  for (int i = 0; i < row; i++) {
    cin >> id;
    insertKey('h', id);
    string values[col-1];
    for (int j = 0; j < col-1;  j++) cin >> values[j];
    insertRow(values, id);
  }
  printHashTable();
}
