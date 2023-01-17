#pragma once
#include <string>

using namespace std;

class Material {
protected:
	string name;
	int price;

public:
	~Material();
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

