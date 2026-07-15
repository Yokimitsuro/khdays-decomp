/* func_ov245_020cce08 -- set node mode 3 and re-run its layout, ov245 (tail-call to func_ov107_020c9264
 * with the freshly-set mode byte @+0x4d8). */
extern int func_ov107_020c9264(void *node, int mode, int);
int func_ov245_020cce08(char *node) {
    *(signed char *)(node + 0x4d8) = 3;
    return func_ov107_020c9264(node, *(signed char *)(node + 0x4d8), 0);
}
