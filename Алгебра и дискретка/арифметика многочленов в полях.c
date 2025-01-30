#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#define N 3


struct Node
{
    int pow;
    int value;
    struct Node* next;
};

struct Node* createpoly()
{
    int k, a;
    printf("������� ����������: ");
    scanf("%d", &k);
    struct Node* odnochlen = (struct Node*)malloc(sizeof(struct Node));
    if (odnochlen == NULL) 
	{
        // ��������� ������ ��������� ������
        return NULL;
    }
    odnochlen->pow = k;
    printf("����������� ��� x^(%d): ", k);
    scanf("%d", &a);
    odnochlen->value = a;
    odnochlen->next = NULL;

    struct Node* polynom = odnochlen;
    struct Node* pred = odnochlen;

    for (int i = 0; i < k; i++)
    {
        struct Node* odnochlen = (struct Node*)malloc(sizeof(struct Node));
        if (odnochlen == NULL) 
		{
            // ��������� ������ ��������� ������
            // ������������ ��� ���������� ������
            while (polynom != NULL) 
			{
                struct Node* temp = polynom;
                polynom = polynom->next;
                free(temp);
            }
            return NULL;
        }
        pred->next = odnochlen;
        odnochlen->pow = k - i-1;
        printf("����������� ��� x^(%d): ", k - i-1);
        scanf("%d", &a);
        odnochlen->value = a;
        odnochlen->next = NULL;
        pred = odnochlen;
    }
    return polynom;
}

void printpoly(struct Node* head)
{

    if(!head) // HEAD == NULL
        printf("��� ������ ����\n");
    printf("%d�^%d", head->value, head->pow);
    head = head->next;
    while(head) //���� ��������� �� ������ ������ �� ����� ����
    {
        if(head->value>0)
            printf("+%d�^%d", head->value, head->pow);

        if(head->value<0)
            printf("%d�^%d", head->value, head->pow);
        head = head->next;}
    printf("\n");
}

int sum(int a, int b, int n)
{
    return((a+b)%n);
}

int sub(int a, int b, int n)
{
    int c = a-b;
    if(c>=n)
    {
        c = c%n;
    }
    if (c<0)
    {
        while(c<0)
        {
            c = c + n;
        }
    }
    return(c);
}

int mul(int a, int b, int n)
{
    return((a*b)%n);
}

int divv(int a, int b, int n)
{
    int c;
    for(int j=0;j<n;j++)
    {
        c = mul(b,j,n);
        if (c==a)
        {
            c = j;
            return(c);
        }
    }

}

int reducing(int a, int n)
{
    if (a >= 0)
    {
        return(a%n);
    }
    while(a<0)
    {
        a = a +n;
    }
    return a;

}

struct Node* copyPoly(struct Node* head) 
{
    if (head == NULL) 
	{
        return NULL; // ���� ������ ����, ���������� ����
    }

    // ������� ����� ���� � ������� �� ������� ���� ��������� ������
    struct Node* newHead = (struct Node*)malloc(sizeof(struct Node));
    if (newHead == NULL) 
	{
        return NULL; // �� ������� �������� ������
    }
    newHead->value = head->value;
    newHead->pow = head->pow;
    newHead->next = NULL;

    // ��������� ���� ������ ������, ������� �� ����� ���������
    struct Node* last = newHead;

    //������� ���� ��������� ������, ������� �� �������
    struct Node* current = head->next;

    while (current != NULL) {
        // ������� ����� ����
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            // ������� ������ � ������ ������
            while (newHead != NULL) {
                struct Node* temp = newHead;
                newHead = newHead->next;
                free(temp);
            }
            return NULL;
        }

        // �������� ������
        newNode->value = current->value;
        newNode->pow = current->pow;
        newNode->next = NULL;

        // ��������� ����� ���� � ����� ������ ������
        last->next = newNode;
        last = newNode;

        // ��������� � ���������� ���� ��������� ������
        current = current->next;
    }

    return newHead; //���������� ����� ������
}

struct Node* createEmptyPoly(int l)
{
    if (l <= 0) 
	{
        return NULL; // ���������� NULL ��� ������������ �����
    }

    // ������� �������� ���� ��� ����������
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    if (head == NULL) 
	{
        return NULL; // �� ������� �������� ������
    }
    head->value = 0;
    head->pow = l - 1;
    head->next = NULL;

    struct Node* current = head;

    // ������� ��������� ���� ����������
    for (int i = l - 2; i >= 0; --i) 
	{
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL)
		{
            // ������� ������ � ������ ������
            while (head != NULL) 
			{
                struct Node* temp = head;
                head = head->next;
                free(temp);
            }
            return NULL;
        }

        newNode->value = 0;
        newNode->pow = i;
        newNode->next = NULL;

