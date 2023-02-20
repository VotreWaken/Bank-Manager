/*
The Time class works to determine the time in costs used in a
binary search tree due to to the "iomanip" library, it has access
to get the current time from the computer
*/
#ifndef TIME_H
#define TIME_H
#include <iostream>
#include <iomanip>
#define _CRT_SECURE_NO_WARNINGS
class Time
{
public:

	// Default Constructor
	Time()
	{
		time_t Times;
		time(&Times);
		struct tm* timeinfo;
		timeinfo = localtime(&Times);

		minutes_ = timeinfo->tm_min;
		hours_ = timeinfo->tm_hour;
		seconds_ = timeinfo->tm_sec;
	}

	// Int Constructor
	Time(int hour, int min, int sec) : seconds_(sec), minutes_(min), hours_(hour)
	{
		if (hour > 24 || min > 59 || sec > 59)
		{
			throw(std::domain_error("Time value out of range"));
		}
	};

	// String Constructor
	Time(std::string stringValue)
	{
		int tempSeconds = 0;
		int tempMinutes = 0;
		int tempHours = 0;

		if (std::sscanf(stringValue.c_str(), "%i:%i:%i", &hours_, &minutes_, &seconds_) != 3)
		{
			throw(std::domain_error("Too many arguments"));
		}

		if (tempHours > 24 || tempMinutes > 59 || tempSeconds > 59)
		{
			throw(std::domain_error("Time value out of range"));
		}
	}

	// Seconds Constructor
	Time(int Seconds)
	{
		minutes_ = Seconds / 60;
		hours_ = minutes_ / 60;
		seconds_ = Seconds % 60;
		minutes_ = minutes_ % 60;
	}

	// Current Time Constructor 
	Time(time_t Time)
	{
		time(&Time);
		struct tm* timeinfo;
		timeinfo = localtime(&Time);

		minutes_ = timeinfo->tm_min;
		hours_ = timeinfo->tm_hour;
		seconds_ = timeinfo->tm_sec;
	};

	// Difference between 2 dates 
	Time Difference(const Time& SecondTime)
	{
		Time temp;

		if (SecondTime.seconds_ > seconds_) {
			minutes_--;
			seconds_ += 60;
		}

		temp.seconds_ = seconds_ - SecondTime.seconds_;

		if (SecondTime.minutes_ > minutes_) {
			hours_--;
			minutes_ += 60;
		}

		temp.minutes_ = minutes_ - SecondTime.minutes_;
		temp.hours_ = hours_ - SecondTime.hours_;

		return temp;
	}

	// Add Seconds to class time
	constexpr void addSeconds(int Sec)
	{
		seconds_ += Sec;

		if (seconds_ > 59)
		{
			minutes_ += seconds_ / 60;

			if (minutes_ > 59)
			{
				hours_ += minutes_ / 60;
				minutes_ = 0;
			}

			seconds_ -= Sec;
		}
	}

	// Subtract Seconds to class time (Need Work)
	constexpr void SubtractSeconds(int Sec)
	{
		seconds_ -= Sec;

		if (seconds_ > 59)
		{
			minutes_ += seconds_ / 60;

			if (minutes_ > 59)
			{
				hours_ += minutes_ / 60;
				minutes_ = 0;
			}

			seconds_ -= Sec;
		}
	}

	// Overload Operator << 
	friend std::ostream& operator<<(std::ostream& out, const Time& t)
	{
		auto oldfill = out.fill('0');
		return out << t.hours_
			<< ':' << std::setw(2) << t.minutes_
			<< ':' << std::setw(2) << t.seconds_ << std::setfill(oldfill);
	}

	// Set Second
	void SetSeconds(int Seconds)
	{
		seconds_ = Seconds;
	}

	// Set Minutes
	void SetMinutes(int Minutes)
	{
		minutes_ = Minutes;
	}

	// Set Hours
	void SetHours(int Hours)
	{
		hours_ = Hours;
	}

	// Destructor 
	~Time()
	{

	};

private:
	int seconds_;
	int minutes_;
	int hours_;
};
#endif