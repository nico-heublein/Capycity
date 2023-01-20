#pragma once
#include "Buildings.h"

using namespace std;

class Blueprint {
protected:
//Attribute
	//Matrix der einzelnen Felder
	Building*** content;
	//Zeilen und Spalten
	int rows;
	int columns;
	//Kennzahl
	double ratio;

public:
	//Konstruktor
	Blueprint(int r, int c);
//Methoden
	//Berechnung der wichtigen Werte
	int calculatePrice();
	int calculatePower();
	double calculateRatio();
	//Vergleich mit anderen Plänen
	bool operator() (Blueprint other);
	//Map mit allen Gebaeuden und der Größe dieser
	map<Building*, int> getBuildings();
//Getter
	Building*** getContent();
	int getRows();
	int getColumns();
	double getRatio();
};

