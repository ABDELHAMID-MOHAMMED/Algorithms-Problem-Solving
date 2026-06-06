#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

//مكتبات خاصة بتحديد السنة الكبيسة و الصغيرة 
bool Leapyear(int Number)
{
    return (Number % 400 == 0) || (Number % 4 == 0 && Number % 100 != 0);
}
short NumberOfDays(int Number)
{
    return Leapyear(Number) ? 366 : 355;
}
short NumberOfHours(int Number)
{
    return NumberOfDays(Number) * 24;
}
int NumberOfMinutes(int Number)
{
    return NumberOfHours(Number) * 60;
}
int NumberOfSrconds(int Number)
{
    return NumberOfMinutes(Number) * 60;
}

short DayOrder(short Day, short Month, short Year)
{
    short m, a, y;
    a = (14 - Month) / 12;
    y = Year - a;
    m = Month + (12 * a) - 2;
    return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}
string PrintDay(short day)
{
    string days[] = { "sun","mon","tus","wed","thurs","fry" ,"sat" };
    return days[day];
}
string PrintMonth(short Month)
{
    string PM[] = { "JAN","FEB","MARCH","IPREL","MAY","JUNE","JULY","AUGEST","SEP","AUCT","NOV","DEC" };
    return PM[Month - 1];
}

