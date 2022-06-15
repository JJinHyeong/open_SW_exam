#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<Windows.h>

typedef struct node_data {

    int iden;
    char bookname[50];
    char writer[20];
    int price;
}N_data;

typedef struct node {

    struct node_data nd;
    struct node* next;

}Node;

typedef struct linkedlist {

    Node* head;
    Node* cur;
    Node* before;
    int numofdata;
    int (*comp)(int iden1, int iden2);

}List;

void ListInit(List* list);
void SearchBook(List* list);
int SearchBookFirst(List* list, int* num);
int SearchBookNext(List* list, int* num);
void BookList(List* list);
void BookInsert(List* list);
void BookFix(List* list);
void BookDeletion(List* list);
void ProgramClose(List* list);
void FBookInsert(List* list, N_data data);
void SBookInsert(List* list, N_data data);
void SetSortRule(List* list, int (*comp)(int iden1, int iden2));
int WhoIsPrecede(int iden1, int iden2);
void ShowData(List* list);
void FixData(List* list);
void DeletionData(List* list);
void GetDataFromFile(List* list);

int main(void) {


    int chosen_num;
    List list;
    ListInit(&list);


    printf("#############################################################################################################\n");
 
    printf("#\t\t\t\t\t\t�������� ���α׷�\t\t\t\t\t    #\n");

    printf("#\t\t\t\t\t\t\t\t\t\t\t\t\t    #\n");
    printf("#\t\t\t\t\t\t 1.���� �˻�\t\t\t\t\t\t    #\n");
    printf("#\t\t\t\t\t\t 2.���� ���\t\t\t\t\t\t    #\n");
    printf("#\t\t\t\t\t\t 3.���� ���\t\t\t\t\t\t    #\n");
    printf("#\t\t\t\t\t\t 4.���� ����\t\t\t\t\t\t    #\n");
    printf("#\t\t\t\t\t\t 5.���� ����\t\t\t\t\t\t    #\n");
    printf("#\t\t\t\t\t\t 6.���α׷� ����\t\t\t\t\t    #\n");
    printf("#\t\t\t\t\t\t\t\t\t\t\t\t\t    #\n");
    printf("#############################################################################################################\n");

    while (1) {
        printf("\n����� �����ϼ���:");
        scanf("%d", &chosen_num);

        switch (chosen_num) {
        case 1:
            SearchBook(&list);
            break;

        case 2:
            BookList(&list);
            break;

        case 3:
            BookInsert(&list);
            break;

        case 4:
            BookFix(&list);
            break;

        case 5:
            BookDeletion(&list);
            break;

        case 6:
            ProgramClose(&list);
            exit(1);
            break;

       
            printf("#############################################################################################################\n");
            printf("#\t\t\t\t\t\t\t\t\t\t\t\t\t        #\n");
            printf("#\t\t\t\t\t\t�������� ���α׷�\t\t\t\t\t        #\n");

            printf("#\t\t\t\t\t\t\t\t\t\t\t\t\t    #\n");
            printf("#\t\t\t\t\t\t 1.���� �˻�\t\t\t\t\t\t    #\n");
            printf("#\t\t\t\t\t\t 2.���� ���\t\t\t\t\t\t    #\n");
            printf("#\t\t\t\t\t\t 3.���� ���\t\t\t\t\t\t    #\n");
            printf("#\t\t\t\t\t\t 4.���� ����\t\t\t\t\t\t    #\n");
            printf("#\t\t\t\t\t\t 5.���� ����\t\t\t\t\t\t    #\n");
            printf("#\t\t\t\t\t\t 6.���α׷� ����\t\t\t\t\t    #\n");
            printf("#\t\t\t\t\t\t\t\t\t\t\t\t\t    #\n");
            printf("#############################################################################################################\n");
            break;

        default:
            printf("���ڸ� �߸� �Է��߽��ϴ�. �ٽ� �Է��ϼ���. \n\a");
            break;
        }

    }

    return 0;

}


void ListInit(List* list) {


    list->head = (Node*)malloc(sizeof(Node));
    list->head->next = NULL;
    list->comp = NULL;
    SetSortRule(list, WhoIsPrecede);
    GetDataFromFile(list);

}

