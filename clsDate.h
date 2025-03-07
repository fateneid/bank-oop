#pragma warning(disable : 4996)
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include "clsString.h"
using namespace std;

class clsDate
{

private:
	short _Day;
	short _Month;
	short _Year;

public:

	clsDate() {
		*this = GetSystemDate();
	}

	clsDate(string Date) {
		*this = DateStringToStructure(Date);
	}

	clsDate(short Day, short Month, short Year) {
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(int TotalDays, short Year) {
		*this = DateFromDayOrderInAYear(Year, TotalDays);
	}

	void SetDay(short Day) {
		_Day = Day;
	}

	short GetDay() {
		return _Day;
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;


	void SetMonth(short Month) {
		_Month = Month;
	}

	short GetMonth() {
		return _Month;
	}

	__declspec(property(get = GetMonth, put = SetMonth)) short Month;


	void SetYear(short Year) {
		_Year = Year;
	}

	short GetYear() {
		return _Year;
	}

	__declspec(property(get = GetYear, put = SetYear)) short Year;

	/* :: [^*^] ::  */

	void Print() {

		cout << DateToString() << '\n';

	}

	static bool IsLeapYear(int Year) {

		return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);

	}

	bool IsLeapYear() {
		return IsLeapYear(_Year);
	}


	static short NumberOfDaysInAYear(short Year) {
		return IsLeapYear(Year) ? 366 : 365;
	}

	short NumberOfDaysInAYear() {
		return NumberOfDaysInAYear(_Year);
	}

	static short NumberOfHoursInAYear(short Year) {
		return NumberOfDaysInAYear(Year) * 24;
	}

	short NumberOfHoursInAYear() {
		return NumberOfHoursInAYear(_Year);
	}

	static int NumberOfMinutesInAYear(short Year) {
		return NumberOfHoursInAYear(Year) * 60;
	}

	int NumberOfMinutesInAYear() {
		return NumberOfMinutesInAYear(_Year);
	}

	static int NumberOfSecondsInAYear(short Year) {
		return NumberOfMinutesInAYear(Year) * 60;
	}

	int NumberOfSecondsInAYear() {
		return NumberOfSecondsInAYear(_Year);
	}


	static short NumberOfDaysInAMonth(short Year, short Month) {

		if (Month < 1 || Month > 12) return 0;

		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) :
			((Month == 4 || Month == 6 || Month == 9 || Month == 11) ? 30 : 31);

		//or 
		/*

		int NumberOfDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];


		*/

	}

	short NumberOfDaysInAMonth() {
		return NumberOfDaysInAMonth(_Year, _Month);
	}

	static short NumberOfHoursInAMonth(short Year, short Month) {
		return NumberOfDaysInAMonth(Year, Month) * 24;
	}

	short NumberOfHoursInAMonth() {
		return NumberOfHoursInAMonth(_Year, _Month);
	}

	static int NumberOfMinutesInAMonth(short Year, short Month) {
		return NumberOfHoursInAMonth(Year, Month) * 60;
	}

	int NumberOfMinutesInAMonth() {
		return NumberOfMinutesInAMonth(_Year, _Month);
	}

	static int NumberOfSecondsInAMonth(short Year, short Month) {
		return NumberOfMinutesInAMonth(Year, Month) * 60;
	}

	int NumberOfSecondsInAMonth() {
		return NumberOfSecondsInAMonth(_Year, _Month);
	}

	/* :: [^*^] ::  */

