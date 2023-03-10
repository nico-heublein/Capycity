#include "Buildings.h"
#include <iostream>
#include <string>

using namespace std;

//Destruktor
Building::~Building() {
	name.clear();
	label.clear();
	materials.clear();
}

SolarGenerator::SolarGenerator() {
	name = "Solarplatten";
	label = "S";
	price = 100;
	power = 85;

	materials = {{new Plastic, 1}, {new Metal, 2}};
}
AquaGenerator::AquaGenerator() {
	name = "Wasserkraftwerk";
	label = "A";
	price = 150;
	power = 125;

	materials = { {new Plastic, 1}, {new Metal, 1}, {new Wood, 2}};
}
WindGenerator::WindGenerator() {
	name = "Windturbine";
	label = "W";
	price = 50;
	power = 50;

	materials = { {new Plastic, 1}, {new Metal, 1}, {new Wood, 1} };
}

int Building::getDefaultPrice() {
	return price;
}

//Berechne Gesamtpreis (Grundpreis + Materialpreis)
int Building::getTotalPrice(int size) {
	int result = this->getDefaultPrice();

	for (auto m : this->getMaterials()) {
		result += m.second * (size * m.first->getPrice());
	}
	return result;
}


//Getter
int Building::getPower() {
	return power;
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
