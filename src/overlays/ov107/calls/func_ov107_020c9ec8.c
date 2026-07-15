/* func_ov107_020c9ec8 -- refresh the node's child widget then re-select it, ov107. */
extern void func_0203c7ac(void *child);
extern void func_0203c86c(void *child, int sel);
void func_ov107_020c9ec8(char *node) {
    func_0203c7ac(*(void **)(node + 0x3c));
    func_0203c86c(*(void **)(node + 0x3c), 1);
}
