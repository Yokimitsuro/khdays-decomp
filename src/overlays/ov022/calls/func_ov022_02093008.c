/* Written as a ternary, not `a && b`: the && form makes mwcc branch over the second
 * test, while the ROM predicates it (moveq/movne). */
extern int func_ov022_02092ff0(unsigned char *arg0);
int func_ov022_02093008(unsigned char *arg0) {
    return func_ov022_02092ff0(arg0) == 0 ? 0 : *(int *)(arg0 + 0x958) == 0;
}
