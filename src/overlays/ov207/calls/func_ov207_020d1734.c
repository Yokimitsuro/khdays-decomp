/* Spawn the child via 020cab14; once present clear its gate byte and dispatch via c634. */
extern int func_0203c634(int, int, void *);
extern int func_ov107_020cab14(int, int);
extern int func_ov207_020d1780(int);
void func_ov207_020d1734(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int child = func_ov107_020cab14(*(int *)owner, 0);
    *(int *)(owner + 0x10) = child;
    if (child == 0) return;
    *(signed char *)(*(int *)(*(int *)owner + 0x384) + 0xa8) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov207_020d1780);
}
