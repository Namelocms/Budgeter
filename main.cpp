#include "Budgeter.h"

int main() {
	Budgeter uI;
	int x;
	
	// Initialize
	if (!uI.initBalance() || !uI.initExpences() || !uI.initIncome()) {
		cout << "Failed to load a file!" << endl;
		return 0;
	}

	do {
		x = uI.mainMenu();
	} while (x != 5);

	return 0;
}