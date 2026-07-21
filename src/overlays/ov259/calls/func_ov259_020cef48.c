/* Enter the flinch state, but only while the target lock (node[1]+0xad) is clear: advance the RNG
 * once (to desync), set the reaction state to 2, and re-register the think callback. */
extern int func_02023eb4();
extern void func_0203c634(int self, int idx, int cb);

void func_ov259_020cef48(int param_1) {
    int *node = *(int **)(param_1 + 4);
    if (*(unsigned char *)(node[1] + 0xad) != 0) {
        return;
    }
    func_02023eb4(0x65);
    *(char *)(*node + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), 0);
}
