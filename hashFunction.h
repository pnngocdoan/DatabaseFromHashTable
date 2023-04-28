#include <iostream>
#include <string>
using namespace std;
// Robert Sedgewick Hash Function
int RSHash(string keys) {
  int a = 63689, b = 378551;
  int hashValue = 0;
  for (int i = 0; i < keys.size(); i++) {
    hashValue = (hashValue * a + keys[i]) & 0x7FFFFFFF;
    a = (a * b) & 0x7FFFFFFF;
  }
  return hashValue & 0x7FFFFFFF;
}
// Polynomial Hash Function
int polyHash(string keys) {
  int hashValue = 0;
  int a = 33;
  for (int i = 0; i < keys.size(); i++) hashValue = (keys[i] + a*hashValue) & 0x7FFFFFFF;
  return hashValue & 0x7FFFFFFF;
}

// Cyclic shift Hash Function: 
int JSHash(string keys) {
  int hashValue = 1315423911;
  int a = 5, b = 2;
  for (int i = 0; i < keys.size(); i++) {
    int x = hashValue << a & 0x7FFFFFFF;
    int y = hashValue >> b & 0x7FFFFFFF;
    hashValue ^= (x + keys[i] + y) & 0x7FFFFFFF;
  }
  return hashValue & 0x7FFFFFFF;
}