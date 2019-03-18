#include <stdio.h>
#include <stdlib.h>         // ȭ�������ִ� �Լ��� ����ϱ� ���� ����ؾ���.
#include <string.h>

#define MAX 2
#define NAME_SIZ 50
#define GROUP_SIZ 50
#define PLACE_SIZ 50
#define LIFE_SIZ 20

FILE *fp, *fp1;

void com(int x, int y, int *w);
void fun_init(void); 
void fun_input(void);
void fun_call(void);
void fun_del(void);
void clrscr(void);
void Search_Question(void);

struct MASTER
{
	int key;
	char name[NAME_SIZ];
	char group[GROUP_SIZ];
	char place[PLACE_SIZ];
	char life[LIFE_SIZ];
} a[MAX];

void main()
{
	int s;
	clrscr();

	printf("\n\n\n\n");
	printf("\t================================\n\n");
	printf("\t|\t1. �� ��  �ʱ�ȭ       |\n\n");
	printf("\t|\t2. ������� �߰�       |\n\n");
	printf("\t|\t3. ������� �˻�       |\n\n");
	printf("\t|\t4. ������� ����       |\n\n");
	printf("\t|\t5. ��         ��       |\n\n");
	printf("\t================================\n");

	printf("\n\t\t��ȣ�� ���ÿ� : ");
	scanf("%d", &s);

	switch (s) {
	case 1: fun_init();		//	1. �� ��  �ʱ�ȭ
		break;
	case 2: fun_input();	//  2. ������� �߰�
		break;
	case 3: fun_call();     //  3. ������� �˻� 
		break;
	case 4: fun_del();      //  4. ������� ����  
		break;
	case 5:
		printf("\n\n\t���α׷��� �����մϴ�.\n");
		break;
	}
}

void fun_init(void)//	1. �� ��  �ʱ�ȭ
{
	char d;
	clrscr();

	fp1 = fopen("data.txt", "w");  // ��������� ���� �����.���� �̸��� �ִٸ� �����
	fp = fopen("anilist.txt", "w");

	printf("\n\n\t\t\t !! ������ �ʱ�ȭ �Ǿ����ϴ�. !!\n");
	fclose(fp);
	fclose(fp1);

	printf("\n\n\n\t\t����ȭ������ ���ư��ðڽ��ϱ�(y/n)? ");

	rewind(stdin);
	scanf("%c", &d);

	switch (d) {
	case 'y':
	case 'Y':
		main();
		break;
	case 'n':
	case 'N':
		printf("\n\n\t\t\t\t�����մϴ�.\n");
		return;
	}
}

void fun_input(void)//		2. ������� �߰�
{
	int i = 0, z = 0;
	char d;
	clrscr();  // ȭ���� �����ִ� �Լ�

	fp1 = fopen("data.txt", "r");  //fp1�����Ϳ� �̸� ������� data.txt�� �о���δ�.

	// ������ �ִٸ� �о�´�, ������ ������ ���� a����ü�� �ִ´�.
	while (fscanf(fp1, "%d %50s %50s %50s %10s", &a[z].key, &a[z].name, &a[z].group, &a[z].place, &a[z].life) != EOF)
	{
		i = a[z].key + 1;
		printf("%d\n", a[z].key);
	}

	if (i <= MAX)
	{
		printf("\n\n\t\t������ ����\n");

		printf("\n\n\t���ڵ� ��ȣ : %d\n", ((i == 0) ? i + 1 : i));
		fclose(fp1); // ���� data.txt�� ����

		printf("\n\t�����̸� : ");
		scanf("%s", &a[i].name);

		printf("\n\t�з� : ");
		scanf("%s", &a[i].group);

		printf("\n\t������ : ");
		scanf("%s", &a[i].place);

		printf("\n\t���� : ");
		scanf("%10s", &a[i].life);

		fp1 = fopen("data.txt", "a");

		fprintf(fp1, "\n%d  %s  %s  %s  %s", ((i == 0) ? i + 1 : i), a[i].name, a[i].group, a[i].place, a[i].life);
	}
	else
		printf("\n\n\t       !! 15���� ���ڵ常 ������ �� �ֽ��ϴ� !!\n");


	printf("\n\n\n\t\t����ȭ������ ���ư��ðڽ��ϱ�(y/n)? ");
	rewind(stdin);
	scanf("%c", &d);

	switch (d) {
	case 'y':
	case 'Y':
		fclose(fp1);
		main();
		break;
	case 'n':
	case 'N':
		printf("\n\n\t\t\t�����ϼ̽��ϴ�.\n");
		return;
		break;
	}
}

