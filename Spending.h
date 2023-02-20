#ifndef SPENDING_H
#define SPENDING_H
#include <string>
#include "Time.h"
class Spending
{
public:
	Spending(std::string n, double c) : name(n), cost(c)
	{

	}

	Spending(std::string n, double c, Time Dates) : name(n), cost(c), CurTime(Dates)
	{

	}
	std::string getName() const { return name; }
	constexpr double getCost() const { return cost; }
	Time getDate() const { return CurTime; }

	std::string name;
	double cost;
	Time CurTime;
private:

};
#endif