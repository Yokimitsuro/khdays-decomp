/* Hide the two reaction icons (slots 2 and 0, state 2) and register the recover callback, unless
 * the animation is still on the hit frame (*node+0x1c6 == 9). */
extern void func_0203b9fc(int obj, int slot, int a, int b);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov255_020d16f0(void);

void func_ov255_020d1690(int param_1) {
    int *node = *(int **)(param_1 + 4);
    if (*(signed char *)(*node + 0x1c6) == 9) {
        return;
    }
    func_0203b9fc(node[1], 2, 2, 0);
    func_0203b9fc(node[1], 0, 2, 0);
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov255_020d16f0);
}
