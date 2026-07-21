/* Dispatches an event to the handler registered for this node's type (*node), if any. */

extern int func_ov107_020c9b68(unsigned int type);
extern void func_ov107_020c0d2c(int handler, int node, int arg);

void func_ov107_020c9b3c(unsigned short *node, int arg) {
    int handler = func_ov107_020c9b68(*node);
    if (handler == 0) {
        return;
    }
    func_ov107_020c0d2c(handler, (int)node, arg);
}
