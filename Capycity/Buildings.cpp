#include "Buildings.h"
#include <iostream>
#include <string>

using namespace std;

Building::~Building() {
	name.clear();
	label.clear();
	materials.clear();
}

SolarGenerator::SolarGenerator() {
	name = "Solarkraftwerk";
	label = "S";
	price = 100;

	materials = {Plastic(), Metal(), Metal()};
}
AquaGenerator::AquaGenerator() {
	name = "Wasserkraftwerk";
	label = "A";
	price = 200;

	materials = {Plastic(), Metal(), Wood(), Wood()};
}
WindGenerator::WindGenerator() {
	name = "Windturbine";
	label = "W";
	price = 50;

	materials = { Plastic(), Metal(), Wood() };
}

Empty::Empty() {
	name = "Empty";
	label = "X";
	price = 0;

	materials = {};
	
}

int Building::getDefaultPrice() {
	return price;
}

string Building::getLabel() {
	return label;
}

string Building::getName() {
	return name;
}

vector<Material> Building::getMaterials() {
	return materials;
}
