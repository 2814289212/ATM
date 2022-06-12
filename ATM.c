#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
void homePage();
struct Transaction
{
	char username[100];
	time_t timestamp;
	int type;//0-取款，1-存款
	int amount;

	struct Transaction* next;
};
typedef struct Transaction Transaction;

//交易记录信息链表 
Transaction* tHead = NULL;
Transaction* tTail = NULL;


struct Account
{
	char password[7];
	char username[19];
	int money;
	struct Account* next;
};
typedef struct Account Account;

int language;
Account a;

typedef struct Account Account;

Account* head = NULL;//指向头结点 
Account* tail = NULL;//指向尾结点 
Account* curAccount = NULL;//记录当前账户 


//加载成功返回1，否则返回0 
void loadData()
{
	FILE* fp = fopen("D:/demo2/atm.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			//创建结点
			Account* newNode = (Account*)malloc(sizeof(Account));
			if (newNode == NULL) {
				exit(-1);
			}//判断malloc申请空间是否成功，消除警告

			//结点初始化
			newNode->next = NULL;
			fscanf_s(fp, "%s %s %d\n", newNode->username,19, newNode->password,7,&newNode->money);

			//添加结点到链表
			if (head == NULL)
			{
				head = newNode;
				tail = newNode;
			}
			else
			{
				tail->next = newNode;
				tail = newNode;
			}
		}
		fclose(fp);
	}
}

void drawMoney()
{
	system("cls");
	printf("-	取款>1		返回>2	-\n");
		
	int n;
	scanf_s("%d",&n);
	switch (n)
	{
	case 1:
			printf("请输入取款金额：");
			int money;
			while (1)
			{
				scanf_s("%d", &money);
				if ((money % 100) != 0)
					printf("请整百取款，重新输入：\n");
				else
					break;

			}
			

			//验证金额
			if (curAccount->money >= money)
			{
				printf("取款成功！\n");
				curAccount->money -= money;

				//产生交易记录...	

				//创建结点
				Transaction* newNode = (Transaction*)malloc(sizeof(Transaction));
				if (newNode == NULL) {
					exit(-1);
				}//判断malloc申请空间是否成功，消除警告
				//结点初始化
				newNode->next = NULL;
				strcpy(newNode->username, curAccount->username);
				newNode->timestamp = time(NULL);
				newNode->type = 0;
				newNode->amount = money;

				//添加结点到链表
				if (tHead == NULL)
				{
					tHead = newNode;
					tTail = newNode;
				}
				else
				{
					tTail->next = newNode;
					tTail = newNode;
				}
			}
			else
			{
				printf("余额不足！\n");
			}
			system("pause");
	case 2: homePage(); break;
	default:
		break;
	}
	
}

void transfer() {
	system("cls");
	FILE* fp = fopen("D:/demo2/atm.txt", "r+");
	if (fp == NULL)	//无该条件判断将会出现警告Warning C6387
		exit(-1);
	int money;
	char id[7] = {"\0"};
	Account* curp=head;
	

	
	printf("\n\n\t\t请输入转账人的用户名：");
	scanf_s("%s", &id,7);
	while (curp!=NULL)
	{
	
	
		if (strcmp(id,curp->username) == 0) 
		{
			printf("\n\n\t\t请输入要转账的金额：");
			scanf_s("%d", &money);
			printf("\n\n\t\t请确认数目：%d", money);
			curp->money += money;
			curAccount->money -= money;
			printf("\n\n\n转账成功");
			fprintf(fp, "%s\t%s\t%d\n", curAccount->username, curAccount->password,curAccount->money);
			fclose(fp);
		}
		curp =curp-> next;
		
	}
	system("pause");
	homePage();
}


void saveMoney()
{
	system("cls");
	printf("-	存款>1		返回>2	-\n");

	int n;
	scanf_s("%d", &n);
	switch (n)
	{
	case 1:
			printf("请输入存款金额：");
			int money;
			while (1)
			{
				scanf_s("%d", &money);
				if ((money % 100) != 0)
					printf("请整百存款，重新输入：\n");
				else
					break;

			}
			printf("存款成功！\n");
			curAccount->money += money;

			//产生交易记录...	
			system("pause");
	case 2: homePage(); break;
	default:
		break;
	}
	
}

void esc()
{
	void saveData();
	saveData();
	exit(0);
}

void enquiryService()
{
	system("cls");
	printf("-	查询服务>1		返回>2	-\n");
	
	int n;
	scanf_s("%d", &n);
	switch (n)
	{
	case 1:printf("%s\t%s\t%d\t\n", curAccount->username, curAccount->password, curAccount->money);
		   system("pause");
	case 2:homePage(); break;
	default:
		break;
	}
	

}

