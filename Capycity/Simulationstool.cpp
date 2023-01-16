#include <iostream>
#include <vector>
#include "Buildings.h"
using namespace std;

class CapycitySim {
public:
	//Speciherung des Bauplans
	Building** blueprint;

	//Groesse des Bauplans
	int rows;
	int columns;

	//Variable für Endlosschleife (siehe main)
	bool run = true;

	//Initialisieren des Baubereichs
	void prepareSpace() {
		int input;

		cout << "Bitte geben Sie die Laenge des Bereichs an." << endl;
		cin >> input;
		rows = input;
		cout << "Bitte geben Sie die Breite des Bereichs an." << endl;
		cin >> input;
		columns = input;
		cout << "Baubereich wird vorbereitet..." << endl;

		blueprint = new Building * [columns];
		for (int i = 0; i < columns; i++) {
			blueprint[i] = new Empty[rows];
		}
	}

	//Pruefen, ob Gebaeude gesetzt werden kann und nicht durch andere Gebaeude blockiert wird
	bool isValidSet(int length, int width, int xCoord, int yCoord) {
		bool valid = true;

		if (xCoord + length > rows)
			return false;
		if (yCoord + width > columns)
			return false;

		for (int i = yCoord; i < yCoord + width; i++) {
			for (int j = xCoord; j < xCoord + length; j++) {
				if (blueprint[i][j].getName().compare("Empty") != 0)
					valid = false;
			}
		}
		return valid;
	}

	//Pruefen, ob Lösch-Bereich innerhalb des Bauplans ist
	bool isValidDel(int length, int width, int xCoord, int yCoord) {
		if (xCoord + length > rows)
			return false;
		if (yCoord + width > columns)
			return false;

		return true;
	}

	//Erstellen eines Gebaeudes
	void setBuilding() {
		int length;
		int width;
		int xCoord;
		int yCoord;
		int buildingInput;
		Building buildingType;

		cout << "Bitte geben Sie die Laenge des Gebaeudes an." << endl;
		cin >> length;
		cout << "Bitte geben Sie die Breite des Gebaeudes an." << endl;
		cin >> width;
		cout << "Bitte geben Sie die X-Koordinate der linken oberen Ecke an." << endl;
		cin >> xCoord;
		cout << "Bitte geben Sie die Y-Koordinate der linken oberen Ecke an." << endl;
		cin >> yCoord;
		cout << "Welche Art von Gebaeude wollen Sie setzen?" << endl;
		cout << "Solarkraftwerk[0]	Wasserkraftwerk[1]	Windkraftwerk[2]" << endl;
		cin >> buildingInput;

		if (!isValidSet(length, width, xCoord, yCoord)) {
			cout << "Dieser Bereich ist ungueltig!" << endl;
			return;
		}
		if (buildingInput < 0 || buildingInput > 2) {
			cout << "Fehler: Unbekanntes Gebaeude" << endl;
			return;
		}

		switch (buildingInput) {
		case 0:
			buildingType = SolarGenerator();
			break;
		case 1:
			buildingType = AquaGenerator();
			break;
		case 2:
			buildingType = WindGenerator();
			break;
		default:
			return;
			break;
		}

		for (int i = xCoord; i < xCoord + length; i++) {
			for (int j = yCoord; j < yCoord + width; j++) {
				blueprint[j][i] = buildingType;
			}
		}
		cout << "Gebaeude wurde erfolgreich platziert!" << endl;
	}

	//Loeschen eines Gebaeudes
	void delBuilding() {
		int length;
		int width;
		int xCoord;
		int yCoord;

		cout << "Bitte geben Sie die Laenge des Bereichs an." << endl;
		cin >> length;
		cout << "Bitte geben Sie die Breite des Bereichs an." << endl;
		cin >> width;
		cout << "Bitte geben Sie die X-Koordinate der linken oberen Ecke an." << endl;
		cin >> xCoord;
		cout << "Bitte geben Sie die Y-Koordinate der linken oberen Ecke an." << endl;
		cin >> yCoord;

		if (!isValidDel(length, width, xCoord, yCoord)) {
			cout << "Dieser Bereich ist ungueltig!" << endl;
			return;
		}

		for (int i = xCoord; i < xCoord + length; i++) {
			for (int j = yCoord; j < yCoord + width; j++) {
				blueprint[j][i] = Empty();
			}
		}
		cout << "Gebaeude wurde erfolgreich geloescht!" << endl;
	}

	//Berechne Preis eines gegebenen Gebaeuedes
	int buildingPrice(Building b) {
		int result = b.getDefaultPrice();
		for (auto m : b.getMaterials()){
			result += m.getPrice();
		}
		
		return result;
	}

	//Berechne Preis des gesamten Bauplans
	int totalPrice() {
		int result = 0;

		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				result += buildingPrice(blueprint[i][j]);
			}
		}
		return result;
	}

	//Ausgabe des aktuellen Bauplans
	void printBlueprint() {
		cout << "--------------------------------------------------------------" << endl;
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				cout << blueprint[i][j].getLabel();
			}
			cout << "\n";
		}
		cout << "--------------------------------------------------------------" << endl;
		cout << "LEGENDE" << endl;
		cout << "--------------------------------------------------------------" << endl;
		vector<Building> buildingTypes = {SolarGenerator(), AquaGenerator(), WindGenerator()};
		for (auto b : buildingTypes) {
			cout << "[" << b.getLabel() << "] " << b.getName() << endl;
			cout << "Materialien:	[ ";
			for (auto m : b.getMaterials()) {
				cout << m.getName() << " ";
			}
			cout << "]" << endl;
			cout << "Preis:		" << buildingPrice(b) << "$" << endl;
			cout << "--------------------------------------------------------------" << endl;
		}
		cout << "Gesamtpreis:	" << totalPrice() << "$" << endl;
	}

	//Begruessung und Aufruf zur Bauplan-Erstellung
	void startUp() {
		cout << "--------------------------------------------------------------" << endl;
		cout << "CapyCity" << endl;
		cout << "--------------------------------------------------------------" << endl;
		cout << "Bitte erstellen sie zunaechst Ihren Baubereich." << endl;
		prepareSpace();

	}

	//Hauptmenue mit Aufruf der einzelnen Methoden
	void mainMenu() {
		int input = 0;

		cout << "--------------------------------------------------------------" << endl;
		cout << "Sie befinden sich im Hauptmenue. Welche Aktion moechten Sie ausfuehren?" << endl;
		cout << "[1] Gebaeude setzen" << endl;
		cout << "[2] Bereich loeschen" << endl;
		cout << "[3] Bauplan anzeigen" << endl;
		cout << "[4] Programm beenden" << endl;
		cout << "--------------------------------------------------------------" << endl;

		cin >> input;

		switch (input) {
		case 1:
			setBuilding();
			break;
		case 2:
			delBuilding();
			break;
		case 3:
			printBlueprint();
			break;
		case 4:
			run = false;
			break;
		default:
			cout << "Fehler: Der angegebene Befehl konnte nicht gefunden werden!" << endl;
			break;
		}
	}
};
	//Main-Methode mit Endlosschleife bis Programm beendet wird
	int main() {
		CapycitySim sim;
		sim.startUp();
		while (sim.run)
		{
			sim.mainMenu();
		}
	}