	static short GetDayOrder(short Year, short Month, short Day) {
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;

		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	short GetDayOrder() {
		return GetDayOrder(_Year, _Month, _Day);
	}

	static string GetDayName(short DayOrder) {

		string DaysOfWeek[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

		return DaysOfWeek[DayOrder];

	}

	static string GetMonthName(short Month) {

		string MonthsOfYear[12] = {
	   "Jan", "Feb", "Mar", "Apr", "May", "Jun",
	   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
		};

		return  MonthsOfYear[Month - 1];

	}

	string GetMonthName() {
		return GetMonthName(_Month);
	}

	static void PrintMonthCalendar(short Year, short Month) {

		short DaysInAMonth = NumberOfDaysInAMonth(Year, Month);
		short Place = GetDayOrder(Year, Month, 1) * 5;

		cout << "\n  _______________" << GetMonthName(Month) << "_______________\n";
		cout << "\n  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

		for (short i = 1; i <= DaysInAMonth; i++) {

			if (i == 1) {
				cout << "  " << setw(Place) << "";
			}

			cout << setw(3) << i << "  ";
			Place += 5;

			if (Place >= 33) {
				cout << "\n  ";
				Place = 0;
			}

		}
		cout << "\n  _________________________________\n";


	}

	void PrintMonthCalendar() {
		PrintMonthCalendar(_Year, _Month);
	}

	static void PrintYearCalendar(short Year) {

		cout << "\n  _________________________________\n";
		cout << "\n\t  Calendar - " << Year;
		cout << "\n  _________________________________\n";

		for (short i = 1; i <= 12; i++) {
			PrintMonthCalendar(Year, i);
		}

	}

	void PrintYearCalendar() {
		PrintYearCalendar(_Year);
	}

	static short DaysFromTheBeginningOfYear(short Year, short Month, short Day) {

		short TotalDays = 0;
		for (short i = 1; i < Month; i++) {
			TotalDays += NumberOfDaysInAMonth(Year, i);
		}
		TotalDays += Day;

		return TotalDays;

	}

	short DaysFromTheBeginningOfYear() {
		return DaysFromTheBeginningOfYear(_Year, _Month, _Day);
	}

	static clsDate DateFromDayOrderInAYear(short Year, short DayOrderInAYear) {

		clsDate Date;
		Date.Year = Year;
		Date.Month = 1;

		short RemainingDays = DayOrderInAYear;
		short MonthDays = 0;

		while (true) {

			MonthDays = NumberOfDaysInAMonth(Year, Date.Month);

			if (RemainingDays > MonthDays) {
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else {
				Date.Day = RemainingDays;
				break;
			}
		}

		return Date;

	}

	static clsDate AddDaysToDate(short Year, short Month, short Day, int DaysToAdd) {

		int TotalDays = DaysToAdd + DaysFromTheBeginningOfYear(Year, Month, Day);

		while (TotalDays >= NumberOfDaysInAYear(Year)) {
			TotalDays -= NumberOfDaysInAYear(Year);
			Year++;
		}
		if (TotalDays == 0) {
			TotalDays++;
		}
		return DateFromDayOrderInAYear(Year, TotalDays);

	}

	clsDate AddDaysToDate(int DaysToAdd) {
		return AddDaysToDate(_Year, _Month, _Day, DaysToAdd);
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2) {

		return (Date1.Year < Date2.Year) || (Date1.Year == Date2.Year && Date1.Month < Date2.Month) ||
			(Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day < Date2.Day);

	}

	bool IsDateBeforeDate2(clsDate Date2) {
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualsToDate2(clsDate Date1, clsDate Date2) {
		return (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day == Date2.Day);
	}

	bool IsDateEqualsToDate2(clsDate Date2) {
		return IsDate1EqualsToDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(clsDate Date) {
		return Date.Day == NumberOfDaysInAMonth(Date.Year, Date.Month);
	}

	bool IsLastDayInMonth() {
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month) {
		return Month == 12;
	}

	bool IsLastMonthInYear() {
		return IsLastMonthInYear(_Month);
	}

	static clsDate IncreaseDateByOneDay(clsDate& Date) {

		if (IsLastDayInMonth(Date)) {

			if (IsLastMonthInYear(Date.Month)) {
				Date.Day = 1;
				Date.Month = 1;
				Date.Year++;
			}
			else {
				Date.Day = 1;
				Date.Month++;
			}
		}
		else {
			Date.Day++;
		}

		return Date;

	}

	void IncreaseDateByOneDay() {
		IncreaseDateByOneDay(*this);
	}

	static short GetDiffrenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false) {

		short TotalDays = 0;

		if (!IsDate1BeforeDate2(Date1, Date2)) {
			swap(Date1, Date2);
		}

		if (Date1.Year != Date2.Year) {

			for (short i = Date1.Year; i < Date2.Year; i++) {
				TotalDays += NumberOfDaysInAYear(i);
			}

		}

		TotalDays += DaysFromTheBeginningOfYear(Date2.Year, Date2.Month, Date2.Day) -
			DaysFromTheBeginningOfYear(Date1.Year, Date1.Month, Date1.Day);

		return IncludeEndDay ? ++TotalDays : TotalDays;

	}

	short GetDiffrenceInDays(clsDate Date2, bool IncludeEndDay = false) {
		return GetDiffrenceInDays(*this, Date2, IncludeEndDay);
	}

	static clsDate GetSystemDate() {

		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year;

		Day = now->tm_mday;
		Month = now->tm_mon + 1;
		Year = now->tm_year + 1900;

		return clsDate(Day, Month, Year);
	}

	static string GetSystemDateTimeString() {

		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Day = now->tm_mday;
		Month = now->tm_mon + 1;
		Year = now->tm_year + 1900;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute)
			+ ":" + to_string(Second));

	}

	static int YourAgeInDays(clsDate BirthDate) {

		clsDate CurrentDate = GetSystemDate();
		return GetDiffrenceInDays(CurrentDate, BirthDate);

	}

	/* :: [^*^] ::  */

	static clsDate IncreaseDateByXDays(clsDate& Date, short XDays) {

		while (XDays--) {
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;

	}

	void IncreaseDateByXDays(short XDays) {
		IncreaseDateByXDays(*this, XDays);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date) {

		Date = IncreaseDateByXDays(Date, 7);

		return Date;

	}

	void IncreaseDateByOneWeek() {
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate& Date, short XWeeks) {

		while (XWeeks--) {
			Date = IncreaseDateByOneWeek(Date);
		}

		return Date;

	}

	void IncreaseDateByXWeeks(short XWeeks) {
		IncreaseDateByXWeeks(*this, XWeeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date) {

		if (Date.Month == 12) {
			Date.Year++;
			Date.Month = 1;
		}
		else {
			Date.Month++;
		}
		short NumberOfDaysInMonth = NumberOfDaysInAMonth(Date.Year, Date.Month);
		if (Date.Day > NumberOfDaysInMonth) {
			Date.Day = NumberOfDaysInMonth;
		}

		return Date;

	}

	void IncreaseDateByOneMonth() {
		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate& Date, short XMonths) {

		while (XMonths--) {
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;

	}

	void IncreaseDateByXMonths(short XMonths) {
		IncreaseDateByXMonths(*this, XMonths);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date) {

		Date.Year++;

		if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year)) {
			Date.Day = 28;
		}

		return Date;

	}

	void IncreaseDateByOneYear() {
		IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate& Date, short XYears) {

		Date.Year += XYears;

		if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year)) {
			Date.Day = 28;
		}

		return Date;

	}

	void IncreaseDateByXYears(short XYears) {
		IncreaseDateByXYears(*this, XYears);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date) {

		Date.Year += 10;

		if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year)) {
			Date.Day = 28;
		}

