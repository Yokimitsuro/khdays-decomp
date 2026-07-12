/* Register the ov233 object factory (type 0x3c) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov233_020cbf38(int);
int func_ov233_020cbf20(void) {
    return func_ov107_020c2f7c(0x3c, (void *)&func_ov233_020cbf38);
}
