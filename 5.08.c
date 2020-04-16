/*
Ćwiczenie 5.8. W funkcjach day_of_year i month_day nie ma żadnego sprawdzania 
poprawności danych. Napraw tę usterkę: 
*/
#include <stdio.h>

int day_of_year(int year, int day, int month);
int month_day(int year, int yearday, int *pmonth, int *pday);

int main(void)
{
    int day, month;
    printf("09.04.2020 is %d day of year 2020\n", day_of_year(2020, 9, 4));
    month_day(2020, 100, &month, &day);
    printf("100's yearday in 2020 is in %d %d\n", day, month);
    return 0;
}

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int year, int day, int month)
{
    char leap;

    if (year < 1)
        return -1;
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    if (month < 1 || month > 12 || day < 1 || day > daytab[leap][month])
        return -1;
    for (int i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    if (year < 1)
    {
        *pmonth = -1, *pday = -1;
        return 0;
    }
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    if (yearday < 1 || (!leap && yearday > 365) || (leap && yearday > 366))
    {
        *pmonth = -1, *pday = -1;
        return 0;
    }
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i, *pday = yearday;
    return 1;
}