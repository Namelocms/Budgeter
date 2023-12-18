#include "Budgeter.h"

// ===================
// INPUT CHECKING
// ===================
// Check input is a number 1-5 for main menu
int Budgeter::inputCheck5() {
	string num;
	int i;

	while (!(cin >> num) || (num != "1" && num != "2" && num != "3" && num != "4" && num != "5")) {		// While the input fails, or the number is not 1-5
		cout << endl;
		for (i = 0; i < 37; ++i) {
			cout << "=";
		}
		cout << "\nERROR: SELECTION MUST BE A NUMBER 1-8" << endl;							// Print error message
		for (i = 0; i < 37; ++i) {
			cout << "=";
		}
		cout << endl << endl;
		cout << "Enter a new selection: ";
		cin.clear();					// Clear input
		cin.ignore(1000, '\n');
	}

	return stoi(num);					// convert to integer for output
}
// Check input is a number 1-3 for balance and budget menus
int Budgeter::inputCheck3() {
	string num;
	int i;

	while (!(cin >> num) || (num != "1" && num != "2" && num != "3")) {		// While the input fails, or the number is not 1-3
		cout << endl;
		for (i = 0; i < 37; ++i) {
			cout << "=";
		}
		cout << "\nERROR: SELECTION MUST BE A NUMBER 1-3" << endl;							// Print error message
		for (i = 0; i < 37; ++i) {
			cout << "=";
		}
		cout << endl << endl;
		cout << "Enter a new selection: ";
		cin.clear();					// Clear input
		cin.ignore(1000, '\n');
	}

	return stoi(num);					// convert to integer for output
}
// Back to main menu button, checks user enters 'x'
void Budgeter::backToMain() {
	char x;

	cout << "\nEnter \'x\' to return to Main Menu: ";
	while (!(cin >> x) || x != 'x') {
		cout << "ERROR: Enter \'x\' to return to Main Menu: ";

		cin.clear();
		cin.ignore(1000, '\n');
	}
}

// ===================
// INITIALIZATION
// ===================
// Set Balance
bool Budgeter::initBalance() {
	ifstream file;
	double balance;
	
	file.open("PATH_TO_BALANCE/CurrentBalance.txt");
	if (!file.is_open()) {
		cout << "ERROR: Could not open file \'CurrentBalance.txt\'" << endl;
		return false;
	}
	file >> balance;
	Budgeter::setCurrentBalance(balance);

	file.close();
	return true;
}
// Set Expenses
bool Budgeter::initExpences() {
	ifstream file;
	string currExp;

	file.open("PATH_TO_EXPENSES/ExpensesPerMonth.txt");
	if (!file.is_open()) {
		cout << "Could not open file \'ExpensesPerMonth.txt\'" << endl;
		return false;
	}

	while (!file.eof()) {
		file >> currExp;
		if (file.eof()) {
			break;
		}
		monthlyExpenses.push_back(currExp);
	}
	//quickSort(monthlyExpenses, 0, monthlyExpenses.size() - 1);
	file.close();
	return true;
}
// Set Income
bool Budgeter::initIncome() {
	ifstream file;
	double income;
	
	file.open("PATH_TO_INCOME/IncomePerMonth.txt");
	if (!file.is_open()) {
		cout << "Could not open file \'IncomePerMonth.txt\'" << endl;
		return false;
	}
	file >> income;
	Budgeter::currentIncome = income;

	file.close();
	return true;
}

// ====================
// BALANCE MANIPULATORS
// ====================
// Change number in "CurrentBalance.txt" to new balance number
void Budgeter::updateCurrBal(double newBalance) {
	Budgeter::currentBalance = newBalance;
}
// Show the current balance
double Budgeter::getCurrBalance() {
	return Budgeter::currentBalance;
}
// Set current balance
void Budgeter::setCurrentBalance(double balance) {
	Budgeter::currentBalance = balance;
}

