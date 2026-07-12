/* Register the ov257 object factory (type 0x51) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov257_020cbf38(int);
int func_ov257_020cbf20(void) {
    return func_ov107_020c2f7c(0x51, (void *)&func_ov257_020cbf38);
}
