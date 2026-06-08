#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

short ReadYear()
{
    short Number = 0;
    cout << "PLEASE ENTER Year : ";
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
bool Leapyear(short Year)
{
    return (Year % 400 == 0 )|| (Year % 4 == 0 && Year % 100 != 0);
}
int NumberOfDays(short Year,short Month)
{
    if (Month < 1 || Month>12)
        return 0;

    short arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    return (Month==2)?(Leapyear(Year)?29:28):arr[Month-1];
 
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
    string days[] = {"sun","mon","tus","wed","thurs","fri" ,"sat"};
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
struct stPeriod {
    stDate StartDate;
    stDate EndDate;
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
bool IsDate1AfterDate2(stDate Date, stDate Date2)
{
    return (!IsDate1BeforeDate2(Date, Date2) && !IsEquvalant(Date, Date2));
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
stDate IncreaseDateByXDays(stDate Date, short XDays)
{
    for (short i = 0;i < XDays;i++)
    {
       Date= IncreaseByOneDay(Date);
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
    if(Date.Day > NumberOfDay)
    {
        Date.Day = NumberOfDay;
    }
    return Date;
}
stDate IncreaseDateByXMonth(stDate Date,int Month)
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
string ReplaceWordInString(string S1, string StringToReplace, string sReplaceTo)
{
    short pos = S1.find(StringToReplace);
    while (pos != std::string::npos)
    {
        S1 = S1.replace(pos, StringToReplace.length(), sReplaceTo);
        pos = S1.find(StringToReplace);
    }
    return S1;
}
vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable
    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }
    return vString;
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
{
    int Days = 0;
    int SwapFlagValue = 1;

    if (!IsDate1BeforeDate2(Date, Date2))
    {
        //Swap Dates 
        SwapDates(Date, Date2);
        SwapFlagValue = -1;
    }
    while (IsDate1BeforeDate2(Date, Date2))
    {
        Days++;
        Date = IncreaseByOneDay(Date);
    }
    return IncludLastday ? ++Days * SwapFlagValue : Days * SwapFlagValue;
}
stDate DecreaseDateByOneDay(stDate Date)
{
    if (Date.Day == 1 && Date.Month == 1)
    {
        Date.Month=12;
        Date.Year--;
        Date.Day = 31;
    }
  
    else if (Date.Day == 1)
    {
        Date.Month--;
        Date.Day = NumberOfDays(Date.Year, Date.Month);
    }
    else
    {
        Date.Day--;
    }
    return Date;
}
stDate DecreaseDateByXDays(stDate Date, short XDays)
{
    for (short i = 0;i < XDays;i++)
    {
        Date = DecreaseDateByOneDay(Date);
    }
    return Date;
}
stDate DecreaseDateByOneWeek(stDate Date)
{
    for (short i = 0;i < 7;i++)
    {
        Date = DecreaseDateByOneDay(Date);
    }
    return Date;
}
stDate DecreaseDateByXWeek(stDate Date, int Weeks)
{
    for (short i = 0;i < Weeks;i++)
    {
        Date = DecreaseDateByOneWeek(Date);
    }
    return Date;
}
stDate DecreaseDateByOneMonth(stDate Date)
{
    if (Date.Month == 1)
    {
        Date.Year--;
        Date.Month = 12;
    }
    else
    {
        Date.Month--;
    }
    short NumberOfDay = NumberOfDays(Date.Year, Date.Month);
    if (Date.Day > NumberOfDay)
    {
        Date.Day = NumberOfDay;
    }
    return Date;
}
stDate DecreaseDateByXMonth(stDate Date, int Month)
{
    for (int i = 0;i < Month;i++)
    {
        Date = DecreaseDateByOneMonth(Date);
    }
    return Date;
}
stDate DecreaseDateByOneYear(stDate Date)
{
    Date.Year--;
    short NumberOfDay = NumberOfDays(Date.Year, Date.Month);
    if (Date.Day > NumberOfDay)
    {
        Date.Day = NumberOfDay;
    }
    return Date;
}
stDate DecreaseDateByXYear(stDate Date, int Year)
{
    Date.Year -= Year;
    short NumberOfDay = NumberOfDays(Date.Year, Date.Month);
    if (Date.Day > NumberOfDay)
    {
        Date.Day = NumberOfDay;
    }
    return Date;
}
stDate DecreaseDateByXYearFaster(stDate Date, int Years)
{
   
    return DecreaseDateByXYear(Date,Years);
}
stDate DecreaseDateByOneDecade(stDate Date)
{
    return DecreaseDateByXYear(Date, 10);
}
stDate DecreaseDateByXDecade(stDate Date, int Decade)
{
    return DecreaseDateByXYear(Date, Decade * 10);
}
short Dayorder(stDate Date)
{
    return DayOrder(Date.Day, Date.Month, Date.Year);
}
bool IsItEndOfWeek(stDate Date)
{
    return (DayOrder(Date.Day,Date.Month,Date.Year)==6);
}
bool IsWeekEnd(stDate Date)
{
    short DayIndex = DayOrder(Date.Day, Date.Month, Date.Year);
    return (DayIndex==5||DayIndex==6);
}
bool IsBussinessDay(stDate Date)
{
    return !IsWeekEnd(Date);
}
short DaysUntilEndOfWeek(stDate Date)
{
    short DayIndex = DayOrder(Date.Day, Date.Month, Date.Year);

    return 6 - DayIndex;
}
short DaysUntilEndOfMonth(stDate Date)
{
    stDate EndOfMonthDate;
    EndOfMonthDate.Day = NumberOfDays(Date.Year, Date.Month);
    EndOfMonthDate.Month = Date.Month;
    EndOfMonthDate.Year = Date.Year;

    return DiffrentOfDate1AndDate2(Date, EndOfMonthDate, true);

}
short DaysUntilEndOfYear(stDate Date)
{
    stDate EndOfYearDate;
    EndOfYearDate.Day = 31;
    EndOfYearDate.Month = 12;
    EndOfYearDate.Year = Date.Year;

    return DiffrentOfDate1AndDate2(Date, EndOfYearDate, true);

}
short CalculateVacationDays(stDate Date, stDate Date2)
{

    int VacationDayCount = 0;
    while (IsDate1BeforeDate2(Date, Date2))
    {
        if (IsBussinessDay(Date))
            VacationDayCount++;

        Date = IncreaseByOneDay(Date);
    }
    return VacationDayCount;
}
stDate CalculateVacationReturnDate(stDate Date,short VacationDays)
{
    short WeekEndCounter = 0;
    while (IsWeekEnd(Date))
    {
        Date = IncreaseByOneDay(Date);
    }
    for (short i = 1;i <= VacationDays + WeekEndCounter;i++)
    {
        if (IsWeekEnd(Date))
        {
            WeekEndCounter++;
        }
        Date = IncreaseByOneDay(Date);
    }
    while (IsWeekEnd(Date))
    {
        Date = IncreaseByOneDay(Date);

    }
    return Date;
}
enum EnDate{Befor=-1,Equal=0,After=1};
short CompareDates(stDate Date1, stDate Date2)
{
    if (IsDate1BeforeDate2(Date1, Date2))
    {
        return   EnDate::Befor;
    }
    if (IsEquvalant(Date1, Date2))
    {
        return  EnDate::Equal;
    }

    return  EnDate::After;
}
bool IsOverLapDates(stPeriod Period, stPeriod Period2)
{
    if (
        CompareDates(Period2.EndDate, Period.StartDate) == EnDate::Befor
        || CompareDates(Period2.StartDate, Period.EndDate) == EnDate::After
        )
        return false;
    else
        return true;
}
stPeriod ReadPeriod()
{
    stPeriod Period;
    cout << "\nEnter Start Dates : \n";
    Period.StartDate = ReadFullDate();
    cout << "\nEnter End Dates : \n";
    Period.EndDate = ReadFullDate();
    return Period;
}
int PeriodLengthInDays(stPeriod Period, bool IncludEndDate = false)
{
    return DiffrentOfDate1AndDate2(Period.StartDate, Period.EndDate, IncludEndDate);
}
bool IsDateWithinPeriod(stDate Date, stPeriod Period)
{
    return !(CompareDates(Date, Period.StartDate) == EnDate::Befor)
        || (CompareDates(Date, Period.EndDate) == EnDate::After);
}
int CountOverLapdays(stPeriod Period1, stPeriod Period2)
{
    int Period1Length = PeriodLengthInDays(Period1, true);;
    int Period2Length = PeriodLengthInDays(Period2, true);;
    int OverLapDays = 0;
    if (!IsOverLapDates(Period1, Period2))
        return 0;

    if (Period1Length < Period2Length)
    {
        while (IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate))
        {
            if (IsDateWithinPeriod(Period1.StartDate, Period2))
                OverLapDays++;
                Period1.StartDate = IncreaseByOneDay(Period1.StartDate);
        }
    }
    else
    {
        while (IsDate1BeforeDate2(Period2.StartDate, Period2.EndDate))
        {
            if (IsDateWithinPeriod(Period2.StartDate, Period1))
                OverLapDays++;
            Period2.StartDate = IncreaseByOneDay(Period2.StartDate);
        }
    }
    return OverLapDays;
}
bool IsValidDate(stDate Date)
{
    if (Date.Day < 1 || Date.Day>31)
        return false;
    if (Date.Month < 1 || Date.Month>12)
        return false;
    if (Date.Month == 2)
    {
        if (Leapyear(Date.Year))
        {
            if (Date.Day > 29)
                return false;
        }
        else
        {
            if (Date.Day > 28)
                return false;
        }
    }
        short DaysInMonth=(NumberOfDays(Date.Year, Date.Month));

        if (Date.Day > DaysInMonth)
        return false;
        

        return true;
    }
stDate StringToDate(string DateSting)
{
    stDate Date;
    vector<string>VDate;
    VDate = SplitString(DateSting, "/");
    
    Date.Day = stoi(VDate[0]);
    Date.Month = stoi(VDate[1]);
    Date.Year = stoi(VDate[2]);

    return Date;
}
string DateToString(stDate Date)
{
    return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
}
string ReadText()
{
    string Text;
    cout << "Enter Text : ";
    getline(cin >> ws, Text);
    return Text;
}
string FromatDate(stDate Date,string DateFormat="dd/mm/yyyy")
{
    string FormatDateString = "";
    FormatDateString = ReplaceWordInString(DateFormat, "dd", to_string(Date.Day));
    FormatDateString = ReplaceWordInString(FormatDateString, "mm", to_string(Date.Month));
    FormatDateString = ReplaceWordInString(FormatDateString, "yyyy", to_string(Date.Year));

    return FormatDateString;

}
int main()
{
        string Text = ReadText();
        cout << endl;

        stDate Date = StringToDate(Text);

        cout << "\n" << FromatDate(Date) << "\n";

        cout << "\n" << FromatDate(Date,"yyyy/dd/mm") << "\n";
        cout << "\n" << FromatDate(Date,"mm/dd/yyyy") << "\n";
        cout << "\n" << FromatDate(Date,"mm-dd-yyyy") << "\n";
        cout << "\n" << FromatDate(Date,"dd-mm-yyyy") << "\n";
        cout << "\n" << FromatDate(Date,"day:dd , month:mm , year:yyyy") << "\n";


        return 0;
    
}
