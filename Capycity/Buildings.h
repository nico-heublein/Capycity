#pragma once

#include "Materials.h"
#include <string>
#include <map>

using namespace std;

class Building
{
protected:
	string name;
	string label;
	int price;

	//Ich habe mich entschlossen Carlas Idee umzusetzen, da ich die Map in der Building-Klasse persönlich übersichtlicher und leichter zu verstehen finde.
	//Die Auslagerung der Materialien in eine gekapselte Klasse finde ich eher unübersichtlich und unpraktisch.
	map<Material*, int> materials;

public:
	~Building();
	string getName();
	string getLabel();
	int getDefaultPrice();
	map<Material*, int> getMaterials();
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

