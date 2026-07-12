/* Unless busy, cache the 020cab14 result at +0x420, mark state 4 and dispatch. */
extern int func_0203c634(int, int, void *);
extern int func_ov107_020cab14(int, int);
void func_ov260_020cdcb4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    int r = func_ov107_020cab14(*(int *)owner, 0);
    *(int *)(*(int *)owner + 0x420) = r;
    *(signed char *)(*(int *)owner + 0x1c7) = 4;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