        current->next = newNode;
        current = newNode;
    }

    return head; // ���������� ��������� �� ��������� ���������
}
int isZeroPoly(struct Node* head) 
{
    // ���������, �� �������� �� ������ ������
    if (head == NULL) 
	{
        return -1; // ���������� -1, ��� ��� ��������� �� ����� ���� ������
    }

    struct Node* current = head;
    while (current != NULL) 
	{
        if (current->value != 0) 
		{
            return -1; // ������ �����������, �� ������ ����
        }
        current = current->next;
    }

    return 1; // ��� ������������ ����� ����
}

struct Node* delenie(struct Node* poly1,struct Node* poly2)
{
    struct Node* copypoly1 = copyPoly(poly1);
    struct Node* resultat = createEmptyPoly((poly1->pow)-(poly2->pow)+1);
    for(int i=0;i<(poly1->pow)-(poly2->pow)+1;i++)
    {
        (resultat+i)->value=divv((copypoly1+i)->value,poly2->value,N);
        for(int j=0;j<(poly2->pow)+1;j++)
        {
            (copypoly1+i+j)->value = sub((copypoly1+i+j)->value,mul((resultat+i)->value,(poly2+j)->value,N),N);
        }
    }
    if(isZeroPoly(copypoly1)==1)
    {
        free(copypoly1);
        return resultat;
    }
    else
    {
        free(resultat);
        free(copypoly1);
        return NULL;
    }
};

