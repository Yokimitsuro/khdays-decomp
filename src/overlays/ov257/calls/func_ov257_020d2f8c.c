/* Show the two "reaction ready" subitem icons (slots 2 and 0) and register the reaction think
 * callback, while the target lock (node[1]+0xad) is clear. */
extern void func_0203b9fc(int obj, int slot, int a, int b);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov257_020d2fe4(void);

void func_ov257_020d2f8c(int param_1) {
    int *node = *(int **)(param_1 + 4);
    if (*(unsigned char *)(node[1] + 0xad) != 0) {
        return;
    }
    func_0203b9fc(node[1], 2, 1, 1);
    func_0203b9fc(node[1], 0, 1, 1);
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov257_020d2fe4);
}
