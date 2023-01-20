#include "Blueprint.h"

	//Konstruktor
	Blueprint::Blueprint(int r, int c) {
		rows = r;
		columns = c;
		ratio = 0;

		content = new Building** [columns];
		for (int i = 0; i < columns; i++) {
			content[i] = new Building*[rows];
			for (int j = 0; j < rows; j++) {
				content[i][j] = nullptr;
			}
		}
	}

	//Berechne Preis des gesamten Bauplans
	int Blueprint::calculatePrice() {
		int result = 0;

		for (auto building : getBuildings()) {
			result += building.first->getTotalPrice(building.second);
		}
		return result;
	}
	//Berechne Leistung des gesamten Bauplans
	int Blueprint::calculatePower() {
		int result = 0;

		for (auto building : getBuildings()) {
			result += building.first->getPower();
		}
		return result;
	}
	//Berechne Kennzahl des Bauplans
	double Blueprint::calculateRatio() {
		double divisor = this->calculatePrice() * rows * columns;
		if (divisor == 0) {
			return -1;
		}
		return this->calculatePower() / divisor;
	}
	//Funktor zur Überprüfung auf Gleichheit
	bool Blueprint::operator() (Blueprint other) {
		if (this->calculateRatio() != other.calculateRatio())
			return false;
		if (this->calculatePower() != other.calculatePower())
			return false;
		if (this->calculatePrice() != other.calculatePrice())
			return false;
		if (this->getColumns() != other.getColumns() || this->getRows() != other.getRows())
			return false;

		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				if ((this->getContent()[i][j] == nullptr) && (other.getContent()[i][j] != nullptr))
					return false;
				if ((this->getContent()[i][j] != nullptr) && (other.getContent()[i][j] == nullptr))
					return false;
				if ((this->getContent()[i][j] != nullptr) && (other.getContent()[i][j] != nullptr)) {
					if (this->getContent()[i][j]->getLabel() != other.getContent()[i][j]->getLabel())
						return false;
				}
			}
		}

		return true;
	}

	//Gibt Liste aller Gebäude-Objekte in der Matrix und deren Größe zurück
	map<Building*, int> Blueprint::getBuildings() {
		map<Building*, int> buildings = {};
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				if (content[i][j] != nullptr) {
					if (buildings.count(content[i][j]) > 0) {
						buildings[content[i][j]]++;
					} else {
						buildings.insert({content[i][j],1 });
					}
				}	
			}
		}
		return buildings;
	}

	//Getter
	Building*** Blueprint::getContent() {
		return content;
	}
	int Blueprint::getRows() {
		return rows;
	}
	int Blueprint::getColumns() {
		return columns;
	}
	double Blueprint::getRatio() {
		return ratio;
	}

