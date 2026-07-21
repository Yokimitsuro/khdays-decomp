extern void func_0203c7ac(int child);
extern void func_0203c86c(void *child, int flag);
/* Refresh the node's child object (node+0x3c) and then re-select it. */
void func_ov107_020c9ec8(int node) {
    func_0203c7ac(*(int *)(node + 0x3c));
    func_0203c86c(*(void **)(node + 0x3c), 1);
}