struct stDate {
    int Year;
    int Month;
    int Day;
};
stDate DateOrderInYear(int DateOrder, int Year)
{
    stDate Date;
    int RemaningDate = DateOrder;
    int MonthsDays = 0;
    Date.Year = Year;
    Date.Month = 1;
    while (true)
    {
        MonthsDays = NumberOfDays(Year, Date.Month);
        if (RemaningDate > MonthsDays)
        {
            RemaningDate -= MonthsDays;
            Date.Month++;
        }
        else
        {
            Date.Day = RemaningDate;
            break;
        }

    }
    return Date;
}
void PrintMonthDays(short Month, short year)
{
    short NumberOfDay;
    short Current = DayOrder(1, Month, year);
    NumberOfDay = NumberOfDays(year, Month);

    printf("----------%s----------\n\n",
        PrintMonth(Month).c_str());

    printf(" Sun Mon Tue Wed Thu Fri Sat\n");

    int i;
    for (i = 0; i < Current; i++)
        printf(" ");
    for (int j = 1; j <= NumberOfDay; j++)
    {
        printf("%5d", j);
        if (++i == 7)
        {
            i = 0;
            printf("\n");
        }
    }

}
void PrintAllMonthsDays(short year)
{
    short NumberOfDay;
    short Counter = 1;


    cout << "-------------------------------------\n";
    cout << "\t\tCalender " << year << endl;
    cout << "-------------------------------------\n";
    do {
        short Current = DayOrder(1, Counter, year);
        NumberOfDay = NumberOfDays(year, Counter);
        printf("-------------- %s -------------------\n\n", PrintMonth(Counter).c_str());
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        int i;
        for (i = 0; i < Current; i++)
            printf("     ");
        for (int j = 1; j <= NumberOfDay; j++)
        {
            printf("%5d", j);
            if (++i == 7)
            {
                i = 0;
                printf("\n");
            }
        }
        Counter++;
        cout << "\n\n";
    } while (Counter <= 12); {

    }

}
int PrintSpecificDay(int Day, int Month, int Year)
{
    int DayCount = 0;
    for (int i = 1;i <= Month - 1;i++)
    {
        DayCount += NumberOfDays(Year, i);
    }
    DayCount += Day;
    return DayCount;
}
stDate ReadFullDate()
{
    stDate Date;
    Date.Day = ReadDay();
    Date.Month = ReadMonth();
    Date.Year = ReadYear();
    return Date;
}
stDate AddMoreDaysToYears(int Day, stDate Date)
{
    int Remining = Day + PrintSpecificDay(Date.Day, Date.Month, Date.Year);
    short MonthsDay = 0;
    Date.Month = 1;
    while (true)
    {
        MonthsDay = NumberOfDays(Date.Year, Date.Month);
        if (Remining > MonthsDay)
        {
            Remining -= MonthsDay;
            Date.Month++;
            if (Date.Month > 12)
            {
                Date.Month = 1;
                Date.Year++;
            }
        }
        else
        {
            Date.Day = Remining;
            break;
        }
    }
    return Date;
}
bool IsDate1BeforeDate2(stDate& Date, stDate& Date2)
{
    return (Date.Year < Date2.Year) ? true : ((Date.Year == Date2.Year) ? (Date.Month < Date2.Month ? true : (Date.Month == Date2.Month ? Date.Day < Date2.Day : false)) : false);
}
bool IsEquvalant(stDate Date, stDate Date2)
{
    return (Date.Year == Date2.Year && Date.Month == Date2.Month && Date.Day == Date2.Day);
}
bool IsLastday(stDate Date)
{
    return (Date.Day == NumberOfDays(Date.Year, Date.Month));
}
bool IsLastMonth(stDate Date)
{
    return (Date.Month == 12);
}
stDate IncreaseByOneDay(stDate& Date)
{

    if (IsLastday(Date) && IsLastMonth(Date))
    {
        Date.Day = 1;
        Date.Month = 1;
        Date.Year++;
    }
    else if (IsLastday(Date))
    {
        Date.Month++;
        Date.Day = 1;
    }
    else
    {
        Date.Day++;
    }
    return Date;
}
stDate IncreaseDateByXDays(stDate Date, short XDays)
{
    for (short i = 0;i < XDays;i++)
    {
        Date = IncreaseByOneDay(Date);
    }
    return Date;
}
stDate IncreaseDateByOneWeek(stDate Date)
{
    for (short i = 0;i < 7;i++)
    {
        Date = IncreaseByOneDay(Date);
    }
    return Date;
}
stDate IncreaseDateByXWeek(stDate Date, int Weeks)
{
    for (short i = 0;i < Weeks;i++)
    {
        Date = IncreaseDateByOneWeek(Date);
    }
    return Date;
}
stDate IncreaseDateByOneMonth(stDate Date)
{
    if (Date.Month == 12)
    {
        Date.Year++;
        Date.Month = 1;
    }
    else
    {
        Date.Month++;
    }
    short NumberOfDay = NumberOfDays(Date.Year, Date.Month);
    if (Date.Day > NumberOfDay)
    {
        Date.Day = NumberOfDay;
    }
    return Date;
}
stDate IncreaseDateByXMonth(stDate Date, int Month)
{
    for (int i = 0;i < Month;i++)
    {
        Date = IncreaseDateByOneMonth(Date);
    }
    return Date;
}
stDate IncreaseDateByOneYear(stDate Date)
{
    Date.Year++;
    return Date;
}
stDate IncreaseDateByXYear(stDate Date, int Year)
{
    for (int i = 0;i < Year;i++)
    {
        Date = IncreaseDateByOneYear(Date);
    }
    return Date;
}
stDate IncreaseDateByXYearFaster(stDate Date, int Years)
{
    Date.Year += Years;
    return Date;
}
stDate IncreaseDateByOneDecade(stDate Date)
{
    Date.Year += 10;
    return Date;
}
stDate IncreaseDateByXDecade(stDate Date, int Decade)
{
    for (int i = 0;i < Decade * 10;i++)
    {
        Date = IncreaseDateByOneYear(Date);
    }
    return Date;
}
int DiffrentOfDate1AndDate2(stDate Date, stDate Date2, bool IncludLastday = false)
{
    int Diff = 0;
    while (IsDate1BeforeDate2(Date, Date2))
    {
        Diff++;
        Date = IncreaseByOneDay(Date);
    }
    return IncludLastday ? ++Diff : Diff;
}
int CountYourDays(stDate Date, stDate Date2)
{
    int Days = 0;
    while (IsDate1BeforeDate2(Date, Date2))
    {
        Days++;
        Date = IncreaseByOneDay(Date);

    }
    return Days;
}
stDate GetSystemDate()
{
    stDate Date;

    time_t t = time(0);
    tm* now = localtime(&t);

    Date.Year = now->tm_year + 1900;
    Date.Month = now->tm_mon + 1;
    Date.Day = now->tm_mday;

    return Date;
}
void SwapDates(stDate& Date, stDate& Date2)
{
    stDate Tempdate;

    Tempdate.Day = Date.Day;
    Tempdate.Month = Date.Month;
    Tempdate.Year = Date.Year;

    Date.Day = Date2.Day;
    Date.Month = Date2.Month;
    Date.Year = Date2.Year;

    Date2.Day = Tempdate.Day;
    Date2.Month = Tempdate.Month;
    Date2.Year = Tempdate.Year;

}
int DiffrentOfDate1AndDate2WithMinus(stDate Date, stDate Date2, bool IncludLastday = false)