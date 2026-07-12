/* Clear +4/+8; dispatch to one of two handlers depending on whether +0xc is set. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov272_020d3478(int);
extern void func_ov272_020d34f0(int);
void func_ov272_020d3430(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 4) = 0;
    *(int *)(child + 8) = 0;
    if (*(int *)(child + 0xc) == 0)
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov272_020d3478);
    else
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov272_020d34f0);
}
