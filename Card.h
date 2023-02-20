/*
The card class contains a binary search tree for saving expenses on certain dates,
it also contains the fields of the bank name, and the credit limit. Also presented
are the Debut Card and Credit Card classes that are inherited from the Base class
*/
#ifndef CARD_H
#define CARD_H
#include "Tree.h"

// Base class for cards
class Card
{
protected:
	tree SpendingData;
	std::string BankName;
	bool CreditLimit;

public:
	// Constructor By Parametres
	Card(std::string& Name, int LimitValue)
	{
		BankName = Name;
		CreditLimit = LimitValue;
		SpendingData;
	}

	// Add Spendings to Binary Search Tree
	void AddData(int value)
	{
		Tnode temp;
		int Day;
		std::cout << "Enter Day: \n";
		std::cin >> Day;
		temp.dateSpending_.SetDay(Day);
		std::cout << "Enter Month: \n";
		int Month;
		std::cin >> Month;
		temp.dateSpending_.SetMonth(Month);
		std::cout << "Enter Year: \n";
		int Year;
		std::cin >> Year;
		temp.dateSpending_.SetYear(Year);
		cin.ignore();
		temp.key = value;
		SpendingData += temp;
	}

	// A certain Spending in a Day
	void SpendingsByDayReportCard()
	{
		std::cout << "Enter Day: \n";
		int Day = 0;
		std::cin >> Day;
		std::cout << "Enter Month: \n";
		int Month = 0;
		std::cin >> Month;
		std::cout << "Enter Year: \n";
		int Year = 0;
		std::cin >> Year;
		SpendingData.searchDay(SpendingData.root, Day, Month, Year);
	}

	// A certain Spending in a Month
	void SpendingsByMonthReportCard()
	{
		std::cout << "Enter Month: \n";
		int Month = 0;
		std::cin >> Month;
		std::cout << "Enter Year: \n";
		int Year = 0;
		std::cin >> Year;
		SpendingData.search(SpendingData.root, Month, Year);
	}

	// A certain Spending in a Week
	void SpendingsByWeekReportCard()
	{
		std::cout << "Enter Year: \n";
		int Year = 0;
		std::cin >> Year;
		std::cout << "Enter Month: \n";
		int Month = 0;
		std::cin >> Month;
		std::cout << "Enter Week: \n";
		int Week = 0;
		std::cin >> Week;
		SpendingData.searchByWeek(SpendingData.root, Year, Month, Week);
	}

	// Top Three Spendings at certain Week
	void TopThreeByWeekCard()
	{
		std::cout << "Enter Year: \n";
		int Year = 0;
		std::cin >> Year;
		std::cout << "Enter Month: \n";
		int Month = 0;
		std::cin >> Month;
		std::cout << "Enter Week: \n";
		int Week = 0;
		std::cin >> Week;
		SpendingData.searchByWeeks(SpendingData.root, Year, Month, Week);
	}

	// Top Three Spendings at certain Month
	void TopThreeByMonthCard()
	{
		std::cout << "Enter Year: \n";
		int Year = 0;
		std::cin >> Year;
		std::cout << "Enter Month: \n";
		int Month = 0;
		std::cin >> Month;
		SpendingData.searchByMonth(SpendingData.root, Year, Month);
	}

	// Top Three Spendings by Category at certain Week 
	void TopThreeByWeekCategory()
	{
		std::cout << "Enter Year: \n";
		int Year = 0;
		std::cin >> Year;
		std::cout << "Enter Month: \n";
		int Month = 0;
		std::cin >> Month;
		std::cout << "Enter Week: \n";
		int Week = 0;
		std::cin >> Week;
		SpendingData.searchByWeekCategory(SpendingData.root, Year, Month, Week);
	}

	// Top Three Spendings by Category at certain Month 
	void TopThreeByMonthCategory()
	{
		std::cout << "Enter Year: \n";
		int Year = 0;
		std::cin >> Year;
		std::cout << "Enter Month: \n";
		int Month = 0;
		std::cin >> Month;
		SpendingData.searchByMonthCategory(SpendingData.root, Year, Month);
	}

	// Write Spendings to File 
	void WriteToFileCard()
	{
		std::ofstream file("tree.txt", std::ios::binary);
		if (!file.is_open())
		{
			std::cerr << "Error opening file for writing.\n";
			return;
		}
		SpendingData.writeToFile("tree.txt", SpendingData.root);
		file.close();
	}

	// Read Spendings from File
	void ReadFromFileCard()
	{
		SpendingData.readFromFile(SpendingData, "tree.txt");
		std::cout << SpendingData;
	}

	// Print Card Fields
	virtual void print()
	{
		cout << "Bank Name: " << BankName << endl;
		cout << "Credit Limit: " << CreditLimit << endl;
		std::cout << SpendingData;
	}
};

// Derived class for debit cards
class DebitCard : public Card
{
protected:

public:

	// Constructor
	DebitCard(std::string& Name, int LimitValue) : Card(Name, LimitValue)
	{

	}
	// Display Card To Screen
	virtual void print()
	{
		cout << "Debit Card Details" << endl;
		Card::print();
	}
};

// Derived class for credit cards
class CreditCard : public Card {
protected:
	int credit_limit;

public:
	// Constructor
	CreditCard(std::string& Name, int LimitValue) : Card(Name, LimitValue)
	{
		credit_limit = 0;
	}

	// Display Card To Screen
	virtual void print()
	{
		cout << "Credit Card Details" << endl;
		Card::print();
		cout << "Credit Limit: $" << credit_limit << endl;
	}
};
#endif
