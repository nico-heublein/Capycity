#pragma once
#include "Buildings.h"

using namespace std;

class Blueprint {
protected:
	Building** content;
	int rows;
	int columns;
	double ratio;

public:
	int calculatePrice();
	int calculatePower();
	double calculateRatio();
	bool operator() (Blueprint other);

	Blueprint(int r, int c);

	Building** getContent();
	int getRows();
	int getColumns();
	double getRatio();
};

