#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<conio.h>

struct Transaction
{
	char username[100];
	time_t timestamp;//时间戳 
	int type;//交易类型 0-取钱，1-存钱
	float amount;//数额 

	struct Transaction* next;
};
typedef struct Transaction TR;

//交易记录信息链表 
TR* tHead = NULL;
TR* tTail = NULL;
TR* Tr = NULL;


struct Account
{
	char password[7];
	char username[19];
	float money;
	struct Account* next;
};
typedef struct Account Account;

int language;
Account a;

typedef struct Account Account;

Account* head = NULL;//指向头结点 
Account* tail = NULL;//指向尾结点 
Account* curAccount = NULL;//记录当前账户 
void homePage();
void transfer();


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
			if (newNode == NULL) 
			{
				exit(-1);
			}//判断malloc申请空间是否成功，消除警告

			//结点初始化
			newNode->next = NULL;
			fscanf_s(fp, "%s %s %f\n", newNode->username,19, newNode->password,7,&newNode->money);

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

void loadDataTR()
{
	FILE* fp = fopen("D:/demo2/Tatm.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			//创建结点
			TR* Node = (TR*)malloc(sizeof(TR));
			if (Node == NULL)
			{
				exit(-1);
			}//判断malloc申请空间是否成功，消除警告

			//结点初始化
			Node->next = NULL;
			fscanf_s(fp, "%s %d %f\n", Node->username, 19, & Node->type, &Node->amount);

			//添加结点到链表
			if (tHead == NULL)
			{
				tHead = Node;
				tTail = Node;
			}
			else
			{
				tTail->next = Node;
				tTail =Node;
			}
		}
		fclose(fp);
	}
}




void saveTR()
{
	FILE* fp = fopen("D:/demo2/Tatm.txt", "w");
	TR* curP = tHead;
	while (curP != NULL)
	{
		fprintf(fp, "%s\t\t%d\t %f\n", curP->username,curP->type, curP->amount);
		curP = curP->next;
	}
	fclose(fp);
}

void findeTR(Account *a)
{
	TR* curP = tHead;
	system("cls");
	printf("\t\t-	交易记录>1		返回>2	-\n");

	int n;
	scanf_s("%d", &n);
	switch (n)
	{
	case 1:
			while (curP != NULL)
			{
				if (strcmp(curP->username, a->username) == 0)
				{
					printf("%s\t\t%d\t%f\t\n\n", curP->username,curP->type, curP->amount);
				}
				curP = curP->next;
			}
			system("pause");
	case 2:homePage(); break;
	default:
		break;
	}
	
}

