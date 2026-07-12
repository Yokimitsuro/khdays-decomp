/* Register the ov206 object factory (type 0x29) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov206_020cbf38(int);
int func_ov206_020cbf20(void) {
    return func_ov107_020c2f7c(0x29, (void *)&func_ov206_020cbf38);
}