void fun_call(void)    //  3. ������� �˻�,    
{
	int i, j, h, l, m, w, x, z;
	char d;

	clrscr();  // ȭ���� �����ִ� �Լ�
	printf("\n\n=========================\n");
	printf("         �����˻� \n");
	printf("=========================\n\n");

	fp1 = fopen("data.txt", "r");  //fp1�����Ϳ� �̸� ������� data.txt�� �о���δ�.
	fp = fopen("anilist.txt", "a+");

	//������ ������ ���� a����ü�� �ִ´�.
	z = 0;
	while (fscanf(fp1, "%d %50s %50s %50s %10s", &a[z].key, &a[z].name, &a[z].group, &a[z].place, &a[z].life) != EOF)
		z++;

	if (z == 0)
	{
		printf("\n   ���� ����� �����ϴ�.");
		Search_Question();
		return;
	}

	// ���� ��� ���
	printf("   Input data : \n");
	for (i = 0; i < z; i++)
		printf("\t %d. %s\n", a[i].key, a[i].name);

key:
	printf("\n\n   Select Number :  ");
	scanf(" %d", &x);

	l = 0;  // ��: �ּڰ�
	h = z;  // h : �ִ�
	j = -1; 

	//void com(int x, int y, int *w)
	//{
	//	if (x > y)
	//		*w = '>';
	//	else if (x == y)
	//		*w = '=';
	//	else
	//		*w = '<';
	//}
	while (l <= h)
	{
		m = (l + h) / 2;
		com(x, a[m].key, &w);   // x : ã�� ��
		switch (w)
		{
		case '>':
			l = m + 1; // ��: �ּڰ�
			break;
		case '<':
			h = m - 1; // h = �ִ�
			break;
		case '=':
			j = m;
			break;
		}
		if (j == m)
			break;
	}

	if (j == -1)
	{
		printf("\n   %d���� �����͸� ã�� ���� �����ϴ�.\n", x);
		goto key;
	}
	else
	{
		// ȭ�� ���
		printf("   Index Key ===> %d", j + 1);
		printf("   ������ ===>  %s\n", a[j].name);
		printf("\n   ==================================\n");
		printf("       ������ : %s\n", a[j].name);
		printf("        �з�  : %s\n", a[j].group);
		printf("       ������ : %s\n", a[j].place);
		printf("        ����  : %s\n", a[j].life);
		printf("     ==================================\n");

		// ���� ���
		fprintf(fp, "\n==================================\n");
		fprintf(fp, "   ������ : %s\n", a[j].name);
		fprintf(fp, "    �з�  : %s\n", a[j].group);
		fprintf(fp, "   ������ : %s\n", a[j].place);
		fprintf(fp, "    ����  : %s\n", a[j].life);
		fprintf(fp, "  ==================================\n");
	}

	Search_Question();
}

void fun_del(void)  //  4. ������� ����  
{
	int i, z = 0, j = 0;
	char d;

	clrscr();
	fp1 = fopen("data.txt", "r");

	while (fscanf(fp1, "%d %50s %50s %50s %10s", &a[z].key, &a[z].name, &a[z].group, &a[z].place, &a[z].life) != EOF)
		z++; 

	printf("\t ������� \n\n");

	for (i = 0; i < z; i++)
		printf("\t %d. %s\n", a[i].key, a[i].name);

	fclose(fp1);

	while (z != 0)
	{
		printf(" ���� �� ��ȣ : ");
		scanf("%d", &i);

		if (i<1 || i>z)
		{
			printf("\n ���� ��ȣ �Դϴ�. \n\n");
		}
		else
			break;
	}

	if (i == z) // ������ ��ȣ�� 1��
	{
		a[z - 1].key = NULL;
		*a[z - 1].name = NULL;
		*a[i - 1].group = NULL;
		*a[i - 1].place = NULL;
		*a[i - 1].life = NULL;
	}

	for (i; i < z; i++) // ����
	{
		a[i - 1].key = a[i].key;
		strcpy(a[i - 1].name, a[i].name);
		strcpy(a[i - 1].group, a[i].group);
		strcpy(a[i - 1].place, a[i].place);
		strcpy(a[i - 1].life, a[i].life);
	}

	clrscr();
	printf("\n\t������� \n\n");

	fp1 = fopen("data.txt", "w");

	for (i = 0; i < z - 1; i++)
	{
		printf("\t %d. %s\n", i + 1, a[i].name);
		fprintf(fp1, "\n%d  %s  %s  %s  %s", i + 1, a[i].name, a[i].group, a[i].place, a[i].life);
	}
	fclose(fp1);

	if (z == 0)
	{
		printf("������ ����� �����ϴ�.");
	}

	printf("\n\n   ������ ��� �Ͻðڽ��ϱ�(y/n)? ");
	rewind(stdin);
	scanf("%c", &d);

	switch (d)
	{
	case 'y':
	case 'Y':
		fun_del();
		break;
	case 'n':
	case 'N':
		main();
		return;
	}

}

void com(int x, int y, int *w)
{
	if (x > y)
		*w = '>';
	else if (x == y)
		*w = '=';
	else
		*w = '<';
}

