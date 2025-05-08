/*  call_stack

    실제 시스템에서는 스택이 메모리에 저장되지만, 본 과제에서는 `int` 배열을 이용하여 메모리를 구현합니다.
    원래는 SFP와 Return Address에 실제 가상 메모리 주소가 들어가겠지만, 이번 과제에서는 -1로 대체합니다.

    int call_stack[]      : 실제 데이터(`int 값`) 또는 `-1` (메타데이터 구분용)을 저장하는 int 배열
    char stack_info[][]   : call_stack[]과 같은 위치(index)에 대한 설명을 저장하는 문자열 배열

    ==========================call_stack 저장 규칙==========================
    매개 변수 / 지역 변수를 push할 경우   : int 값 그대로
    Saved Frame Pointer 를 push할 경우  : call_stack에서의 index
    반환 주소값을 push할 경우       : -1
    =======================================================================


    ==========================stack_info 저장 규칙==========================
    매개 변수 / 지역 변수를 push할 경우        : 변수에 대한 설명
    Saved Frame Pointer 를 push할 경우  : 어떤 함수의 SFP인지
    반환 주소값을 push할 경우                 : "Return Address"
    ========================================================================
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define STACK_SIZE 50 // 최대 스택 크기

int     call_stack[STACK_SIZE];         // Call Stack을 저장하는 배열
char    stack_info[STACK_SIZE][20];     // Call Stack 요소에 대한 설명을 저장하는 배열

/*  SP (Stack Pointer), FP (Frame Pointer)

    SP는 현재 스택의 최상단 인덱스를 가리킵니다.
    스택이 비어있을 때 SP = -1, 하나가 쌓이면 `call_stack[0]` -> SP = 0, `call_stack[1]` -> SP = 1, ...

    FP는 현재 함수의 스택 프레임 포인터입니다.
    실행 중인 함수 스택 프레임의 sfp를 가리킵니다.
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
    현재 call_stack 전체를 출력합니다.
    해당 함수의 출력 결과들을 바탕으로 구현 완성도를 평가할 예정입니다.
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


//func 내부는 자유롭게 추가해도 괜찮으나, 아래의 구조를 바꾸지는 마세요
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
        printf(" 무엇을 할까?? \n");
        printf("1 : pop     2 : push    3 : exit    4 : show stack \n");
        scanf(" %d", &res);


        if (res == 2)
        {
            printf("\npush를 선택하셨습니다.\n\n");
            home = 1;
            func2(11, 13);
        }

        else if (res == 1) 
        {
            printf("\npop을 선택하셨습니다.\n\n");

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

        else if (res == 3) printf("종료합니다");
    
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
        printf(" 무엇을 할까?? \n");
        printf("1 : pop     2 : push    3 : exit    4 : show stack \n");
        scanf(" %d", &res);


        if (res == 2)
        {
            printf("\npush를 선택하셨습니다.\n\n");
            func3(77);
        }

        else if (res == 1)
        {
            printf("\npop을 선택하셨습니다.\n\n");

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

        else if (res == 3) printf("종료합니다");

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
        printf(" 무엇을 할까?? \n");
        printf("1 : pop     2 : push    3 : exit    4 : show stack \n");
        scanf(" %d", &res);


        if (res == 2)
        {
            printf("\npush를 선택하셨습니다.\n\n");
            printf("Stack is full !\n");

        }

        else if (res == 1)
        {
            printf("\npop을 선택하셨습니다.\n\n");

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

        else if (res == 3) printf("종료합니다");

    } while (res == 4 | res == 2);

   
}


//main 함수에 관련된 stack frame은 구현하지 않아도 됩니다.
int main()
{   
    int res;
    do {
        
        printf("무엇을 할까? \n");
        printf("1 : pop     2 : push    3 : exit    4 : show stack \n");
        scanf(" %d", &res);

        if (res == 2)
        {
            printf("\npush를 선택하셨습니다.\n\n");
            home = 1;
            func1(1, 2, 3);
        }

        else if (res == 1) 
        {
            printf("\npop을 선택하셨습니다.\n\n");

            printf("stack is empty!\n");
        }

        else if (res == 4)
        {
            print_stack();
        }

        else if (res == 3) printf("종료합니다");

    } while (res == 1 | res == 4);
    return 0;
}
