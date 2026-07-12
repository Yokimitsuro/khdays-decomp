/* Register the ov253 object factory (type 0x4d) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov253_020cbf38(int);
int func_ov253_020cbf20(void) {
    return func_ov107_020c2f7c(0x4d, (void *)&func_ov253_020cbf38);
}
