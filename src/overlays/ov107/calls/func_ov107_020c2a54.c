/* func_ov107_020c2a54 -- request node action bit 2 when idle, ov107. Forwards to
 * func_ov107_020c28f0(node, 2) only if the busy flag (arg1) is clear. */
extern void func_ov107_020c28f0(void *node, int action);
void func_ov107_020c2a54(void *node, int busy) {
    if (busy == 0) {
        func_ov107_020c28f0(node, 2);
    }
}
