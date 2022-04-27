#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _data {		//����ü ���
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
	}	//book.txt������ �о���̰�, ������ ������� �����޽����� �����


	data_num = line(fp);	//line �Լ��� ȣ���Ͽ� �������� ���� �����Ͽ� ����

	book = (data *)malloc(sizeof(data) * data_num);		//�����͸� �����ϱ� ���� ���� �޸� �Ҵ�

	read(fp, book);	//�Լ��� ȣ���Ͽ� ���Ͽ��� �����͸� �о�鿩 ����ü �迭�� ����

	sort(book, data_num);	//sort �Լ��� ȣ���Ͽ� �����͸� ����

	total_sales = total(book, data_num);	//�� ������� ���ϴ� �Լ��� ȣ���Ͽ� ����

	max = find_max(book, data_num);		//���� ��Ѱ��� ���� ������ ������ ã�Ƽ� ����

	print_data(book, data_num, max, total_sales);


	free(book);	//�����Ҵ��� �޸𸮸� ��ȯ

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



int find_max(data *book, int data_num) // ������ ���� ��� å�� ã�´�
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

	printf("            ����                   ����        ����     �ǸűǼ�     �����\n");

	printf(" =================================================================================\n");

	for( i = 0 ; i < data_num ; i++ )
		printf("%20s %20s      %5d      %3d      %7d\n", book[i].subject, book[i].author, book[i].price, book[i].volume, book[i].sales);

	printf(" =================================================================================\n");

	printf(" # �Էµ� å�� ��� %d�� �Դϴ�.\n", data_num);

	printf(" # ���� ������ ��� å�� %d���� %s �Դϴ�.\n", book[max].price, book[max].subject);

	printf(" # ���� �� ������� %d�� �Դϴ�.\n", total_sales);

	printf(" =================================================================================\n");

}