void clrscr(void)
{
	system("cls");
}

void Search_Question(void)
{
	char d;
	printf("\n\n   �˻��� ����Ͻðڽ��ϱ�(y/n)? ");
	rewind(stdin);
	scanf("%c", &d);

	switch (d)
	{
	case 'y':
	case 'Y':
		fun_call();
		break;
	case 'n':
	case 'N':
		main();
		fclose(fp);
		fclose(fp1);
		return;
	}
}


////////////////////////////////
////
//
//
//
//
//�����͸� �����ϰ� �޸� �Ҵ��ϱ�
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//struct Person {
//	char name[20];
//	int age;
//	char address[100];
//};
//int main()
//{
//	struct Person *p1 = malloc(sizeof(struct Person));
//
//	strcpy(p1->name, "ȫ�浿");
//	p1->age = 30;
//	strcpy(p1->address, "����� ������");
//
//	printf("�̸�: %s\n", p1->name);
//	printf("����: %d\n", (*p1).age);
//	printf("�ּ�: %s\n", p1->address);
//	free(p1);
//}
//
//
//����ü ��Ī���� �����͸� �����ϰ� �޸� �Ҵ��ϱ�
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//typedef struct studet
//{
//	char name[20];
//	int age;
//	char address[50];
//}student;
//
//void main()
//{
//	student *p1 = malloc(sizeof(p1));
//
//	strcpy(p1->name, "����");
//	p1->age = 20;
//	strcpy(p1->address, "�����");
//
//	printf("%s \n", p1->name);
//	printf("%d \n", p1->age);
//	printf("%s \n", p1->address);
//}
//
//
//����ü �����Ϳ� ����ü ������ �ּ� �Ҵ��ϱ�
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//struct person {
//	char name[20];
//	int age;
//	char address[40];
//};
//
//void main()
//{
//	struct person p1;
//	struct person *p2;
//
//	p2 = &p1;
//
//	strcpy(p1.name, "��");
//	p1.age = 30;
//	strcpy(p2->address, "����");
//
//	printf("%s \n %d \n %s", p2->name, p1.age, (*p2).address);
//
//
//}
//
//65.1 ����ü �Ű����� ����ϱ�
//#include<stdio.h>
//#include<string.h>
//
//struct Person {
//	char name[20];
//	int age;
//	char address[100];
//};
//
//void printPerson(struct Person p)
//{
//	printf("�̸�: %s\n", p.name);
//	printf("����: %d\n", p.age);
//	printf("�ּ�: %s\n", p.address);
//
//}
//
//int main()
//{
//	struct Person p1;
//	strcpy(p1.name, "ȫ�浿");
//	p1.age = 30;
//	strcpy(p1.address, "����� ��걸 �ѳ���");
//
//	printPerson(p1);
//}
//
//
////// 65.2 ����ü ������ �Ű����� ����ϱ�
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//typedef struct person {
//	char name[100];
//	int age;
//	char address[30];
//}person;
//
//void set(person * p)
//{
//	strcpy(p->name, "�Լ�");
//	p->age = 30;
//	strcpy(p->address, "�����");
//
//
//}
//
//int main()
//{
//	person s;
//	strcpy(s.name, "��浿");
//
//	set(&s);
//
//	printf("%s \n", s.name);
//	printf("%d \n", s.age);
//	printf("%s \n", s.address);
//}
//
//����ü ������ �Ű����� ���� ����(����)
//#include<stdio.h>
//#include<string.h>
//
//struct person
//{
//	char name[10];
//	int age;
//	char address[40];
//};
//
//struct person getsum(struct person *p1, struct  person *p2)
//{
//	struct person p3;
//	strcpy(p3.name, p1->name);
//	strcat(p3.name, p2->name);
//	p3.age = p1->age + p2->age;
//	strcpy(p3.address, p1->address);
//	strcat(p3.address, p2->address);
//
//	return p3;
//}
//
//int main()
//{
//	struct person p1, p2, p3;
//
//	strcpy(p1.name, "oi");
//	strcpy(p2.name, "io");
//	p1.age = 20;
//	p2.age = 30;
//	strcpy(p1.address, "onami");
//	strcpy(p2.address, "imano");
//
//	p3 = getsum(&p1, &p2);
//
//	printf("%s \n", p3.name);
//	printf("%s \n", p3.address);
//	printf("%d \n", p3.age);
//
//
//}
//
//
//
//
//
//
//#include <stdio.h>
//
//int main() {
//
//	int i = 1, j = 15, k = 7;
//
//	i += ++k + j;
//	//printf("%d \n", i);
//	//printf("k=%d\n", k);
//	//printf("j=%d\n", j);
//
//
//	i = (i++ - j) * 9;
//	printf("%d\n", i);
//
//	printf("%d", i);
//	return 0;
//}