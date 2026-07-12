/* Set the timer (+0x68=0x400) and clear +0x38 on the child, then dispatch to the handler. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov186_020d15d0(int);
void func_ov186_020d15a4(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x68) = 0x400;
    *(int *)(child + 0x38) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov186_020d15d0);
}
