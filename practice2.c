//�e�{�쵲��C
//���ϥΪ̼��g�@���쵲��C�\��]�t,�s�W,�R��,�ק�,�L�X,����
//�g�@�ӥ[�J�����
//�g�@�ӧR�������
//�g�@�ӭק諸���
//�g�@�ӦL�X�����
//�g�@�Ӥ��઺���
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//�禡���쫬�ŧi
void insert(void); //�[�J
void del(void);
void modify(void);
void display(void);
void processing(void);
void reverse(void);

//�ŧi�@�Ӹ`�I���ҪO
struct Node {
	long int id;
	char name[10];
	double score;
	struct Node *next; //�ŧi���c���� 
}; 
//�w�q�H�U�����c�����ܼ�
struct Node *head,*prev,*current,*pNode,temp,*p;

//�w�q�@���VFILE������
FILE *fptr;

int main()
{
	head=(struct Node*)malloc(sizeof(struct Node)); //���o���c�Ҧ����줸��,�æ^�Ƕ}�Ŷ��Ĥ@�Ӧ줸�զ�}
	head->next=NULL; //�Ĥ@�ӪŶ���}�ȮɨS�����
	
	//�Q�Τ@��氵��ܱ���
	int choice;
	do
	{
		printf("�쵲��C�����\n");
		printf("1.�[�J�@�`�I\n");
		printf("2.�R���@�`�I\n");
		printf("3.�ק�@�`�I\n");
		printf("4.��ܩҦ��`�I\n");
		printf("5.�����C\n");
		printf("6.����\n");
		printf("�п��\n");
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
		       printf("�{������");
		       exit(0);
		    default:
		       printf("��J���~,�Э��s��J:");
		}
		printf("\n");
	} while(choice!=6);
	getchar();
	system("pause");
	return 0;
 } 
//�[�J�@�`�I
void insert(void)
{
    //�Q��malloc()�禡���t�O���鵹n1
	pNode=malloc(sizeof(struct Node)); 
	printf("\n�п�JID:");
	scanf("%ld",&pNode->id);
	printf("\n�п�J�m�W:");
	scanf("%s",pNode->name);
	printf("�п�J����:");
	scanf("%lf",&pNode->score);
	
	//�[�J�@�`�I���쵲��C
	current=head->next; //�@�}�l�S�����
	prev=head; //��C�e�� 
	//���P�_�쵲�C�O�_����
	if(current==NULL) {
		head->next=pNode; //�p�G����,�[�J����J�����
		pNode->next=NULL; //��^�S���ƾ� 
	} 
	//�Y���O�Ū�,�h��Ʒ���m�[�J���쵲��C
	else {
		while(current!=NULL&&(pNode->score<current->score)) {
			prev=current;
			current=current->next;
		}
		prev->next=pNode;
		pNode->next=current;
	} 
} 
//�R���`�I
void del(void)
{
	long int deleteID;
	//�Ncurrent���Ы��Vhead���U�@�Ӹ`�I
	current=head->next;
	prev=head;
	//���P�_�쵲��C�O�_����
	if(current!=NULL) {
		//�Y���O�Ū�,�h��M���R�����`�I
		printf("\n�п�J���R����ID:");
		scanf("%ld",&deleteID);
		//��M���R�����`�I
		while((current!=NULL)&&current->id!=deleteID) {
			prev=current; //�R���W�@�Ӹ`�I 
			current=current->next; //�R�����`�I 
		} 
		//�Y���,�h�N�L�R��
		if(current!=NULL) {
			prev->next=current->next;
			current->next=NULL;
			printf("ID:%ld�w�R��\n",current->id);
			free(current);
		} 
		//�Y�S�����,�h��X�䤣����R���`�I���T��
		else {
			printf("\n�䤣����R�����`�I\n");
		} 
	} 
	//�Y�O�Ū�,�h��X�쵲��C�O�Ū��T��
	else {
		printf("�쵲��C�O�Ū�\n");
	} 
} 
//�ק�Y�@�`�I
void modify()
{
	struct Node *temp;
	long int modifyID; //�ŧi�ק�`�I�ܼ�
	double modifyScore; 
	int flag=0;
	printf("�п�J���ק�`�I��ID:");
	scanf("%ld",&modifyID);
	current=head->next;
	prev=head; 
	
	//��M���ק諸�`�I 
	while(current!=NULL) {
		if(current->id==modifyID) {
		   printf("�ثe���ק諸�`�I��Ʀp�U:\n");
		   printf("%%6ld %10s %8.1f\n\n",current->id,
		                   current->name,current->score);
		   printf("�п�J���ק諸����:");
		   scanf("%lf",&modifyScore);
		   current->score=modifyScore; //���Ƥ@�ˤ~�|�ק� 
		   flag=1;
		   break;
		}
		else {
			prev=current;
			current=current->next;
		}
	}
	//�P�_�O�_�������ק諸�`�I
	if(flag=0) {  
	  //�Ncurrent���`�I���w��temp
	  temp=current;
	  prev->next=current->next;
	  //�Ntemp�`�I�[�J���쵲��C 
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
		printf("�䤣����ק諸�`�I\n");
	}
}
//����쵲��C���Ҧ��`�I���
void display(void)
{
	//�L�X�쵲��C�Ҧ��`�I�����
	current=head->next;
	
	//�˵��쵲��C�O�_����
	if(current!=NULL) {
		printf("\n%6s %10s %8s\n","ID","Name","Score");
		while(current!=NULL) {
			printf("%6ld %10s %8.1f\n",current->id,
			               current->name,current->score);
			//�N���в���U�@�Ӹ`�I
			current=current->next; //�C�@��next���O�N��@��node�`�I��� 
		}
	} 
	//�Y�O�Ū�,�h��X��C�L���
	else {
		printf("�쵲��C�L���...");
	} 
} 
void reverse(void)
{
	p=head->next; //�@�}�l�����Vp����C�}�Y 
	current=NULL;
	while(p!=NULL) {
		prev=current;
		current=p;
		p=p->next;
		current->next=prev;
	}
	head->next=current;
}
