// Class Tree
// Contains the structure of the node, methods for searching by date elements,
// methods implemented thanks to a recursive traversal of all its elements
#ifndef TREE_H
#define TREE_H
#include <iostream>
#include "Date.h"
#include "Time.h"
#include "Spending.h"
#include "Tnode.h"
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
#include <unordered_map>
#include <fstream>
#include <sstream>
using namespace std;



// Class Tree
class tree
{
public:
	tree() { root = 0; }
	~tree() { del_tree(root); }
	Tnode* root;

	tree& operator+=(Tnode& k)
	{
		Tnode* existing_node = find_elem(root, k.dateSpending_);

		if (existing_node == nullptr)
		{
			root = addsearch(root, &k);
		}
		else
		{
			// Node with same date as k already exists, update its key
			existing_node->key += k.key;
			std::cout << "Enter Category: \n";
			std::string BankValues;
			getline(std::cin, BankValues);
			Spending temp(BankValues, k.key);
			existing_node->stratifications.push_back(temp);
		}

		return *this;
	}

	constexpr Tnode* find_elem(Tnode* n, Date& d) const
	{
		if (n == nullptr || n->dateSpending_ == d)
		{
			return n;
		}

		if (d < n->dateSpending_)
		{
			return find_elem(n->left, d);
		}
		else
		{
			return find_elem(n->right, d);
		}
	}

	constexpr Tnode* addsearch(Tnode* c, Tnode* p) const
	{
		if (c == nullptr)
		{
			c = new Tnode(p->dateSpending_, p->key);
			c->key = p->key;
			c->parent = p;
		}
		else if (p->dateSpending_ < c->dateSpending_)
		{
			c->left = addsearch(c->left, p);
		}
		else if (p->dateSpending_ > c->dateSpending_)
		{
			c->right = addsearch(c->right, p);
		}

		return c;
	}

	// Search Spendings in Day
	constexpr void searchDay(Tnode* root, int day, int month, int year) const
	{
		if (root != nullptr)
		{
			if (root->dateSpending_.GetDay() == day && root->dateSpending_.GetMonth() == month && root->dateSpending_.GetYear() == year)
			{
				cout << "Date: " << root->dateSpending_.GetDay() << "/" << root->dateSpending_.GetMonth() << "/" << root->dateSpending_.GetYear() << " Key: " << root->key << endl;
				for (auto& s : root->stratifications)
				{
					cout << s.getName() << "   Time: " << s.getDate() << "   Value: " << s.getCost() << endl;
				}
			}
			searchDay(root->left, day, month, year);
			searchDay(root->right, day, month, year);
		}
	}

	// TOP CATEGORIES BY WEEK
	void searchByWeekCategory(Tnode* root, int year, int month, int week) const
	{
		std::unordered_map<std::string, double> weekSpendings; // map to store total spendings for each category in the week

		// recursive function to traverse the tree and calculate total spendings for each category	in the week
		std::function<void(Tnode*, int, int, int)> traverse = [&](Tnode* node, int year, int month, int week) {
			if (node != nullptr) {
				int nodeYear = node->dateSpending_.GetYear();
				int nodeMonth = node->dateSpending_.GetMonth();
				int nodeWeek = (node->dateSpending_.GetDay() - 1) / 7 + 1;

				if (nodeYear == year && nodeMonth == month && nodeWeek == week) {
					for (const auto& strat : node->stratifications) {
						std::string category = strat.getName();
						double cost = strat.getCost();
						weekSpendings[category] += cost;
					}
				}

				traverse(node->left, year, month, week);
				traverse(node->right, year, month, week);
			}
		};

		traverse(root, year, month, week);

		// create a vector of pairs with category name and total spending
		std::vector<std::pair<std::string, double>> weekSpendingsVec;
		for (const auto& item : weekSpendings) {
			weekSpendingsVec.emplace_back(item);
		}

		// sort categories by total spendings in descending order
		std::sort(weekSpendingsVec.begin(), weekSpendingsVec.end(), [](const auto& a, const auto& b) {
			return a.second > b.second;
			});

		// print top 3 categories
		std::cout << "Top 3 categories of spending in week " << week << " of month " << month << " in year " << year << ":\n";
		for (int i = 0; i < std::min(3, static_cast<int>(weekSpendingsVec.size())); i++) {
			auto& categorySpending = weekSpendingsVec[i];
			std::cout << categorySpending.first << ": " << categorySpending.second << std::endl;

			// check if there are other categories with the same total spending
			double currentSpending = categorySpending.second;
			int j = i + 1;
			while (j < weekSpendingsVec.size() && weekSpendingsVec[j].second == currentSpending) {
				std::cout << "  " << weekSpendingsVec[j].first << std::endl;
				categorySpending.second += weekSpendingsVec[j].second;
				j++;
			}
			i = j - 1;
		}
	}

