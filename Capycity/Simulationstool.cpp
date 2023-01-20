#include <iostream>
#include <vector>
#include <algorithm>
#include "Buildings.h"
#include "Blueprint.h"

class CapycitySim {
public:
	//Variable für Endlosschleife (siehe main)
	bool run = true;
	//Aktuell zu bearbeitender Plan
	Blueprint* currentBlueprint;
	//Vektor mit allen fertigen, abgespeicherten Plänen
	vector<Blueprint> savedBlueprints;


	//Initialisieren des Baubereichs
	void prepareSpace() {
		int input;
		int rows;
		int columns;

		cout << "Bitte geben Sie die Laenge des Bereichs an." << endl;
		cin >> input;
		rows = input;
		cout << "Bitte geben Sie die Breite des Bereichs an." << endl;
		cin >> input;
		columns = input;

		if (rows <= 0 || columns <= 0) {
			cout << "Fehler: Diese Eingabe ist ungueltig. Bitte versuchen Sie es erneut." << endl;
			prepareSpace();
			return;
		}

		cout << "Baubereich wird vorbereitet..." << endl;

		currentBlueprint = new Blueprint(rows, columns);
	}

	//Pruefen, ob Gebaeude gesetzt werden kann und nicht durch andere Gebaeude blockiert wird
	bool isValidSet(int length, int width, int xCoord, int yCoord) {
		bool valid = true;
		if (length < 0 || width < 0 || xCoord < 0 || yCoord < 0)
			return false;
		if (xCoord + length > currentBlueprint->getRows())
			return false;
		if (yCoord + width > currentBlueprint->getColumns())
			return false;

		for (int i = yCoord; i < yCoord + width; i++) {
			for (int j = xCoord; j < xCoord + length; j++) {
				if (currentBlueprint->getContent()[i][j] != nullptr)
					valid = false;
			}
		}
		return valid;
	}

	//Pruefen, ob Lösch-Bereich innerhalb des Bauplans ist
	bool isValidDel(int length, int width, int xCoord, int yCoord) {
		if (length < 0 || width < 0 || xCoord < 0 || yCoord < 0)
			return false;
		if (xCoord + length > currentBlueprint->getRows())
			return false;
		if (yCoord + width > currentBlueprint->getColumns())
			return false;

		return true;
	}

	//Erstellen eines Gebaeudes (Koordinaten beginnen bei 0)
	void setBuilding() {
		int length;
		int width;
		int xCoord;
		int yCoord;
		int buildingInput;
		Building* building;

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

		//Pruefen auf Fehler
		if (!isValidSet(length, width, xCoord, yCoord)) {
			cout << "Dieser Bereich ist ungueltig!" << endl;
			return;
		}
		if (buildingInput < 0 || buildingInput > 2) {
			cout << "Fehler: Unbekanntes Gebaeude" << endl;
			return;
		}

		//Auswahl der Art
		switch (buildingInput) {
		case 0:
			building = new SolarGenerator();
			break;
		case 1:
			building = new AquaGenerator();
			break;
		case 2:
			building = new WindGenerator();
			break;
		default:
			return;
			break;
		}

		//Platzieren des Gebaeudes
		for (int i = xCoord; i < xCoord + length; i++) {
			for (int j = yCoord; j < yCoord + width; j++) {
				currentBlueprint->getContent()[j][i] = building;
			}
		}
		cout << "Gebaeude wurde erfolgreich platziert!" << endl;
	}

	//Loeschen eines Gebaeudes (Koordinaten starten bei 0)
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

		//Pruefen auf Validitaet des Bereichs
		if (!isValidDel(length, width, xCoord, yCoord)) {
			cout << "Dieser Bereich ist ungueltig!" << endl;
			return;
		}