void freePoly(struct Node* head) 
{
    struct Node* tmp;

    // �������� �� ������ � ����������� ���� �� ������
    while (head != NULL) 
	{
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

struct Node* Delenie(struct Node* poly1, struct Node* poly2) 
{
    if (poly1 == NULL || poly2 == NULL || poly2->value == 0) 
	{
        return NULL; // ������ ������ �� ���� ��� ������ ���������
    }

    if ((poly1->pow)<(poly2->pow))
    {
        return NULL;
    }
    struct Node* copypoly1 = copyPoly(poly1);
    struct Node* resultat = createEmptyPoly(poly1->pow - poly2->pow + 1);
    struct Node* currentResult = resultat;

    while (copypoly1 != NULL && copypoly1->pow >= poly2->pow) 
	{
        if (copypoly1->value != 0) 
		{
            int coefficient = divv(copypoly1->value, poly2->value, N);
            currentResult->value = coefficient;
            currentResult->pow = copypoly1->pow - poly2->pow;

            struct Node* tempPoly2 = poly2;
            struct Node* tempCopyPoly1 = copypoly1;
            while (tempPoly2 != NULL) 
			{
                tempCopyPoly1->value = sub(tempCopyPoly1->value, mul(coefficient, tempPoly2->value, N), N);
                tempPoly2 = tempPoly2->next;
                if (tempPoly2 != NULL) 
				{
                    tempCopyPoly1 = tempCopyPoly1->next;
                }
            }
        }
        copypoly1 = copypoly1->next;
        if (currentResult->pow > 0) {
            currentResult->next = createEmptyPoly(currentResult->pow);
            currentResult = currentResult->next;
        }
    }

    if (isZeroPoly(copypoly1) == 1) 
	{
        freePoly(copypoly1); // ������� freePoly ������ ��������� ����������� ��� ������ �������� ������
        return resultat;
    } else {
        freePoly(resultat); // ����������, ������� freePoly ������ ����������� ������
        freePoly(copypoly1);
        return NULL;
    }
}

void qqnext(int* mass, int k)
{
    mass[k]=mass[k]+1;
    for (int i = k; i >0; i--)
    {
        if (mass[i]==N)
        {
            mass[i] = 0;
            mass[i-1] = mass[i-1] + 1;
        }
    }
}

int* createmass(int k)
{
    int* massiv = (int*)malloc(sizeof(int)*(k+1));
    for (int i = 0; i<k+1;i++)
    {
        massiv[i] = 0;
    }
    massiv[0] = 1;
    return massiv;
}

struct Node* masstopoly(int* mass, int k)
{
    struct Node* a = createEmptyPoly(k+1);
    struct Node* b = a;
    for(int i=0;i<k+1;i++)
    {
        a->value=mass[i];
        a=a->next;
    }
    return b;
};

void dozapis (struct Node** array, int k)
{
    int f = 0;
    while(array[f]!=NULL)
    {
        f++;
    }
    int* mas = createmass(k);
    while(mas[0]!=N)
    {
        array[f] =  masstopoly(mas,k);
        qqnext(mas,k);
        f++;
    }
}

struct Node** createitogmass(int k)
{
    struct Node** array = (struct Node**)malloc(sizeof(struct Node*)*((N)^(k+1)));
    int u;
    printf("������� ��������� �����������?");
    scanf("%d",&u);
    for (int i=0;i<u;i++)
    {
        array[i] = createpoly();
    }
    for (int i = u; i<pow(N,k+1);i++)
    {
        array[i] = NULL;
    }
    return array;
};

int syzeitogmass(struct Node** array)
{
    int i =0;
    while(array[i]!=NULL)
    {
        i++;
    }
    return i;
}

void printitog(struct Node** array)
{
    for(int i = 0;i<syzeitogmass(array);i++)
    {
        if(array[i]==NULL)
        {
            printf("����� �������");
            break;
            //return;
        }
        printpoly(array[i]);
    }
}

int* newarray(int length) {
    // ��������� ������ ��� �������
    int* array = (int*)malloc(length * sizeof(int));

    // �������� �� �������� ��������� ������
    if (array == NULL) 
	{
        return NULL; // � ������ ������ ��������� ������ ���������� NULL
    }

    // ������������� ������� ������
    for (int i = 0; i < length; i++) 
	{
        array[i] = 0;
    }

    return array; // ���������� ��������� �� ������
}

void function(struct Node** array,int* a)
{
    for(int i = N;i<syzeitogmass(array);i++)
    {
        for (int j=0;j<N;j++)
        {
            if (Delenie(array[i],array[j])!=NULL)
                {
                a[i] = a[i] +1;
                }
        }
    }
}


void Reduc(struct Node** poly) {
    if (poly == NULL || *poly == NULL) 
	{
        return; // �������� �� ������ ������
    }

    struct Node* tm = *poly;
    struct Node* prev = NULL;
    int count=0;
    int c =0;
    // ������������� �������������
    while (tm != NULL) 
	{
        count++;
        if((reducing(tm->value,N)==0))
           {
               c++;
           }
        tm->value = reducing(tm->value,N);
        tm = tm->next;
    }
    if (count==c)
    {
        return;
    }
    // �������� ������� �����
    tm = *poly;
    while (tm != NULL && tm->value == 0) 
	{
        prev = tm;
        tm = tm->next;
        free(prev); // ������������ ������
    }

    *poly = tm; // ���������� ��������� �� ������ ������
}

struct Node* multipoly(struct Node* poly1,struct Node* poly2)
{
    struct Node* itog = createEmptyPoly((poly1->pow)+(poly2->pow)+2);
    for (int i = 0; i < (poly2->pow)+1;i++)
    {
        for (int j = 0;j<(poly1->pow)+1;j++)
        {
            (itog+i+j)->value = ((itog+i+j)->value) + ((poly1+j)->value)*((poly2+i)->value);
        }
    }
    Reduc(itog);
    return itog;
};

struct Node* createNode(int pow, int value) 
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->pow = pow;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// ������� ��� ���������� ���� � ���������
void addNode(struct Node** poly, int pow, int value) 
{
    struct Node* newNode = createNode(pow, value);
    if (*poly == NULL) 
	{
        *poly = newNode;
    } else 
	{
        struct Node* temp = *poly;
        while (temp->next != NULL) 
		{
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

struct Node* Multipoly(struct Node* poly1, struct Node* poly2) 
{
    if (poly1 == NULL || poly2 == NULL) 
	{
        return NULL;
    }

    struct Node* result = NULL;

    for (struct Node* p1 = poly1; p1 != NULL; p1 = p1->next) 
	{
        for (struct Node* p2 = poly2; p2 != NULL; p2 = p2->next) 
		{
            int pow = p1->pow + p2->pow;
            int value = p1->value * p2->value;

            // ���������� ��� ���������� ������������ � �������������� ����������
            struct Node* temp = result;
            struct Node* prev = NULL;
            while (temp != NULL && temp->pow > pow) 
			{
                prev = temp;
                temp = temp->next;
            }
            if (temp != NULL && temp->pow == pow) 
			{
                temp->value += value;
            } else 
			{
                struct Node* newNode = createNode(pow, value);
                if (prev == NULL) 
				{
                    newNode->next = result;
                    result = newNode;
                } else 
				{
                    newNode->next = temp;
                    prev->next = newNode;
                }
            }
        }
    }

    Reduc(&result);
    return result;
}

int main()
{
    setlocale(LC_ALL, "rus"); // ��� �������� �����
    setlocale(LC_NUMERIC, "C"); // ��� �������� �����
// ������������� ����� � ���������� �� ����������!!!! ���� ��������� ������������ ��� ���� ������ ����, ����� ���������� ��� ������ 
    struct Node* poly1 = createpoly();
    struct Node* poly2 = createpoly();
    Reduc(&poly1);
    Reduc(&poly2);
    struct Node* poly3 = Delenie(poly1,poly2);
    struct Node* poly3 = Multipoly(poly1,poly2);

    printpoly(poly3);
    return 0;
}