		return Date;

	}

	void IncreaseDateByOneDecade() {
		IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate& Date, short XDecades) {

		Date.Year += XDecades * 10;

		if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year)) {
			Date.Day = 28;
		}

		return Date;

	}

	void IncreaseDateByXDecades(short XDecades) {
		IncreaseDateByXDecades(*this, XDecades);
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date) {

		Date.Year += 100;

		if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year)) {
			Date.Day = 28;
		}

		return Date;

	}

	void IncreaseDateByOneCentury() {
		IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate& Date) {

		Date.Year += 1000;

		if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year)) {
			Date.Day = 28;
		}

		return Date;

	}

	void IncreaseDateByOneMillennium() {
		IncreaseDateByOneMillennium(*this);
	}

	/* :: [^*^] ::  */

	static clsDate DecreaseDateByOneDay(clsDate& Date) {

		if (Date.Day == 1) {
			if (Date.Month == 1) {
				Date.Year--;
				Date.Month = 12;
				Date.Day = 31;
			}
			else {
				Date.Month--;
				Date.Day = NumberOfDaysInAMonth(Date.Year, Date.Month);
			}
		}
		else {
			Date.Day--;
		}

		return Date;

	}

	void DecreaseDateByOneDay() {
		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate& Date, short XDays) {

		while (XDays--) {
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;

	}

	void DecreaseDateByXDays(short XDays) {
		DecreaseDateByXDays(*this, XDays);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date) {

		Date = DecreaseDateByXDays(Date, 7);

		return Date;

	}

	void DecreaseDateByOneWeek() {
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate& Date, short XWeeks) {

		while (XWeeks--) {
			Date = DecreaseDateByOneWeek(Date);
		}

		return Date;

	}

	void DecreaseDateByXWeeks(short XWeeks) {
		DecreaseDateByXWeeks(*this, XWeeks);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date) {

		if (Date.Month == 1) {
			Date.Year--;
			Date.Month = 12;
		}
		else {
			Date.Month--;
		}

		short NumberOfDaysInMonth = NumberOfDaysInAMonth(Date.Year, Date.Month);

		if (Date.Day > NumberOfDaysInMonth) {
			Date.Day = NumberOfDaysInMonth;
		}

		return Date;

	}

	void DecreaseDateByOneMonth() {
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate& Date, short XMonths) {

		while (XMonths--) {
			Date = DecreaseDateByOneMonth(Date);
		}

		return Date;

	}

	void DecreaseDateByXMonths(short XMonths) {
		DecreaseDateByXMonths(*this, XMonths);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date) {

		Date.Year--;

		if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year)) {
			Date.Day = 28;
		}

		return Date;

	}

	void DecreaseDateByOneYear() {
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate& Date, short XYears) {

		Date.Year -= XYears;

		if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year)) {
			Date.Day = 28;
		}

		return Date;

	}

	void DecreaseDateByXYears(short XYears) {
		DecreaseDateByXYears(*this, XYears);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date) {

		Date.Year -= 10;

		if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year)) {
			Date.Day = 28;
		}

		return Date;

	}

	void DecreaseDateByOneDecade() {
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate& Date, short XDecades) {

		Date.Year -= XDecades * 10;

		if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year)) {
			Date.Day = 28;
		}

		return Date;

	}

	void DecreaseDateByXDecades(short XDecades) {
		DecreaseDateByXDecades(*this, XDecades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date) {

		Date.Year -= 100;

		if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year)) {
			Date.Day = 28;
		}

		return Date;

	}

	void DecreaseDateByOneCentury() {
		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date) {

		Date.Year -= 1000;

		if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year)) {
			Date.Day = 28;
		}

		return Date;

	}

	void DecreaseDateByOneMillennium() {
		DecreaseDateByOneMillennium(*this);
	}

	/* :: [^*^] ::  */

	static bool IsEndOfWeek(clsDate Date) {
		return GetDayOrder(Date.Year, Date.Month, Date.Day) == 6;
	}

	bool IsEndOfWeek() {
		return IsEndOfWeek(*this);
	}

	static bool IsWeekend(clsDate Date) {
		short DayIndex = GetDayOrder(Date.Year, Date.Month, Date.Day);
		return (DayIndex == 5 || DayIndex == 6);
	}

	bool IsWeekend() {
		return IsWeekend(*this);
	}

	static bool IsBusinessDay(clsDate Date) {
		//short DayIndex = DayOfWeekOrder(Date);
		//return !(DayIndex == 5 || DayIndex == 6);
		return !IsWeekend(Date);
	}

	bool IsBusinessDay() {
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date) {
		return 6 - GetDayOrder(Date.Year, Date.Month, Date.Day);
	}

	short DaysUntilTheEndOfWeek() {
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date) {
		return NumberOfDaysInAMonth(Date.Year, Date.Month) - Date.Day;
	}

	short DaysUntilTheEndOfMonth() {
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date) {
		return NumberOfDaysInAYear(Date.Year) - DaysFromTheBeginningOfYear(Date.Year, Date.Month, Date.Day);
	}

	short DaysUntilTheEndOfYear() {
		return DaysUntilTheEndOfYear(*this);
	}

	static short CalcBusinessDays(clsDate DateFrom, clsDate DateTo) {

		short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo)) {

			if (IsBusinessDay(DateFrom)) {
				Days++;
			}

			DateFrom = IncreaseDateByOneDay(DateFrom);

		}

		return Days;

	}

	static short CalcVacationDays(clsDate DateFrom, clsDate DateTo) {
		return CalcBusinessDays(DateFrom, DateTo);
	}

	static clsDate GetReturnDate(clsDate Date, short VacationDays) {

		while (VacationDays > 0) {
			if (IsBusinessDay(Date)) {
				VacationDays--;
			}
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;

	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2) {

		return !(IsDate1BeforeDate2(Date1, Date2) || IsDate1EqualsToDate2(Date1, Date2));

		//return (Date1.Year > Date2.Year) || (Date1.Year == Date2.Year && Date1.Month > Date2.Month) ||
		//	(Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day > Date2.Day);

	}

	bool IsDateAfterDate2(clsDate Date2) {
		return IsDate1AfterDate2(*this, Date2);
	}

	enum enCompareDate { Before = -1, Equal = 0, After = 1 };

	static enCompareDate CompareDate(clsDate Date1, clsDate Date2) {

		if (IsDate1BeforeDate2(Date1, Date2)) {
			return enCompareDate::Before;
		}
		else if (IsDate1EqualsToDate2(Date1, Date2)) {
			return enCompareDate::Equal;
		}
		else {
			return enCompareDate::After;
		}

	}

	enCompareDate CompareDate(clsDate Date2) {
		return CompareDate(*this, Date2);
	}

	/* :: [^*^] ::  */

	static bool IsAValidDate(clsDate Date) {

		return (Date.Day >= 1 && Date.Day <= NumberOfDaysInAMonth(Date.Year, Date.Month) &&
			Date.Month >= 1 && Date.Month <= 12 && Date.Year >= 1);

	}

	bool IsAValidDate() {
		return IsAValidDate(*this);
	}

	static clsDate DateStringToStructure(string DateString) {

		clsDate Date;
		vector<string> vDate = clsString::SplitString(DateString, "/");

		Date.Day = stoi(vDate[0]);
		Date.Month = stoi(vDate[1]);
		Date.Year = stoi(vDate[2]);

		return Date;

	}

	static string DateToString(clsDate Date) {

		return to_string(Date.Day) + '/' + to_string(Date.Month) + '/' + to_string(Date.Year);

	}

	string DateToString() {
		return DateToString(*this);
	}

	static string FormatDate(clsDate Date, string Format = "dd/mm/yyyy") {

		Format.replace(Format.find("dd"), 2, to_string(Date.Day));
		Format.replace(Format.find("mm"), 2, to_string(Date.Month));
		Format.replace(Format.find("yyyy"), 4, to_string(Date.Year));

		return Format;

	}

	string FormatDate(string Format = "dd/mm/yyyy") {
		return FormatDate(*this, Format);
	}

};