		//Loeschen der entsprechenden Felder
		for (int i = xCoord; i < xCoord + length; i++) {
			for (int j = yCoord; j < yCoord + width; j++) {
				//Löschen des Gebäude-Objekts, falls letzter Verweis gelöscht wird
				if (currentBlueprint->getBuildings()[currentBlueprint->getContent()[j][i]] == 1)
					delete currentBlueprint->getContent()[j][i];
				//Reset des Pointers
				currentBlueprint->getContent()[j][i] = nullptr;
			}
		}
		cout << "Gebaeude wurde erfolgreich geloescht!" << endl;
	}

	//Ausgabe der Gebäude-Infos (Hilfsmethode für das Drucken der Pläne)
	void printBuildingInfo() {
		cout << "---------------------------------------------------------------------------------------" << endl;
		cout << "LEGENDE" << endl;
		cout << "---------------------------------------------------------------------------------------" << endl;
		vector<Building> buildingTypes = { SolarGenerator(), AquaGenerator(), WindGenerator() };

		//Ausgabe von Label, Name, Preis jedes Gebaeudetyps (pro Feld)
		for (auto b : buildingTypes) {
			cout << "[" << b.getLabel() << "] " << b.getName() << endl;
			cout << "Materialien:" << endl;

			for (auto m : b.getMaterials()) {
				cout << m.second << "x " << m.first->getName() << endl;
			}
			cout << "Grundpreis:	" << b.getTotalPrice(0) << "$" << endl;
			cout << "Gesamtpreis:	" << b.getTotalPrice(1) << "$" << endl;
			cout << "Leistung:	" << b.getPower() << "MW" << endl;

			cout << endl;
		}
		cout << "---------------------------------------------------------------------------------------" << endl;
		buildingTypes.clear();
	}

	//Ausgabe eines Bauplans
	void printBlueprint(Blueprint* plan) {

		//Ausgabe eines Bauplans mir Kennzahl K
		cout << endl;
		cout << "Bauplan	[K: " << plan->calculateRatio() << "]" << endl;
		cout << endl;

		//Ausgabe der Gebäude-Labels
		for (int i = 0; i < plan->getColumns(); i++) {
			for (int j = 0; j < plan->getRows(); j++) {
				if (plan->getContent()[i][j] != nullptr) {
					cout << plan->getContent()[i][j]->getLabel() << " ";
				} else {
					cout << "X ";
				}
				
			}
			cout << "\n";
		}
		//Ausgabe aller Gebäude
		printBuildings(plan);
		//Ausgabe des Gesamtpreis
		cout << "Gesamtpreis:		" << plan->calculatePrice() << "$" << endl;
		cout << "Energieproduktion:	" << plan->calculatePower() << "MW" << endl;
	}

	//Ausgabe aller Gebäude eines Planes
	void printBuildings(Blueprint* plan) {
		cout << endl;
		cout << "Gebaeude:" << endl;

		for (auto b : plan->getBuildings()) {
			cout << "[" << b.first->getLabel() << "] " << b.first->getName() << ":	Matererialien[ ";
			for (auto m : b.first->getMaterials())
				cout << b.second * m.second << "x" << m.first->getName() << " ";
			cout << "]	Preis: " << b.first->getTotalPrice(b.second) << "$" << "	Leistung: " << b.first->getPower() << "MW" << endl;
		}
		cout << endl;
	}

	//Ausgabe aller Baupläne nach Reihenfolge mithilfe von Lambda
	void printAll() {
		printBuildingInfo();

		cout << "---------------------------------------------------------------------------------------" << endl;
		cout << "BLAUPAUSEN" << endl;
		cout << "---------------------------------------------------------------------------------------" << endl;

		//Lambda zum Sortieren des Vektors in absteigender Reihenfolge
		auto sortRuleLambda = [](Blueprint& b1, Blueprint& b2) -> bool
		{
			return b1.calculateRatio() > b2.calculateRatio();
		};
		//Sortieren mithilfe von Lambda
		sort(savedBlueprints.begin(), savedBlueprints.end(), sortRuleLambda);

		for (auto b : savedBlueprints) {
			printBlueprint(&b);
		}
	}

	//Speichern des aktuellen Plans und Erstellen eines Neuen
	void createPlan() {
		cout << "Aktueller Bauplan wird abgespeichert..." << endl;

		//Suche nach gleichen Plänen
		for (auto b : savedBlueprints) {
			//Vergleich durch Funktor
			if ((*currentBlueprint)(b)) {
				cout << "INFO: Ein Bauplan mit diesen Eigenschaften existiert bereits (Bauplan wurde verworfen)" << endl;
				cout << "---------------------------------------------------------------------------------------" << endl;
				prepareSpace();
				return;
			}
		}
		savedBlueprints.push_back(*currentBlueprint);
		cout << "Bauplan wurde erfolgreich gespeichert!" << endl;
		cout << "---------------------------------------------------------------------------------------" << endl;
		prepareSpace();
	}

	//Begruessung und Aufruf zur Bauplan-Erstellung
	void startUp() {
		cout << "---------------------------------------------------------------------------------------" << endl;
		cout << "CapyCity" << endl;
		cout << "---------------------------------------------------------------------------------------" << endl;
		cout << "Bitte erstellen Sie zunaechst Ihren Baubereich." << endl;
		prepareSpace();

	}

	//Hauptmenü mit Aufruf der einzelnen Methoden
	void mainMenu() {
		int input = 0;
		//Hauptmenü, Auswahl durch Nummer der Option
		cout << "---------------------------------------------------------------------------------------" << endl;
		cout << "Sie befinden sich im Hauptmenue. Welche Aktion moechten Sie ausfuehren?" << endl;
		cout << "[0] Gebaeude setzen" << endl;
		cout << "[1] Bereich loeschen" << endl;
		cout << "[2] Aktuellen Bauplan anzeigen" << endl;
		cout << "[3] Gespeicherte Bauplaene anzeigen" << endl;
		cout << "[4] Neuen Bauplan erstellen" << endl;
		cout << "[5] Programm beenden" << endl;
		cout << "---------------------------------------------------------------------------------------" << endl;

		cin >> input;

		//Auswahl der Funktionalitaet
		switch (input) {
		case 0:
			setBuilding();
			break;
		case 1:
			delBuilding();
			break;
		case 2:
			printBuildingInfo();
			cout << "BLAUPAUSEN" << endl;
			cout << "---------------------------------------------------------------------------------------" << endl;
			printBlueprint(currentBlueprint);
			break;
		case 3:
			printAll();
			break;
		case 4:
			createPlan();
			break;
		case 5:
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
			sim.mainMenu();
	}