/* Run 020ce370; unless the child is busy, clear +0xa0, mark state 0xd and dispatch. */
extern int func_0203c634(int, int, void *);
extern int func_ov252_020ce370(int);
void func_ov252_020d19b8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov252_020ce370(param_1);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(int *)(owner + 0xa0) = 0;
    *(signed char *)(*(int *)owner + 0x1c7) = 0xd;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