	// Top CATEGORIES BY MONTH
	void searchByMonthCategory(Tnode* root, int year, int month) const
	{
		std::unordered_map<std::string, double> monthSpendings; // map to store total spendings for each category in the month

		// recursive function to traverse the tree and calculate total spendings for each category in the month
		std::function<void(Tnode*, int, int)> traverse = [&](Tnode* node, int year, int month) {
			if (node != nullptr) {
				int nodeYear = node->dateSpending_.GetYear();
				int nodeMonth = node->dateSpending_.GetMonth();

				if (nodeYear == year && nodeMonth == month) {
					for (const auto& strat : node->stratifications) {
						std::string category = strat.getName();
						double cost = strat.getCost();
						monthSpendings[category] += cost;
					}
				}

				traverse(node->left, year, month);
				traverse(node->right, year, month);
			}
		};

		traverse(root, year, month);

		// create a vector of pairs with category name and total spending
		std::vector<std::pair<std::string, double>> monthSpendingsVec;
		for (const auto& item : monthSpendings) {
			monthSpendingsVec.emplace_back(item);
		}

		// sort categories by total spendings in descending order
		std::sort(monthSpendingsVec.begin(), monthSpendingsVec.end(), [](const auto& a, const auto& b) {
			return a.second > b.second;
			});

		// print top 3 categories
		std::cout << "Top 3 categories of spending in month " << month << " and year " << year << ":\n";
		for (int i = 0; i < std::min(3, static_cast<int>(monthSpendingsVec.size())); i++) {
			auto& categorySpending = monthSpendingsVec[i];
			std::cout << categorySpending.first << ": " << categorySpending.second << std::endl;

			// check if there are other categories with the same total spending
			double currentSpending = categorySpending.second;
			int j = i + 1;
			while (j < monthSpendingsVec.size() && monthSpendingsVec[j].second == currentSpending) {
				std::cout << "  " << monthSpendingsVec[j].first << std::endl;
				categorySpending.second += monthSpendingsVec[j].second;
				j++;
			}
			i = j - 1;
		}
	}

	// TOP 3 by week Done
	void searchByWeeks(Tnode* root, int year, int month, int week) const
	{
		std::vector<std::pair<std::string, double>> weekSpendings; // vector to store total spendings for each week

		// recursive function to traverse the tree and calculate total spendings for each week
		std::function<void(Tnode*, int, int, int)> traverse = [&](Tnode* node, int year, int month, int week) {
			if (node != nullptr) {
				int nodeYear = node->dateSpending_.GetYear();
				int nodeMonth = node->dateSpending_.GetMonth();
				int nodeWeek = (node->dateSpending_.GetDay() - 1) / 7 + 1;

				if (nodeYear == year && nodeMonth == month && nodeWeek == week) {
					std::vector<std::pair<std::string, double>> stratSpendings;
					for (const auto& strat : node->stratifications) {
						stratSpendings.emplace_back(strat.getName(), strat.getCost());
					}
					std::string dateStr = "Week " + std::to_string(nodeWeek) + " of month " + std::to_string(nodeMonth) + " in " + std::to_string(nodeYear);
					for (const auto& stratSpending : stratSpendings) {
						weekSpendings.emplace_back(dateStr + " - " + stratSpending.first, stratSpending.second);
					}
				}

				traverse(node->left, year, month, week);
				traverse(node->right, year, month, week);
			}
		};

		traverse(root, year, month, week);

		// sort weeks by total spendings in descending order
		std::sort(weekSpendings.begin(), weekSpendings.end(), [](const auto& a, const auto& b) {
			return a.second > b.second;
			});

		// print top 3 spendings
		std::cout << "Top 3 spendings for week " << week << " of month " << month << " in " << year << ":\n";
		for (int i = 0; i < std::min(3, static_cast<int>(weekSpendings.size())); i++) {
			auto& weekSpending = weekSpendings[i];
			std::cout << weekSpending.first << ": " << weekSpending.second << std::endl;
		}
	}

