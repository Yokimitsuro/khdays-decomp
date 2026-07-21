/* Face the target on entry: clear the pause flag (+0xac), and if a target is set (node[3]) compute
 * the heading to it (atan2 of the flattened owner->target vector) into node[0x1f]/[0x1e]; then
 * register the think callback. */
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_020050b4(int x, int z);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov259_020ceff4(void);

void func_ov259_020cef8c(int param_1) {
    int *node = *(int **)(param_1 + 4);
    int aim[3];
    *(char *)((char *)node + 0xac) = 0;
    if (node[3] != 0) {
        int heading;
        VEC_Subtract((void *)(node[3] + 0x190), (void *)(*node + 0xb0), aim);
        heading = func_020050b4(aim[0], aim[2]);
        node[0x1f] = heading;
        node[0x1e] = heading;
    }
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov259_020ceff4);
}
