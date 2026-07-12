/* Register the ov146 object factory (type 0x10) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov146_020cbf38(int);
int func_ov146_020cbf20(void) {
    return func_ov107_020c2f7c(0x10, (void *)&func_ov146_020cbf38);
}