void GetDataFromFile(List* list) {

    
    int flag = 0;
    FILE* stream;
    N_data bookdata = { 0,NULL,NULL,0 };
    stream = fopen("c:\\bookdata.txt", "r");

    if (stream == NULL) {
        return;
    }

    while (1) {

        flag = fscanf(stream, "%d %d\n", &bookdata.iden, &bookdata.price);
        fgets(bookdata.bookname, sizeof(bookdata.bookname), stream);
        fgets(bookdata.writer, sizeof(bookdata.writer), stream);
        
        bookdata.bookname[strlen(bookdata.bookname) - 1] = '\0';
        bookdata.writer[strlen(bookdata.writer) - 1] = '\0';

        
        if (flag != EOF) {

            if (list->comp == NULL) {
                FBookInsert(list, bookdata);
               
            }
            else {
                SBookInsert(list, bookdata);
            }
        }

        else
            return;
    }

    fclose(stream);

}


void SearchBook(List* list) {

    int sbnum;
    int indexnum;
    int num;
    printf("ã���� �ϴ� å�� �ĺ���ȣ�� �Է��ϼ���:");
    scanf("%d", &sbnum);


    if (SearchBookFirst(list, &num)) {

        if (num == sbnum) {
            ShowData(list);
            return;
        }
    }

    while (SearchBookNext(list, &num)) {

        if (num == sbnum) {
            ShowData(list);
            return;
        }
    }


    printf("ã���ô� å�� �����ϴ�. \n");
    return;

}


void BookList(List* list) {

    Node* nd = list->head->next;
    if (nd == NULL) {
        printf("������ ��ϵ� å�� �����ϴ�.\n");
        return;
    }
    printf("�ĺ���ȣ \t\t       ���� �̸�       \t\t    ���� �̸�   \t����\n");
    while (nd != NULL) {


        printf("%8d%43s%19s%14d\n", nd->nd.iden, nd->nd.bookname, nd->nd.writer, nd->nd.price);

        nd = nd->next;

    }
}



void BookInsert(List* list) {

    char ask;
   
    while (1) {
        N_data data = { 0,NULL,NULL,0 };
        printf("���� �ĺ���ȣ�� �Է�:");
        scanf("%d", &data.iden);
        getchar();
        printf("���� �̸� �Է�:");
        gets(data.bookname);
        printf("���� ���� �̸� �Է�:");
        gets(data.writer);
        printf("���� ���� �Է�:");
        scanf("%d", &data.price);
        getchar();

        if (list->comp == NULL)
            FBookInsert(list, data);

        else {
            SBookInsert(list, data);

        }
        printf("å�� �߰� �Ͻðڽ��ϱ�?(y or n):");
        scanf("%c", &ask);

        if (ask == 'y')
            continue;
        else if (ask != 'y' && ask != 'n') {
            printf("\n");
            printf("�߸��� �Է��Դϴ�.\n");
            return;
        }
        else
            break;
    }

}


void FBookInsert(List* list, N_data data) {

    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->nd.iden = data.iden;
    newnode->nd.price = data.price;
    strcpy(newnode->nd.bookname, data.bookname);
    strcpy(newnode->nd.writer, data.writer);

    newnode->next = list->head->next; 
    list->head->next = newnode; 

}

void SBookInsert(List* list, N_data data) {

    Node* newnode = (Node*)malloc(sizeof(Node));
    Node* pred = list->head; 
    newnode->nd.iden = data.iden;
    newnode->nd.price = data.price;
    strcpy(newnode->nd.bookname, data.bookname);
    strcpy(newnode->nd.writer, data.writer); 

    while (pred->next != NULL && list->comp(data.iden, pred->next->nd.iden) != 0)
    {
        if (data.iden == pred->next->nd.iden) {
            printf("�̹� ��ϵǾ� �ֽ��ϴ�. �ٽ� �Է��ϼ���. \n");
            return;
        }
        pred = pred->next;
    }

    newnode->next = pred->next;
    pred->next = newnode;
}


void BookFix(List* list) {

    int sbnum;
    int num;
    printf("�����ϰ��� �ϴ� å�� �ĺ���ȣ�� �Է��ϼ���:");
    scanf("%d", &sbnum);


    if (SearchBookFirst(list, &num)) {

        if (num == sbnum) {
            FixData(list);
            return;
        }
    }

    if (SearchBookFirst(list, &num) == 0) {
        printf("��ϵǾ� ���� �ʽ��ϴ�.\n");

        return;
    }

   
    while (SearchBookNext(list, &num)) {

        if (num == sbnum) {
            FixData(list);
            return;

        }
    }

    printf("ã���ô� å�� �����ϴ�.\n");
    return;

}