void drawMoney()
{
	system("cls");
	printf("\t\t-	取款>1		返回>2	-\n");
		
	int n;
	scanf_s("%d",&n);
	switch (n)
	{
	case 1:
			printf("\t\t请输入取款金额：");
			float money;
			while (1)
			{
				scanf_s("%f", &money);
				if (((int)money % 100) != 0)
					printf("\n\t\t请整百取款，重新输入：\n");
				else
					break;

			}
			

			//验证金额
			if (curAccount->money >= money)
			{
				printf("\t\t取款成功！\n");
				curAccount->money -= money;

				//产生交易记录...	
				TR* newNode = (TR*)malloc(sizeof(TR));
				if (newNode == NULL)
				{
					exit(-1);
				}//判断malloc申请空间是否成功，消除警告
				newNode->next = NULL;
				strcpy(newNode->username, curAccount->username);
				newNode->type =0;
				newNode->amount = money;
				newNode->timestamp = time(NULL);

				
				//结点初始化

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
				printf("\t\t余额不足！\n");
			}
			saveTR();
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
	float money;
	char id[7] = {"\0"};
	Account* curp=head;
	

	printf("\t\t-	转账>1		返回>2	-\n");
	int n;
	scanf_s("%d",&n);
	system("cls");
	switch (n)
	{
	case 1:
		printf("\n\n\t\t请输入转账人的用户名：");
		scanf_s("%s", &id, 7);
		while (curp != NULL)
		{


			if (strcmp(id, curp->username) == 0)
			{
				printf("\n\n\t\t请输入要转账的金额：");
				scanf_s("%f", &money);
				if (curAccount->money >= money)
				{
					printf("\n\n\t\t请确认数目：%f", money);
					system("pause");
					curp->money += money;
					curAccount->money -= money;
					printf("\n\n\n转账成功!\n");
					fprintf(fp, "%s\t%s\t%f\n", curAccount->username, curAccount->password, curAccount->money);
					curAccount->money -= money;

					//产生交易记录...	

					//创建结点
					TR* newNode = (TR*)malloc(sizeof(TR));
					if (newNode == NULL)
					{
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
					printf("\t\t余额不足！\n\n\n");
					system("pause");
					transfer();
				}


				fclose(fp);
			}
			curp = curp->next;

		}
		saveTR();
		system("pause");
	case 2:homePage();
	default:
		break;
	}
	
	
	
}


void saveMoney()
{
	system("cls");
	printf("\t\t-	存款>1		返回>2	-\n");

	int n;
	scanf_s("%d", &n);
	switch (n)
	{
	case 1:
			printf("\t\t请输入存款金额：");
			float money;
			while (1)
			{
				scanf_s("%f", &money);
				if (((int)money % 100) != 0)
					printf("\t\t请整百存款，重新输入：\n\n\n");
				else
					break;

			}
			printf("\t\t存款成功！\n\n\n");
			curAccount->money += money;

						//产生交易记录...	
			TR* newNode = (TR*)malloc(sizeof(TR));
			if (newNode == NULL)
			{
				exit(-1);
			}//判断malloc申请空间是否成功，消除警告
			newNode->next = NULL;
			strcpy(newNode->username, curAccount->username);
			newNode->type = 1;
			newNode->amount = money;
			newNode->timestamp = time(NULL);

			//结点初始化

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
			saveTR();
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
	printf("\t\t-	余额查询>1		返回>2	-\n");
	
	int n;
	scanf_s("%d", &n);
	switch (n)
	{
	case 1:printf("%s\t\t%f\t\n", curAccount->username, curAccount->money);
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
		printf("%s\t%s\t%f\t\n", curP->username, curP->password,  curP->money);
		curP = curP->next;
	}
}



void signUp()
{
	void showMenu();
	Account* newNode = (Account*)malloc(sizeof(Account));
	if (newNode == NULL)
	{
		exit(-1);
	}//判断malloc申请空间是否成功，消除警告
	newNode->next = NULL;
	printf("\t\t请输入账号：\n");
	scanf_s("%s", newNode->username,19);

	printf("\t\t请输入密码：\n");
	scanf_s("%s", newNode->password,7);
	newNode->money = 0.0;
	tail->next = newNode;
	tail = newNode;
	printf("\t\t注册成功！\n");
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
	printf("\t\t-	更改密码>1		返回>2	-\n");
	
	int n;
	scanf_s("%d", &n);
	switch (n)
	{
	case 1:
			printf("\t\t请输入旧密码：");
			char oldPassword[7] = { "\0" };
			scanf_s("%s", oldPassword, 7);
			if (strcmp(oldPassword, curAccount->password) == 0)
			{
				printf("\t\t请输入新密码：");
				while (1)
				{
					scanf_s("%s", curAccount->password, 7);
					if (strcmp(oldPassword, curAccount->password) == 0)
					{
						printf("\t\t新旧密码不能一样!\n");
						printf("\t\t重新输入!\n");
					}
					else
						break;
				}
				printf("\t\t修改成功！\n");

			}
			else
			{
				printf("\t\t密码错误！不能修改！\n");
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
		printf("\t\t\t请输入账号：");
		scanf_s("%s", a.username,19);

		printf("\t\t\t请输入密码：");
		scanf_s("%s", a.password,7);

		if (findAccount(a))
		{
			printf("\t\t\t登录成功！\n");
			homePage();
		}
		else
		{
			printf("\t\t\t登录失败！\n");
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
		esc();
		system("pause");

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
			fprintf(fp, "%s\t%s\t%f\n",curP->username, curP->password,  curP->money);
			curP = curP->next;
		}
		fclose(fp);
	}
}

void homePage()
{
	system("cls");
	printf("\t\t||--------------------------------------||\n");
	printf("\t\t||	取款>1		余额查询>4	||\n");
	printf("\t\t||	存款>2		更改密码>5	||\n");
	printf("\t\t||	转账>3		交易记录>6	||\n");
	printf("\t\t||	        		退出>7	||\n");
	printf("\t\t||--------------------------------------||\n");
	
	
	int n;
	scanf_s("%d",&n);
	switch (n)
	{
	case 1: drawMoney(); break;
	case 2: saveMoney(); break;
	case 3:transfer(curAccount); break;
	case 4: enquiryService(); break;
	case 5: updatePassword(); break;
	case 6: findeTR(curAccount); break;
	case 7: esc(); break;
	default:
		break;
	}
}


int main()
{
	loadData();
	loadDataTR();
	printf("\t\t||-----------ATM服务------------||\n");
	printf("\t\t||	   业务办理>1		||\n");
	printf("\t\t||	      退出>2		||\n");
	printf("\t\t||------------------------------||\n");
	scanf_s("%d", &language);
	showMenu();
	saveTR();
	saveData();
	return 0;
}
