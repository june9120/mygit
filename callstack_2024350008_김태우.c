#include <stdio.h>
#include <string.h>

#define STACK_SIZE 50

int call_stack[STACK_SIZE];
char stack_info[STACK_SIZE][50];

int SP = -1;
int FP = -1;

void func1(int arg1, int arg2, int arg3);
void func2(int arg1, int arg2);
void func3(int arg1);

void push(int value, const char* desc) {
    SP++;
    call_stack[SP] = value;
    snprintf(stack_info[SP], 50, "%s", desc);
}

void pop() {
    SP--;
}

void print_stack() {
    if (SP == -1) {
        printf("Stack is empty.\n");
        return;
    }

    printf("====== Current Call Stack ======\n");
    for (int i = SP; i >= 0; i--) {
        if (call_stack[i] != -1)
            printf("%d : %s = %d", i, stack_info[i], call_stack[i]);
        else
            printf("%d : %s", i, stack_info[i]);

        if (i == SP)
            printf("    <=== esp\n");
        else if (i == FP)
            printf("    <=== ebp\n");
        else
            printf("\n");
    }
    printf("================================\n\n");
}

void func1(int arg1, int arg2, int arg3) {
    int var_1 = 100;

    push(arg3, "arg3");
    push(arg2, "arg2");
    push(arg1, "arg1");
    push(-1, "Return Address");

    int saved_fp = FP;
    char sfp_label[50];
    snprintf(sfp_label, sizeof(sfp_label), "func1 SFP = %d", saved_fp);
    push(saved_fp, sfp_label);
    FP = SP;

    push(var_1, "var_1");

    print_stack();
    func2(11, 13);

    // 에필로그
    while (SP > FP) pop();   // 지역 변수 제거
    FP = call_stack[FP];     // SFP 복구
    pop();                   // SFP
    pop();                   // Return Address
    pop();                   // arg1
    pop();                   // arg2
    pop();                   // arg3
}

void func2(int arg1, int arg2) {
    int var_2 = 200;

    push(arg2, "arg2");
    push(arg1, "arg1");
    push(-1, "Return Address");

    int saved_fp = FP;
    char sfp_label[50];
    snprintf(sfp_label, sizeof(sfp_label), "func2 SFP = %d", saved_fp);
    push(saved_fp, sfp_label);
    FP = SP;

    push(var_2, "var_2");

    print_stack();
    func3(77);

    while (SP > FP) pop();   // 지역 변수 제거
    FP = call_stack[FP];     // SFP 복구
    pop();                   // SFP
    pop();                   // Return Address
    pop();                   // arg1
    pop();                   // arg2
}

void func3(int arg1) {
    int var_3 = 300;
    int var_4 = 400;

    push(arg1, "arg1");
    push(-1, "Return Address");

    int saved_fp = FP;
    char sfp_label[50];
    snprintf(sfp_label, sizeof(sfp_label), "func3 SFP = %d", saved_fp);
    push(saved_fp, sfp_label);
    FP = SP;

    push(var_3, "var_3");
    push(var_4, "var_4");

    print_stack();

    while (SP > FP) pop();   // 지역 변수 제거
    FP = call_stack[FP];     // SFP 복구
    pop();                   // SFP
    pop();                   // Return Address
    pop();                   // arg1
}

int main() {
    func1(1, 2, 3);
    print_stack();
    return 0;
}
