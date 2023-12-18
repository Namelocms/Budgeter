#ifndef PRACTICEPROBLEMS_REPOS_PP_H_
#define PRACTICEPROBLEMS_REPOS_PP_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Budgeter {
public:
	// Initialization
	bool initBalance();
	bool initExpences();
	bool initIncome();

	// Menus
	int mainMenu();
	void balanceMenu();
	void expenseMenu();
	void incomeMenu();
	void budgetMenu();
	void backToMain();

	// Balance manipulation
	void updateCurrBal(double newBalance);
	double getCurrBalance();
	void setCurrentBalance(double balance);

	// Expense manipulation
	void getAllExpenses();
	void addExpense(string exp, double amt);
	void updateExpense();
	double getTotalExpense();

	// Income manipulation
	double getCurrentIncome();
	void updateCurrentIncome(double newIncome);

	// Budget manipulation
	void currentBudget();
	void forecast(int month);

	// Input Validation
	int inputCheck5();
	int inputCheck3();

private:
	vector<string> monthlyExpenses;
	double currentIncome;
	double currentBalance;
};
#endif