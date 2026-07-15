/* func_ov107_020c2a6c -- request node action bit 4 when idle, ov107. Forwards to
 * func_ov107_020c28f0(node, 4) only if the busy flag (arg1) is clear. */
extern void func_ov107_020c28f0(void *node, int action);
void func_ov107_020c2a6c(void *node, int busy) {
    if (busy == 0) {
        func_ov107_020c28f0(node, 4);
    }
}
