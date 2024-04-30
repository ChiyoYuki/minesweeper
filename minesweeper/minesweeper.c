/*
author:ECNU_10234507025
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int box[32][32], floors[32][32];//box保存格子的类型，floor判断是否被打开
bool over = 1;//判断游戏是否结束
int size_l, size_c, num; // size:[1,30]

void Make();  // 生成雷
void Print(); // 输出当前情况
void Open();//打开格子
void Lose(int x, int y);//判定游戏失败 输出被点击的地雷坐标
void Win();//判断游戏是否满足胜利条件

int main()
{
	Make();
	Print();
	while (over)
	{
		#ifdef __WIN32
			system("cls");
		#endif
		#ifdef __linux__
			system("clear");
		#endif
		Print();
		Open();
		Win();
	}
	Print();
	printf("\nPress ENTER to exit"); 
	getchar();
	getchar();
	return 0;
}

void Make()
{
	while (1)//获取合法的输入数据
	{
		printf("Please enter the number of rows and columns of the map (the maxium map is 30*30), separated by spaces:");
		scanf("%d%d", &size_l, &size_c);
		printf("Please enter the total number of mines:");
		scanf("%d", &num);
		if (num > size_l * size_c)//判定雷数是否超过格子总数
		{
			#ifdef _WIN32
				system("cls");
			#endif
			#ifdef __linux__
				system("clear");
			#endif
			printf("**ERROR:Illegal values!**\n");
		}
		else break;
	}
	int i, j, k, l;
	int sum = num, x, y;
	srand(time(NULL));
	while (sum)//生成num个雷的随机坐标
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
	for (i = 1; i <= size_c; i++)//输出列坐标
	{
		printf("   %2d", i);
	}
	printf("\n  ");
	for (i = 1; i <= size_c; i++)//输出列坐标与第一行的分隔线
	{
		printf("    v");
	}
	printf("\n");
	for (i = 1; i <= size_l; i++)
	{
		//printf("\n");
		printf("%2d> ", i);//输出行坐标及分隔线
		for (j = 1; j <= size_c; j++)
		{
			//printf("  ");
			if (floors[i][j])
			{
				if (box[i][j] == 9)
					printf("\033[1;30;41m");//以粗体红色输出地雷
				else if (box[i][j] == 8)
					printf("\033[1;37m", box[i][j]);
				else if (box[i][j] == 7)
					printf("\033[1;30m", box[i][j]);
				else if (box[i][j] == 6)
					printf("\033[1;36m", box[i][j]);
				else if (box[i][j] == 5)
					printf("\033[1;33m", box[i][j]);
				else if (box[i][j] == 4)
					printf("\033[1;35m", box[i][j]);
				else if (box[i][j] == 3)
					printf("\033[1;31m", box[i][j]);
				else if (box[i][j] == 2)
					printf("\033[1;32m", box[i][j]);
				else if (box[i][j] == 1)
					printf("\033[1;34m", box[i][j]);
				
				if (box[i][j] == 0)
					printf("     ");//以空格代替0输出被打开的空格子
				else if (box[i][j]>0&&box[i][j]<9)
					printf("  %d  ",box[i][j]);
				else if (box[i][j] == 9)
					printf("  X  ");//以粗体红色输出地雷
				printf("\033[0m");
			}
			else
				printf("  ?  ");//输出未打开的格子
			//printf("  ");
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
	scanf("%d%d", &x, &y);//获取将要打开的格子坐标
	if (x > size_l || y > size_c) return;//如果超过地图范围，则返回主函数，主函数通过while实现重新输入
	if (box[x][y] == 9)//点击到了有地雷的格子，判定游戏失败
	{
		Lose(x, y);
		return;
	}
	floors[x][y] = 2;//以2表示周围格子待更新的打开格子
	while (ok)
	{
		ok = 0;
		for (i = 1; i <= size_l; i++)
		{
			for (j = 1; j <= size_c; j++)
			{
				if (floors[i][j] == 2)
				{
					floors[i][j] = 1;//以1表示周围格子已更新的打开格子
					ok = 1;
					if (box[i][j] == 0)//如果被标识为2的格子为空格子，则打开周围一周的格子
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
	#ifdef __WIN32
		system("cls");
	#endif
	#ifdef __linux__
		system("clear");
	#endif
	printf("You click the mine in \033[1;31m(%d,%d)\033[0m. You lose.\n", x, y);
	for (i = 1; i <= size_l; i++)//打开全图格子
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
	for (i = 1; i <= size_l; i++)//计算未打开格子的数目
	{
		for (j = 1; j <= size_c; j++)
		{
			if (floors[i][j] == 0)
				sum++;
		}
	}
	if (sum == num)//判定游戏胜利
	{
		over = 0;
		#ifdef __WIN32
			system("cls");
		#endif
		#ifdef __linux__
			system("clear");
		#endif
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
