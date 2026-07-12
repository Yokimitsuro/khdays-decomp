extern int func_ov107_020cab14(int, int);
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c9ee8(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov255_020ce050(int);
void func_ov255_020cdfd8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int child = func_ov107_020cab14(*(int *)owner, 0);
    *(int *)(owner + 0x5c) = child;
    if (child == 0) {
        *(signed char *)(*(int *)owner + 0x1c7) = 2;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
    } else {
        func_ov107_020c9264(*(int *)owner, 7, 0);
        func_ov107_020c9ee8(*(int *)(*(int *)owner + 0x3a4), 6, 0);
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov255_020ce050);
    }
}
