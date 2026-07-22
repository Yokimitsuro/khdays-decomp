/* func_ov245_020d5ab8 -- stop the current action (mode 0), record the caller's value at +0x10 and
 * put the owner in state 1. */
extern void func_ov107_020c73a0(int owner, int a);

void func_ov245_020d5ab8(int *node, int v) {
    func_ov107_020c73a0(node[0], 0);
    node[4] = v;
    *(unsigned char *)(node[0] + 0x1c7) = 1;
}
