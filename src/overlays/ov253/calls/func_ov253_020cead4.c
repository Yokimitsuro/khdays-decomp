/* func_ov253_020cead4 -- forward a 16-bit value to the node's owner, ov253 (tail-call to
 * func_0203b9fc over the owner @+0x38c, passing (short)val and flags). */
extern int func_0203b9fc(void *owner, int, int val, int flags);
int func_ov253_020cead4(char *node, int val, int flags) {
    return func_0203b9fc(*(void **)(node + 0x38c), 0, (short)val, flags);
}
