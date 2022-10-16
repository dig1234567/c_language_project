//用c語言寫出一個踩地雷遊戲
//程式分析寫一個初始化界面的函式 
//寫一個開始遊戲的函式 
//寫一個判斷當前的位子是否有炸彈的函式 
//寫一個判斷當前位子附近周圍的位置情況
//寫一個更新地圖的函式 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <time.h>
//定義全域變數
#define MAX_ROW 9
#define MAX_COL 9

#define DEFAULT 9

char show_map[MAX_ROW+2][MAX_COL+2];
char mine_map[MAX_ROW+2][MAX_COL+2];
//寫一個遊戲選端

int Menu()
{
	printf("------------");
	printf("1:開始遊戲");
	printf("0:結束遊戲");
	printf("------------");
	printf("請輸入遊戲選單選項");
	int choice;
	while(1)
	{
		scanf("%d",&choice);
		if(choice!=0&&choice!=1)
		{
			printf("你的輸入有誤請重新輸入:");
			continue;
		}
		break;
	}
	return choice;
 } 
void Init_Interface()
{
	int row,col;
	for(row=0;row<MAX_ROW+2;row++) {
		for(col=0;col<MAX_COL+2;col++) {
			show_map[row][col]='*'; //一開始是show_map因為還沒輸入要座標,先預設全部都是炸彈 
		}
	}
	for(col=0;col<MAX_COL+2;col++) {
		for(row=0;row<MAX_COL+2;row++) {
			mine_map[row][col]='0'; //要執行的座標必須初始化先預設全部都枚炸彈 
		}
	}
	int mine_count=DEFAULT; //先預設mine有9個炸彈
	while(mine_count>0) {
		row=rand()% MAX_ROW+1;
		col=rand()% MAX_COL+1; 
		if(mine_map[row][col]=='1') {
		      continue;
		}
		mine_count--;
		mine_map[row][col]='1';
	}
}
//列印初始化介面
void Print_Interface(char map[MAX_ROW+2][MAX_COL+2]) 
{
	int i,row,col; 
	printf("    ");
	for(col=1;col<MAX_COL;col++) {
		printf("%d ",col);
	}
	printf("\n  ");
	for(row=1;row<MAX_ROW;row++) {
		printf("--");
	}
	printf("\n  ");
	for(row=1;row<=MAX_ROW;row++) {
		printf("%02d |",row);
		for(col=1;col<=MAX_COL;col++) {
			printf("%c ",map[row][col]);
		}
		printf("\n");
	}
}
//寫一個統計周為雷數個數的函式
int Around_Mine_count(int row,int col)
{
	//假設輸入3 3 
	return (mine_map[row-1][col-1]-'0'
	       +mine_map[row-1][col]-'0'
	       +mine_map[row-1][col+1]-'0'
	       +mine_map[row][col-1]-'0'
		   +mine_map[row][col+1]-'0'
		   +mine_map[row+1][col-1]-'0'
		   +mine_map[row+1][col]-'0'
		   +mine_map[row+1][col+1]-'0');
 } 
//寫一個判斷位置是否有炸彈的函式
int No_mine(int row,int col)
{
	if(Around_Mine_count(row,col)==0)
	{
		return 1; //有雷 
	}
	return 0; 
} 
//寫一個掀開位置周圍空地的函式
void Open(int row,int col) 
{
	show_map[row-1][col-1]+Around_Mine_count(row-1,col-1);
	show_map[row-1][col]+Around_Mine_count(row-1,col);
	show_map[row-1][col+1]+Around_Mine_count(row-1,col+1);
	show_map[row][col-1]+Around_Mine_count(row,col-1);
	show_map[row][col+1]+Around_Mine_count(row,col+1);
	show_map[row+1][col-1]+Around_Mine_count(row+1,col-1);
	show_map[row+1][col]+Around_Mine_count(row+1,col);
	show_map[row+1][col+1]+Around_Mine_count(row+1,col+1); 
}
//寫一個判斷遊戲結束的函式
int Success_Sweep(char show_map[MAX_ROW+2][MAX_COL+2])
{
	int count=0;
	int row,col;
	for(row=1;row<=MAX_ROW;row++) {
		for(col=1;col<=MAX_COL;col++) {
			if(show_map[row][col]=='*') //判斷是否等於炸彈
			count++; 
		}
	}
	if(count==DEFAULT) {
		return 1; //炸彈全部清除, 
	}
	return 0;
 } 
//start game
void Startgame()
{
	while(1) {
		printf("請輸入你要掀開的座標");
		int row=0; //每次掀開座標,下一回都會歸0好讓使用者可重新輸入 
		int col=0;
		while(1) {
			scanf("%d%d",&row,&col);
			if(row<1||row>MAX_ROW||col<1||col>MAX_COL) {
				printf("你的輸入有誤,請重新輸入");
				continue;
			}
			if(show_map[row][col]!='*')
			{
				printf("該位置已經被掀開,請重新選擇!");
				continue;
			}
			break; //不管輸入錯誤,還是輸入的位置已被掀開,都會跳出上層while到重新輸入的地方 
		}
		//判斷該地方,是否有雷
		if(mine_map[row][col]=='1')
		{
			Print_Interface(mine_map);
			printf("該地方有雷,遊戲結束:");
			break;
	    }
	    if(No_mine(row,col))
	    {
	    	show_map[row][col]='0'; //無雷
			Open(row,col); 
		}
		show_map[row][col]='0'+Around_Mine_count(row,col);
		//判斷是否掀開所有空地
		if(Success_Sweep(show_map)==1)
		{
			Print_Interface(mine_map);
			printf("你已成功掃雷!");
			break;
		} 
		system("cls"); //清頻
		//更新地圖
		Print_Interface(show_map); 
	  }
} 
int main()
{
	if(Menu()==0) {
		exit(0); //如果回傳的是0,就結束遊戲,注意這裡的exit是強制結束,並不是回傳 
	}
	srand((unsigned int)time(NULL)); //讓每次炸彈都不一樣
	Init_Interface();
	Print_Interface(show_map);
	
	Startgame(); 
	
	system("pause");
	return 0;
}
