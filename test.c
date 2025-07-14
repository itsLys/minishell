#include <stdio.h>
#include <stdlib.h>

int doomcentury(int x)
{
	int result = 2;
	int siecle = (x/100) * 100;
	int i = siecle;
	int diff = 0;
	while (i%400)
	{
		i -= 100;
		diff++;
	}
	if (diff == 1)
		result = 0;
	else if (diff == 2)
		result = 5;
	else if (diff == 3)
		result = 3;
	return result;
}

int doomday(int x)
{
	int siecle = (x/100)* 100;
	int diff = (x - siecle);
	int w = diff / 4;
	int to_add = (diff + w)%7;
	return (doomcentury(x) + to_add)%7;
}

int other_months(int d, int doomdate, int doomday)
{
	int diff = doomdate - d;
	int result;
	result = ((doomday - diff%7)%7);
	return result;
}

int month(int y, int m, int d)
{
	int doom = doomday(y);
	int i = 0;
	int result = doom;
	int diff = m - d;
	if (m % 2 == 0 && m != 2)
		result = ((doom - diff%7)%7);
	else if (m == 1)
	{
		if (y%100 == 0 && y%400 == 0)
			result = other_months(d, 4, doom);
		else if (y%100 == 0 && y%400)
			result = other_months(d, 3, doom);
		else if (y%4 == 0)
			result = other_months(d, 4, doom);	
		else if (y%4)
			result = other_months(d, 3, doom);
	}
	else if (m == 2)
	{
		if (y%100 == 0 && y%400 == 0)
			result = other_months(d, 29, doom);
		else if (y%100 == 0 && y%400)
			result = other_months(d, 28, doom);
		else if (y%4 == 0)
			result = other_months(d, 29, doom);	
		else if (y%4)
			result = other_months(d, 28, doom);
	}
	else if (m == 3)
		result = other_months(d, 14, doom);
	else if (m == 5)
		result = other_months(d, m + 4, doom);
	else if (m == 7)
		result = other_months(d, m + 4, doom);	
	else if (m == 9)
		result = other_months(d, m - 4, doom);
	else if (m == 11)
		result = other_months(d, m - 4, doom);				
	return result;
}

int main (int ac, char **av)
{
	if (ac == 4)
	{
		char *tab[] = {"dimanche", "lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi"};
		int sol = month(atoi(av[3]), atoi(av[2]), atoi(av[1]));
		if (sol < 0)
			sol = 7 + sol;
		printf("%s\n", tab[sol%7]);
	}
	else
		printf("format invalid\n");
	return (0);	
}
