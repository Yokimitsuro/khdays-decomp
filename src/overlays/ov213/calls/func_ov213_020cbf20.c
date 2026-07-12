/* Register the ov213 object factory (type 0x2d) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov213_020cbf38(int);
int func_ov213_020cbf20(void) {
    return func_ov107_020c2f7c(0x2d, (void *)&func_ov213_020cbf38);
}
