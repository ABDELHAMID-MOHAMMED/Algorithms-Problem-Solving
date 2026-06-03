#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

short ReadYear()
{
    short Number = 0;
    cout << "PLEASE ENTER NUMBER : ";
    cin >> Number;
    return Number;
}
short ReadMonth()
{
    short Month = 0;
    cout << "enter Month ?";
    cin >> Month;
    return Month;
}
short ReadDay()
{
    short Day = 0;
    cout << "Enter your Day : ";
    cin >> Day;
    return Day;
}
int DaysToAdd()
{
    int AddDay = 0;
    cout << "How Many Days Do You Want to Add : ";
    cin >> AddDay;
    return AddDay;
}
string PrintTextNumber(short Number)
{
    if (Number == 0)
    {
        return "";
   }
    if (Number >= 1 && Number <= 19) {
        string arr[] = { "",
"One","Two","Three","Four","Five","Six","Seven",
"Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
"Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
        return arr[Number]+" ";
   }
    if (Number >= 20 && Number <= 99) {
        string arr[] = {
"","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty"
,"Ninety" };
        return arr[Number / 10] + " " + PrintTextNumber(Number % 10);
    }
    if (Number >= 100 && Number <= 199) {
        return "One Handred " + PrintTextNumber(Number % 100);
    }
    if (Number >= 200 && Number <= 999) {
        return PrintTextNumber(Number / 100) + "Handreds " +
            PrintTextNumber(Number % 100);
    }
    if (Number >= 1000 && Number <= 1999) {
        return "One Thousand " + PrintTextNumber(Number % 1000);
    }
    if (Number >= 2000 && Number <= 999999) {
        return PrintTextNumber(Number / 1000) + "Thousand " +
            PrintTextNumber(Number % 1000);
    }
    if (Number >= 1000000 && Number <= 1999999)
    {
        return "One Million " + PrintTextNumber(Number % 1000000);
    }
    if (Number >= 2000000 && Number <= 999999999)
    {
        return PrintTextNumber(Number / 1000000) + "Millions " +
            PrintTextNumber(Number % 1000000);
    }
    if (Number >= 1000000000 && Number <= 1999999999)
    {
        return "One Billion " + PrintTextNumber(Number %
            1000000000);
    }
    else
    {
        return PrintTextNumber(Number / 1000000000) + "Billions " +
            PrintTextNumber(Number % 1000000000);
    }
}
bool Leapyear(short Number)
{
    return (Number % 400 == 0 )|| (Number % 4 == 0 && Number % 100 != 0);
}
int NumberOfDays(short Number,short Month)
{
    if (Month < 1 || Month>12)
        return 0;

    short arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    return (Month==2)?(Leapyear(Number)?29:28):arr[Month-1];
 
}
int NumberOfHours(int Number, int Month)
{
    return NumberOfDays(Number, Month) * 24;
}
int NumberOfMinutes(short Number, short Month)
{
    return NumberOfHours(Number,Month) * 60;
}
int NumberOfSrconds(short Number, short Month)
{
    return NumberOfMinutes(Number, Month) * 60;
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
    string days[] = {"sun","mon","tus","wed","thurs","fry" ,"sat"};
    return days[day];
}
string PrintMonth(short Month)
{
    string PM[] = { "JAN","FEB","MARCH","IPREL","MAY","JUNE","JULY","AUGEST","SEP","AUCT","NOV","DEC" };
    return PM[Month-1];
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
void PrintMonthDays(short Month,short year)
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
        short Current = DayOrder(1,Counter , year);
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
int PrintSpecificDay(int Day,int Month, int Year)
{
    int DayCount = 0;
    for (int i = 1;i <= Month-1;i++)
    {
        DayCount += NumberOfDays(Year, i);
    }
    DayCount += Day;
    return DayCount;
}
stDate ReadFullDate()
{
    stDate Date;
    Date.Day= ReadDay();
    Date.Month= ReadMonth();
    Date.Year= ReadYear();
    return Date;
}

stDate AddMoreDaysToYears(int Day,stDate Date)
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
bool IsDate1BeforeDate2(stDate &Date,stDate &Date2)
{
    return (Date.Year < Date2.Year) ? true : ((Date.Year == Date2.Year) ? (Date.Month < Date2.Month ? true : (Date.Month == Date2.Month ? Date.Day < Date2.Day : false)) : false);
}
bool IsEquvalant(stDate Date, stDate Date2)
{
    return (Date.Year == Date2.Year && Date.Month == Date2.Month && Date.Day == Date2.Day);
}
bool IsLastday(stDate Date)
{
    return (Date.Day == NumberOfDays(Date.Year,Date.Month));
}
bool IsLastMonth(stDate Date)
{
    return (Date.Month == 12);
}
stDate IncreaseByOneDay(stDate &Date)
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
int CountYourDays(stDate Date,stDate Date2)
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

    Date.Year = now->tm_year+1900;
    Date.Month = now->tm_mon + 1;
    Date.Day = now->tm_mday;

    return Date;
}
int main()
{
    stDate Date=ReadFullDate();
    cout << endl;
    stDate Date2 = GetSystemDate();
    cout << endl;
   cout << "Your Age Is : "<< CountYourDays(Date,Date2)<<" (Days)\n";
   
}
