#include "DynamicHash.h"


int main() {

	HashMap hashmap;
	hashmap.GetDataFromFile();

	hashmap.PrintHashTable();
	hashmap.PrintOutHashFile();
	
	cout << "Done!!" << endl;
	return 0;
}