//��c�y���g�X�@�ӽ�a�p�C��
//�{�����R�g�@�Ӫ�l�Ƭɭ����禡 
//�g�@�Ӷ}�l�C�����禡 
//�g�@�ӧP�_��e����l�O�_�����u���禡 
//�g�@�ӧP�_��e��l����P�򪺦�m���p
//�g�@�ӧ�s�a�Ϫ��禡 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <time.h>
//�w�q�����ܼ�
#define MAX_ROW 9
#define MAX_COL 9

#define DEFAULT 9

char show_map[MAX_ROW+2][MAX_COL+2];
char mine_map[MAX_ROW+2][MAX_COL+2];
//�g�@�ӹC�����

int Menu()
{
	printf("------------");
	printf("1:�}�l�C��");
	printf("0:�����C��");
	printf("------------");
	printf("�п�J�C�����ﶵ");
	int choice;
	while(1)
	{
		scanf("%d",&choice);
		if(choice!=0&&choice!=1)
		{
			printf("�A����J���~�Э��s��J:");
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
			show_map[row][col]='*'; //�@�}�l�Oshow_map�]���٨S��J�n�y��,���w�]�������O���u 
		}
	}
	for(col=0;col<MAX_COL+2;col++) {
		for(row=0;row<MAX_COL+2;row++) {
			mine_map[row][col]='0'; //�n���檺�y�Х�����l�ƥ��w�]�������T���u 
		}
	}
	int mine_count=DEFAULT; //���w�]mine��9�Ӭ��u
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
//�C�L��l�Ƥ���
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
//�g�@�Ӳέp�P���p�ƭӼƪ��禡
int Around_Mine_count(int row,int col)
{
	//���]��J3 3 
	return (mine_map[row-1][col-1]-'0'
	       +mine_map[row-1][col]-'0'
	       +mine_map[row-1][col+1]-'0'
	       +mine_map[row][col-1]-'0'
		   +mine_map[row][col+1]-'0'
		   +mine_map[row+1][col-1]-'0'
		   +mine_map[row+1][col]-'0'
		   +mine_map[row+1][col+1]-'0');
 } 
//�g�@�ӧP�_��m�O�_�����u���禡
int No_mine(int row,int col)
{
	if(Around_Mine_count(row,col)==0)
	{
		return 1; //���p 
	}
	return 0; 
} 
//�g�@�ӱȶ}��m�P��Ŧa���禡
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
//�g�@�ӧP�_�C���������禡
int Success_Sweep(char show_map[MAX_ROW+2][MAX_COL+2])
{
	int count=0;
	int row,col;
	for(row=1;row<=MAX_ROW;row++) {
		for(col=1;col<=MAX_COL;col++) {
			if(show_map[row][col]=='*') //�P�_�O�_���󬵼u
			count++; 
		}
	}
	if(count==DEFAULT) {
		return 1; //���u�����M��, 
	}
	return 0;
 } 
//start game
void Startgame()
{
	while(1) {
		printf("�п�J�A�n�ȶ}���y��");
		int row=0; //�C���ȶ}�y��,�U�@�^���|�k0�n���ϥΪ̥i���s��J 
		int col=0;
		while(1) {
			scanf("%d%d",&row,&col);
			if(row<1||row>MAX_ROW||col<1||col>MAX_COL) {
				printf("�A����J���~,�Э��s��J");
				continue;
			}
			if(show_map[row][col]!='*')
			{
				printf("�Ӧ�m�w�g�Q�ȶ},�Э��s���!");
				continue;
			}
			break; //���޿�J���~,�٬O��J����m�w�Q�ȶ},���|���X�W�hwhile�쭫�s��J���a�� 
		}
		//�P�_�Ӧa��,�O�_���p
		if(mine_map[row][col]=='1')
		{
			Print_Interface(mine_map);
			printf("�Ӧa�観�p,�C������:");
			break;
	    }
	    if(No_mine(row,col))
	    {
	    	show_map[row][col]='0'; //�L�p
			Open(row,col); 
		}
		show_map[row][col]='0'+Around_Mine_count(row,col);
		//�P�_�O�_�ȶ}�Ҧ��Ŧa
		if(Success_Sweep(show_map)==1)
		{
			Print_Interface(mine_map);
			printf("�A�w���\���p!");
			break;
		} 
		system("cls"); //�M�W
		//��s�a��
		Print_Interface(show_map); 
	  }
} 
int main()
{
	if(Menu()==0) {
		exit(0); //�p�G�^�Ǫ��O0,�N�����C��,�`�N�o�̪�exit�O�j���,�ä��O�^�� 
	}
	srand((unsigned int)time(NULL)); //���C�����u�����@��
	Init_Interface();
	Print_Interface(show_map);
	
	Startgame(); 
	
	system("pause");
	return 0;
}
