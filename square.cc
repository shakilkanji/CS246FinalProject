#include "square.h"
using namespace std;

Square::Square(int index, string name) : index(index), name(name) {}

Square::~Square() {}

int Square::getIndex() {
	return index;
}

string Square::getName() {
	return name;
}
