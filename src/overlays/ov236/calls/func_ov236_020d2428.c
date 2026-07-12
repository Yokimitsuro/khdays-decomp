/* Spawn the child via 020cab14; if it appears mark state 0xa and dispatch via c634. */
extern int func_0203c634(int, int, void *);
extern int func_ov107_020cab14(int, int);
void func_ov236_020d2428(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int child = func_ov107_020cab14(*(int *)owner, 0);
    *(int *)(owner + 4) = child;
    if (child == 0) return;
    *(signed char *)(*(int *)owner + 0x1c7) = 0xa;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
