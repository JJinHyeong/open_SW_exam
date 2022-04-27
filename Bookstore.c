#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _data {		//구조체 사용
	char subject[20], author[20];
	int price, volume, sales;
} data;	


int line(FILE *);
void read(FILE *, data *);
void sort(data *, int);
int total(data *, int);
int find_max(data *, int);
void print_data(data *, int, int, int);

int main(void)
{

	FILE *fp;
	data *book;
	int data_num, max, total_sales;
	
		

	if(!(fp=fopen("book.txt","r")))
	{
		fprintf(stderr, "book.txt does not exist\n");
		exit(1);
	}	//book.txt파일을 읽어들이고, 파일이 없을경우 에러메시지를 출력함


	data_num = line(fp);	//line 함수를 호출하여 테이터의 수를 리턴하여 저장

	book = (data *)malloc(sizeof(data) * data_num);		//데이터를 저장하기 위한 동적 메모리 할당

	read(fp, book);	//함수를 호출하여 파일에서 데이터를 읽어들여 구조체 배열에 저장

	sort(book, data_num);	//sort 함수를 호출하여 데이터를 정렬

	total_sales = total(book, data_num);	//총 매출액을 구하는 함수를 호출하여 저장

	max = find_max(book, data_num);		//가장 비싼값을 가진 데이터 라인을 찾아서 리턴

	print_data(book, data_num, max, total_sales);


	free(book);	//동적할당한 메모리를 반환

	fclose(fp);	

	return 0;

}



int line(FILE *fp)
{

	char data_tmp[100], string[100];
	int data_num = 0;

	while(fgets(data_tmp, 100, fp))

	{
		if(sscanf(data_tmp, "%s", string) != 1)
		{
			continue;
		}

		data_num++;
	}

	rewind(fp);

	return data_num;
}


void read(FILE *fp, data *book)
{

	char subject[40], author[40];
	int i, rt, volume, price;

	i = 0;

	while((rt = fscanf(fp, "%s %s %d %d", subject, author, &volume, &price)) != EOF)
	{

		strcpy(book[i].subject, subject);
		strcpy(book[i].author, author);
		book[i].price = price;
		book[i].volume = volume;
		book[i].sales = price * volume;

		i++;
	}
}


void sort(data *book, int data_num)
{
	data tmp;
	int i, j;

	for( i = 0 ; i < data_num - 1; i++)
	{
		for( j = i + 1 ; j < data_num; j++)
		{
			if( book[i].sales < book[j].sales )
			{
				tmp = book[i];
				book[i] = book[j];
				book[j] = tmp;
			}
		}
	}
}



int total(data *book, int data_num)
{

	int i, total_sales;

	for( i = 0, total_sales = 0 ; i < data_num ; i++ )
	{
		total_sales += book[i].sales;
	}

	return total_sales;
}



int find_max(data *book, int data_num) // 가격이 가장 비싼 책을 찾는다
{
	int i, max;

	for( i = 1, max = 0 ; i < data_num ; i++ )
	{
		if( book[max].price < book[i].price )
		{
			max = i;
		}
	}

	return max;
}



void print_data(data *book, int data_num, int max, int total_sales)
{

	int i;

	printf(" =================================================================================\n");

	printf("            제목                   저자        가격     판매권수     매출액\n");

	printf(" =================================================================================\n");

	for( i = 0 ; i < data_num ; i++ )
		printf("%20s %20s      %5d      %3d      %7d\n", book[i].subject, book[i].author, book[i].price, book[i].volume, book[i].sales);

	printf(" =================================================================================\n");

	printf(" # 입력된 책은 모두 %d권 입니다.\n", data_num);

	printf(" # 가장 가격이 비싼 책은 %d원인 %s 입니다.\n", book[max].price, book[max].subject);

	printf(" # 현재 총 매출액은 %d원 입니다.\n", total_sales);

	printf(" =================================================================================\n");

}