/*
author:ECNU_10234507025
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

short box[32][32], floors[32][32], mine[2048][2];
bool over = 1;
int size_l, size_c, num; // size:[1,30]

void Make();  // 生成雷
void Print(); // 输出当前情况
void Open();
void Lose(int x, int y);
void Win();

int main()
{
	Make();
	Print();
	while (over)
	{
		system("cls");
		Print();
		Open();
		Win();
	}
	Print();
	printf("\nPress any key to exit"); 
	getchar();
	getchar();
	return 0;
}

void Make()
{
	while (1)
	{
		printf("Please enter the number of rows and columns of the map (the maxium map is 30*30), separated by spaces:");
		scanf("%d%d", &size_l, &size_c);
		printf("Please enter the total number of mines:");
		scanf("%d", &num);
		if (num > size_l * size_c)
		{
			system("cls");
			printf("**ERROR:Illegal values!**\n");
		}
		else break;
	}
	int i, j, k, l;
	int sum = num, x, y;
	srand(time(NULL));
	while (sum)
	{
		x = rand() % size_l + 1;
		y = rand() % size_c + 1;
		if (box[x][y] != 9)
		{
			box[x][y] = 9;
			sum--;
		}
	}
	for (i = 1; i <= size_l; i++) // 计算全图box的数值
		for (j = 1; j <= size_c; j++)
			if (box[i][j] != 9)
				for (k = i - 1; k <= i + 1; k++)
					for (l = j - 1; l <= j + 1; l++)
						if (box[k][l] == 9)
							box[i][j]++;
}

void Print()
{
	int i, j;
	printf("  ");
	for (i = 1; i <= size_c; i++)
	{
		printf("   %2d", i);
	}
	printf("\n  ");
	for (i = 1; i <= size_c; i++)
	{
		printf("    v");
	}
	printf("\n");
	for (i = 1; i <= size_l; i++)
	{
		printf("\n");
		printf("%2d> ", i);
		for (j = 1; j <= size_c; j++)
		{
			if (floors[i][j])
			{
				if (box[i][j] > 0 && box[i][j] < 9)
					printf("\033[1;32;40m  %d  \033[0m", box[i][j]);
				else if (box[i][j] == 9)
					printf("\033[1;31;40m  X  \033[0m");
				else
					printf("     ");
			}
			else
				printf("  ?  ");
		}
		printf("\n");
	}
}

void Open()
{
	int i, j, k, l;
	int x, y;
	bool ok = 1;
	printf("\n\nPlease enter the coordinates (x,y) of the boxes you want to open, ");
	printf("separated by spaces between x and y:\n");
	scanf("%d%d", &x, &y);
	if (x > size_l || y > size_c) return;
	if (box[x][y] == 9)
	{
		Lose(x, y);
		return;
	}
	floors[x][y] = 2;
	while (ok)
	{
		ok = 0;
		for (i = 1; i <= size_l; i++)
		{
			for (j = 1; j <= size_c; j++)
			{
				if (floors[i][j] == 2)
				{
					floors[i][j] = 1;
					ok = 1;
					if (box[i][j] == 0)
					{
						for (k = i - 1; k <= i + 1; k++)
						{
							for (l = j - 1; l <= j + 1; l++)
							{
								if (floors[k][l] == 0)
								{
									floors[k][l] = 2;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Lose(int x, int y)
{
	int i, j;
	system("cls");
	printf("You click the mine in \033[1;31;40m(%d,%d)\033[0m. You lose.\n", x, y);
	for (i = 1; i <= size_l; i++)
	{
		for (j = 1; j <= size_c; j++)
		{
			floors[i][j] = 1;
		}
	}
	over = 0;
}

void Win()
{
	int i, j;
	int sum = 0;
	for (i = 1; i <= size_l; i++)
	{
		for (j = 1; j <= size_c; j++)
		{
			if (floors[i][j] == 0)
				sum++;
		}
	}
	if (sum == num)
	{
		over = 0;
		system("cls");
		printf("You win!!!\n");
		for (i = 1; i <= size_l; i++)
		{
			for (j = 1; j <= size_c; j++)
			{
				floors[i][j] = 1;
			}
		}
	}
}