// ====================
// EXPENSE MANIPULATORS
// ====================
// Display all expenses and amounts in "ExpensesPerMonth.txt" file
void Budgeter::getAllExpenses() {
	int i;

	for (i = 0; i < monthlyExpenses.size(); ++i) {
		if (i % 2 != 0) {	// If i is odd
			cout << monthlyExpenses.at(i) << endl << endl;
		}
		else {
			cout << monthlyExpenses.at(i) << " : ";
		}
	}
}
// Append a new expense 
void Budgeter::addExpense(string exp, double amt) {
	Budgeter::monthlyExpenses.push_back(exp);
	Budgeter::monthlyExpenses.push_back(to_string(amt));
}
// Update an existing expense
void Budgeter::updateExpense() {
	int index;
	string exp;
	double amt;

	cout << "FIXME" << endl;
}
// Get Expense total
double Budgeter::getTotalExpense() {
	double total = 0;

	cout << endl << endl;
	for (int i = 0; i < Budgeter::monthlyExpenses.size(); i++) {
		if (i % 2 != 0) {
			total += stod(Budgeter::monthlyExpenses[i]);
		}
	}
	return total;
}

// ====================
// INCOME MANIPULATIONS
// ====================
// Get current income
double Budgeter::getCurrentIncome() {
	return Budgeter::currentIncome;
}
// Update current income
void Budgeter::updateCurrentIncome(double newIncome) {
	Budgeter::currentIncome = newIncome;
}

// ====================
// BUDGET MANIPULATORS
// ====================
// Show current budget aka income - expenses
void Budgeter::currentBudget() {
	double balance = getCurrBalance();
	double expenseTotal = getTotalExpense();
	double incomeTotal = getCurrentIncome();
	double bufferCash;

	bufferCash = incomeTotal - expenseTotal;
	if (bufferCash < 0) {
		cout << "You are losing $" << bufferCash << " per month." << endl;
	}
	else {
		cout << "You are gaining $" << bufferCash << " per month." << endl;
	}

	balance += bufferCash;
	cout << "Your new balance will be $" << balance << endl;
}
// Show future balance and comparison to current balance
void Budgeter::forecast(int month) {
	double origBal = getCurrBalance();
	double balance;
	double expenseTotal = getTotalExpense();
	double incomeTotal = getCurrentIncome();
	double bufferCash;
	int i = 0;

	balance = origBal;
	bufferCash = incomeTotal - expenseTotal;

	while (i < month) {
		balance += bufferCash;
		++i;
	}
	cout << "Start Balance: $" << origBal << "		Balance after " << month << " months: $" << balance << endl << endl;

	if (balance > origBal) {
		cout << "You gained $" << (balance - origBal) << " over " << month << " months" << endl;
	}
	else {
		cout << "You lost $" << (balance - origBal) << " over " << month << " months" << endl;
	}
}

