#pragma once

#include "Materials.h"
#include <string>
#include <vector>

using namespace std;

class Building
{
public:
	string name;
	string label;
	int price;
	vector<Material> materials;

	~Building();

	string getName();
	string getLabel();
	int getDefaultPrice();
	vector<Material> getMaterials();
};

class SolarGenerator : public Building {
public:
	SolarGenerator();
};
class AquaGenerator : public Building {
public:
	AquaGenerator();
};
class WindGenerator : public Building {
public:
	WindGenerator();
};
class Empty : public Building {
public:
	Empty();
};

