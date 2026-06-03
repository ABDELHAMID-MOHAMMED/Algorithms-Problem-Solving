#pragma once
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