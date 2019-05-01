#include <stdio.h>
#include <stdlib.h>         // 화면지워주는 함수를 사용하기 위해 사용해야함.
#include <string.h>

#define MAX 20 // 총 저장 할 수 있는 숫자
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
	printf("\t|\t1. 파 일  초기화       |\n\n");
	printf("\t|\t2. 동물목록 추가       |\n\n");
	printf("\t|\t3. 동물목록 검색       |\n\n");
	printf("\t|\t4. 동물목록 삭제       |\n\n");
	printf("\t|\t5. 종         료       |\n\n");
	printf("\t================================\n");

	printf("\n\t\t번호를 고르시오 : ");
	scanf("%d", &s);

	switch (s) {
	case 1: fun_init();		//	1. 파 일  초기화
		break;
	case 2: fun_input();	//  2. 동물목록 추가
		break;
	case 3: fun_call();     //  3. 동물목록 검색 
		break;
	case 4: fun_del();      //  4. 동물목록 삭제  
		break;
	case 5:
		printf("\n\n\t프로그램을 종료합니다.\n");
		break;
	}
}

void fun_init(void)//	1. 파 일  초기화
{
	char d;
	clrscr();

	fp1 = fopen("data.txt", "w");  // 쓰기용으로 파일 만들기.같은 이름이 있다면 덮어쓰기
	fp = fopen("anilist.txt", "w");

	printf("\n\n\t\t\t !! 파일이 초기화 되었습니다. !!\n");
	fclose(fp);
	fclose(fp1);

	printf("\n\n\n\t\t메인화면으로 돌아가시겠습니까(y/n)? ");

	rewind(stdin);
	scanf("%c", &d);

	switch (d) {
	case 'y':
	case 'Y':
		main();
		break;
	case 'n':
	case 'N':
		printf("\n\n\t\t\t\t감사합니다.\n");
		return;
	}
}

void fun_input(void)//		2. 동물목록 추가
{
	int i = 0, z = 0;
	char d;
	clrscr();  // 화면을 지워주는 함수

	fp1 = fopen("data.txt", "r");  //fp1포인터에 미리 만들어진 data.txt를 읽어들인다.

	// 내용이 있다면 읽어온다, 파일이 끝날때 까지 a구조체에 넣는다.
	while (fscanf(fp1, "%d %50s %50s %50s %10s", &a[z].key, &a[z].name, &a[z].group, &a[z].place, &a[z].life) != EOF)
	{
		i = a[z].key + 1;
		// printf("%d\n", a[z].key);
	}

	if (i <= MAX)
	{
		printf("\n\n\t\t데이터 삽입\n");

		printf("\n\n\t레코드 번호 : %d\n", ((i == 0) ? i + 1 : i));
		fclose(fp1); // 읽은 data.txt를 닫음

		printf("\n\t동물이름 : ");
		scanf("%s", &a[i].name);

		printf("\n\t분류 : ");
		scanf("%s", &a[i].group);

		printf("\n\t서식지 : ");
		scanf("%s", &a[i].place);

		printf("\n\t수명 : ");
		scanf("%10s", &a[i].life);

		fp1 = fopen("data.txt", "a");

		fprintf(fp1, "\n%d  %s  %s  %s  %s", ((i == 0) ? i + 1 : i), a[i].name, a[i].group, a[i].place, a[i].life);
	}
	else
		printf("\n\n\t       !! 20개의 레코드만 저장할 수 있습니다 !!\n");


	printf("\n\n\n\t\t메인화면으로 돌아가시겠습니까(y/n)? ");
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
		printf("\n\n\t\t\t수고하셨습니다.\n");
		return;
		break;
	}
}

