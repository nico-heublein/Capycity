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

	materials = {{new Plastic, 1}, {new Metal, 2}};
}
AquaGenerator::AquaGenerator() {
	name = "Wasserkraftwerk";
	label = "A";
	price = 200;

	materials = { {new Plastic, 1}, {new Metal, 1}, {new Wood, 2}};
}
WindGenerator::WindGenerator() {
	name = "Windturbine";
	label = "W";
	price = 50;

	materials = { {new Plastic, 1}, {new Metal, 1}, {new Wood, 1} };
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

map<Material*, int> Building::getMaterials() {
	return materials;
}
