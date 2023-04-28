#include <iostream>
#include <string>
#include <vector>
#include "hashTable.h"
using namespace std;

int main() {
  createHashTable();
  cout << "Queries include: searchColumn, searchID, searchValue, printTable" << endl;
  string query, column, id;
  while (1) {
    cout << "Enter your query. Type 0 if you don't want to continue: ";
    cin >> query;
    cout << endl;
    if (query == "searchColumn") {
      cout << "Enter a column: ";
      cin >> column;
      cout << (searchKey('c', column) != -2 ? "Yes, it is in the database" : "No, it is not in the database") << endl;
    }
    else if (query == "searchID") {
      cout << "Enter an ID: ";
      cin >> id;
      cout << (searchKey('h', id) != -2 ? "Yes, it is in the database" : "No, it is not in the database") << endl;
    }
    else if (query == "searchValue") {
      cout << "Enter a column and an ID: ";
      cin >> column >> id;
      cout << (searchValue(column, id)) << endl;
    }
    else if (query == "printTable") printHashTable();
    else break;
  }
}