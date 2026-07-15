/* func_ov107_020c9eac -- update the node's child widget then itself, ov107. */
extern void func_0203c7e8(void *child);
extern void func_0203d194(void *node);
void func_ov107_020c9eac(char *node) {
    func_0203c7e8(*(void **)(node + 0x3c));
    func_0203d194(node);
}
