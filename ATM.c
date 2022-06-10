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

Account* head = NULL;//ָ��ͷ��� 
Account* tail = NULL;//ָ��β��� 
Account* curAccount = NULL;//��¼��ǰ�˻� 


//���سɹ�����1�����򷵻�0 
void loadData()
{
	FILE* fp = fopen("D:/demo2/atm.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			//�������
			Account* newNode = (Account*)malloc(sizeof(Account));
			if (newNode == NULL) {
				exit(-1);
			}//�ж�malloc����ռ��Ƿ�ɹ�����������

			//����ʼ��
			newNode->next = NULL;
			fscanf_s(fp, "%s %s\n", newNode->username,100, newNode->password,100);

			//��ӽ�㵽����
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
	

	printf("���������룺\n");
	scanf_s("%s", a.password,7);

	printf("�������˺ţ�\n");
	scanf_s("%s", a.username,19);

	a.money = 0.0f;

	printf("�����ɹ���\n");
}



//�ҵ�����1�����򷵻�0 
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
	printf("����������룺");
	char oldPassword[100];
	scanf_s("%s", oldPassword,100);
	if (strcmp(oldPassword, curAccount->password) == 0)
	{
		printf("�����������룺");
		while (1)
		{
			scanf_s("%s", curAccount->password,100);
			if (strcmp(oldPassword, curAccount->password) == 0)
			{
				printf("�¾����벻��һ��!\n");
				printf("��������!\n");
			}
			else
				break;
		}
		printf("�޸ĳɹ���\n");

	}
	else
	{
		printf("������󣡲����޸ģ�\n");
	}
}
void signIn()
{
	int i;
	for (i = 0; i < 3; i++)
	{
		Account a;
		printf("�������˺ţ�");
		scanf_s("%s", a.username,19);

		printf("���������룺");
		scanf_s("%s", a.password,19);

		if (findAccount(a))
		{
			printf("��¼�ɹ���\n");
			updatePassword();
			break;
		}
		else
		{
			printf("��¼ʧ�ܣ�\n");
		}
	}
}


void showMenu()
{
	if (language == 1)
	{
		printf("��¼���밴1\n");
		printf("�������밴2\n");
		printf("�˳����밴3\n");
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

//���سɹ�����1�����򷵻�0 



int main()
{
	loadData();


	printf("���ķ��񣬰�1\n");
	printf("English Service��Press 2\n");
	printf("һҹ��������3\n");

	scanf_s("%d", &language);
	showMenu();

	signUp();

	printLinkedList();
	
	signIn();

	saveData();

	return 0;
}
