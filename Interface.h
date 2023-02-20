/*
Interface Class defined as a way to describe the behavior of a class Cards by Aggregate
Which in turn contain a binary search tree And Inherit from Wallet
containing dates and expenses on certain dates, also the interface class contains methods
for finding Dates and writing Spendings to a Cards, Wallets and Files.
*/

#ifndef INTERFACE_H
#define INTERFACE_H
#include "Card.h"
#include "Wallet.h"

// Class Interface 
class Interface : public OnlineWallet, public PhysicalWallet
{
public:

	// Default Constructor
	Interface()
	{
		std::string BankValue;
		std::cout << "Welcome to Finance File System\n";
		std::cout << "Enter Your Bank Name: ";
		std::getline(std::cin, BankValue);
		int choice;
		std::cout << "\nDo you want a Credit or Debit card?\n";
		std::cout << "1. Credit Card\n2. Debit Card\n";
		std::cin >> choice;
		if (choice == 1) {
			std::cout << "Enter your credit limit: $";
			int limit;
			std::cin >> limit;
			Card* card = new CreditCard(BankValue, limit);
			cards.push_back(card);
		}
		else if (choice == 2) {
			Card* card = new DebitCard(BankValue, 0);
			cards.push_back(card);
		}
		else {
			std::cout << "Invalid choice.\n";
		}
	}

	// Main Loop
	void Start()
	{
		while (1)
		{
			system("cls");
			int UserChoice;
			std::cout << "1. Write Spendings";
			std::cout << "\n2. Show All Cards";
			std::cout << "\n3. Day Spendings";
			std::cout << "\n4. Month Spendings";
			std::cout << "\n5. Week Spendings";
			std::cout << "\n6. Week TOP - 3 Spendings";
			std::cout << "\n7. Month TOP - 3 Spendings";
			std::cout << "\n8. Week TOP - 3 Category Spendings";
			std::cout << "\n9. Month TOP - 3 Category Spendings";
			std::cout << "\n10. Write To File";
			std::cout << "\n11. Read From File";
			std::cout << "\n12. Add Card To Wallet";
			std::cout << "\n13. Show Cards In Wallet\n";
			cin >> UserChoice;
			switch (UserChoice)
			{
			case 1:
			{
				std::cout << "Enter Index:\n";
				int value = 0;
				std::cin >> value;
				std::cout << "Enter Value:\n";
				int values = 0;
				std::cin >> values;
				addSpending(value, values);
				system("pause");
				break;
			}
			case 2:
			{
				printAllCards();
				system("pause");
				break;
			}
			case 3:
			{
				std::cout << "Enter Index:\n";
				int value = 0;
				std::cin >> value;
				SpendingsByDayReport(value);
				system("pause");
				break;
			}
			case 4:
			{
				std::cout << "Enter Index:\n";
				int value = 0;
				std::cin >> value;
				SpendingsByMonthReport(value);
				system("pause");
				break;
			}
			case 5:
			{
				std::cout << "Enter Index:\n";
				int value = 0;
				std::cin >> value;
				SpendingsByWeek(value);
				system("pause");
				break;
			}
			case 6:
			{
				std::cout << "Enter Index:\n";
				int value = 0;
				std::cin >> value;
				TopThreeByWeek(value);
				system("pause");
				break;
			}
			case 7:
			{
				std::cout << "Enter Index:\n";
				int value = 0;
				std::cin >> value;
				TopThreeByMonth(value);
				system("pause");
				break;
			}
			case 8:
			{
				std::cout << "Enter Index:\n";
				int value = 0;
				std::cin >> value;
				TopThreeByWeekCategory(value);
				system("pause");
				break;
			}
			case 9:
			{
				std::cout << "Enter Index:\n";
				int value = 0;
				std::cin >> value;
				TopThreeByMonthCategory(value);
				system("pause");
				break;
			}
			case 10:
			{
				std::cout << "Enter Index:\n";
				int value = 0;
				std::cin >> value;
				WriteToFile(value);
				system("pause");
				break;
			}
			case 11:
			{
				std::cout << "Enter Index:\n";
				int value = 0;
				std::cin >> value;
				ReadFromFile(value);
				system("pause");
				break;
			}
			case 12:
			{
				std::cout << "Enter Index:\n";
				int value = 0;
				std::cin >> value;
				AddCardToWallet(value);
				system("pause");
				break;
			}
			case 13:
			{
				ShowCardInWallet();
				system("pause");
				break;
			}
			}
		}
	}