void BookDeletion(List* list) {

    int sbnum;
    int num;
    printf("�����ϰ��� �ϴ� å�� �ĺ���ȣ�� �Է��ϼ���:");
    scanf("%d", &sbnum);


    if (SearchBookFirst(list, &num)) {

        if (num == sbnum) {
            DeletionData(list);
            return;
        }
    }

    if (SearchBookFirst(list, &num) == 0) {
        printf("��ϵǾ� ���� �ʽ��ϴ�. \n");

        return;
    }

    
    while (SearchBookNext(list, &num)) {

        if (num == sbnum) {
            DeletionData(list);
            return;

        }
    }

    printf("ã���ð��� �ϴ� �����Ͱ� �����ϴ�. �ٽ� Ȯ�����ֽñ� �ٶ��ϴ�.\n");
    return;

}

void ProgramClose(List* list) {

    FILE* stream;

    Node* nd = list->head->next;
    stream = fopen("c:\\bookdata.txt", "w");

    if (nd == NULL) {
        return;
    }

    while (nd != NULL) {

        fprintf(stream, "%d %d\n%s\n%s\n", nd->nd.iden, nd->nd.price, nd->nd.bookname, nd->nd.writer);
        nd = nd->next;
    }

    fclose(stream);
}


int SearchBookFirst(List* list, int* num) {

    if (list->head->next == NULL)
        return 0;

    list->before = list->head;
    list->cur = list->head->next;

    *num = list->cur->nd.iden;
    return 1;

}
int SearchBookNext(List* list, int* num) {

    if (list->cur->next == NULL)
        return 0;

    list->before = list->cur;
    list->cur = list->cur->next;

    *num = list->cur->nd.iden;
    return 1;
}

void SetSortRule(List* list, int (*comp)(int iden1, int iden2)) {

    list->comp = comp;

}

int WhoIsPrecede(int iden1, int iden2) {
    if (iden1 < iden2)
        return 0;

    else
        return 1;
}


void ShowData(List* list) {

    Node* c_nd = list->cur;

    printf("�ĺ���ȣ \t\t       ���� �̸�       \t\t    ���� �̸�   \t����\n");
    printf("%8d%43s%19s%14d\n", c_nd->nd.iden, c_nd->nd.bookname, c_nd->nd.writer, c_nd->nd.price);
}

void FixData(List* list) {

    int chose_num;
    Node* c_nd = list->cur;

    Node* pred = list->head; 
    N_data nd;


    printf("������ �����Ͻðڽ��ϱ�?\n");
    while (1) {
        printf("(1)��ü(����,����,����) (2)���� �̸� (3)���� (4)���� (5)��� : ");
        scanf("%d", &chose_num);
        getchar();

        switch (chose_num) {

        case 1:
            printf("���� �̸� �Է�:");
            gets(nd.bookname);
            strcpy(c_nd->nd.bookname, nd.bookname);
            printf("���� ���� �̸� �Է�:");
            gets(nd.writer);
            strcpy(c_nd->nd.writer, nd.writer);
            printf("���� ���� �Է�:");
            scanf("%d", &nd.price);
            c_nd->nd.price = nd.price;

            return;

        case 2:
            printf("���� �̸� �Է�:");
            gets(nd.bookname);
            strcpy(c_nd->nd.bookname, nd.bookname);
            return;

        case 3:
            printf("���� ���� �̸� �Է�:");
            gets(nd.writer);
            strcpy(c_nd->nd.writer, nd.writer);
            return;

        case 4:
            printf("���� ���� �Է�:");
            scanf("%d", &nd.price);
            c_nd->nd.price = nd.price;
            return;
        case 5:
            return;

        default:
            printf("�߸� �Է��Ͽ����ϴ�.");
            continue;

        }
    }
}

void DeletionData(List* list) {

    Node* c_nd = list->cur;

    list->before->next = list->cur->next;
    list->cur = list->before;

    free(c_nd);

    printf("���� �Ǿ����ϴ�.\n");

}