	// Search Spendings in Week
	constexpr void searchByWeek(Tnode* root, int year, int month, int week) const
	{
		if (root != NULL) {
			int rootYear = root->dateSpending_.GetYear();
			int rootMonth = root->dateSpending_.GetMonth();
			if (rootYear == year && rootMonth == month) {
				int dayOfWeek = (root->dateSpending_.GetDay() - 1) % 7;
				int currentWeek = (root->dateSpending_.GetDay() - dayOfWeek + 6) / 7;

				if (currentWeek == week) {
					for (const auto& stratification : root->stratifications) {
						cout << root->dateSpending_.GetDay() << "." << rootMonth << "." << rootYear << " " << stratification.name << " " << stratification.cost << endl;
					}
				}
			}
			searchByWeek(root->left, year, month, week);
			searchByWeek(root->right, year, month, week);
		}
	}

	// TOP 3 IN MONTH
	// Define a function to find the maximum cost in a given month
	void searchByMonth(Tnode* root, int year, int month) const
	{
		std::vector<std::pair<std::string, double>> monthSpendings; // vector to store spendings for each day in the month

		// recursive function to traverse the tree and calculate spendings for each day in the month
		std::function<void(Tnode*, int, int)> traverse = [&](Tnode* node, int year, int month) {
			if (node != nullptr) {
				int nodeYear = node->dateSpending_.GetYear();
				int nodeMonth = node->dateSpending_.GetMonth();
				int nodeDay = node->dateSpending_.GetDay();

				if (nodeYear == year && nodeMonth == month) {
					std::vector<std::pair<std::string, double>> stratSpendings;
					for (const auto& strat : node->stratifications) {
						stratSpendings.emplace_back(strat.getName(), strat.getCost());
					}
					std::string dateStr = std::to_string(nodeDay) + "/" + std::to_string(nodeMonth) + "/" + std::to_string(nodeYear);
					for (const auto& stratSpending : stratSpendings) {
						monthSpendings.emplace_back(dateStr + " - " + stratSpending.first, stratSpending.second);
					}
				}

				traverse(node->left, year, month);
				traverse(node->right, year, month);
			}
		};

		traverse(root, year, month);

		// sort spendings by cost in descending order
		std::sort(monthSpendings.begin(), monthSpendings.end(), [](const auto& a, const auto& b) {
			return a.second > b.second;
			});

		// print spendings
		std::cout << "Spendings for month " << month << " of year " << year << ":\n";
		for (const auto& daySpending : monthSpendings) {
			std::cout << daySpending.first << ": " << daySpending.second << std::endl;
		}
	}

	// Helper function to recursively collect all spending categories for a given month
	constexpr void collectCosts(Tnode* node, std::vector<Spending>& allCosts, int month) const
	{
		if (node == nullptr) {
			return;
		}

		if (node->dateSpending_.GetMonth() == month) {
			for (const auto& cost : node->stratifications) {
				allCosts.push_back(cost);
			}
		}

		collectCosts(node->left, allCosts, month);
		collectCosts(node->right, allCosts, month);
	}

	// Search Spendings in Month and Year
	constexpr void search(Tnode* root, int month, int year) const
	{
		if (root != nullptr)
		{
			if (root->dateSpending_.GetMonth() == month && root->dateSpending_.GetYear() == year)
			{
				cout << root->dateSpending_.GetDay() << "/" << root->dateSpending_.GetMonth() << "/" << root->dateSpending_.GetYear() << " Key: " << root->key << endl;
				for (auto& s : root->stratifications)
				{
					cout << s.getName() << "   Time: " << s.getDate() << "   Value: " << s.getCost() << endl;
				}
			}
			search(root->left, month, year);
			search(root->right, month, year);
		}
	}

	// Destructor To Tree
	constexpr void del_tree(Tnode* n)
	{
		if (n != NULL)
		{
			del_tree(n->left);
			del_tree(n->right);
			delete n;
		}
		n = 0;
	}

