#include "DynamicHash.h"


int main() {

	HashMap hashmap;
	hashmap.GetDataFromFile();

	hashmap.PrintHashTable();
	//hashmap.PrintOutHashFile();
	//hashmap.HandleOverflow(6);
	cout << "Done!!" << endl;
	return 0;
}