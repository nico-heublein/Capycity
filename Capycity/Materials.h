#pragma once
#include <string>

using namespace std;

class Material {
	public:
	string name;
	int price;

	string getName();
	int getPrice();
};

class Wood : public Material {
public:
	Wood();
};

class Metal : public Material {
public:
	Metal();
};

class Plastic : public Material {
public:
	Plastic();
};

