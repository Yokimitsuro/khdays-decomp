/* Written as a ternary, not `a && b`: the && form makes mwcc branch over the second
 * test, while the ROM predicates it (moveq/movne). */
extern int func_ov022_0209405c(unsigned char *arg0);
int func_ov022_02094174(unsigned char *arg0) {
    return func_ov022_0209405c(arg0) == 0 ? 0 : *(int *)(arg0 + 0x110) > 0;
}
