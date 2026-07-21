extern int *OS_IsThreadAvailable_0x020c9848(void);
extern void func_0203c650(int list, int node);
/* Unlink the node from the active owner's child list, if a node was given. */
void func_ov107_020cb100(int node) {
    if (node == 0) {
        return;
    }
    func_0203c650(*(int *)(*OS_IsThreadAvailable_0x020c9848() + 0x3c), node);
}