	// Create Card From Bank Name and Limit Value
	void CreateCard(std::string BankValue, int LimitValue)
	{
		Card temp(BankValue, LimitValue);
		std::vector<Card*> cards;
		cards.push_back(&temp);
	}

	// Print All Wallets 
	void printAllWallets()
	{
		cout << "All Wallets" << endl;
		OnlineWallet::printCards();
		PhysicalWallet::printCards();
	}

	// Print All Cards
	void printAllCards()
	{
		std::cout << "All Cards:\n";
		for (Card* card : cards) {
			card->print();
		}
	}

	// Add Spending to Card
	void addSpending(int cardIndex, int amount)
	{
		if (cardIndex < 0 || cardIndex >= cards.size())
		{
			std::cout << "Invalid card index.\n";
		}
		else {
			cards[cardIndex]->AddData(amount);
		}
	}

	// A certain Spending in a Day
	void SpendingsByDayReport(int cardIndex)
	{
		if (cardIndex < 0 || cardIndex >= cards.size())
		{
			std::cout << "Invalid card index.\n";
		}
		else {
			cards[cardIndex]->SpendingsByDayReportCard();
		}
	}

	// A certain Spending in a Month
	void SpendingsByMonthReport(int cardIndex)
	{
		if (cardIndex < 0 || cardIndex >= cards.size())
		{
			std::cout << "Invalid card index.\n";
		}
		else {
			cards[cardIndex]->SpendingsByMonthReportCard();
		}
	}

	// A certain Spending in a Week
	void SpendingsByWeek(int cardIndex)
	{
		if (cardIndex < 0 || cardIndex >= cards.size())
		{
			std::cout << "Invalid card index.\n";
		}
		else
		{
			cards[cardIndex]->SpendingsByWeekReportCard();
		}
	}

	// Top Three Spendings at certain Week
	void TopThreeByWeek(int cardIndex)
	{
		if (cardIndex < 0 || cardIndex >= cards.size())
		{
			std::cout << "Invalid card index.\n";
		}
		else
		{
			cards[cardIndex]->TopThreeByWeekCard();
		}
	}

	// Top Three Spendings at certain Month
	void TopThreeByMonth(int cardIndex)
	{
		if (cardIndex < 0 || cardIndex >= cards.size())
		{
			std::cout << "Invalid card index.\n";
		}
		else
		{
			cards[cardIndex]->TopThreeByMonthCard();
		}
	}

	// Top Three Spendings by Category at certain Week 
	void TopThreeByWeekCategory(int cardIndex)
	{
		if (cardIndex < 0 || cardIndex >= cards.size())
		{
			std::cout << "Invalid card index.\n";
		}
		else
		{
			cards[cardIndex]->TopThreeByWeekCategory();
		}
	}

	// Top Three Spendings by Category at certain Month 
	void TopThreeByMonthCategory(int cardIndex)
	{
		if (cardIndex < 0 || cardIndex >= cards.size())
		{
			std::cout << "Invalid card index.\n";
		}
		else
		{
			cards[cardIndex]->TopThreeByMonthCategory();
		}
	}

	// Write Spendings to File 
	void WriteToFile(int cardIndex)
	{
		if (cardIndex < 0 || cardIndex >= cards.size())
		{
			std::cout << "Invalid card index.\n";
		}
		else
		{
			cards[cardIndex]->WriteToFileCard();
		}
	}

	// Read Spendings from File
	void ReadFromFile(int cardIndex)
	{
		if (cardIndex < 0 || cardIndex >= cards.size())
		{
			std::cout << "Invalid card index.\n";
		}
		else
		{
			cards[cardIndex]->ReadFromFileCard();
		}
	}

	// Add Card To Wallet
	void AddCardToWallet(int cardIndex)
	{
		if (cardIndex < 0 || cardIndex >= cards.size())
		{
			std::cout << "Invalid card index.\n";
		}
		else
		{
			Wallet::addCard(cards[cardIndex]);
		}
	}

	// Show Cards at certain Wallet
	void ShowCardInWallet()
	{
		Wallet::printCards();
	}

	// Destructor
	~Interface()
	{

	}

private:
	std::vector<Card*> cards;
};
#endif