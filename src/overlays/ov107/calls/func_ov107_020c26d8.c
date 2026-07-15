/* func_ov107_020c26d8 -- refresh a node and forward the event to its parent, ov107. */
extern void func_ov107_020c2cec(void *node);
extern void func_0203c86c(void *parent, int event);
void func_ov107_020c26d8(char *node, int event) {
    func_ov107_020c2cec(node);
    func_0203c86c(*(void **)(node + 0x104), event);
}
