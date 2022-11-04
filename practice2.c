//呈現鏈結串列
//讓使用者撰寫一個鏈結串列功能包含,新增,刪除,修改,印出,反轉
//寫一個加入的函數
//寫一個刪除的函數
//寫一個修改的函數
//寫一個印出的函數
//寫一個反轉的函數
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//函式的原型宣告
void insert(void); //加入
void del(void);
void modify(void);
void display(void);
void processing(void);
void reverse(void);

//宣告一個節點的模板
struct Node {
	long int id;
	char name[10];
	double score;
	struct Node *next; //宣告結構指標 
}; 
//定義以下的結構全域變數
struct Node *head,*prev,*current,*pNode,temp,*p;

//定義一指向FILE的指標
FILE *fptr;

int main()
{
	head=(struct Node*)malloc(sizeof(struct Node)); //取得結構所佔的位元組,並回傳開空間第一個位元組位址
	head->next=NULL; //第一個空間位址暫時沒有資料
	
	//利用一選單做選擇條件
	int choice;
	do
	{
		printf("鏈結串列的選單\n");
		printf("1.加入一節點\n");
		printf("2.刪除一節點\n");
		printf("3.修改一節點\n");
		printf("4.顯示所有節點\n");
		printf("5.反轉串列\n");
		printf("6.結束\n");
		printf("請選擇\n");
		scanf("%d",&choice);
		switch (choice)
		{
			case 1: 
			   insert();
			   break;
			case 2:
			   del();
			   break;
		    case 3:
		       modify();
		       break;
		    case 4:
		       display();
		       break;
		    case 5:
		       reverse();
		       break;
		    case 6:
		       printf("程式結束");
		       exit(0);
		    default:
		       printf("輸入錯誤,請重新輸入:");
		}
		printf("\n");
	} while(choice!=6);
	getchar();
	system("pause");
	return 0;
 } 
//加入一節點
void insert(void)
{
    //利用malloc()函式分配記憶體給n1
	pNode=malloc(sizeof(struct Node)); 
	printf("\n請輸入ID:");
	scanf("%ld",&pNode->id);
	printf("\n請輸入姓名:");
	scanf("%s",pNode->name);
	printf("請輸入分數:");
	scanf("%lf",&pNode->score);
	
	//加入一節點於鏈結串列
	current=head->next; //一開始沒有資料
	prev=head; //串列前端 
	//先判斷鏈結列是否為空
	if(current==NULL) {
		head->next=pNode; //如果為空,加入剛剛輸入的資料
		pNode->next=NULL; //改回沒有數據 
	} 
	//若不是空的,則找事當的位置加入於鏈結串列
	else {
		while(current!=NULL&&(pNode->score<current->score)) {
			prev=current;
			current=current->next;
		}
		prev->next=pNode;
		pNode->next=current;
	} 
} 
//刪除節點
void del(void)
{
	long int deleteID;
	//將current指標指向head的下一個節點
	current=head->next;
	prev=head;
	//先判斷鏈結串列是否為空
	if(current!=NULL) {
		//若不是空的,則找尋欲刪除的節點
		printf("\n請輸入欲刪除的ID:");
		scanf("%ld",&deleteID);
		//找尋欲刪除的節點
		while((current!=NULL)&&current->id!=deleteID) {
			prev=current; //刪除上一個節點 
			current=current->next; //刪除的節點 
		} 
		//若找到,則將他刪除
		if(current!=NULL) {
			prev->next=current->next;
			current->next=NULL;
			printf("ID:%ld已刪除\n",current->id);
			free(current);
		} 
		//若沒有找到,則輸出找不到欲刪除節點的訊息
		else {
			printf("\n找不到欲刪除的節點\n");
		} 
	} 
	//若是空的,則輸出鏈結串列是空的訊息
	else {
		printf("鏈結串列是空的\n");
	} 
} 
//修改某一節點
void modify()
{
	struct Node *temp;
	long int modifyID; //宣告修改節點變數
	double modifyScore; 
	int flag=0;
	printf("請輸入欲修改節點的ID:");
	scanf("%ld",&modifyID);
	current=head->next;
	prev=head; 
	
	//找尋欲修改的節點 
	while(current!=NULL) {
		if(current->id==modifyID) {
		   printf("目前欲修改的節點資料如下:\n");
		   printf("%%6ld %10s %8.1f\n\n",current->id,
		                   current->name,current->score);
		   printf("請輸入欲修改的分數:");
		   scanf("%lf",&modifyScore);
		   current->score=modifyScore; //分數一樣才會修改 
		   flag=1;
		   break;
		}
		else {
			prev=current;
			current=current->next;
		}
	}
	//判斷是否有找到欲修改的節點
	if(flag=0) {  
	  //將current的節點指定給temp
	  temp=current;
	  prev->next=current->next;
	  //將temp節點加入於鏈結串列 
	  current=head->next;
	  prev=head;
	  while((current!=NULL)&&
	        (temp->score<current->score)) {
	      prev=current;
		  current=current->next;  	
		}
		prev->next=temp;
		temp->next=current;
	} 
	else {
		printf("找不到欲修改的節點\n");
	}
}
//顯示鏈結串列的所有節點資料
void display(void)
{
	//印出鏈結串列所有節點的資料
	current=head->next;
	
	//檢視鏈結串列是否為空
	if(current!=NULL) {
		printf("\n%6s %10s %8s\n","ID","Name","Score");
		while(current!=NULL) {
			printf("%6ld %10s %8.1f\n",current->id,
			               current->name,current->score);
			//將指標移到下一個節點
			current=current->next; //每一個next都是代表一個node節點資料 
		}
	} 
	//若是空的,則輸出串列無資料
	else {
		printf("鏈結串列無資料...");
	} 
} 
void reverse(void)
{
	p=head->next; //一開始先指向p為串列開頭 
	current=NULL;
	while(p!=NULL) {
		prev=current;
		current=p;
		p=p->next;
		current->next=prev;
	}
	head->next=current;
}
