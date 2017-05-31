#include "DBHelper.h"
#include <list>


int main() {

	DBHelper dbhelper;
	dbhelper.GetDataFromFile();
	dbhelper.CreateHashFile();
	dbhelper.CreateDBFile();

	cout << "Done!!" << endl;
	return 0;
}