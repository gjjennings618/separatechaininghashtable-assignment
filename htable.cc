/* 	Garrett Jennings | ZID: z1927185
 *	Separate Chaining Hash Table Assignment
 *	CS340 - 3
 *
 *	I certify that this is my own work and where appropriate an extension 
 *	of the starter code provided for the assignment.
 */

#include "htable.h"

#define N1 10  // num of decimal digits
#define N2 26  // num of upper-case letters

#define TBL_SZ 31 // Default Table Size
#define ITEM_KW 7 // Item width for key
#define ITEM_NW 6 // Item width for num
#define ITEM_LI 4 // Item left indent

// Hash function, you may NOT modify this function
int HT::hash(const string &s) {
  int n = (N2 * N1) * (s[0] - 'A') + N1 * (s[1] - 'A') + (s[2] - '0');

  return n % hsize;
}

// You will complete the code below ...
HT::HT(const unsigned &hs) {
  hsize = hs;
  hTable.resize(hs);
}
// Delete every element in pTable
HT::~HT() {
  for (Entry *e: pTable){
    delete e;
  }
}
// Inserts the entry into hTable according to its hash(key),
// adds pointer to each entry to pTable
// if key is already in use, the entry is rejected
void HT::insert(const Entry &e) {
  int index = hash(e.key);
  list<Entry> &l = hTable[index];
  auto lambda = [e](Entry cent) { return e.key == cent.key;  };
  if (l.size() > 0){ // This avoids segmentation fault for empty list. no need to check keys on empty list
    list<Entry>::iterator it = find_if(begin(l), end(l), lambda);
    if (it->key != e.key) {
      l.push_front(e); // New entries are added to the front of the list
      pTable.push_back( new Entry(e));
      cout << "entry = " << index << endl;
    }
    else cout << "not inserted - duplicate key!!!" << endl; // If the key is already present, reject the entry
  }
  else {
    l.push_front(e);
    pTable.push_back( new Entry(e));
    cout << "entry = " << index << endl;
  }

}
// Searches each entry in each list for the string argument
void HT::search(const string &s) {
  int index = hash(s);
  list<Entry> &l = hTable[index];
  auto lambda = [s](Entry cent) { return s == cent.key;  }; // Lambda function compares the key of each entry to the string
  list<Entry>::iterator it = find_if(begin(l), end(l), lambda);
  if (it == l.cend()) { // If the entry wasn't found, find_if returns l.cend();
    cout << " not in table!!" << endl;
  }
  else {
    cout << " ==> number: " << right << setw(ITEM_LI) << it->num << " - " << "item: " << it->desc << endl;
  }
}
// Loop through every list in hTable, printing info on each entry in the list
void HT::hTable_print() {
  cout << endl;
  for (unsigned int i = 0; i < hTable.size(); i++){
    for (list<Entry>::iterator j = hTable[i].begin(); j != hTable[i].end(); j++){
      cout << left << setw(ITEM_LI) << i << ":" << left << setw(ITEM_KW) << j->key << " - " << left << setw(ITEM_NW) << j->num << " -  " << j->desc << endl;
    }
  }
  cout << endl;
}
// Loop through each element in pTable, printing info on each entry in the list
void HT::pTable_print() {
  sort(pTable.begin(), pTable.end(), [](Entry *p, Entry *q){ return p->key < q->key; } ); // Lambda function compares the keys, sorts alphabetically
  for (Entry *e: pTable){
    cout << right << setw(ITEM_KW - 1 ) << e->key << " - " << right << setw(ITEM_NW+1) << e->num << "  -  " << e->desc << endl;
  }
}