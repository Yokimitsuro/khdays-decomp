/* Register the ov212 object factory (type 0x2c) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov212_020cbf38(int);
int func_ov212_020cbf20(void) {
    return func_ov107_020c2f7c(0x2c, (void *)&func_ov212_020cbf38);
}
