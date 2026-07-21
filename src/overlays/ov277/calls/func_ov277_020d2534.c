/* Start a sidestep: cancel the current action (mode 1) and roll a random sidestep direction
 * (-1 or +1) into the facing byte at +0x48, then register the sidestep think callback. */
extern void func_ov107_020c9264(int owner, int mode, int b);
extern int func_02023eb4();
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov277_020d2580(void);

void func_ov277_020d2534(int param_1) {
    int v;
    int *node = *(int **)(param_1 + 4);
    func_ov107_020c9264(*node, 1, 1);
    *(char *)((char *)node + 0x48) = func_02023eb4(2) + (v - v) != 0 ? -1 : 1;
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov277_020d2580);
}
