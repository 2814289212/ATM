#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Account
{
	char password[7];
	char username[19];
	float money;
	struct Account* next;
};
typedef struct Account Account;

int language;//1-Chinese,2-English,3-Rich

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
			fscanf_s(fp, "%s %s\n", newNode->username,100, newNode->password,100);

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

void printLinkedList()
{
	Account* curP = head;
	while (curP != NULL)
	{
		printf("%s\t%s\t%f\t\n", curP->username, curP->password,  curP->money);
		curP = curP->next;
	}
}

void saveData()
{
	FILE* fp = fopen("D:/demo2/atm.txt", "w");
	if (fp != NULL)
	{
		Account* curP = head;
		while (curP != NULL)
		{
			fprintf(fp, "%s\t%s\t%f\t\n",curP->username, curP->password,  curP->money);
			curP = curP->next;
		}
		fclose(fp);
	}
}



void signUp()
{
	

	printf("请输入密码：\n");
	scanf_s("%s", a.password,7);

	printf("请输入账号：\n");
	scanf_s("%s", a.username,19);

	a.money = 0.0f;

	printf("创建成功！\n");
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
	printf("请输入旧密码：");
	char oldPassword[100];
	scanf_s("%s", oldPassword,100);
	if (strcmp(oldPassword, curAccount->password) == 0)
	{
		printf("请输入新密码：");
		while (1)
		{
			scanf_s("%s", curAccount->password,100);
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
		scanf_s("%s", a.password,19);

		if (findAccount(a))
		{
			printf("登录成功！\n");
			updatePassword();
			break;
		}
		else
		{
			printf("登录失败！\n");
		}
	}
}


void showMenu()
{
	if (language == 1)
	{
		printf("登录，请按1\n");
		printf("开户，请按2\n");
		printf("退出，请按3\n");
	}
	else if (language == 2)
	{
		printf("Sign in, press 1\n");
		printf("Sign up, press 2\n");
		printf("Sign out, press 3\n");
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



int main()
{
	loadData();


	printf("中文服务，按1\n");
	printf("English Service，Press 2\n");
	printf("一夜暴富，按3\n");

	scanf_s("%d", &language);
	showMenu();

	signUp();

	printLinkedList();
	
	signIn();

	saveData();

	return 0;
}
