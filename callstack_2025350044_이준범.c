/*  call_stack

    ���� �ý��ۿ����� ������ �޸𸮿� ���������, �� ���������� `int` �迭�� �̿��Ͽ� �޸𸮸� �����մϴ�.
    ������ SFP�� Return Address�� ���� ���� �޸� �ּҰ� ��������, �̹� ���������� -1�� ��ü�մϴ�.

    int call_stack[]      : ���� ������(`int ��`) �Ǵ� `-1` (��Ÿ������ ���п�)�� �����ϴ� int �迭
    char stack_info[][]   : call_stack[]�� ���� ��ġ(index)�� ���� ������ �����ϴ� ���ڿ� �迭

    ==========================call_stack ���� ��Ģ==========================
    �Ű� ���� / ���� ������ push�� ���   : int �� �״��
    Saved Frame Pointer �� push�� ���  : call_stack������ index
    ��ȯ �ּҰ��� push�� ���       : -1
    =======================================================================


    ==========================stack_info ���� ��Ģ==========================
    �Ű� ���� / ���� ������ push�� ���        : ������ ���� ����
    Saved Frame Pointer �� push�� ���  : � �Լ��� SFP����
    ��ȯ �ּҰ��� push�� ���                 : "Return Address"
    ========================================================================
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define STACK_SIZE 50 // �ִ� ���� ũ��

int     call_stack[STACK_SIZE];         // Call Stack�� �����ϴ� �迭
char    stack_info[STACK_SIZE][20];     // Call Stack ��ҿ� ���� ������ �����ϴ� �迭

/*  SP (Stack Pointer), FP (Frame Pointer)

    SP�� ���� ������ �ֻ�� �ε����� ����ŵ�ϴ�.
    ������ ������� �� SP = -1, �ϳ��� ���̸� `call_stack[0]` -> SP = 0, `call_stack[1]` -> SP = 1, ...

    FP�� ���� �Լ��� ���� ������ �������Դϴ�.
    ���� ���� �Լ� ���� �������� sfp�� ����ŵ�ϴ�.
*/
int SP = -1;
int FP = -1;
int home, SFP1, SFP2;

void func1(int arg1, int arg2, int arg3);
void func2(int arg1, int arg2);
void func3(int arg1);

void push(int num1, char str1[20])
{
    SP++;
    if (num1 != -2) {
        call_stack[SP] = num1;
        strcpy(stack_info[SP], str1);
    }
    else {
        call_stack[SP] = SP;
        strcpy(stack_info[SP], str1);
        FP = SP;
    }
}

void pop(void) {

    strcpy(stack_info[SP], "\0");
    SP--;
}

/*
    ���� call_stack ��ü�� ����մϴ�.
    �ش� �Լ��� ��� ������� �������� ���� �ϼ����� ���� �����Դϴ�.
*/
void print_stack()
{
    if (SP == -1)
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("====== Current Call Stack ======\n");

    for (int i = SP; i >= 0; i--)
    {
        if (call_stack[i] != -1)
            printf("%d : %s = %d", i, stack_info[i], call_stack[i]);
        else
            printf("%d : %s", i, stack_info[i]);

        if (i == SP)
            printf("    <=== [esp]\n");
        else if (i == FP)
            printf("    <=== [ebp]\n");
        else
            printf("\n");
    }
    printf("================================\n\n");
}


//func ���δ� �����Ӱ� �߰��ص� ��������, �Ʒ��� ������ �ٲ����� ������
void func1(int arg1, int arg2, int arg3)
{
    if (home == 1)
    {
        push(arg3, "arg3");
        push(arg2, "arg2");
        push(arg1, "arg1");

        int var_1 = 100;

        push(-1, "Return Address");
        push(-2, "func1 SFP");

        push(var_1, "var_1");

        SFP1 = FP;
    }

    int res;

    do
    {
        printf(" ������ �ұ�?? \n");
        printf("1 : pop     2 : push    3 : exit    4 : show stack \n");
        scanf(" %d", &res);


        if (res == 2)
        {
            printf("\npush�� �����ϼ̽��ϴ�.\n\n");
            home = 1;
            func2(11, 13);
        }

        else if (res == 1) 
        {
            printf("\npop�� �����ϼ̽��ϴ�.\n\n");

            pop();
            pop();
            pop();
            pop();
            pop();
            pop();

            main();
        }

        else if (res == 4)
        {
            print_stack();
        }

        else if (res == 3) printf("�����մϴ�");
    
    } while (res == 4);
}


void func2(int arg1, int arg2)
{
    if (home == 1) 
    {
        int var_2 = 200;

        push(arg2, "arg2");
        push(arg1, "arg1");

        push(-1, "Return Address");
        push(-2, "func2 SFP");

        push(var_2, "var_2");

        SFP2 = FP;
    }

    int res;

    do
    {
        printf(" ������ �ұ�?? \n");
        printf("1 : pop     2 : push    3 : exit    4 : show stack \n");
        scanf(" %d", &res);


        if (res == 2)
        {
            printf("\npush�� �����ϼ̽��ϴ�.\n\n");
            func3(77);
        }

        else if (res == 1)
        {
            printf("\npop�� �����ϼ̽��ϴ�.\n\n");

            pop();
            pop();
            pop();
            pop();
            pop();

            FP = SFP1;
            home = 2;
            func1(0,0,0);
        }

        else if (res == 4)
        {
            print_stack();
        }

        else if (res == 3) printf("�����մϴ�");

    } while (res == 4);

    
}


void func3(int arg1)
{
    int var_3 = 300;
    int var_4 = 400;

    push(arg1, "arg1");

    push(-1, "Return Address");
    push(-2, "func3 SFP");

    push(var_3, "var_3");
    push(var_4, "var_4");

    int res;

    do
    {
        printf(" ������ �ұ�?? \n");
        printf("1 : pop     2 : push    3 : exit    4 : show stack \n");
        scanf(" %d", &res);


        if (res == 2)
        {
            printf("\npush�� �����ϼ̽��ϴ�.\n\n");
            printf("Stack is full !\n");

        }

        else if (res == 1)
        {
            printf("\npop�� �����ϼ̽��ϴ�.\n\n");

            pop();
            pop();
            pop();
            pop();
            pop();

            FP = SFP2;
            home = 2;
            func2(0, 0);
        }

        else if (res == 4)
        {
            print_stack();
        }

        else if (res == 3) printf("�����մϴ�");

    } while (res == 4 | res == 2);

   
}


//main �Լ��� ���õ� stack frame�� �������� �ʾƵ� �˴ϴ�.
int main()
{   
    int res;
    do {
        
        printf("������ �ұ�? \n");
        printf("1 : pop     2 : push    3 : exit    4 : show stack \n");
        scanf(" %d", &res);

        if (res == 2)
        {
            printf("\npush�� �����ϼ̽��ϴ�.\n\n");
            home = 1;
            func1(1, 2, 3);
        }

        else if (res == 1) 
        {
            printf("\npop�� �����ϼ̽��ϴ�.\n\n");

            printf("stack is empty!\n");
        }

        else if (res == 4)
        {
            print_stack();
        }

        else if (res == 3) printf("�����մϴ�");

    } while (res == 1 | res == 4);
    return 0;
}