void fun_call(void)    //  3. 동물목록 검색,    
{
	int i, j, h, l, m, w, x, z;
	char d;

	clrscr();  // 화면을 지워주는 함수
	printf("\n\n=========================\n");
	printf("         동물검색 \n");
	printf("=========================\n\n");

	fp1 = fopen("data.txt", "r");  //fp1포인터에 미리 만들어진 data.txt를 읽어들인다.
	fp = fopen("anilist.txt", "a+");

	//파일이 끝날때 까지 a구조체에 넣는다.
	z = 0;
	while (fscanf(fp1, "%d %50s %50s %50s %10s", &a[z].key, &a[z].name, &a[z].group, &a[z].place, &a[z].life) != EOF)
		z++;

	if (z == 0)
	{
		printf("\n   동물 목록이 없습니다.");
		Search_Question();
		return;
	}

	// 동물 목록 출력
	printf("   Input data : \n");
	for (i = 0; i < z; i++)
		printf("\t %d. %s\n", a[i].key, a[i].name);

key:
	printf("\n\n   Select Number :  ");
	scanf(" %d", &x);

	l = 0;  // ㅣ: 최솟값
	h = z;  // h : 최댓값
	j = -1; 

	
	while (l <= h)
	{
		m = (l + h) / 2;
		com(x, a[m].key, &w);   // x : 찾는 값
		switch (w)
		{
		case '>':
			l = m + 1; // ㅣ: 최솟값
			break;
		case '<':
			h = m - 1; // h = 최댓값
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
		printf("\n   %d번의 데이터를 찾을 수가 없습니다.\n", x);
		goto key;
	}
	else
	{
		// 화면 출력
		printf("   Index Key ===> %d", j + 1);
		printf("   동물명 ===>  %s\n", a[j].name);
		printf("\n   ==================================\n");
		printf("       동물명 : %s\n", a[j].name);
		printf("        분류  : %s\n", a[j].group);
		printf("       서식지 : %s\n", a[j].place);
		printf("        수명  : %s\n", a[j].life);
		printf("     ==================================\n");

		// 파일 출력
		fprintf(fp, "\n==================================\n");
		fprintf(fp, "   동물명 : %s\n", a[j].name);
		fprintf(fp, "    분류  : %s\n", a[j].group);
		fprintf(fp, "   서식지 : %s\n", a[j].place);
		fprintf(fp, "    수명  : %s\n", a[j].life);
		fprintf(fp, "  ==================================\n");
	}

	Search_Question();
}

void fun_del(void)  //  4. 동물목록 삭제  
{
	int i, z = 0, j = 0;
	char d;

	clrscr();
	fp1 = fopen("data.txt", "r");

	while (fscanf(fp1, "%d %50s %50s %50s %10s", &a[z].key, &a[z].name, &a[z].group, &a[z].place, &a[z].life) != EOF)
		z++; 

	printf("\t 동물목록 \n\n");

	for (i = 0; i < z; i++)
		printf("\t %d. %s\n", a[i].key, a[i].name);

	fclose(fp1);

	while (z != 0)
	{
		printf(" 삭제 할 번호 : ");
		scanf("%d", &i);

		if (i<1 || i>z)
		{
			printf("\n 없는 번호 입니다. \n\n");
		}
		else
			break;
	}

	if (i == z) // 삭제할 번호가 1번
	{
		a[z - 1].key = NULL;
		*a[z - 1].name = NULL;
		*a[i - 1].group = NULL;
		*a[i - 1].place = NULL;
		*a[i - 1].life = NULL;
	}

	for (i; i < z; i++) // 정렬
	{
		a[i - 1].key = a[i].key;
		strcpy(a[i - 1].name, a[i].name);
		strcpy(a[i - 1].group, a[i].group);
		strcpy(a[i - 1].place, a[i].place);
		strcpy(a[i - 1].life, a[i].life);
	}

	clrscr();
	printf("\n\t동물목록 \n\n");

	fp1 = fopen("data.txt", "w");

	for (i = 0; i < z - 1; i++)
	{
		printf("\t %d. %s\n", i + 1, a[i].name);
		fprintf(fp1, "\n%d  %s  %s  %s  %s", i + 1, a[i].name, a[i].group, a[i].place, a[i].life);
	}
	fclose(fp1);

	if (z == 0)
	{
		printf("삭제할 목록이 없습니다.");
	}

	printf("\n\n   삭제를 계속 하시겠습니까(y/n)? ");
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
	printf("\n\n   검색을 계속하시겠습니까(y/n)? ");
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