// ====================
// MENUS
// ====================
int Budgeter::mainMenu() {
	int i;
	int choice;

	for (i = 0; i < 39; ++i) {
		cout << endl;
	}
	cout << endl << endl << "|   MONTHLY BUDGET MENU    |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "=";
	}
	cout << endl << "1 | Balance Options        |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "-";
	}
	cout << endl << "2 | Expense Options        |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "-";
	}
	cout << endl << "3 | Income Options         |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "-";
	}
	cout << endl << "4 | Budget Options         |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "-";
	}
	cout << endl << "5 | Quit                   |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "-";
	}
	
	cout << endl << "Enter Menu Selection(1-5): ";
	choice = inputCheck5();

	if (choice == 1) {
		balanceMenu();
		return 1;
	}
	else if (choice == 2) {
		expenseMenu();
		return 2;
	}
	else if (choice == 3) {
		incomeMenu();
		return 3;
	}
	else if (choice == 4) {
		budgetMenu();
		return 4;
	}
	else if (choice == 5) {
		return 5;
	}
}
void Budgeter::balanceMenu() {
	int i;
	int balChoice;
	double currBalance;

	for (i = 0; i < 39; ++i) {
		cout << endl;
	}
	cout << "|       BALANCE MENU       |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "=";
	}
	cout << "\n1 | Update Balance         |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "-";
	}
	cout << "\n2 | Show Current Balance   |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "-";
	}
	cout << "\n3 | Return to Main Menu    |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "-";
	}
	
	cout << "\n\nEnter a menu selection: ";
	balChoice = inputCheck3();
	if (balChoice == 1) {
		double newBalance;

		cout << endl;
		cout << "Enter the new balance: ";
		cin >> newBalance;
		updateCurrBal(newBalance);
	}
	else if (balChoice == 2) {
		cout << endl;
		currBalance = getCurrBalance();
		cout << "Current Balance: " << currBalance << endl;
	}
	else if (balChoice == 3) {
		cout << "\n\nRETURNING TO MAIN MENU\n\n";
	}
	
	backToMain();
}
void Budgeter::expenseMenu() {
	int i;
	int exChoice;
	double totalExp;
	string expenseName = "UNKNOWN";
	double expenseAmount = 0.00;

	for (i = 0; i < 39; ++i) {
		cout << endl;
	}
	cout << "|      EXPENSE MENU        |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "=";
	}
	cout << "\n1 | Add New Expense        |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "-";
	}
	cout << "\n2 | Update an Expense Item |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "-";
	}
	cout << "\n3 | Show All Expenses      |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "-";
	}
	cout << "\n4 | Total Expense Amount   |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "-";
	}
	cout << "\n5 | Return to Main Menu    |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "-";
	}

	cout << "\n\nEnter a menu selection: ";
	exChoice = inputCheck5();
	if (exChoice == 1) {
		cout << "\nEnter a new expense to add: ";
		cin >> expenseName;

		cout << "\nEnter the $ amount of the expense: ";
		cin >> expenseAmount;

		addExpense(expenseName, expenseAmount);
	}
	else if (exChoice == 2) {
		cout << endl;
		updateExpense();
	}
	else if (exChoice == 3) {
		cout << endl;
		getAllExpenses();
	}
	else if (exChoice == 4) {
		cout << endl;
		totalExp = getTotalExpense();
		cout << "Total Expenses: $" << totalExp << endl;
	}
	else if (exChoice == 5) {
		cout << "\n\nRETURNING TO MAIN MENU\n\n";
	}

	backToMain();
}
void Budgeter::incomeMenu() {
	int i;
	int inChoice;

	for (i = 0; i < 39; ++i) {
		cout << endl;
	}
	cout << endl << endl << "|       INCOME MENU        |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "=";
	}
	cout << "\n1 | Update Income          |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "-";
	}
	cout << "\n2 | Check Current Income   |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "-";
	}
	cout << "\n3 | Return to Main Menu    |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "-";
	}

	cout << "\n\nEnter a menu selection: ";
	inChoice = inputCheck3();
	if (inChoice == 1) {
		double newIncome;

		cout << endl;
		cout << "Enter the new balance: ";
		cin >> newIncome;
		updateCurrentIncome(newIncome);
	}
	else if (inChoice == 2) {
		cout << endl;
		cout << "Current Balance: " << getCurrentIncome() << endl;
	}
	else if (inChoice == 3) {
		cout << "\n\nRETURNING TO MAIN MENU\n\n";
	}

	backToMain();
}
void Budgeter::budgetMenu() {
	int i;
	int buChoice;

	for (i = 0; i < 39; ++i) {
		cout << endl;
	}
	cout << endl << endl << "|       BUDGET MENU        |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "=";
	}
	cout << "\n1 | Show Current Budget    |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "=";
	}
	cout << "\n2 | Forecast               |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "=";
	}
	cout << "\n3 | Return to Main Menu    |" << endl;
	for (i = 0; i < 28; ++i) {
		cout << "=";
	}
	
	cout << "\nEnter a menu selection: ";
	buChoice = inputCheck3();
	if (buChoice == 1) {
		cout << endl;
		currentBudget();
	}
	else if (buChoice == 2) {
		int months;

		cout << endl << "Enter number of months to forecast: ";
		cin >> months;
		forecast(months);
	}

	backToMain();
}
