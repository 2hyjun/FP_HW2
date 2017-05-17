//#include "DynamicHash.h"
#include <iostream>

using namespace std;
class Node {
	float mScore;
};
class LeafNode : public Node{
private:
	double addr;
	LeafNode* next;
};
int main() {
	cout << sizeof(LeafNode) << endl;

}
