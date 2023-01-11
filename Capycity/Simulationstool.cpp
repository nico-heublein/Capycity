#include <iostream>
using namespace std;

enum Building {Empty, Solar, Water, Wind};
Building* buildingArea;
bool run = true;

void prepareSpace() {
	int input;

	cout << "Bitte geben Sie die Laenge des Bereichs an." << endl;
	cin >> input;
	const int rows = input;
	cout << "Bitte geben Sie die Breite des Bereichs an." << endl;
	cin >> input;
	const int columns = input;
	cout << "Baubereich wird vorbereitet..." << endl;

	Building** area = new Building* [rows];

	for (int i = 0; i < rows; i++) {
		area[i] = new Building [columns];
		for (int j = 0; j < columns; j++) {
			area[i][j] = Empty;
		}
	}
}

void startUp() {
	cout << "--------------------------------------------------------------" << endl;
	cout << "CapyCity" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "Bitte erstellen sie zunaechst Ihren Baubereich." << endl;
	prepareSpace();

}

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
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		run = false;
		break;
	default:
		cout << "Fehler: Der angegebene Befehl konnte nicht gefunden werden!" << endl;
		break;
	}
}

int main() {
	startUp();
	while (run)
	{
		mainMenu();
	}
}
