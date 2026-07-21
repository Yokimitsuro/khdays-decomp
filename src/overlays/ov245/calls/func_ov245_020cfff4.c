/* Start a hover/wait: cancel the current action (mode 1) and seed a randomised wait timer
 * (0x1000 + d0x4001) into node[0xc], then register the wait think callback. */
extern void func_ov107_020c9264(int owner, int mode, int b);
extern int func_02023eb4();
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov245_020d003c(void);

void func_ov245_020cfff4(int param_1) {
    int *node = *(int **)(param_1 + 4);
    func_ov107_020c9264(*node, 1, 1);
    node[0xc] = func_02023eb4(0x4001) + 0x1000;
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov245_020d003c);
}
