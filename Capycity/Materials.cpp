#include "Materials.h"

using namespace std;

Material::~Material() {
	name.clear();
}

Wood::Wood() {
	name = "Holz";
	price = 20;
}
Metal::Metal() {
	name = "Metall";
	price = 40;
}
Plastic::Plastic() {
	name = "Kunststoff";
	price = 10;
}

string Material::getName() {
	return name;
}

int Material::getPrice() {
	return price;
}