	// Read From File
	void readFromFile(tree& t, const std::string& filename)
	{
		std::ifstream file(filename);
		if (!file)
		{
			std::cerr << "Error: could not open file " << filename << '\n';
			return;
		}

		std::string line;
		std::vector<Spending> spendings;
		Date date(0, "", 0); // default date
		int total = 0;
		while (std::getline(file, line))
		{
			if (line.empty()) continue; // skip empty lines
			if (line.find("Date: ") == 0)
			{
				// Store previous node, if any
				if (!spendings.empty())
				{
					Tnode node(date, total, Time(0, 0, 0));
					node.stratifications = spendings;
					insertNode(node, t.root);
					spendings.clear();
				}

				// Read date
				std::istringstream iss(line);
				std::string dateStr;
				int day, year;
				std::string monthStr;
				char Point;
				iss >> dateStr >> day >> Point >> year >> monthStr;
				if (dateStr != "Date:" || iss.fail())
				{
					std::cerr << "Error: could not read date from line: " << line << '\n';
					continue;
				}
				date = Date(day, monthStr, year);

				// Read total
				std::getline(file, line);
				std::istringstream totals(line);
				std::string totalStr;
				totals >> totalStr >> total;
				if (totalStr != "Total:" || totals.fail())
				{
					std::cerr << "Error: could not read total from line: " << line << '\n';
					continue;
				}
			}
			else
			{
				// Read stratification
				std::istringstream stratIss(line);
				std::string stratName;
				int stratCost, stratHour, stratMinute, stratSecond;
				char stratColumn1, stratColumn2;
				stratIss >> stratName >> stratCost >> stratHour >> stratColumn1 >> stratMinute >> stratColumn2 >> stratSecond;
				stratName.pop_back();
				if (stratIss.fail()) {
					std::cerr << "Error: could not read stratification from line: " << line << '\n';
					continue;
				}
				Time stratTime(stratHour, stratMinute, stratSecond);
				spendings.push_back(Spending(stratName, stratCost, stratTime));
			}
		}

		// Store last node, if any
		if (!spendings.empty())
		{
			Tnode node(date, total, Time(0, 0, 0));
			node.stratifications = spendings;
			insertNode(node, t.root);
			spendings.clear();
		}
	}

	void insertNode(Tnode& node, Tnode*& root)
	{
		if (root == nullptr)
		{
			root = new Tnode(node);
		}
		else if (node.dateSpending_ < root->dateSpending_)
		{
			insertNode(node, root->left);
		}
		else if (node.dateSpending_ > root->dateSpending_)
		{
			insertNode(node, root->right);
		}
		else
		{
			for (const auto& stratification : node.stratifications)
			{
				root->stratifications.push_back(stratification);
			}
		}
	}

	// Write To File
	void writeToFile(const std::string& filename, Tnode* node)
	{
		std::ofstream file(filename);
		if (!file.is_open())
		{
			std::cerr << "Failed to open file " << filename << std::endl;
			return;
		}

		// Traverse the tree and write each node's information to the file
		if (node != nullptr)
		{
			writeToFileHelper(file, node);
		}

		file.close();
	}

	void writeToFileHelper(std::ofstream& file, Tnode* node)
	{
		if (node->left != nullptr)
		{
			writeToFileHelper(file, node->left);
		}

		file << node->dateSpending_ << "Total: " << node->key << "\n";
		for (const auto& strat : node->stratifications)
		{
			file << strat.getName() << ": " << strat.getCost() << " " << strat.getDate() << " \n";
		}

		if (node->right != nullptr)
		{
			writeToFileHelper(file, node->right);
		}
	}

	friend std::ostream& operator << (std::ostream& out, const tree& t) { return print(out, t.root); }

	static std::ostream& print(std::ostream& out, Tnode* n);
};
std::ostream& tree::print(std::ostream& out, Tnode* n)
{
	if (n != NULL)
	{
		print(out, n->left);
		for (size_t i = 0; i < n->stratifications.size(); i++)
		{
			std::cout << n->dateSpending_;
			std::cout << "Name: " << n->stratifications[i].name << "\n";
			std::cout << "Time: " << n->stratifications[i].CurTime << "\n";
			std::cout << "Spending: " << n->stratifications[i].cost << "\n";
		}
		print(out, n->right);
	}
	return out;
}
std::ostream& operator<< (std::ostream& out, const Tnode& TnodeValue)
{
	return out;
}
#endif