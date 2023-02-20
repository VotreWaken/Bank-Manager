#ifndef TNODE_H
#define TNODE_H
// Structure "Tree Node" 
#include "Spending.h"
#include "Time.h"
#include <vector>
#include "Date.h"
struct Tnode
{
	// Constructor by parameters
	Tnode(int k, Tnode* p = nullptr) : key(k), left(nullptr), right(nullptr), parent(p) {}
	// Constructor by parameters
	Tnode(Time k, int w, Tnode* p = nullptr) : key(w), left(nullptr), right(nullptr), parent(p)
	{
		std::cout << "Enter Category: \n";
		std::string BankValues;
		getline(std::cin, BankValues);
		Spending temp(BankValues, w, k);
		temp.name = BankValues;
		stratifications.push_back(temp);
	}

	Tnode(Date k, int w, Time p) : key(w), left(nullptr), right(nullptr), parent(nullptr)
	{
		dateSpending_ = k;
	}

	Tnode(Date k, int w, Tnode* p = nullptr) : key(w), left(nullptr), right(nullptr), parent(p)
	{
		std::cout << "Enter Category: \n";
		std::string BankValues;
		getline(std::cin, BankValues);
		Spending temp(BankValues, w);
		temp.name = BankValues;
		dateSpending_ = k;
		std::cout << "What Time do you want to Use? \n";
		std::cout << "1. Write Specific Time \n";
		std::cout << "0. Current: \n";
		Time CurTime;
		int userChoice;
		std::cin >> userChoice;
		if (userChoice)
		{
			std::cout << "Enter Seconds: \n";
			int Seconds;
			std::cin >> Seconds;
			CurTime.SetSeconds(Seconds);
			std::cout << "Enter Minutes: \n";
			int Minutes;
			std::cin >> Minutes;
			CurTime.SetMinutes(Minutes);
			std::cout << "Enter Hours: \n";
			int Hours;
			std::cin >> Hours;
			CurTime.SetHours(Hours);
		}
		temp.CurTime = CurTime;
		stratifications.push_back(temp);
	}
	// Constructor by parameters
	Tnode(Spending temp, Tnode* p = nullptr) : left(nullptr), right(nullptr), parent(p)
	{
		std::cout << "Enter Category: \n";
		std::string BankValues;
		getline(std::cin, BankValues);
		Spending temps(BankValues, temp.cost, temp.CurTime);
		temps.name = BankValues;
		key = temp.cost;
		stratifications.push_back(temps);
	}
	// Node Key
	int key;
	// Category
	// Pointers to Left, Right, And Parent 
	Tnode* left, * right, * parent;
	// Date Key
	std::vector<Spending> stratifications;
	Date dateSpending_;
	// Overload Operator "<<" To Display Node Fields 
	friend ostream& operator<< (std::ostream& out, const Tnode& TnodeValue);
	// Default Constructor
	Tnode() : Tnode(0)
	{

	}
};
#endif