void printLinkedList()
{
	Account* curP = head;
	while (curP != NULL)
	{
		printf("%s\t%s\t%d\t\n", curP->username, curP->password,  curP->money);
		curP = curP->next;
	}
}



void signUp()
{
	void showMenu();
	Account* newNode = (Account*)malloc(sizeof(Account));
	if (newNode == NULL) {
		exit(-1);
	}//判断malloc申请空间是否成功，消除警告
	newNode->next = NULL;
	printf("请输入账号：\n");
	scanf_s("%s", newNode->username,19);

	printf("请输入密码：\n");
	scanf_s("%s", newNode->password,7);
	newNode->money = 0;
	tail->next = newNode;
	tail = newNode;
	printf("注册成功！\n");
	showMenu();

}


//找到返回1，否则返回0 
int findAccount(Account a)
{
	Account* curp = head;
	while (curp != NULL)
	{
		if ((strcmp(curp->username, a.username) == 0) && (strcmp(curp->password, a.password) == 0))
		{
			curAccount = curp;
			return 1;
		}
		curp = curp->next;
	}
	return 0;
}
void updatePassword()
{

	system("cls");
	printf("-	更改密码>1		返回>2	-\n");
	
	int n;
	scanf_s("%d", &n);
	switch (n)
	{
	case 1:
			printf("请输入旧密码：");
			char oldPassword[7] = { "\0" };
			scanf_s("%s", oldPassword, 7);
			if (strcmp(oldPassword, curAccount->password) == 0)
			{
				printf("请输入新密码：");
				while (1)
				{
					scanf_s("%s", curAccount->password, 7);
					if (strcmp(oldPassword, curAccount->password) == 0)
					{
						printf("新旧密码不能一样!\n");
						printf("重新输入!\n");
					}
					else
						break;
				}
				printf("修改成功！\n");

			}
			else
			{
				printf("密码错误！不能修改！\n");
			}
			system("pause");
	case 2:	homePage(); break;
	default:
		break;
	}
	

}


void signIn()
{

	int i;
	for (i = 0; i < 3; i++)
	{
		Account a;
		printf("请输入账号：");
		scanf_s("%s", a.username,19);

		printf("请输入密码：");
		scanf_s("%s", a.password,7);

		if (findAccount(a))
		{
			printf("登录成功！\n");
			homePage();
		}
		else
		{
			printf("登录失败！\n");
		}
	}
	Account* node=head;
	curAccount = node;

}


void showMenu()
{
	system("cls");
	if (language == 1)
	{
		printf("\t\t||------------------------------||\n");
		printf("\t\t||	    登录>1		||\n");
		printf("\t\t||	    开户>2		||\n");
		printf("\t\t||	    退出>3		||\n");
		printf("\t\t||------------------------------||\n");
	}
	else if (language == 2)
	{
		printf("-	Sign in> 1	-\n");
		printf("-	Sign up> 2	-\n");
		printf("-	Sign out> 3	-\n");
	}
	int n;
	scanf_s("%d", &n);
	if (n == 1)
	{
		signIn();
	}
	else if (n == 2)
	{
		signUp();
	}
	else if (n == 3)
	{
		return;
	}
}

//加载成功返回1，否则返回0 

void saveData()
{
	FILE* fp = fopen("D:/demo2/atm.txt", "w");
	if (fp != NULL)
	{
		Account* curP = head;
		while (curP != NULL)
		{
			fprintf(fp, "%s\t%s\t%d\n",curP->username, curP->password,  curP->money);
			curP = curP->next;
		}
		fclose(fp);
	}
}

void homePage()
{
	system("cls");
	printf("\t\t||--------------------------------------||\n");
	printf("\t\t||	取款>1			存款>2	||\n");
	printf("\t\t||	查询服务>3		转账>4	||\n");
	printf("\t\t||	更改密码>4		退出>6	||\n");
	printf("\t\t||--------------------------------------||\n");
	
	
	int n;
	scanf_s("%d",&n);
	switch (n)
	{
	case 1: drawMoney(); break;
	case 2: saveMoney(); break;
	case 4:transfer(curAccount); break;
	case 3: enquiryService(); break;
	case 5: updatePassword(); break;
	case 6: esc(); break;
	default:
		break;
	}
}


int main()
{
	loadData();
	printf("\t\t||-----------ATM服务------------||\n");
	printf("\t\t||	   中文服务>1		||\n");
	printf("\t\t||	English Service>2	||\n");
	printf("\t\t||------------------------------||\n");
	scanf_s("%d", &language);
	showMenu();
	saveData();
	return 0;
}
