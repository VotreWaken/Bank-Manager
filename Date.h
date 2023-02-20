/*
The Date class is used in the Binary Search Tree
*/
#ifndef DATE_H
#define DATE_H
#include <iostream>
using namespace std;
class Date
{
public:

	// Constructor By Parametres
	Date(int day, int month, int year) : days_{ day }, month_{ month }, year_{ year }
	{
		if ((days_ > 31) || (month_ > 12))
		{
			cout << "Date error" << endl;
			return;
		}
	}

	// Default Constructor ( Initialize Current Time )
	Date()
	{
		std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);
		days_ = now->tm_mday;
		month_ = now->tm_mon + 1;
		year_ = now->tm_year + 1900;
	}

	// Constructor By Parametres ( Can Accept Month Value by String )
	Date(int day, std::string monthStr, int year)
	{
		// Convert month string to int
		int monthInt = 0;
		const char* Month[] = { "January","February","March","April","May","June","July","August","September","October","November","December" };
		for (int i = 0; i < 12; i++)
		{
			if (Month[i] == monthStr)
			{
				monthInt = i + 1;
				break;
			}
		}
		// Set the date values
		days_ = day;
		month_ = monthInt;
		year_ = year;
	}

	// Is year leap 
	constexpr bool isLeap() const
	{
		if ((year_ % 4 == 0 && year_ % 100 != 0) && year_ % 400) {
			return true;
		}
		return false;
	}

	// Display Date Fields to screen
	void Show() const
	{
		cout << "Days: " << days_ << endl;
		cout << "Month: " << month_ << endl;
		cout << "Year: " << year_ << endl;
	}

	// Operator " + " for Int value
	Date& operator + (int Day)
	{
		if (days_ + Day > days[month_ - 1]) {
			for (;days_ + Day > days[month_ - 1];)
			{
				Day -= days[month_ - 1];
				Day = Day + days_;
				if (++month_ - 1 >= 12)
				{
					month_ = 1;
					year_++;
					isLeap() == true ? Day-- : Day;
				}
				days_ = Day;
				Day = 0;
			}
		}
		else
			days_ += Day;

		return *this;
	}

	// Operator "-" to take the value of the second instance of the Date type class
	// Taking into account leap year
	int operator - (const Date& SecondDate) const
	{
		// Assign value to the value of the object for which the method is called
		// To the value of the Temporary object
		Date temp = *this;

		// Remember the old value of the Year field
		int i = temp.year_;
		int j = 0;
		// Decrement the year in the Loop header
		// In the body of the Loop, check the result of the returned value by the isLeap() function
		// And decrement Days depending on Iterations and Return Value
		for (;temp.year_ != 0;temp.year_--)
		{
			temp.isLeap() == true ? j-- : j;
		};

		int TempDays = i * 365 + temp.days_ - j;

		for (int i = 0; i < month_ - 1; i++)
			TempDays += days[i];

		// Repeat above action

		Date tempSecond = SecondDate;

		int q = tempSecond.year_;
		int w = 0;

		for (;tempSecond.year_ != 0;tempSecond.year_--)
		{
			tempSecond.isLeap() == true ? w-- : w;
		};

		int TempSecondDays = q * 365 + tempSecond.days_ - w;

		for (int i = 0; i < tempSecond.month_ - 1; i++)
			TempSecondDays += days[i];

		return TempDays - TempSecondDays;
	}

	bool operator== (const Date& rhs)
	{
		return (GetYear() == rhs.GetYear()) &&
			(GetMonth() == rhs.GetMonth()) &&
			(GetDay() == rhs.GetDay());
	}

	bool operator<(Date& d2)
	{
		if (GetYear() < d2.GetYear())
			return true;
		else if (GetYear() == d2.GetYear() && GetMonth() < d2.GetMonth())
			return true;
		else if (GetYear() == d2.GetYear() && GetMonth() == d2.GetMonth() && GetDay() < d2.GetDay())
			return true;
		return false;
	}

	bool operator>(Date& d2)
	{
		if (GetYear() > d2.GetYear())
			return true;
		else if (GetYear() == d2.GetYear() && GetMonth() > d2.GetMonth())
			return true;
		else if (GetYear() == d2.GetYear() && GetMonth() == d2.GetMonth() && GetDay() > d2.GetDay())
			return true;
		return false;
	}

	// Overload comparison operators
	bool operator<(const Date& other) const
	{
		if (GetYear() != other.GetYear()) {
			return GetYear() < other.GetYear();
		}
		else if (GetMonth() != other.GetMonth()) {
			return GetMonth() < other.GetMonth();
		}
		else {
			return  GetDay() < other.GetDay();
		}
	}

	bool operator>(const Date& other) const
	{
		if (GetYear() != other.GetYear()) {
			return GetYear() > other.GetYear();
		}
		else if (GetMonth() != other.GetMonth()) {
			return GetMonth() > other.GetMonth();
		}
		else {
			return  GetDay() > other.GetDay();
		}
	}

	bool operator==(const Date& other) const
	{
		return (GetDay() == other.GetDay()) && (GetMonth() == other.GetMonth()) && (GetYear() == other.GetYear());
	}

	// Get Day
	constexpr int GetDay() const
	{
		return days_;
	}

	// Get Month
	constexpr int GetMonth() const
	{
		return month_;
	}

	// Get Year
	constexpr int GetYear() const
	{
		return year_;
	}

	// Set Day
	constexpr void SetDay(int days)
	{
		days_ = days;
	}

	// Set Month
	constexpr void SetMonth(int month)
	{
		month_ = month;
	}

	// Set Year
	constexpr void SetYear(int year)
	{
		year_ = year;
	}

	// Get Count of Days In Specific Month
	constexpr static int GetDaysInMonth(int index)
	{
		return days[index - 1];
	}

	// Destructor
	~Date()
	{

	};

private:
	int days_;
	int month_;
	int year_;
	constexpr static int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
};

// Operator Overload "<<" To Output Number
ostream& operator<< (ostream& out, const Date& Date)
{
	const char* Month[] =
	{ "January","February","March","April","May","June","July","August","September","October","November","December" };

	out << "Date: " << Date.GetDay() << "." << Date.GetYear() << " " << Month[Date.GetMonth() - 1] << "\n";

	return out;
}
#endif